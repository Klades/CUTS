// $Id$

#include "Dataset_Repo.h"

#if !defined (__CUTS_INLINE__)
#include "Dataset_Repo.inl"
#endif

#include "Dataflow_Graph.h"
#include "Log_Format.h"
#include "Log_Format_Data_Entry.h"
#include "Relation.h"
#include "Variable.h"
#include "cuts/utils/db/SQLite/Connection.h"
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
  process_log_format (const CUTS_Dataflow_Graph & graph,
                      CUTS_Log_Format_Data_Entry & entry,
                      CUTS_DB_SQLite_Record & record)
    : graph_ (graph),
      entry_ (entry),
      record_ (record)
  {

  }

  void operator () (CUTS_Dataflow_Graph::vertex_descriptor vertex) const
  {
    // Get the log format from the vertex.
    CUTS_Log_Format * format = this->graph_.get_log_format (vertex);

    if (format->relations ().empty ())
    {
      // Process this log format.
      this->entry_.prepare (this->graph_.name (), format);
      this->process_entry ();
    }
    else
    {
      // Iterate over each of the relations.
      size_t relation_count = format->relations ().size ();

      for (size_t i = 0; i < relation_count; ++ i)
      {
        this->entry_.prepare (this->graph_.name (), format, i);
        this->process_entry ();
      }
    }
  }

private:
  void process_entry (void) const
  {
    char message[1024];

    for ( ; !this->record_.done (); this->record_.advance ())
    {
      // Get the message from the row.
      this->record_.get_data (4, message, sizeof (message));

      // Execute the entry against this message. It may or may not update
      // the database. It depends on if the message matches the current
      // log format.
      this->entry_.execute (message);
    }

    this->record_.reset ();
  }

  const CUTS_Dataflow_Graph & graph_;

  mutable CUTS_Log_Format_Data_Entry & entry_;

  mutable CUTS_DB_SQLite_Record & record_;
};

//
// CUTS_Dataset_Repo
//
CUTS_Dataset_Repo::CUTS_Dataset_Repo (void)
: data_ (0),
  vtable_ (0)
{
  ACE_NEW_THROW_EX (this->vtable_,
                    CUTS_DB_SQLite_Connection (),
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
bool CUTS_Dataset_Repo::insert (const CUTS_Dataflow_Graph & graph)
{
  try
  {
    // Create an empty table for the data set.
    this->create_vtable (graph);

    // Create all the indices for the dataset.
    this->create_vtable_indices (graph);

    // Get the order for processing the log formats.
    std::vector <CUTS_Dataflow_Graph::vertex_descriptor> sorted_list;
    graph.get_process_order (sorted_list);

    // First, select all the log message from the database.
    CUTS_DB_SQLite_Query * query = this->data_->create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query> auto_clean (query, &CUTS_DB_SQLite_Query::destroy);
    CUTS_DB_SQLite_Record * record = query->execute ("SELECT * FROM cuts_logging ORDER BY lid");

    // Next, iterate over all the log formats. This will enable
    // us to construct the dataset using the provided data.
    CUTS_Log_Format_Data_Entry entry (*this->vtable_);

    std::for_each (sorted_list.begin (),
                   sorted_list.end (),
                   process_log_format (graph, entry, *record));

    // Finally, prune the incomplete rows from the table.
    this->prune_incomplete_rows (graph);
    return true;
  }
  catch (const CUTS_DB_Exception & ex)
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
create_vtable (const CUTS_Dataflow_Graph & graph)
{
  CUTS_Dataflow_Graph::vertex_iterator iter, iter_end;
  boost::tie (iter, iter_end) = boost::vertices (graph.graph ());

  // Create a new query on the variable table database.
  CUTS_DB_SQLite_Query * query = this->vtable_->create_query ();

  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query>
    auto_clean (query, &CUTS_DB_SQLite_Query::destroy);

  // Delete the variable table for the unit test.
  ACE_CString sqlstmt = "DROP TABLE IF EXISTS " + graph.name ();
  query->execute_no_record (sqlstmt.c_str ());

  // Begin the SQL statement for creating the table.
  bool first_entry = true;
  const CUTS_Log_Format * format = 0;

  std::ostringstream sqlstr;
  sqlstr << "CREATE TABLE IF NOT EXISTS " << graph.name ().c_str () << " (";

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
create_vtable_indices (const CUTS_Dataflow_Graph & graph)
{
  CUTS_Dataflow_Graph::vertex_iterator iter, iter_end;
  boost::tie (iter, iter_end) = boost::vertices (graph.graph ());

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
create_vtable_indices (const CUTS_Dataflow_Graph & test,
                       const CUTS_Log_Format & format)
{
  // Allocate a new database query.
  CUTS_DB_SQLite_Query * query = this->vtable_->create_query ();

  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query>
    auto_clean (query, &CUTS_DB_SQLite_Query::destroy);

  // Iterate over all the relations
  CUTS_Log_Format::relations_type::const_iterator
    iter = format.relations ().begin (),
    iter_end = format.relations ().end ();

  size_t index = 0;
  std::string column_name;

  std::string tablename = test.name ().c_str ();
  std::replace (tablename.begin (), tablename.end (), ' ', '_');

  for ( ; iter != iter_end; ++ iter)
  {
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
prune_incomplete_rows (const CUTS_Dataflow_Graph & graph)
{
  CUTS_Dataflow_Graph::vertex_iterator iter, iter_end;
  boost::tie (iter, iter_end) = boost::vertices (graph.graph ());

  // Create a new query on the variable table database.
  CUTS_DB_SQLite_Query * query = this->vtable_->create_query ();
  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query>
    auto_clean (query, &CUTS_DB_SQLite_Query::destroy);

  // Begin the SQL statement for creating the table.
  bool first_entry = true;
  const CUTS_Log_Format * format = 0;

  std::ostringstream sqlstr;
  sqlstr << "DELETE FROM " << graph.name ().c_str () << " WHERE ";

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
CUTS_DB_SQLite_Query * CUTS_Dataset_Repo::create_query (void)
{
  return this->vtable_->create_query ();
}
