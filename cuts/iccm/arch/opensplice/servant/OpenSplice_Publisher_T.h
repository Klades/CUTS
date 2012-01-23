// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_PUBLISHER_T_H_
#define _CUTS_OPENSPLICE_CCM_PUBLISHER_T_H_

#include "OpenSplice_Publisher.h"
#include "OpenSplice_Traits_T.h"

#include "OpenSplice_EventsC.h"

namespace iCCM
{

/**
 * @class OpenSplice_Publisher_T
 *
 * Template version of the OpenSplice publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class OpenSplice_Publisher_T :
  public OpenSplice_Publisher
{
public:
  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the traits for this object.
  typedef OpenSplice_Traits_T <EVENT> traits_type;

  /// Default constructor.
  OpenSplice_Publisher_T (void);

  /// Destructor.
  virtual ~OpenSplice_Publisher_T (void);

  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   * @param[in]         topic             Topic for writer
   */
  virtual void configure (::DDS::Publisher_ptr pub, const ACE_CString & topic_name);

  // Connect the consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /**
   * Publish a CORBA event. This method will transform the CORBA event
   * to a DDS event before publishing it over the network.
   *
   * @param[in]         ev            The event to send
   */
  void send_event (EVENT * ev);

  /**
   * Publish a DDS event.
   *
   * @param[in]         ev            The event to publish
   */
  void send_event (typename traits_type::dds_event_type & ev);

  EVENT * allocate_event (void);

protected:
  /// Type specific writer for the publisher.
  typename traits_type::writer_type_var writer_;
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher_T.inl"
#endif

#include "OpenSplice_Publisher_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_

