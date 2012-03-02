// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Publisher.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_DDS_PUBLISHER_H_
#define _CUTS_ICCM_DDS_PUBLISHER_H_

#include "cuts/iccm/servant/Publisher.h"
#include "DDS_EventsC.h"

namespace iCCM
{

/**
 * @class DDS_Publisher
 *
 * The base class for all DDS publishers that are integrated into
 * the CCM architecture. In essence, this class is an adapter class that
 * allows a DDS publisher to integrate with the CCM architecture.
 */
template <typename T>
class DDS_Publisher : public Publisher
{
public:
  /// Type definition of the DDS entities.
  typedef typename T::publisher_ptr_type publisher_ptr_type;
  typedef typename T::topicqos_type topicqos_type;
  typedef typename T::topic_ptr_type topic_ptr_type;
  typedef typename T::datawriter_ptr_type datawriter_ptr_type;
  typedef typename T::datawriter_var_type datawriter_var_type;

  /// Default constructor.
  DDS_Publisher (void);

  /// Destructor.
  virtual ~DDS_Publisher (void);

  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   * @param[in]         topic             Topic for writer
   */
  virtual void configure (publisher_ptr_type publisher,
                          const topicqos_type & topic_qos,
                          const char * topic_name) = 0;

  /// Get the container data writer for this publisher.
  datawriter_ptr_type get_datawriter (void);

  /// Test if the publisher is configured.
  bool is_configured (void) const;

  // Connect a consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  // Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   * @param[in]         topic             Topic for writer
   */
  void configure (publisher_ptr_type publisher, topic_ptr_type topic);

  /// The consumer connected to this publisher.
  ::Components::DDS::EventConsumer_var consumer_;

  /// The writer assigned to this publisher.
  datawriter_var_type abs_writer_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Publisher.inl"
#endif

#include "DDS_Publisher.cpp"

#endif  // !defined _CUTS_ICCM_DDS_PUBLISHER_H_
