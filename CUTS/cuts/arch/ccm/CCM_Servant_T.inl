// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
CUTS_CCM_Servant_T (T * servant, const char * name, typename EXECUTOR::_ptr_type exec)
: SERVANT_BASE (name),
  impl_ (EXECUTOR::_duplicate (exec)),
  servant_ (servant)
{
  // Create the context for the servant/executor.
  CONTEXT * context = 0;

  ACE_NEW_THROW_EX (context,
                    CONTEXT (*servant),
                    ::CORBA::NO_MEMORY ());

  // Set the session context of the implementation.
  this->ctx_.reset (context);

  if (this->impl_)
    this->impl_->set_session_context (this->ctx_.get ());
}

//
// ~CUTS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::~CUTS_CCM_Servant_T (void)
{

}

//
// get_all_consumers
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::ConsumerDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_all_consumers (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_named_consumers
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::ConsumerDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_consumers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_all_emitters
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::EmitterDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_emitters (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_name_emitters
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::EmitterDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_emitters (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_all_publishers
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::PublisherDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_all_publishers (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_named_publishers
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::PublisherDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_publishers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::CORBA::Object_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::provide_facet (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::FacetDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_facets (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::FacetDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_facets (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::Cookie *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
connect (const char *, ::CORBA::Object_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::CORBA::Object_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
disconnect (const char *, ::Components::Cookie *)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::ConnectionDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_connections (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::ReceptacleDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_receptacles (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::ReceptacleDescriptions *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_receptacles (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::CORBA::Boolean
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::same_component (::CORBA::Object_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::CORBA::IRObject_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_component_def (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::CCMHome_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_ccm_home (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::PrimaryKeyBase *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_primary_key (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::ComponentPortDescription *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_ports (void)
{
  throw CORBA::NO_IMPLEMENT ();
}
