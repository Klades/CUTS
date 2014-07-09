// $Id$

#include "Dataset_Repo.h"

#if !defined (__CUTS_INLINE__)
#include "Dataset_Repo.inl"
#endif

#include "Log_Format.h"
#include "Log_Format_Data_Entry.h"
#include "Graph_Worker.h"
#include "Relation.h"
#include "Variable.h"
#include "adbc/SQLite/Connection.h"
#include "cuts/utils/testing/Test_Database.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/CORBA_macros.h"
#include "boost/bind.hpp"
#include "boost/graph/topological_sort.hpp"
#include <sstream>

/**
 * @class process_log_format
 *
 * Functor for processing a log format.
 */
class process_log_format
{
public:
  process_log_format (CUTS_Dataflow_Graph & graph,
                      CUTS_Log_Format_Data_Entry & entry,
                      ADBC::SQLite::Record & record,
                      CUTS_Dataset_Repo & repo)
    : graph_ (graph),
      entry_ (entry),
      record_ (record),
      repo_ (repo)
  {

  }

  void operator () (CUTS_Dataflow_Graph::vertex_descriptor vertex) const
  {
    // Get the log format from the vertex.
    CUTS_Log_Format * format = this->graph_.get_log_format (vertex);

    bool is_relations = false;
    std::vector <size_t> qualified_rels;

    if (format->relations ().empty ())
      is_relations = false;

    // Relations may not be empty, in that situation also we have
    // to check whether they are qualified for this subgraph

    else
    {
      size_t relation_count = format->relations ().size ();

      for (size_t i = 0; i < relation_count; i++)
      {
        if (this->repo_.qualified_relation (format->relations ()[i], this->graph_))
        {
          is_relations = true;
          qualified_rels.push_back (i);
        }
      }
    }

    if (!is_relations)
    {
      // Process this log format.
      this->entry_.prepare (this->repo_.table_name (), format);
      this->process_entry ();
    }
    else
    {
       // Iterate over each of the relations.
      size_t qual_relation_count = qualified_rels.size ();

      for (size_t j = 0; j < qual_relation_count; ++ j)
      {
        this->entry_.prepare (this->repo_.table_name (), format, qualified_rels [j]);
        this->process_entry ();
      }
    }
  }

private:
  void process_entry (void) const
  {
    char message[1024];

    // Reset the private variables in the adapter
    if(graph_.adapter ())
    {
      graph_.adapter ()->reset ();
    }

    for ( ; !this->record_.done (); this->record_.advance ())
    {
      // Get the message from the row.
      this->record_.get_data (5, message, sizeof (message));

      // Execute the entry against this message. It may or may not update
      // the database. It depends on if the message matches the current
      // log format.

      this->entry_.execute(message, graph_.adapter ());

    }

    this->record_.reset ();
  }

  CUTS_Dataflow_Graph & graph_;

  CUTS_Log_Format_Data_Entry & entry_;

  ADBC::SQLite::Record & record_;

  CUTS_Dataset_Repo & repo_;
};

//
// CUTS_Dataset_Repo
//
CUTS_Dataset_Repo::CUTS_Dataset_Repo (void)
: data_ (0),
  vtable_ (0),
  graph_worker_ (0)
{
  ACE_NEW_THROW_EX (this->vtable_,
                    ADBC::SQLite::Connection (),
                    ACE_bad_alloc ());
}

//
// ~CUTS_Dataset_Repo
//
CUTS_Dataset_Repo::~CUTS_Dataset_Repo (void)
{
  if (0 != this->vtable_)
    delete this->vtable_;
}

//
// open
//
bool CUTS_Dataset_Repo::
open (const ACE_CString & location, CUTS_Test_Database & data)
{
  // First, make sure the database was previously closed.
  if (this->data_ != 0)
    this->close ();

  if (location == ACE_TEXT (":memory:"))
  {
    // We are performing all operations in-memory.
    this->vtable_->connect (ACE_TEXT (":memory:"));
  }
  else
  {
    // Extract the profile from the database.
    CUTS_Test_Profile profile;

    if (data.get_test_profile (profile) != 0)
      return false;

    // Construct the location of the variable table.
    std::ostringstream ostr;
    ostr << location
         << "/"
         << profile.uuid_.to_string ()->c_str ()
         << ".vtable";

    std::cout << ostr.str () << std::endl;

    this->vtable_->connect (ostr.str ().c_str ());
    this->repo_name_ = ostr.str ().c_str ();
  }

  // Store the test database for later usage.
  if (this->vtable_->is_connected ())
    this->data_ = &data;

  return this->vtable_->is_connected ();
}

