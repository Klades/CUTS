// -*- C++ -*-

#ifndef _OPENSPLICE_HELLOWORLDC_H_
#define _OPENSPLICE_HELLOWORLDC_H_

#include "HelloWorldC.h"
#include "ddstypes/HelloWorld_OSPLDcps_impl.h"
#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"

HELLOWORLD_STUB_Export bool operator <<= (Message &, const ::CUTS_OSPL::Message & );
HELLOWORLD_STUB_Export bool operator >>= (const Message &, ::CUTS_OSPL::Message & );

HELLOWORLD_STUB_Export bool operator <<= (TimeValue &, const ::CUTS_OSPL::TimeValue & );
HELLOWORLD_STUB_Export bool operator >>= (const TimeValue &, ::CUTS_OSPL::TimeValue & );

/**
 * @class CUTS_OpenSplice_Traits_T < ::Message >
 *
 * Trait class for the ::Message event
 */
template < >
class HELLOWORLD_STUB_Export CUTS_OpenSplice_Traits_T < ::CUTS_OSPL::Message >
{
  public:
  // The reader type traits
  typedef ::CUTS_OSPL::MessageDataReader reader_type;
  typedef reader_type::_ptr_type reader_ptr_type;
  typedef reader_type::_var_type reader_var_type;

  // The writer type traits
  typedef ::CUTS_OSPL::MessageDataWriter writer_type;
  typedef writer_type::_ptr_type writer_ptr_type;
  typedef writer_type::_var_type writer_var_type;

  // The DDS event type traits
  typedef ::CUTS_OSPL::Message dds_event_type;
  typedef ::CUTS_OSPL::MessageSeq dds_event_sequence_type;
  typedef ::CUTS_OSPL::MessageSeq_var dds_event_sequence_var_type;

  typedef ::CUTS_OSPL::MessageTypeSupportInterface dds_typesupport_interface_type;
  typedef dds_typesupport_interface_type::_var_type dds_typesupport_interface_var_type;
  typedef dds_typesupport_interface_type::_ptr_type dds_typesupport_interface_ptr_type;

  typedef ::CUTS_OSPL::MessageTypeSupport dds_typesupport_type;
  typedef ::CUTS_OSPL::MessageTypeSupport_var dds_typesupport_var_type;

  // The CORBA event type traits
  typedef ::Message corba_event_type;
  typedef corba_event_type::_var_type corba_event_var_type;
  typedef corba_event_type::_ptr_type corba_event_ptr_type;
  typedef ::OBV_Message corba_obv_event_type;
};

#endif  // _OPENSPLICE_HELLOWORLDC_H_

