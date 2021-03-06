// -*- C++ -*-
// $Id$

//
// ~CUTS_CCM_Container_T
//
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
INST_HANDLER * CUTS_CCM_Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::inst_handler (void)
{
  return this->inst_handler_;
}

//
// connect_local_facet
//
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
::Components::Cookie *
CUTS_CCM_Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::
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
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::
disconnect_local_facet (::Components::Cookie *,
                        ::Components::CCMObject_ptr,
                        const char * ,
                        ::Components::CCMObject_ptr,
                        const char *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// init
//
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::
init (const char * name)
{
  this->name_ = name;
}

//
// fini
//
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::fini (void)
{

}
