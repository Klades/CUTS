// $Id$

#include "Unit_Test_Evaluator.h"
#include "Unit_Test_Graph.h"
#include "Unit_Test.h"
#include "Unit_Test_Result.h"
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
// CUTS_Unit_Test_Evaluator
//
CUTS_Unit_Test_Evaluator::
CUTS_Unit_Test_Evaluator (const ACE_CString & sandbox)
: sandbox_ (sandbox)
{

}

//
// ~CUTS_Unit_Test_Evaluator
//
CUTS_Unit_Test_Evaluator::~CUTS_Unit_Test_Evaluator (void)
{

}

//
// evaluate
//
bool CUTS_Unit_Test_Evaluator::evaluate (CUTS_Test_Database & data,
                                         const CUTS_Unit_Test & test,
                                         CUTS_Unit_Test_Result & result)
{
  typedef
    boost::graph_traits <CUTS_Unit_Test_Graph::graph_type>::
    vertex_descriptor vertex_type;

  // Sort the contents of the graph. This will give us the processing
  // order for each log format in the unit test.
  typedef std::vector <vertex_type> vertex_list_type;
  vertex_list_type sorted_list;
  boost::topological_sort (test.graph ()->graph (),
                           std::back_inserter (sorted_list));

  // Open the variable table for the unit test.
  CUTS_Test_Profile profile;
  if (data.get_test_profile (profile) != 0)
    return false;

  std::ostringstream ostr;

  ostr << this->sandbox_.c_str ()
       << "/"
       << profile.uuid_.to_string ()->c_str ()
       << "."
       << test.name ()
       << ".vtable";

  CUTS_DB_SQLite_Connection data_table;

  try
  {
    // Open the database.
    data_table.connect (ostr.str ().c_str ());

    // Create the table for the dataset.
    this->create_vtable (data_table, test);

    // Create the indices for the dataset.
    vertex_list_type::iterator
      iter = sorted_list.begin (),
      iter_end = sorted_list.end ();

    CUTS_Log_Format * format = 0;

    for ( ; iter != iter_end; ++ iter)
    {
      // Get the log format from the vertex.
      format = boost::get (CUTS_Unit_Test_Graph::log_format_t (),
                           test.graph ()->graph (),
                           *iter);

      if (!format->relations ().empty ())
        this->create_vtable_indices (data_table, *format);
    }

    // First, select all the log message from the database.
    CUTS_DB_SQLite_Query * query = data.create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query> auto_clean (query, &CUTS_DB_SQLite_Query::destroy);
    CUTS_DB_SQLite_Record * record = query->execute ("SELECT * FROM cuts_logging ORDER BY lid");
    CUTS_Log_Format_Data_Entry entry (data_table);

    // Next, iterate over all the log formats. This will enable
    // us to construct the dataset using the provided data.
    iter = sorted_list.begin ();
    iter_end = sorted_list.end ();

    for ( ; iter != iter_end; ++ iter)
    {
      // Get the log format from the vertex.
      format = boost::get (CUTS_Unit_Test_Graph::log_format_t (),
                           test.graph ()->graph (),
                           *iter);

      if (format->relations ().empty ())
      {
        // Process this log format.
        entry.prepare (format);
        this->process (entry, *record);
      }
      else
      {
        // Iterate over each of the relations.
        size_t relation_count = format->relations ().size ();

        for (size_t i = 0; i < relation_count; ++ i)
        {
          entry.prepare (format, i);
          this->process (entry, *record);
        }
      }
    }

    // Get the result from the dataset.
    this->get_result (data_table, test, result);
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
// get_result
//
void CUTS_Unit_Test_Evaluator::get_result (CUTS_DB_SQLite_Connection & conn,
                                           const CUTS_Unit_Test & test,
                                           CUTS_Unit_Test_Result & result)
{
  // Normalize the evaluation string.
  std::string eval = test.evaluation ().c_str ();
  std::replace (eval.begin (), eval.end (), '.', '_');

  // Construct the grouping portion of the string.
  std::ostringstream group_str;

  if (test.groupings ().size () != 0)
  {
    std::string name;
    CUTS_Unit_Test::grouping_type::const_iterator
      iter = test.groupings ().begin (), end = test.groupings ().end ();

    // Normalize the name.
    name = iter->c_str ();
    std::replace (name.begin (), name.end (), '.', '_');

    // Append the name to the SQL string.
    group_str << name;

    for (++ iter; iter != end; ++ iter)
    {
      // Normalize the name.
      name = iter->c_str ();
      std::replace (name.begin (), name.end (), '.', '_');

      // Append the name to the SQL string.
      group_str << ", " << name;
    }
  }

  // Construct the final SQL string.
  std::ostringstream sqlstr;
  sqlstr << "SELECT";

  if (!group_str.str ().empty ())
    sqlstr << ' ' << group_str.str () << ", ";

  sqlstr << ' ' << test.aggregation ().c_str ()
         << '(' << eval << ") AS result FROM vtable";

  if (!group_str.str ().empty ())
    sqlstr << " GROUP BY " << group_str.str ()
           << " ORDER BY " << group_str.str ();

  // Allocate a new SQL statement on the connection.
  CUTS_DB_SQLite_Query * query = conn.create_query ();
  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query> auto_clean (query, &CUTS_DB_SQLite_Query::destroy);

  // Execute the SQL statement.
  ACE_CString result_str;
  CUTS_DB_SQLite_Record * record = query->execute (sqlstr.str ().c_str ());

  if (test.groupings ().size () == 0)
  {
    record->get_data (0, result_str);
    result.result (result_str);
  }
  else
  {
    // Get the number of columns in the record. We need to keep one less
    // since the result is the last column.
    ACE_CString group_name, temp;
    size_t columns = record->columns () - 1;

    for ( ; !record->done (); record->advance ())
    {
      record->get_data (0, group_name);

      for (size_t index = 1; index < columns; ++ index)
      {
        record->get_data (index, temp);
        group_name += '.' + temp;
      }

      record->get_data (columns, result_str);
      result.groups ().bind (group_name, result_str);
    }
  }
}

//
// process
//
void CUTS_Unit_Test_Evaluator::
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
void CUTS_Unit_Test_Evaluator::
create_vtable (CUTS_DB_SQLite_Connection & conn,
               const CUTS_Unit_Test & test)
{
  // Delete the 'vtable' if it already exist.
  CUTS_DB_SQLite_Query * query = conn.create_query ();

  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query>
    auto_clean (query, &CUTS_DB_SQLite_Query::destroy);

  query->execute_no_record ("DROP TABLE IF EXISTS vtable");

  // Begin the SQL statement for creating the table.
  CUTS_Unit_Test::formats_type::CONST_ITERATOR log_iter (test.log_formats ());

  std::ostringstream sqlstr;
  sqlstr << "CREATE TABLE IF NOT EXISTS vtable (";

  bool first_entry = true;

  for ( ; !log_iter.done (); ++ log_iter)
  {
    // Iterate over the variables in the log format. We need to
    // make sure we include columns for them in the data set.
    CUTS_Log_Format * format = log_iter->item ();
    CUTS_Log_Format_Variable_Table::CONST_ITERATOR var_iter (format->variables ());

    for ( ; !var_iter.done (); ++ var_iter)
    {
      // Make sure we insert a comma between column declarations.
      if (!first_entry)
        sqlstr << ", ";
      else
        first_entry = false;

      // Write the fully qualified name for the column.
      sqlstr << log_iter->key ().c_str ()
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
void CUTS_Unit_Test_Evaluator::
create_vtable_indices (CUTS_DB_SQLite_Connection & conn,
                       const CUTS_Log_Format & format)
{
  // Allocate a new database query.
  CUTS_DB_SQLite_Query * query = conn.create_query ();

  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query>
    auto_clean (query, &CUTS_DB_SQLite_Query::destroy);

  // Iterate over all the relations
  CUTS_Log_Format::relations_type::const_iterator
    iter = format.relations ().begin (),
    iter_end = format.relations ().end ();

  size_t index = 0;
  std::string column_name;

  for ( ; iter != iter_end; ++ iter)
  {
    std::ostringstream ostr;
    ostr << "CREATE INDEX IF NOT EXISTS "
         << format.name ().c_str ()
         << "r" << index << " ON vtable (";

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

