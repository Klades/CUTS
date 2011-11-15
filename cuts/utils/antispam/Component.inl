// -*- C++ -*-
// $Id$

//
// CUTS_Component
//
CUTS_INLINE
CUTS_Component::CUTS_Component (const ACE_CString & name)
: name_ (name)
{

}

//
// ~CUTS_Component
//
CUTS_INLINE
CUTS_Component::~CUTS_Component (void)
{

}

//
// behavior
//
CUTS_INLINE
const CUTS_Behavior_Graph & CUTS_Component::behavior (void) const
{
  return this->graph_;
}

//
// port_count
//
CUTS_INLINE
size_t CUTS_Component::port_count (void) const
{
  return boost::num_vertices (this->graph_);
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Component::name (void) const
{
  return this->name_;
}
