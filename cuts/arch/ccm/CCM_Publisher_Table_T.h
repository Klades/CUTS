// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_CCM_SUBSCRIBER_TABLE_H_

#include "ace/UUID.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Hash_Map_Manager.h"

#include "CCM_Publisher_Table.h"

/**
 * @class CUTS_CCM_Publisher_Table_T
 *
 * Template version of the publisher table that is bound to a specific
 * event type. The event type is determined by the parameter.
 */
template <typename BASE, typename PUBLISHER>
class CUTS_CCM_Publisher_Table_T : public BASE
{
public:
  /// Type definition of the publisher type.
  typedef PUBLISHER publisher_type;

  /// Type definition of the event type.
  typedef typename PUBLISHER::event_type event_type;

  /// Default constructor.
  CUTS_CCM_Publisher_Table_T (void);

  /// Destructor.
  virtual ~CUTS_CCM_Publisher_Table_T (void);

  // Subscribe the consumer.
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  // Unsubscribe a consumer.
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  /**
   * Send an event to all the subscribed consumers.
   *
   * @param[in]         ev          The event to publish
   */
  virtual void send_event (event_type * ev) = 0;

protected:
  /// Type definition of the consumer map.
  typedef ACE_Hash_Map_Manager <ACE_Utils::UUID,
                                PUBLISHER *,
                                ACE_RW_Thread_Mutex> consumer_table_t;

  /// The collection of consumers.
  consumer_table_t table_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Publisher_Table_T.inl"
#endif

#include "CCM_Publisher_Table_T.cpp"

#endif  // !defined _CUTS_CCM_SUBSCRIBER_TABLE_H_
