// $Id$

#include "Log_Format_Data_Entry.h"
#include "Log_Format.h"
#include "Variable.h"
#include "adbc/SQLite/Connection.h"
#include <sstream>

//
// CUTS_Log_Format_Data_Entry
//
CUTS_Log_Format_Data_Entry::
CUTS_Log_Format_Data_Entry (ADBC::SQLite::Connection & conn)
: query_ (conn.create_query ())
{
  /// @todo Move this to a better location.
  this->query_->execute_no_record ("BEGIN EXCLUSIVE TRANSACTION");
}

//
// ~CUTS_Log_Format_Data_Entry
//
CUTS_Log_Format_Data_Entry::~CUTS_Log_Format_Data_Entry (void)
{
  if (this->query_ != 0)
  {
    /// @todo Move this to a better location.
    this->query_->execute_no_record ("COMMIT TRANSACTION");

    // Delete the query.
    delete this->query_;
  }
}

//
// prepare
//
void CUTS_Log_Format_Data_Entry::
prepare (const ACE_CString & table, CUTS_Log_Format * format)
{
  std::ostringstream colstr, varstr;

  // First, set the column names we are updating.
  CUTS_Log_Format_Variable_Table::CONST_ITERATOR iter (format->variables ());

  if (!iter.done ())
  {
    colstr << format->name ()
           << "_"
           << iter->key ().c_str ();

    varstr << "@"
           << format->name ()
           << "_"
           << iter->key ().c_str ();

    for (++ iter; !iter.done (); ++ iter)
    {
      colstr << ", " << format->name ()
             << "_"
             << iter->key ().c_str ();

      varstr << ", @"
             << format->name ()
             << "_"
             << iter->key ().c_str ();
    }
  }

  // Now, construct the insert statement
  std::ostringstream ostr;
  ostr << "INSERT INTO " << table << " ("
       << colstr.str () << ") VALUES ("
       << varstr.str () << ")";

  // Prepare the SQL statement.
  this->query_->prepare (ostr.str ().c_str (),
                         ostr.str ().length ());

  // Save the log format for later.
  this->format_ = format;
}

//
// prepare
//
void CUTS_Log_Format_Data_Entry::
prepare (const ACE_CString & table, CUTS_Log_Format * format, size_t relation)
{
  // Get the relation we are preparing.
  const CUTS_Log_Format_Relation & rel = format->relations ()[relation];

  // First, set the column names we are updating.
  ACE_CString varname;
  std::ostringstream setstr;

  CUTS_Log_Format_Variable_Table::CONST_ITERATOR iter (format->variables ());

  if (!iter.done ())
  {
    varname = format->name () + '_' + iter->key ();
    setstr << varname.c_str () << " = @" << varname.c_str ();

    for (++ iter; !iter.done (); ++ iter)
    {
      varname = format->name () + '_' + iter->key ();
      setstr << ", " << varname.c_str () << " = @" << varname.c_str ();
    }
  }

  // Now, construct the WHERE clause of the UPDATE statement.
  std::ostringstream where_str;

  CUTS_Log_Format_Relation::causality_type::const_iterator
    reliter = rel.causality ().begin (),
    reliter_end = rel.causality ().end ();

  if (reliter != reliter_end)
  {
    where_str << '@' << format->name ().c_str ()
              << '_' << reliter->cause ().c_str ()
              << " = "
              << rel.effect ()->name ()
              << '_' << reliter->effect ().c_str ();

    for (++ reliter; reliter != reliter_end; ++ reliter)
    {
      where_str << " AND "
                << '@' << format->name ().c_str ()
                << '_' << reliter->cause ().c_str ()
                << " = "
                << rel.effect ()->name ()
                << '_' << reliter->effect ().c_str ();
    }
  }

  std::ostringstream sqlstr;
  sqlstr << "UPDATE " << table << " SET " << setstr.str ()
         << " WHERE " << where_str.str ();

  // Prepare the statement for execution.
  this->query_->prepare (sqlstr.str ().c_str (),
                         sqlstr.str ().length ());

  // Save the format for later.
  this->format_ = format;
}

//
// execute
//
void CUTS_Log_Format_Data_Entry::execute (const ACE_CString & message, 
										  CUTS_Log_Format_Adapter *adapter)
{
  // The fast path is actually not matching the message.
  
  if (!this->format_->match(message, adapter))
    return;

  ACE_CString fq_name;
  CUTS_Log_Format_Variable_Table::
    CONST_ITERATOR iter (this->format_->variables ());

  for ( ; !iter.done (); ++ iter)
  {
    if (!fq_name.empty ())
      fq_name.clear ();

    // Construct the fully qualified name for the variable.
    fq_name += '@' + this->format_->name () + '_' + iter->key ();

    // Locate the variable in the parameters.
    ADBC::SQLite::Parameter & p = this->query_->parameters ()[fq_name];

    // Bind the variable to the parameter.
    iter->item ()->bind (p);
  }

  // Execute the statement.
  this->query_->execute_no_record ();
  this->query_->reset ();
}

