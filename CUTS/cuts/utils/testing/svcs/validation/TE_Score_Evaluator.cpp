// $Id$

#include "TE_Score_Evaluator.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_Evaluator.inl"
#endif

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
evaluate (const ACE_CString & dataset,
          ::CUTS::XML::correctnessTestType::state_const_iterator begin,
          ::CUTS::XML::correctnessTestType::state_const_iterator end)
{
  this->reset ();

  // First, get total number of points and max priority.
  std::for_each (begin, end,
                 boost::bind (&CUTS_TE_Score_Evaluator::accumulate_maxpoints,
                              this,
                              _1));

  // Evaluate each of the states using the current form.
  std::for_each (begin, end,
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
accumulate_maxpoints (const state_value_type & state)
{
  size_t prio = state->priority ();

  if (prio > this->maxprio_)
    this->maxprio_ = prio;

  this->maxpoints_ += prio;
}

//
// evaluate_state
//
void CUTS_TE_Score_Evaluator::
evaluate_state (const ACE_CString & dataset, const state_value_type & state)
{
  // Construct the SQL validation string.
  std::ostringstream ostr;
  ostr << "SELECT COUNT(*) AS tally, (" << state->value ()
       << ") AS result FROM " << dataset
       << " WHERE (" << state->context ()
       << ") GROUP BY result";

  // Execute the SQL query on the database.
  CUTS_DB_Record * record = this->query_->execute (ostr.str ().c_str ());

  // There will ALWAYS be at least one row in the result sent. The
  // value of the 'result' will be 0.
  long tally, result;
  record->get_data (0, tally);
  record->get_data (1, result);

  bool add_weight = false;

  if (1 == result)
  {
    add_weight = true;
  }
  else if (0 == tally)
  {
    // Ok, so there were no false states in the result set. We
    // can no check for positives in the result set.
    record->advance ();

    if (!record->done ())
      add_weight = true;
  }

  if (add_weight)
    this->points_ = this->maxprio_ - state->priority () + 1;

  // Reset query for the next state.
  this->query_->reset ();
}
