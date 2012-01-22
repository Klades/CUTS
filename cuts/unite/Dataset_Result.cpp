// $Id$

#include "Dataset_Result.h"

#if !defined (__CUTS_INLINE__)
#include "Dataset_Result.inl"
#endif

#include "Dataset_Repo.h"
#include "Unite_Test.h"
#include "adbc/SQLite/Connection.h"
#include "ace/CORBA_macros.h"
#include <map>
#include <set>
#include <sstream>
#include <string>

namespace CUTS
{
namespace UNITE
{
// Type definition of the partition type.
typedef std::map <ACE_CString, std::set <long> > partition_type;

//
// normalize
//
template <typename ITERATOR>
static void normalize (ITERATOR begin, ITERATOR end)
{
  std::replace (begin, end, '.', '_');
}
}
}

//
// operator <<
//
std::ostream &
operator << (std::ostream & out, const CUTS_Unite_Group & group)
{
  if (0 == group.size ())
    return out;

  ACE_CString curr_name;
  CUTS_Unite_Group::const_iterator
    iter = group.begin (), end = group.end ();

  // Normalize and append name to the stream.
  curr_name = *iter;
  ::CUTS::UNITE::normalize (curr_name.begin (), curr_name.end ());

  // Append the name to the SQL string.
  out << curr_name;

  for (++ iter; iter != end; ++ iter)
  {
    // Normalize and append the name to the stream.
    curr_name = *iter;
    ::CUTS::UNITE::normalize (curr_name.begin (), curr_name.end ());

    // Append the name to the SQL string.
    out << ", " << curr_name;
  }

  return out;
}

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
  // Optimize for the fast path, which is returning the current
  // group name.
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
          CUTS_UNITE_Aspect * aspect,
          bool aggr)
{
  if (this->query_ == 0)
    this->query_ = this->repo_->vtable_->create_query ();

  bool has_grouping = test.groupings ().size () != 0 ? true : false;

  bool has_viewpoint =
    aspect != 0 &&
    (aspect->viewpoint_.lower_ != 0 || aspect->viewpoint_.upper_ != 0);

  // Construct the grouping portion of the string.
  std::ostringstream group_str;
  group_str << test.groupings ();

  std::ostringstream where_value;

  if (aspect != 0)
  {
    // Since the aspect works on an state (or variable) in the data
    // table, we first need to select the rows that match the specified
    // condition. Otherwise, we will have a HARD time applying the
    // aspect to the dataset.
    std::ostringstream aspect_sqlstr;
    aspect_sqlstr << "SELECT ROWID";

    if (has_grouping)
      aspect_sqlstr << ", " << group_str.str ();

    aspect_sqlstr << " FROM " << datagraph
                  << " WHERE " << aspect->condition_;

    if (has_grouping)
      aspect_sqlstr << " ORDER BY " << group_str.str ();

    this->record_ = &this->query_->execute (aspect_sqlstr.str ().c_str ());

    // Now that we have selected all ROWIDs that match the condition,
    // the next step is to partition all selected ROWID values by their
    // group. If there is no group information available, then we assume
    // that there is a single partition.
    ::CUTS::UNITE::partition_type partitions;
    long rowid;

    if (!has_grouping && has_viewpoint)
    {
      // This is the easiest case to handle since there is not group
      // information and we just need to ensure we select base our
      // boundaries on the returned ROWID values.
      if (!this->record_->done ())
      {
        this->record_->get_data (0, rowid);

        where_value << ACE_TEXT ("(ROWID BETWEEN ")
                    << rowid - aspect->viewpoint_.lower_
                    << ACE_TEXT (" AND ")
                    << rowid + aspect->viewpoint_.upper_
                    << ACE_TEXT (")");

        for (this->record_->advance (); !this->record_->done (); this->record_->advance ())
        {
          // Insert the next datapoint into the viewpoint.
          this->record_->get_data (0, rowid);

          where_value << ACE_TEXT (" OR (ROWID BETWEEN ")
                      << rowid - aspect->viewpoint_.lower_
                      << ACE_TEXT (" AND ")
                      << rowid + aspect->viewpoint_.upper_
                      << ACE_TEXT (")");
        }
      }
    }
    else if (!has_viewpoint)
    {
      // This case is also easy to handle. We just need to use the
      // returned ROWID values. We do not have to worry about the
      // boundaries. This converts to using an IN(...) SQL statement.
      if (!this->record_->done ())
      {
        this->record_->get_data (0, rowid);

        where_value << ACE_TEXT ("ROWID IN(")
                    << rowid;

        for (this->record_->advance (); !this->record_->done (); this->record_->advance ())
        {
          // Insert the next datapoint into the viewpoint.
          this->record_->get_data (0, rowid);
          where_value << ACE_TEXT (",") << rowid;
        }

        where_value << ACE_TEXT (")");
      }
    }
    else
    {
      // Right now, we do not support this case.
      ACE_ERROR_RETURN ((LM_NOTICE,
                         ACE_TEXT ("%T (%t) - %M - groups are not supported in aspects\n")),
                         -1);

      // Store all ROWID values in the *default* partition.
      for (; !this->record_->done (); this->record_->advance ())
      {
        this->record_->get_data (0, rowid);
        partitions[""].insert (rowid);
      }
    }
  }

  // Normalize the evaluation string.
  ACE_CString eval = test.evaluation ().c_str ();
  ::CUTS::UNITE::normalize (eval.begin (), eval.end ());

  // Construct the final SQL string.
  std::ostringstream sqlstr;
  sqlstr << "SELECT ";

  // Make sure we select the group columns.
  if (has_grouping)
      sqlstr << group_str.str () << ", ";

  // Insert the aggregation construct, if necessary.
  if (aggr)
    sqlstr << test.aggregation () << "(";

  sqlstr << eval;

  if (aggr)
    sqlstr << ")";

  // Set the evaluation column to 'result'.
  sqlstr << " AS result FROM " << datagraph;

  // Insert the aspect in the SQL query.
  if (!(0 == aspect || where_value.str ().empty ()))
    sqlstr << " WHERE " << where_value.str ();

  if (has_grouping)
  {
    // We need to group the data for aggregation.
    if (aggr)
      sqlstr << " GROUP BY " << group_str.str ();

    // Make sure we order the data by its groups.
    sqlstr << " ORDER BY " << group_str.str ();
  }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - executing %s\n"),
              sqlstr.str ().c_str ()));

  // Execute the SQL statement.
  this->record_ = &this->query_->execute (sqlstr.str ().c_str ());

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