// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// ~Container_T
//
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
INST_HANDLER * Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::inst_handler (void)
{
  return this->inst_handler_;
}

//
// connect_local_facet
//
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
::Components::Cookie *
Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::
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
void Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::
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
void Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::
init (const char * name)
{
  this->name_ = name;
}

template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
void Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::fini (void)
{

}

template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
Container_Strategy * Container_T <T, INST_HANDLER, STRATEGY, SERVANT_BASE>::get_strategy (void) const
{
  return this->strategy_.get ();
}
   
}
