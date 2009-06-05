// -*- C++ -*-
// $Id$

//
// ~CUTS_CCM_Container_T
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::~CUTS_CCM_Container_T (void)
{

}

//
// ~CUTS_CCM_Container_T
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
SERVER * CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::server (void)
{
  return this->server_;
}
