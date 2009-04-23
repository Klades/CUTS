// -*- C++ -*-
// $Id$

//
// CUTS_Property_Evaluator_List_Actor
//
CUTS_INLINE
CUTS_Property_Evaluator_List_Actor::CUTS_Property_Evaluator_List_Actor (void)
{

}

//
// ~CUTS_Property_Evaluator_List_Actor
//
CUTS_INLINE
CUTS_Property_Evaluator_List_Actor::~CUTS_Property_Evaluator_List_Actor (void)
{

}

//
// clear
//
CUTS_INLINE
void CUTS_Property_Evaluator_List_Actor::clear (void)
{
  this->list_.reset ();
}

//
// list
//
CUTS_INLINE
const CUTS_Property_Evaluator_List_Actor::list_type &
CUTS_Property_Evaluator_List_Actor::list (void) const
{
  return this->list_;
}

//
// expand
//
template <typename IteratorT>
CUTS_INLINE
void CUTS_Property_Evaluator_List_Actor::append (IteratorT, IteratorT) const
{

}
