// $Id$

#include "TE_Score_Evaluator.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_Evaluator.inl"
#endif

#include "cuts/utils/unite/Dataset_Result.h"
#include "ace/SString.h"
#include "boost/bind.hpp"
#include <algorithm>
#include <sstream>

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

  // Now, check for false negatives.
  std::for_each (begin, end,
                 boost::bind (&CUTS_TE_Score_Evaluator::evaluate_false_negative,
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
  ostr << "SELECT " << state->value ()
       << " FROM " << dataset
       << " WHERE " << state->context ();

  if (this->result_.validate (ostr.str ().c_str ()))
  {
    // Insert the name of the state.
    this->seen_.insert (state->id ().c_str ());

    // Increase the points since the state is valid.
    size_t weight = this->maxprio_ - state->priority () + 1;
    this->points_ += weight;
  }
}

//
// evaluate_false_negative
//
void CUTS_TE_Score_Evaluator::
evaluate_false_negative (const ACE_CString & dataset,
                         const state_value_type & state)
{
  // Construct the SQL validation string.
  std::ostringstream ostr;
  ostr << "SELECT NOT(" << state->value () << ")"
       << " FROM " << dataset
       << " WHERE " << state->context ();

  size_t weight = this->maxprio_ - state->priority () + 1;
  int seen = this->seen_.find (state->id ().c_str ());

  if (this->result_.validate (ostr.str ().c_str ()))
  {
    if (0 == seen)
      // This was not an valid state after all.
      this->points_ -= weight;
  }
  else if (0 != seen)
  {
    this->points_ += weight;
  }
}
