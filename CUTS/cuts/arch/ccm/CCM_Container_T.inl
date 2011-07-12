// -*- C++ -*-
// $Id$

//
// ~CUTS_CCM_Container_T
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
SERVER * CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::server (void)
{
  return this->server_;
}

//
// connect_local_facet
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
connect_local_facet (::Components::CCMObject_ptr,
                     const char * ,
                     ::Components::CCMObject_ptr,
                     const char *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// disconnect_local_facet
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
disconnect_local_facet (::Components::CCMObject_ptr,
                        const char * ,
                        ::Components::CCMObject_ptr,
                        const char *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// init
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
init (const char * name)
{
  this->name_ = name;
}

//
// fini
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::fini (void)
{

}

