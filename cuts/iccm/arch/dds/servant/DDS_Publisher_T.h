// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_PUBLISHER_T_H_
#define _ICCM_DDS_PUBLISHER_T_H_

#include "DDS_Publisher.h"
#include "DDS_Stateful_Writer_T.h"

namespace iCCM
{

/**
 * @class DDS_Publisher_T
 *
 * Template version of the DDS publisher object that is bound to
 * an specific event type.
 */
template <typename T, typename EVENT>
class DDS_Publisher_T : public DDS_Publisher <T>
{
public:
  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the DDS entities.
  typedef typename T::template event_traits_type <EVENT>::result_type event_traits_type;
  typedef typename DDS_Publisher <T>::publisher_ptr_type publisher_ptr_type;
  typedef typename DDS_Publisher <T>::topicqos_type topicqos_type;

  /// Default constructor.
  DDS_Publisher_T (void);

  /// Destructor.
  virtual ~DDS_Publisher_T (void);

  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   * @param[in]         topic             Topic for writer
   */
  virtual void configure (publisher_ptr_type publisher,
                          const topicqos_type & topic_qos,
                          const char * topic_name,
                          bool isinstance);

  // Connect the consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /**
   * Publish a CORBA event. This method will transform the CORBA event
   * to a DDS event before publishing it over the network.
   *
   * @param[in]         ev            The event to send
   */
  void send_event (EVENT * ev);

  /// Allocate a new event.
  EVENT * allocate_event (void);

protected:
  typedef DDS_Stateful_Writer_T <T, EVENT> writer_type;

  ACE_Auto_Ptr <writer_type> writer_;

  /// Type specific writer for the publisher.
//  typename event_traits_type::writer_var_type writer_;

  /// The instance handle for the writer.
//  typename T::instancehandle_type inst_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Publisher_T.inl"
#endif

#include "DDS_Publisher_T.cpp"

#endif  // !defined _ICCM_DDS_PUBLISHER_T_H_

