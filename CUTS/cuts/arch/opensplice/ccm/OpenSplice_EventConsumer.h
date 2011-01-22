// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_

#include "OpenSplice_EventsS.h"
#include "cuts/arch/ccm/CCM_EventConsumer.h"
#include "cuts/arch/opensplice/OpenSplice_ListenerBase.h"
#include "cuts/arch/opensplice/OpenSplice_Endpoint.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_EventConsumer
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_EventConsumer :
  public virtual CUTS_CCM_EventConsumer,
  public virtual ::POA_Components::OpenSplice::EventConsumer,
  public CUTS_OpenSplice_ListenerBase
{
public:
  /// Default constructor.
  CUTS_OpenSplice_CCM_EventConsumer (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_EventConsumer (void);

  virtual int configure (::DDS::Subscriber_ptr subscriber,
                         const char * inst,
                         const char * topic_name) = 0;

  /// Close the event consumer.
  virtual int close (void);

  /// Get the topic description for this event consumer.
  virtual ::Components::OpenSplice::TopicDescription * topic_description (void);

protected:
  /**
   * Open the event consumer for this type.
   *
   * @param[in]       type_support        The type support system
   * @param[in]       topic_name          Name of the topic
   */
  int open_i (::DDS::TypeSupport_ptr type, const char * topic_name);

  /// The endpoint for this consumer.
  CUTS_OpenSplice_Endpoint endpoint_;

  /// The participant assigned to this consumer.
  ::DDS::Subscriber_var subscriber_;

  /// The abstract reader for the event consumer.
  ::DDS::DataReader_var abstract_reader_;
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_EventConsumer.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
