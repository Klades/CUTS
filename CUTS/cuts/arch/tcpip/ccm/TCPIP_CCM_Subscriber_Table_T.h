// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Subscriber_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_SUBSCRIBER_TABLE_T_H_
#define _CUTS_TCPIP_CCM_SUBSCRIBER_TABLE_T_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/UUID.h"
#include "TCPIP_CCM_Remote_Endpoint_T.h"
#include "TCPIP_CCM_Subscriber_Table.h"

/**
 * @class CUTS_TCPIP_CCM_Subscriber_Table_T
 */
template <typename T>
class CUTS_TCPIP_CCM_Subscriber_Table_T :
  public CUTS_TCPIP_CCM_Subscriber_Table
{
public:
  CUTS_TCPIP_CCM_Subscriber_Table_T (void);

  virtual ~CUTS_TCPIP_CCM_Subscriber_Table_T (void);

  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr consumer);

  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie * cookie);

  void send_event (T * ev);

private:
  typedef ACE_Hash_Map_Manager <ACE_Utils::UUID,
                                CUTS_TCPIP_CCM_Subscriber_T <T> *,
                                ACE_RW_Thread_Mutex> table_type;

  table_type table_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Subscriber_Table_T.inl"
#endif

#include "TCPIP_CCM_Subscriber_Table_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_SUBSCRIBER_TABLE_T_H_
