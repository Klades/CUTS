// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_EventConsumer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_OPENSPLICE_EVENTCONSUMER_T_H_
#define _CUTS_ICCM_OPENSPLICE_EVENTCONSUMER_T_H_

#include "OpenSplice_EventConsumer.h"
#include "OpenSplice_Event_Listener_T.h"

namespace iCCM
{

/**
 * @class OpenSplice_EventConsumer_T
 */
template <typename SERVANT, typename EVENT>
class OpenSplice_EventConsumer_T :
  public OpenSplice_EventConsumer
{
public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the listener type.
  typedef OpenSplice_Event_Listener_T <SERVANT, EVENT> listener_type;

  /// Type definition of the event traits.
  typedef typename listener_type::traits_type traits_type;

  /// Type definition of the reader type.
  typedef typename listener_type::reader_type reader_type;

  /// Type definition of the reader _var type.
  typedef typename listener_type::reader_type_var reader_type_var;

  /// Type definition of the servant callback method.
  typedef typename listener_type::DESERIALIZE_METHOD DESERIALIZE_METHOD;

  /**
   * Initializing constructor.
   *
   * @param[in]         servant         The parent servant.
   * @param[in]         callback        Deserialized method on servant.
   */
  OpenSplice_EventConsumer_T (SERVANT * servant,
                                       DESERIALIZE_METHOD callback);

  /// Destructor.
  virtual ~OpenSplice_EventConsumer_T (void);

  // Configure the event consumer object.
  virtual void configure (::DDS::Subscriber_ptr subscriber,
                          const ::DDS::DataReaderQos & qos);

  /**
   * Add a topic to the event consumer. This will results in a new
   * event listener if the topic has not already been added.
   */
  virtual void add_topic (const char * topic);

  /**
   * Remove a topic from the event consumer. This will delete the
   * associated event listener. If the topic does not exist, then
   * nothing happens.
   */
  virtual void remove_topic (const char * topic);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  DESERIALIZE_METHOD callback_;

  /// The concrete reader for this consumer.
  reader_type_var reader_;

  /// Collection of registered listeners.
  ACE_Hash_Map_Manager <ACE_CString,
                        listener_type *,
                        ACE_RW_Thread_Mutex> listeners_;
};

}

#include "OpenSplice_EventConsumer_T.cpp"

#endif  // !definef _CUTS_OPENSPLICE_EVENTCONSUMER_T_H_
