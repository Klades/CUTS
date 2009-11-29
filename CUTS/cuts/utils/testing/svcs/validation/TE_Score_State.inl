// -*- C++ -*-
// $Id$

//
// CUTS_TE_Score_State
//
CUTS_INLINE
CUTS_TE_Score_State::CUTS_TE_Score_State (void)
: priority_ (1),
  is_valid_ (true),
  min_occurs_ (1),
  max_occurs_ (1)
{

}

//
// CUTS_TE_Score_State
//
CUTS_INLINE
CUTS_TE_Score_State::
CUTS_TE_Score_State (const ACE_CString & name,
                     const ACE_CString & condition,
                     size_t priority,
                     bool is_valid,
                     size_t min_occurs,
                     size_t max_occurs)
: name_ (name),
  condition_ (condition),
  priority_ (priority),
  is_valid_ (is_valid),
  min_occurs_ (min_occurs),
  max_occurs_ (max_occurs)
{

}

//
// CUTS_TE_Score_State
//
CUTS_INLINE
CUTS_TE_Score_State::CUTS_TE_Score_State (const CUTS_TE_Score_State & copy)
: name_ (copy.name_),
  condition_ (copy.condition_),
  priority_ (copy.priority_),
  is_valid_ (copy.is_valid_),
  min_occurs_ (copy.min_occurs_),
  max_occurs_ (copy.max_occurs_)
{

}

//
// ~CUTS_TE_Score_State
//
CUTS_INLINE
CUTS_TE_Score_State::~CUTS_TE_Score_State (void)
{

}
