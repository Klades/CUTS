// -*- C++ -*-

#ifndef _RTIDDS_HELLOWORLDC_H_
#define _RTIDDS_HELLOWORLDC_H_

#include "rtidds/HelloWorld_NDDS.h"

#include "HelloWorldC.h"
#include "rtidds/HelloWorld_NDDSSupport.h"
#include "cuts/arch/rtidds/RTIDDS_Traits_T.h"

HELLOWORLD_STUB_Export bool operator <<= (Message &, const ::CUTS_NDDS::Message & );
HELLOWORLD_STUB_Export bool operator >>= (const Message &, ::CUTS_NDDS::Message & );

HELLOWORLD_STUB_Export bool operator <<= (TimeValue &, const ::CUTS_NDDS::TimeValue & );
HELLOWORLD_STUB_Export bool operator >>= (const TimeValue &, ::CUTS_NDDS::TimeValue & );

/**
 * @class CUTS_RTIDDS_Traits_T < ::Message >
 *
 * Trait class for the ::Message event
 */
template < >
class HELLOWORLD_STUB_Export CUTS_RTIDDS_Traits_T < ::CUTS_NDDS::Message >
{
  public:
  // The reader type traits
  typedef ::CUTS_NDDS::MessageDataReader reader_type;
  typedef reader_type * reader_ptr_type;

  // The writer type traits
  typedef ::CUTS_NDDS::MessageDataWriter writer_type;
  typedef writer_type * writer_ptr_type;

  // The DDS event type traits
  typedef ::CUTS_NDDS::Message dds_event_type;
  typedef ::CUTS_NDDS::MessageSeq dds_event_sequence_type;
  typedef ::CUTS_NDDS::MessageTypeSupport dds_typesupport_type;

  // The CORBA event type traits
  typedef ::Message corba_event_type;
  typedef corba_event_type::_var_type corba_event_var_type;
  typedef corba_event_type::_ptr_type corba_event_ptr_type;
  typedef ::OBV_Message corba_obv_event_type;
};

#endif  // _RTIDDS_HELLOWORLDC_H_

