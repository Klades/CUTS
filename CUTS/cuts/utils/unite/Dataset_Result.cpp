// $Id$

#include "Dataset_Result.h"

#if !defined (__CUTS_INLINE__)
#include "Dataset_Result.inl"
#endif

#include "Dataset_Repo.h"
#include "Unite_Test.h"
#include "cuts/utils/db/SQLite/Query.h"
#include "cuts/utils/db/SQLite/Record.h"
#include "cuts/utils/db/SQLite/Connection.h"
#include "ace/CORBA_macros.h"
#include "ace/Pair.h"
#include <string>
#include <sstream>

//
// CUTS_Dataset_Result
//
CUTS_Dataset_Result::
CUTS_Dataset_Result (CUTS_Dataset_Repo & repo, size_t bufsize)
: repo_ (&repo),
  query_ (0),
  record_ (0),
  result_index_ (0),
  bufsize_ (0),
  result_is_old_ (false)
{
  // Allocate space for the result(s).
  char * buffer = 0;

  ACE_NEW_THROW_EX (buffer,
                    char [bufsize],
                    ACE_bad_alloc ());

  this->result_.reset (buffer);
  this->bufsize_ = bufsize;
}

//
// ~CUTS_Dataset_Result
//
CUTS_Dataset_Result::~CUTS_Dataset_Result (void)
{
  if (this->query_ != 0)
    this->query_->destroy ();
}

//
// close
//
void CUTS_Dataset_Result::close (void)
{
  if (this->query_ != 0)
  {
    this->query_->destroy ();
    this->query_ = 0;
  }

  if (this->record_ != 0)
    this->record_ = 0;
}

//
// count
//
size_t CUTS_Dataset_Result::count (void) const
{
  return this->record_ != 0 ? this->record_->count () : 0;
}

//
// done
//
bool CUTS_Dataset_Result::done (void) const
{
  return this->record_->done ();
}

//
// advance
//
void CUTS_Dataset_Result::advance (void)
{
  this->record_->advance ();

  if (!this->result_is_old_)
    this->result_is_old_ = true;

  if (!this->group_is_old_)
    this->group_is_old_ = true;
}

//
// get_result
//
const char * CUTS_Dataset_Result::get_result (void)
{
  // Optimize for the fast path, which is returning the current result.
  if (!this->result_is_old_)
    return this->result_.get ();

  // Get the result from the record.
  this->record_->get_data (this->result_index_,
                           this->result_.get (),
                           this->bufsize_);

  // The data is not old anymore.
  this->result_is_old_ = false;
  return this->result_.get ();
}

//
// get_group_name
//
const CUTS_Group_Name & CUTS_Dataset_Result::get_group_name (void)
{
  // Optimize for the fast path, which is returning the current group name.
  if (!this->group_is_old_)
    return this->group_name_;

  // Get the name of each group item.
  for (size_t i = 0; i < this->result_index_; ++ i)
    this->record_->get_data (i, this->group_name_[i]);

  this->group_is_old_ = false;
  return this->group_name_;
}

