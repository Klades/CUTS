// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// CUTS_CCM_Container_Strategy_T
//
template <typename CONTAINER>
CUTS_INLINE
Container_Strategy_T <CONTAINER>::
Container_Strategy_T (CONTAINER & container)
: container_ (container)
{

}

//
// ~CUTS_CCM_Container_Strategy_T
//
template <typename CONTAINER>
CUTS_INLINE
Container_Strategy_T <CONTAINER>::~Container_Strategy_T (void)
{

}

}
