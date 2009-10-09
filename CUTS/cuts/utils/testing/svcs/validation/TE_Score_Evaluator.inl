// -*- C++ -*-
// $Id$

//
// CUTS_TE_Score_Evaluator
//
CUTS_INLINE
CUTS_TE_Score_Evaluator::
CUTS_TE_Score_Evaluator (CUTS_Dataset_Result & result)
: result_ (result)
{

}

//
// ~CUTS_TE_Score_Evaluator
//
CUTS_INLINE
CUTS_TE_Score_Evaluator::~CUTS_TE_Score_Evaluator (void)
{

}

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
  return this->maxpoints_;
}

//
// final_grade
//
CUTS_INLINE
double CUTS_TE_Score_Evaluator::final_grade (void) const
{
  return this->maxpoints_ > 0 ?
    (double)this->points_ / (double) this->maxpoints_ : 0.0;
}
