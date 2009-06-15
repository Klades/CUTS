// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Subscriber_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_CCM_SUBSCRIBER_TABLE_H_

#include "CCM_Subscriber_Table.h"

/**
 * @class CUTS_CCM_Subscriber_Table_T
 */
template <typename T>
class CUTS_CCM_Subscriber_Table_T : public CUTS_CCM_Subscriber_Table
{
public:
  CUTS_CCM_Subscriber_Table_T (void);

  virtual ~CUTS_CCM_Subscriber_Table_T (void);

  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  void send_event (T * ev);

private:
  typedef ACE_Hash_Map_Manager <ACE_Utils::UUID,
                                CUTS_CCM_Single_Subscriber_T <T> *,
                                ACE_RW_Thread_Mutex> table_type;

  table_type table_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Subscriber_Table_T.inl"
#endif

#include "CCM_Subscriber_Table_T.cpp"

#endif  // !defined _CUTS_CCM_SUBSCRIBER_TABLE_H_
