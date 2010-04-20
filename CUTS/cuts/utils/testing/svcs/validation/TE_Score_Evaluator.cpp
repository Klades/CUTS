// $Id$

#include "TE_Score_Evaluator.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_Evaluator.inl"
#endif

#include "TE_Score_State.h"
#include "cuts/utils/unite/Dataset_Repo.h"
#include "adbc/SQLite/Query.h"
#include "ace/SString.h"
#include "boost/bind.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>

/**
 * @struct CUTS_TE_Score_State_Less_Prio
 *
 * Functor that determines if a state's priority is less than
 * another state's priority.
 */
struct CUTS_TE_Score_State_Less_Prio
{
  bool operator () (const CUTS_TE_Score_State & lhs,
                    const CUTS_TE_Score_State & rhs) const
  {
    return lhs.priority_ < rhs.priority_;
  }
};

/**
 * @struct CUTS_TE_Score_Points_Accumulator
 *
 * Functor for accumulating the max points.
 */
struct CUTS_TE_Score_Points_Accumulator
{
  /**
   * Initializing constructor.
   *
   * @param[in]         maxprio       Max priority of all the states
   */
  CUTS_TE_Score_Points_Accumulator (size_t maxprio)
    : maxprio_ (maxprio)
  {

  }

  /**
   * Binary operator accumulating points.
   *
   * @param[in]       current         Current accumulation
   * @param[in]       state           Next state to add to result
   * @return          Total with new state added.
   */
  size_t operator () (size_t current, const CUTS_TE_Score_State & rhs) const
  {
    return
      current +
      CUTS_TE_Score_Evaluator::calculate_weight (this->maxprio_, rhs);
  }

private:
  /// Max priority of all the states.
  size_t maxprio_;
};

//
// CUTS_TE_Score_Evaluator
//
CUTS_TE_Score_Evaluator::
CUTS_TE_Score_Evaluator (CUTS_Dataset_Repo & repo)
: query_ (repo.create_query ()),
  points_ (0),
  max_points_ (0),
  max_prio_ (0)
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
// evaluate
//
bool CUTS_TE_Score_Evaluator::
evaluate (const ACE_CString & dataset, CUTS_TE_Score_State_List & states)
{
  // Reset the evaluator.
  this->reset ();

  // Locate the max priority in the collection.
  this->max_prio_ = std::max_element (states.begin (),
                                      states.end (),
                                      CUTS_TE_Score_State_Less_Prio ())->priority_;

  // Calculate the maximum number of points possible.
  this->max_points_ =
    std::accumulate (states.begin (),
                     states.end (),
                     0,
                     CUTS_TE_Score_Points_Accumulator (this->max_prio_));

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
  ADBC::Record & record = this->query_->execute (sqlstr.str ().c_str ());

  // Get the 'result' column of the record.
  long count;
  record.get_data (0, count);

  if ((count < state.min_occurs_ ||
      (state.max_occurs_ != -1 && count > state.max_occurs_)) &&
       state.is_valid_)
  {
    return;
  }

  // Add the points to the current count.
  this->points_ += this->calculate_weight (state);

  // Reset query for the next state.
  this->query_->reset ();
}