//
// open
//
bool CUTS_Dataset_Repo::
open (const ACE_CString & location, CUTS_Test_Database & data, int graph_worker_id)
{
  // First, make sure the database was previously closed.
  if (this->data_ != 0)
    this->close ();

  if (location == ACE_TEXT (":memory:"))
  {
    // We are performing all operations in-memory.
    this->repo_name_ = ":memory:";
    this->vtable_->connect (ACE_TEXT (":memory:"));
  }
  else
  {
    // Extract the profile from the database.
    CUTS_Test_Profile profile;

    if (data.get_test_profile (profile) != 0)
      return false;

    // Construct the location of the variable table.
    std::ostringstream ostr;
    ostr << location
         << "/"
         << profile.uuid_.to_string ()->c_str ()
         << "_"
         << graph_worker_id
         << ".vtable";

    this->repo_name_ = ostr.str ().c_str ();
    this->vtable_->connect (ostr.str ().c_str ());
  }

  // Store the test database for later usage.
  if (this->vtable_->is_connected ())
    this->data_ = &data;

  return this->vtable_->is_connected ();
}

//
// close
//
void CUTS_Dataset_Repo::close (void)
{
  if (this->vtable_->is_connected ())
    this->vtable_->disconnect ();

  if (0 != this->data_)
    this->data_ = 0;
}

//
// evaluate
//
bool CUTS_Dataset_Repo::insert (CUTS_Dataflow_Graph & graph,
                                vertex_list & sorted_list)
{
  try
  {
    // Create an empty table for the data set.
    this->create_vtable (graph, sorted_list);

    // Create all the indices for the dataset.
    this->create_vtable_indices (graph, sorted_list);

    // First, select all the log message from the database.
    ADBC::SQLite::Query * query = this->data_->create_query ();
    CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (query, &ADBC::SQLite::Query::destroy);
    ADBC::SQLite::Record & record = query->execute ("SELECT * FROM cuts_logging ORDER BY lid");

    // Next, iterate over all the log formats. This will enable
    // us to construct the dataset using the provided data.
    CUTS_Log_Format_Data_Entry entry (*this->vtable_);

    std::for_each (sorted_list.begin (),
                   sorted_list.end (),
                   process_log_format (graph, entry, record, *this));

    // Finally, prune the incomplete rows from the table.
    this->prune_incomplete_rows (graph, sorted_list);

    // If there is an open adapter close it.
    if(graph.adapter ())
    {
      graph.adapter ()->close ();
    }

    return true;
  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s (%N:%l)\n"),
                ex.message ().c_str ()));
  }

  return false;
}

//
// create_data_table
//
void CUTS_Dataset_Repo::
create_vtable (CUTS_Dataflow_Graph & graph, vertex_list & sorted_list)
{
  vertex_list::iterator iter = sorted_list.begin ();
  vertex_list::iterator iter_end = sorted_list.end ();

  // Create a new query on the variable table database.
  ADBC::SQLite::Query * query = this->vtable_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_clean (query, &ADBC::SQLite::Query::destroy);

  std::ostringstream name_str;

  name_str << graph.name ().c_str ()
           << "_"
           << this->graph_worker_->leaf_id_;

  this->table_name_ = name_str.str ().c_str ();

  // Delete the variable table for the unit test.
  ACE_CString sqlstmt = "DROP TABLE IF EXISTS " + this->table_name_;
  query->execute_no_record (sqlstmt.c_str ());

  // Begin the SQL statement for creating the table.
  bool first_entry = true;
  const CUTS_Log_Format * format = 0;

  std::ostringstream sqlstr;
  sqlstr << "CREATE TABLE IF NOT EXISTS " << this->table_name_ << " (";

  for ( ; iter != iter_end; ++ iter)
  {
    // Iterate over the variables in the log format. We need to
    // make sure we include columns for them in the data set.
    format = graph.get_log_format (*iter);
    CUTS_Log_Format_Variable_Table::CONST_ITERATOR var_iter (format->variables ());

    for ( ; !var_iter.done (); ++ var_iter)
    {
      // Make sure we insert a comma between column declarations.
      if (!first_entry)
        sqlstr << ", ";
      else
        first_entry = false;

      // Write the fully qualified name for the column.
      sqlstr << format->name ().c_str ()
             << "_"
             << var_iter->key ().c_str ()
             << " ";

      // Write the variable's type to the SQL string.
      switch (var_iter->item ()->type ())
      {
      case CUTS_Log_Format_Variable::VT_STRING:
        sqlstr << "TEXT";
        break;

      case CUTS_Log_Format_Variable::VT_INTEGER:
        sqlstr << "INTEGER";
        break;

      case CUTS_Log_Format_Variable::VT_DOUBLE:
        sqlstr << "REAL";
        break;

      case CUTS_Log_Format_Variable::VT_DATETIME:
        sqlstr << "DATETIME";
        break;

      case CUTS_Log_Format_Variable::VT_REGEX:
        sqlstr << "TEXT";
        break;

      default:
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - %s has an unknown variable type\n",
                    var_iter->key ().c_str ()));
      }
    }
  }

  // End the SQL statement.
  sqlstr << ")";

  // Execute the SQL statement.
  query->execute_no_record (sqlstr.str ().c_str ());
}

