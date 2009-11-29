// $Id$

#include "TE_Score_State.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_State.inl"
#endif

const CUTS_TE_Score_State &
CUTS_TE_Score_State::operator = (const CUTS_TE_Score_State & rhs)
{
  if (this == &rhs)
    return *this;

  this->name_ = rhs.name_;
  this->condition_ = rhs.condition_;
  this->priority_ = rhs.priority_;
  this->is_valid_ = rhs.is_valid_;
  this->min_occurs_ = rhs.min_occurs_;
  this->max_occurs_ = rhs.max_occurs_;

  return *this;
}
