// $Id$

#include "TE_Score_Evaluator.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_Evaluator.inl"
#endif

#include "TE_Score_State.h"
#include "cuts/utils/unite/Dataset_Repo.h"
#include "cuts/utils/db/SQLite/Query.h"
#include "ace/SString.h"
#include "boost/bind.hpp"
#include <algorithm>
#include <sstream>

//
// CUTS_TE_Score_Evaluator
//
CUTS_TE_Score_Evaluator::
CUTS_TE_Score_Evaluator (CUTS_Dataset_Repo & repo)
: query_ (repo.create_query ())
{

}

//
// ~CUTS_TE_Score_Evaluator
//
CUTS_TE_Score_Evaluator::~CUTS_TE_Score_Evaluator (void)
{
  if (0 != this->query_)
    this->query_->destroy ();
}


//
// reset
//
void CUTS_TE_Score_Evaluator::reset (void)
{
  this->points_ = 0;
  this->maxprio_ = 0;
  this->maxpoints_ = 0;
}

//
// evaluate
//
bool CUTS_TE_Score_Evaluator::
evaluate (const ACE_CString & dataset, CUTS_TE_Score_State_List & states)
{
  this->reset ();

  // First, get total number of points and max priority.
  std::for_each (states.begin (),
                 states.end (),
                 boost::bind (&CUTS_TE_Score_Evaluator::accumulate_maxpoints,
                              this,
                              _1));

  // Evaluate each of the states using the current form.
  std::for_each (states.begin (),
                 states.end (),
                 boost::bind (&CUTS_TE_Score_Evaluator::evaluate_state,
                              this,
                              dataset,
                              _1));

  return true;
}

//
// accumulate_maxpoints
//
void CUTS_TE_Score_Evaluator::
accumulate_maxpoints (const CUTS_TE_Score_State & state)
{
  // Test the current priority.
  size_t prio = state.priority_;

  if (prio > this->maxprio_)
    this->maxprio_ = prio;

  // Save this priority as the max one.
  this->maxpoints_ += prio;
}

//
// evaluate_state
//
void CUTS_TE_Score_Evaluator::
evaluate_state (const ACE_CString & dataset, const CUTS_TE_Score_State & state)
{
  // Construct the SQL validation string.
  std::ostringstream sqlstr;
  sqlstr << "SELECT COUNT(*) AS result FROM " << dataset
         << " WHERE " << state.condition_;

  // Execute the SQL query on the database.
  CUTS_DB_Record * record = this->query_->execute (sqlstr.str ().c_str ());

  // Get the 'result' column of the record.
  long count;
  record->get_data (0, count);

  if ((count < state.min_occurs_ ||
      (state.max_occurs_ != -1 && count > state.max_occurs_)) &&
       state.is_valid_)
  {
    return;
  }

  // Add the points to the current count.
  this->points_ = this->maxprio_ - state.priority_ + 1;

  // Reset query for the next state.
  this->query_->reset ();
}