//
// evaluate
//
int CUTS_Dataset_Result::
evaluate (const CUTS_Unite_Test & test,
          const ACE_CString & datagraph,
          bool aggr)
{
  try
  {
    if (this->query_ == 0)
      this->query_ = this->repo_->vtable_->create_query ();

    // Normalize the evaluation string.
    ACE_CString eval = test.evaluation ().c_str ();
    std::replace (eval.begin (), eval.end (), '.', '_');

    // Construct the grouping portion of the string.
    std::ostringstream group_str;

    if (test.groupings ().size () != 0)
    {
      ACE_CString name;
      CUTS_Unite_Test::grouping_type::const_iterator
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

    // Make sure we select the group columns.
    if (!group_str.str ().empty ())
        sqlstr << ' ' << group_str.str () << ", ";

    // Insert the aggregation construct, if necessary.
    if (aggr)
      sqlstr << ' ' << test.aggregation ().c_str () << "(";

    sqlstr << eval;

    if (aggr)
      sqlstr << ")";

    // Set the evaluation column to 'result'.
    sqlstr << " AS result FROM " << datagraph.c_str ();

    if (!group_str.str ().empty ())
    {
      // We need to group the data for aggregation.
      if (aggr)
        sqlstr << " GROUP BY " << group_str.str ();

      // Make sure we order the data by its groups.
      sqlstr << " ORDER BY " << group_str.str ();
    }

    // Execute the SQL statement.
    this->record_ = this->query_->execute (sqlstr.str ().c_str ());

    // Prepare the space for storing group information.
    this->group_name_.size (test.groupings ().size ());

    // The result index is the last index in the record
    this->result_index_ = this->record_->columns () - 1;

    // Save information about the evaluation.
    this->vtable_name_ = &datagraph;
    this->unit_test_ = &test;
    this->result_is_old_ = true;
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  return -1;
}

//
// evaluate
//
int CUTS_Dataset_Result::
evaluate (const CUTS_Unite_Test & test,
          const ACE_CString & datagraph,
          const CUTS_UNITE_Aspect & aspect)
{
  try
  {
    if (this->query_ == 0)
      this->query_ = this->repo_->vtable_->create_query ();

    // Normalize the evaluation string.
    ACE_CString eval = test.evaluation ().c_str ();
    std::replace (eval.begin (), eval.end (), '.', '_');

    // Construct the grouping portion of the string.
    std::ostringstream group_str;

    if (test.groupings ().size () != 0)
    {
      ACE_CString name;
      CUTS_Unite_Test::grouping_type::const_iterator
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

    std::ostringstream aspect_sqlstr;

    // First, SELECT all rows that meet the aspect's criteria.
    aspect_sqlstr << "SELECT ROWID FROM " << datagraph
                  << " WHERE " << aspect.condition_
                  << " ORDER BY ROWID";

    this->record_ = this->query_->execute (aspect_sqlstr.str ().c_str ());

    // Extract all the rowids from the dataset.
    long rowid;
    std::ostringstream between_stmt;

    // The aspect needs to display N units before and M units after
    // each row that meets the aspect's criteria.
    if (!this->record_->done ())
    {
      // Begin the SQL condition for the viewpoint.
      this->record_->get_data (0, rowid);
      between_stmt << ACE_TEXT ("(ROWID BETWEEN ") << rowid - aspect.units_before_
                   << ACE_TEXT (" AND ") << rowid + aspect.units_after_ << ACE_TEXT (")");

      for (this->record_->advance (); !this->record_->done (); this->record_->advance ())
        between_stmt << ACE_TEXT (" AND (ROWID BETWEEN ") << rowid - aspect.units_before_
                     << ACE_TEXT (" AND ") << rowid + aspect.units_after_ << ACE_TEXT (")");
    }

    // Now, we can select all the data that will meet the specified
    // aspect's criteria and be within the desired viewpoint.
    std::ostringstream sqlstr;
    sqlstr << ACE_TEXT ("SELECT ");

    // Make sure we select the group columns.
    if (!group_str.str ().empty ())
        sqlstr << ' ' << group_str.str () << ", ";

    sqlstr << eval;

    // Set the evaluation column to 'result'. Make sure to include
    // the aspect that will select the correct rows.
    sqlstr << ACE_TEXT (" AS result FROM ") << datagraph
           << ACE_TEXT (" WHERE ") << between_stmt.str ();

    // Make sure we order the data by its groups.
    if (!group_str.str ().empty ())
      sqlstr << ACE_TEXT (" ORDER BY ") << group_str.str ();

    // Execute the SQL statement.
    this->record_ = this->query_->execute (sqlstr.str ().c_str ());

    // Prepare the space for storing group information.
    this->group_name_.size (test.groupings ().size ());

    // The result index is the last index in the record
    this->result_index_ = this->record_->columns () - 1;

    // Save information about the evaluation.
    this->vtable_name_ = &datagraph;
    this->unit_test_ = &test;
    this->result_is_old_ = true;

    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  return -1;
}

//
// has_groupings
//
bool CUTS_Dataset_Result::has_groupings (void) const
{
  return this->unit_test_->groupings ().size () != 0;
}

//
// rewind
//
void CUTS_Dataset_Result::rewind (void)
{
  this->record_->reset ();
}

bool CUTS_Dataset_Result::validate (const ACE_CString & validation_str)
{
  try
  {
    if (this->query_ == 0)
      this->query_ = this->repo_->vtable_->create_query ();

    // Execute the SQL statement.
    CUTS_DB_SQLite_Record * record;
    record = this->query_->execute (validation_str.c_str ());

    // Check if the record set is empty or not
    return record->done () ? false : true;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }
}