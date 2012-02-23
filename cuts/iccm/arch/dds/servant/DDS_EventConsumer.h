// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_EVENTCONSUMER_H_
#define _ICCM_DDS_EVENTCONSUMER_H_

#include "cuts/iccm/servant/EventConsumer.h"
#include "DDS_EventsC.h"

namespace iCCM
{

/**
 * @class DDS_EventConsumer
 */
template <typename T>
class DDS_EventConsumer :
  public virtual T::corba_poa_eventconsumer_type,
  public virtual EventConsumer
{
public:
  /// Type definition of the DDS entities.
  typedef typename T::subscriber_ptr_type subscriber_ptr_type;
  typedef typename T::topic_ptr_type topic_ptr_type;
  typedef typename T::topicqos_type topicqos_type;
  typedef typename T::datareader_ptr_type datareader_ptr_type;
  typedef typename T::datareader_var_type datareader_var_type;
  typedef typename T::datareaderqos_type datareaderqos_type;

  /// Default constructor.
  DDS_EventConsumer (void);

  /// Destructor.
  virtual ~DDS_EventConsumer (void);

  /**
   * Configure the event consumer. This method stores the target
   * subscriber and QoS parameter for future data readers that will
   * be created for each connection.
   *
   * @param[in]         subscriber        DDS subscriber entity
   * @param[in]         qos               Data reader QoS
   */
  virtual void configure (subscriber_ptr_type subscriber,
                          const topicqos_type & topic_qos,
                          const datareaderqos_type & qos) = 0;

  /// Test if the consumer has been configured.
  bool is_configured (void) const;

  /// Get the data reader.
  datareader_ptr_type get_datareader (void);

protected:
  /// The parent subscriber.
  subscriber_ptr_type subscriber_;

  /// The abstract reader for the event consumer.
  datareader_var_type abs_reader_;

  /// QoS parameters for the data reader.
  const datareaderqos_type * reader_qos_;

  /// Topic QoS for the data reader.
  const topicqos_type * topic_qos_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_EventConsumer.inl"
#endif

#include "DDS_EventConsumer.cpp"

#endif  // !defined _ICCM_DDS_EVENTCONSUMER_H_