//
// create_indices
//
void CUTS_Dataset_Repo::
create_vtable_indices (CUTS_Dataflow_Graph & graph,
                       vertex_list & sorted_list)
{
  vertex_list::iterator iter = sorted_list.begin ();
  vertex_list::iterator iter_end = sorted_list.end ();

  // CUTS_Dataflow_Graph::vertex_iterator iter, iter_end;
  // boost::tie (iter, iter_end) = boost::vertices (graph.graph ());

  const CUTS_Log_Format * format = 0;

  for ( ; iter != iter_end; ++ iter)
  {
    // Get the log format from the vertex.
    format = graph.get_log_format (*iter);

    if (!format->relations ().empty ())
      this->create_vtable_indices (graph, *format);
  }
}

//
// create_indices
//
void CUTS_Dataset_Repo::
create_vtable_indices (CUTS_Dataflow_Graph & test,
                       const CUTS_Log_Format & format)
{
  // Allocate a new database query.
  ADBC::SQLite::Query * query = this->vtable_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_clean (query, &ADBC::SQLite::Query::destroy);

  // Iterate over all the relations
  CUTS_Log_Format::relations_type::const_iterator
    iter = format.relations ().begin (),
    iter_end = format.relations ().end ();

  size_t index = 0;
  std::string column_name;

  std::string tablename = this->table_name_.c_str ();
  std::replace (tablename.begin (), tablename.end (), ' ', '_');

  for ( ; iter != iter_end; ++ iter)
  {
    if (!(this->qualified_relation (*iter, test)))
      continue;

    std::ostringstream ostr;
    ostr << "CREATE INDEX IF NOT EXISTS "
         << format.name ().c_str ()
         << "r" << index << "_"
         << tablename << " ON " << tablename << " (";

    CUTS_Log_Format_Relation::causality_type::const_iterator
      reliter = iter->causality ().begin (),
      reliter_end = iter->causality ().end ();

    if (reliter != reliter_end)
    {
      // Write the first value of the index, which is an effect.
      ostr << iter->effect ()->name ().c_str ()
           << '_' << reliter->effect ().c_str ();

      for (++ reliter ; reliter != reliter_end; ++ reliter)
      {
        // Write the value of the index, which is an effect.
        ostr << ", "
             << iter->effect ()->name ().c_str ()
             << '_' << reliter->effect ().c_str ();
      }
    }

    ostr << ")";

    // Create the index on the table.
    query->execute_no_record (ostr.str ().c_str ());
  }
}

