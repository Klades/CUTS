// -*- C++ -*-
// $Id$


CUTS_INLINE
::Components::Cookie * CUTS_TCPIP_CCM_Events_Impl::
subscribe (const char * publisher_name, ::Components::EventConsumerBase_ptr subscriber)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
::Components::EventConsumerBase_ptr CUTS_TCPIP_CCM_Events_Impl::
unsubscribe (const char * publisher_name, ::Components::Cookie * ck)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::EventConsumerBase_ptr CUTS_TCPIP_CCM_Events_Impl::
get_consumer (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
void CUTS_TCPIP_CCM_Events_Impl::
connect_consumer (const char *, Components::EventConsumerBase_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Events_Impl::
disconnect_consumer (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::ConsumerDescriptions *
CUTS_TCPIP_CCM_Events_Impl::
get_all_consumers (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::ConsumerDescriptions *
CUTS_TCPIP_CCM_Events_Impl::
get_named_consumers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::EmitterDescriptions *
CUTS_TCPIP_CCM_Events_Impl::
get_all_emitters (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::EmitterDescriptions *
CUTS_TCPIP_CCM_Events_Impl::
get_named_emitters (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::PublisherDescriptions *
CUTS_TCPIP_CCM_Events_Impl::
get_all_publishers (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

CUTS_INLINE
Components::PublisherDescriptions *
CUTS_TCPIP_CCM_Events_Impl::
get_named_publishers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}
