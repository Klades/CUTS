// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_DDS_PUBLISHER_TABLE_T_H_
#define _CUTS_ICCM_DDS_PUBLISHER_TABLE_T_H_

#include "cuts/iccm/servant/Publisher_Table_T.h"

#include "DDS_Publisher_Table.h"
#include "DDS_Publisher_T.h"

namespace iCCM
{

/**
 * @class DDS_Publisher_Table_T
 */
template <typename T, typename EVENT>
class DDS_Publisher_Table_T :
  public Publisher_Table_T < typename T::publisher_table_type,
                             typename T::template typed_publisher_type <EVENT>::result_type,
                             false >
{
public:
  /// Type definition of the base type.
  typedef Publisher_Table_T < typename T::publisher_table_type,
                              typename T::template typed_publisher_type <EVENT>::result_type,
                              false> base_type;

  /// Type definition of the DDS entities.
  typedef typename T::template event_traits_type <EVENT>::result_type event_traits_type;
  typedef typename T::publisher_ptr_type publisher_ptr_type;
  typedef typename T::topicqos_type topicqos_type;
  typedef typename T::datawriterqos_type datawriterqos_type;
  typedef typename T::topic_ptr_type topic_ptr_type;
  typedef typename T::datawriter_ptr_type datawriter_ptr_type;
  typedef typename T::datawriter_var_type datawriter_var_type;

  /// Default constructor.
  DDS_Publisher_Table_T (void);

  /// Destructor.
  virtual ~DDS_Publisher_Table_T (void);

  /**
   * Configure the publisher table. This means that all connections
   * in this table use the specified publisher.
   *
   * @param[in]         publisher         Target publisher
   * @param[in]         topic_name        Topic name for writer
   */
  virtual void configure (publisher_ptr_type publisher,
                          const datawriterqos_type & datawriter_qos,
                          const topicqos_type & qos,
                          const char * topic_name,
                          bool isinstance);

  /**
   * Subscribe an event consumer.
   *
   * @param[in]       consumer      Consumer for this connection
   * @return          Cookie for the connection
   */
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  /**
   * Unsubscribe an event consumer.
   *
   * @param[in]       cookie        Cookie associate with consumer
   * @return          Consumer associated with cookie
   */
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  /// Send an event.
  void send_event (EVENT * ev);

  /// Allocate a new event.
  EVENT * allocate_event (void);

  // Activate the publisher table
  virtual void activate (void);

  // Passivate the publisher table
  virtual void passivate (void);

protected:
  typedef DDS_Stateful_Writer_T <T, EVENT> writer_type;

  ACE_Auto_Ptr <writer_type> writer_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Publisher_Table_T.inl"
#endif

#include "DDS_Publisher_Table_T.cpp"

#endif  // !defined _CUTS_ICCM_DDS_PUBLISHER_TABLE_T_H_
