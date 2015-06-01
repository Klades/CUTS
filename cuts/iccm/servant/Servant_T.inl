// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
Servant_T (const char * name)
: SERVANT_BASE (name)
{

}

//
// get_consumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
int Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_consumer (const char * name, typename SERVANT_BASE::eventconsumer_type * & result) const
{
  return this->consumers_.find (name, result);
}

//
// get_publisher
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
int Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_publisher (const char * name, typename SERVANT_BASE::publisher_type * & result) const
{
  return this->emits_.find (name, result);
}

//
// get_publisher_table
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
int Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_publisher_table (const char * name, typename SERVANT_BASE::publisher_table_type * & result) const
{
  return this->publishes_.find (name, result);
}

//
// add_eventconsumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
add_eventconsumer (const char * name, typename SERVANT_BASE::eventconsumer_type * consumer)
{
  this->consumers_.bind (name, consumer);
}

//
// add_eventconsumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
add_eventconsumer (const char * name, EventConsumer * consumer)
{
  typename SERVANT_BASE::eventconsumer_type * ec =
    dynamic_cast < typename SERVANT_BASE::eventconsumer_type * > (consumer);

  if (ec != 0)
    this->add_eventconsumer (name, ec);
}

//
// add_publisher
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
add_publisher (const char * name,
               typename SERVANT_BASE::publisher_type * publisher)
{
  this->emits_.bind (name, publisher);
}

//
// add_publisher
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
add_publisher (const char * name, Publisher * publisher)
{
  typename SERVANT_BASE::publisher_type * p =
    dynamic_cast < typename SERVANT_BASE::publisher_type * > (publisher);

  if (p != 0)
    this->add_publisher (name, p);
}

//
// add_publisher_table
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
add_publisher_table (const char * name,
                     typename SERVANT_BASE::publisher_table_type * publisher_table)
{
  this->publishes_.bind (name, publisher_table);
}

//
// add_publisher_table
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
add_publisher_table (const char * name, Publisher_Table * publisher_table)
{
  typename SERVANT_BASE::publisher_table_type * pt =
    dynamic_cast < typename SERVANT_BASE::publisher_table_type * > (publisher_table);

  if (pt != 0)
    this->add_publisher_table (name, pt);
}

#if !defined (CCM_LW)

//
// get_all_consumers
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::ConsumerDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_emitters (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_name_emitters
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::EmitterDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_publishers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

#endif

#if !defined (CCM_LW)

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::FacetDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_facets (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::FacetDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_facets (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

#endif

#if !defined (CCM_LW)
//
// get_connections
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::ConnectionDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_connections (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_all_receptacles
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::ReceptacleDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_receptacles (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_named_receptacles
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::ReceptacleDescriptions *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_named_receptacles (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

#endif
//
// get_ccm_home
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::CCMHome_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_ccm_home (void)
{
  throw CORBA::NO_IMPLEMENT ();
}


#if !defined (CCM_LW)
//
// same_component
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::CORBA::Boolean
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::same_component (::CORBA::Object_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_component_def
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::CORBA::IRObject_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_component_def (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_primary_key
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::PrimaryKeyBase *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_primary_key (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_all_ports
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE ::Components::ComponentPortDescription *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_all_ports (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

#endif

}