//
// prune_incomplete_rows
//
void CUTS_Dataset_Repo::
prune_incomplete_rows (CUTS_Dataflow_Graph & graph,
                       vertex_list & sorted_list)
{
  vertex_list::iterator iter = sorted_list.begin ();
  vertex_list::iterator iter_end = sorted_list.end ();

  // Create a new query on the variable table database.
  ADBC::SQLite::Query * query = this->vtable_->create_query ();
  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_clean (query, &ADBC::SQLite::Query::destroy);

  // Begin the SQL statement for creating the table.
  bool first_entry = true;
  const CUTS_Log_Format * format = 0;

  std::ostringstream sqlstr;
  sqlstr << "DELETE FROM " << this->table_name_.c_str () << " WHERE ";

  for ( ; iter != iter_end; ++ iter)
    {
      // Iterate over the variables in the log format. We need to
      // make sure we include columns for them in the data set.
      format = graph.get_log_format (*iter);
      CUTS_Log_Format_Variable_Table::CONST_ITERATOR var_iter (format->variables ());

      for ( ; !var_iter.done (); ++ var_iter)
        {
          // Make sure we insert a comma between column declarations.
          if (!first_entry)
            sqlstr << " OR ";
          else
            first_entry = false;

          // Write the fully qualified name for the column.
          sqlstr << format->name ().c_str ()
                 << "_"
                 << var_iter->key ().c_str ()
                 << " IS NULL";
        }
    }

  // Execute the query to delete the incomplete rows.
  query->execute_no_record (sqlstr.str ().c_str ());
}

//
// create_query
//
ADBC::SQLite::Query * CUTS_Dataset_Repo::create_query (void)
{
  return this->vtable_->create_query ();
}

//
// graph_worker
//
void CUTS_Dataset_Repo::graph_worker (CUTS_Graph_Worker * worker)
{
  this->graph_worker_ = worker;
}

//
// table_name
//
const ACE_CString & CUTS_Dataset_Repo::table_name (void) const
{
  return this->table_name_;
}

//
// repo_name
//
const ACE_CString & CUTS_Dataset_Repo::repo_name (void) const
{
  return this->repo_name_;
}

//
// qualified_relation
//
bool CUTS_Dataset_Repo::qualified_relation (const CUTS_Log_Format_Relation & relation,
                                             CUTS_Dataflow_Graph & graph)
{
  // Checks whether both the nodes of the relation in the sub graph nodes

  CUTS_Dataflow_Graph::vertex_descriptor v = graph.find_vertex (relation.effect ()->name ());

  int worker_id = this->graph_worker_->leaf_id_;

  if ((this->graph_worker_->vertex_data_ [v].at (worker_id)) ==
    CUTS_Dataflow_Graph_Analyzer::Visited)
    return true;
  else
    return false;

  // Check whether it is in the subgraph
}

//
// attach_database
//
void CUTS_Dataset_Repo::attach_database (const char * file_name,
                                         const char * sqlite_db_name)
{
  ADBC::SQLite::Query * query = this->vtable_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_clean (query, &ADBC::SQLite::Query::destroy);

  std::ostringstream sqlstr;

  sqlstr << "ATTACH DATABASE '"
         << file_name
         << "' AS '"
         << sqlite_db_name
         << "'";

  std::cout << sqlstr.str ().c_str () << std::endl;

  query->execute_no_record (sqlstr.str ().c_str ());

}

//
// test_repo
//
void CUTS_Dataset_Repo::test_repo (void)
{
  ADBC::SQLite::Query * query = this->vtable_->create_query ();

  std::ostringstream sqlstr;

  sqlstr << "SELECT COUNT(*) AS result FROM "
         << this->table_name_.c_str ();

  ADBC::SQLite::Record * record = &query->execute (sqlstr.str ().c_str ());

  long count;
  record->get_data (0, count);

  std::cout << count << std::endl;


  record->reset ();
}

//
// join
//
void CUTS_Dataset_Repo::join (std::vector <CUTS_Graph_Worker *> & workers,
                              CUTS_Dataflow_Graph & graph)
{
  this->table_name_ = graph.name ().c_str ();

  ADBC::SQLite::Query * query = this->vtable_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_clean (query, &ADBC::SQLite::Query::destroy);

  // Delete the variable table for the unit test.
  ACE_CString sqlstmt = "DROP TABLE IF EXISTS " + this->table_name_;
  query->execute_no_record (sqlstmt.c_str ());

  // Do a natuaral join of the tables
  std::ostringstream sqlstr;
  sqlstr << "CREATE TABLE IF NOT EXISTS " << this->table_name_ << " AS "
         << "SELECT * FROM ";

  size_t i;

  size_t size = workers.size ();

  for (i=0; i < size-1; i++)
  {
    sqlstr << "aux_"
           << workers [i]->leaf_id ()
           << "."
           << workers [i]->repo ().table_name ().c_str ()
           << " NATURAL JOIN ";
  }

  sqlstr   << "aux_"
           << workers [i]->leaf_id ()
           << "."
           << workers [i]->repo ().table_name ().c_str ();

  query->execute_no_record (sqlstr.str ().c_str ());

}