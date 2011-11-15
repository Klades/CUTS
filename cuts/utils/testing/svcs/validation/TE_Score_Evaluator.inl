// -*- C++ -*-
// $Id$

//
// points
//
CUTS_INLINE
size_t CUTS_TE_Score_Evaluator::points (void) const
{
  return this->points_;
}

//
// max_points
//
CUTS_INLINE
size_t CUTS_TE_Score_Evaluator::max_points (void) const
{
  return this->max_points_;
}

//
// final_grade
//
CUTS_INLINE
double CUTS_TE_Score_Evaluator::final_grade (void) const
{
  return this->max_points_ > 0 ?
    (double)this->points_ / (double) this->max_points_ : 0.0;
}

//
// calculate_weight
//
CUTS_INLINE
size_t CUTS_TE_Score_Evaluator::
calculate_weight (const CUTS_TE_Score_State & state)
{
  return this->calculate_weight (this->max_prio_, state);
}

//
// calculate_weight
//
CUTS_INLINE
size_t CUTS_TE_Score_Evaluator::
calculate_weight (size_t maxprio, const CUTS_TE_Score_State & state)
{
  return (maxprio - state.priority_) + 1;
}

//
// reset
//
CUTS_INLINE
void CUTS_TE_Score_Evaluator::reset (void)
{
  this->points_ = 0;
  this->max_prio_ = 0;
  this->max_points_ = 0;
}
