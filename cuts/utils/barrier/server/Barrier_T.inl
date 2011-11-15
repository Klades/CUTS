// -*- C++ -*-
// $Id$

//
// ACE_Node
//
template <typename C>
CUTS_INLINE
ACE_Node <CUTS::BarrierCallback_var, C>::
ACE_Node (const CUTS::BarrierCallback_var & i,
          ACE_Node <CUTS::BarrierCallback_var, C> * n)
: next_ (n),
  item_ (CUTS::BarrierCallback::_duplicate (i))
{

}

//
// ACE_Node
//
template <typename C>
CUTS_INLINE
ACE_Node <CUTS::BarrierCallback_var, C>::
ACE_Node (ACE_Node <CUTS::BarrierCallback_var, C> * n, int)
: next_ (n)
{

}

//
// ACE_Node
//
template <typename C>
ACE_Node <CUTS::BarrierCallback_var, C>::
ACE_Node (const ACE_Node <CUTS::BarrierCallback_var, C> &n)
: next_ (n.next_),
  item_ (CUTS::BarrierCallback::_narrow (n.item_.in ()))
{

}


//
// ~ACE_Node
//
template <typename C>
CUTS_INLINE
ACE_Node <CUTS::BarrierCallback_var, C>::~ACE_Node (void)
{

}
