// $Id$

#include "Variable_Table_Repo.h"

#if !defined (__CUTS_INLINE__)
#include "Variable_Table_Repo.inl"
#endif

#include "Unit_Test_Graph.h"
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

//
// CUTS_Variable_Table_Repo
//
CUTS_Variable_Table_Repo::
CUTS_Variable_Table_Repo (const ACE_CString & sandbox)
: sandbox_ (sandbox),
  data_ (0),
  vtable_ (0)
{
  ACE_NEW_THROW_EX (this->vtable_,
                    CUTS_DB_SQLite_Connection (),
                    ACE_bad_alloc ());
}

//
// ~CUTS_Variable_Table_Repo
//
CUTS_Variable_Table_Repo::~CUTS_Variable_Table_Repo (void)
{
  if (this->vtable_ != 0)
    delete this->vtable_;
}

//
// open
//
bool CUTS_Variable_Table_Repo::open (CUTS_Test_Database & data)
{
  if (this->data_ != 0)
    this->close ();

  // Open the variable table.
  if (this->open_vtable (data) != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open variable table\n"),
                       false);

  // Store the data for later.
  this->data_ = &data;
  return true;
}

//
// close
//
void CUTS_Variable_Table_Repo::close (void)
{
  if (this->vtable_->is_connected ())
    this->vtable_->disconnect ();

  if (this->data_ != 0)
    this->data_ = 0;
}

//
// evaluate
//
bool CUTS_Variable_Table_Repo::insert (const CUTS_Unit_Test_Graph & graph)
{
  try
  {
    // Create an empty table for the data set.
    this->create_vtable (graph);

    // Create all the indices for the dataset.
    this->create_vtable_indices (graph);

    // Sort the contents of the graph. This will give us the processing
    // order for each log format in the unit test.
    typedef
      boost::graph_traits <CUTS_Unit_Test_Graph::graph_type>::
      vertex_descriptor vertex_type;

    typedef std::vector <vertex_type> vertex_list_type;
    vertex_list_type sorted_list;
    boost::topological_sort (graph.graph (), std::back_inserter (sorted_list));

    // First, select all the log message from the database.
    CUTS_DB_SQLite_Query * query = this->data_->create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query> auto_clean (query, &CUTS_DB_SQLite_Query::destroy);
    CUTS_DB_SQLite_Record * record = query->execute ("SELECT * FROM cuts_logging ORDER BY lid");

    // Next, iterate over all the log formats. This will enable
    // us to construct the dataset using the provided data.
    vertex_list_type::iterator
      iter = sorted_list.begin (),
      iter_end = sorted_list.end ();

    const CUTS_Log_Format * format;
    CUTS_Log_Format_Data_Entry entry (*this->vtable_);

    for ( ; iter != iter_end; ++ iter)
    {
      // Get the log format from the vertex.
      format = graph.log_format (*iter);

      if (format->relations ().empty ())
      {
        // Process this log format.
        entry.prepare (graph.name (), format);
        this->process (entry, *record);
      }
      else
      {
        // Iterate over each of the relations.
        size_t relation_count = format->relations ().size ();

        for (size_t i = 0; i < relation_count; ++ i)
        {
          entry.prepare (graph.name (), format, i);
          this->process (entry, *record);
        }
      }
    }

    return true;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  return false;
}

//
// open_vtable
//
int CUTS_Variable_Table_Repo::open_vtable (CUTS_Test_Database & data)
{
  // Extract the profile from the database.
  CUTS_Test_Profile profile;

  if (data.get_test_profile (profile) != 0)
    return -1;

  // Construct the location of the variable table.
  std::ostringstream ostr;
  ostr << this->sandbox_.c_str ()
       << "/"
       << profile.uuid_.to_string ()->c_str ()
       << ".vtable";

  // Open a connection to the variable table.
  this->vtable_->connect (ostr.str ().c_str ());
  return 0;
}

//
// process
//
void CUTS_Variable_Table_Repo::
process (CUTS_Log_Format_Data_Entry & entry, CUTS_DB_SQLite_Record & record)
{
  char message[1024];

  for ( ; !record.done (); record.advance ())
  {
    // Get the message from the row.
    record.get_data (4, message, sizeof (message));

    // Execute the entry against this message. It may or may not update
    // the database. It depends on if the message matches the current
    // log format.
    entry.execute (message);
  }

  record.reset ();
}

//
// create_data_table
//
void CUTS_Variable_Table_Repo::
create_vtable (const CUTS_Unit_Test_Graph & graph)
{
  CUTS_Unit_Test_Graph::vertex_iterator iter, iter_end;
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
    format = graph.log_format (*iter);
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
        ;
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
void CUTS_Variable_Table_Repo::
create_vtable_indices (const CUTS_Unit_Test_Graph & graph)
{
  CUTS_Unit_Test_Graph::vertex_iterator iter, iter_end;
  boost::tie (iter, iter_end) = boost::vertices (graph.graph ());

  const CUTS_Log_Format * format = 0;

  for ( ; iter != iter_end; ++ iter)
  {
    // Get the log format from the vertex.
    format = graph.log_format (*iter);

    if (!format->relations ().empty ())
      this->create_vtable_indices (graph, *format);
  }
}

//
// create_indices
//
void CUTS_Variable_Table_Repo::
create_vtable_indices (const CUTS_Unit_Test_Graph & test,
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

