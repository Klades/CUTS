// $Id$

#if !defined (__CUTS_INLINE__)
#include "CHAOS_CCM_Servant_T.inl"
#endif

#include "cuts/arch/opensplice/ccm/OpenSplice_EventConsumer.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_Subscriber.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_Subscriber_Table.h"

//
// table_
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_TCPIP_Servant_VTable_T <T>
CUTS_CHAOS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::table_;

//
// handle_event
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
int CUTS_CHAOS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
handle_event (ACE_UINT32 id, CUTS_TCPIP_InputCDR & input)
{
  static T * self = dynamic_cast <T *> (this);

  if (0 != self)
  {
    if (id < this->table_.size ())
      return (this->table_[id]) (self, input);
  }

  return -1;
}

//
// configure
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void CUTS_CHAOS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
configure (::DDS::DomainParticipant_ptr participant)
{
  typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);
  CUTS_OpenSplice_CCM_EventConsumer * ospl_consumer = 0;

  for (; !consumer_iter.done (); ++ consumer_iter)
  {
    // Try and cast the object to a OpenSplice event consumer.
    ospl_consumer = dynamic_cast <CUTS_OpenSplice_CCM_EventConsumer *> (consumer_iter->item ());

    if (0 != ospl_consumer)
    {
      // Now, configure the servant for this participant.
      ospl_consumer->configure (participant,
                                this->name_.c_str (),
                                consumer_iter->key ().c_str ());
    }
  }

  typename emits_map_type::ITERATOR emits_iter (this->emits_);
  CUTS_OpenSplice_CCM_Subscriber * ospl_subscriber = 0;

  for (; !emits_iter.done (); ++ emits_iter)
  {
    // Try and cast the object to an OpenSplice subscriber.
    ospl_subscriber = dynamic_cast <CUTS_OpenSplice_CCM_Subscriber *> (emits_iter->item ());

    if (0 != ospl_subscriber)
      ospl_subscriber->configure (participant);
  }

  // Pass control to the base class.
  CUTS_CHAOS_Servant::configure (participant);
}

//
// configure
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void CUTS_CHAOS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
configure (::DDSDomainParticipant * particpant)
{
  typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);
  CUTS_RTIDDS_CCM_EventConsumer * ndds_consumer = 0;

  for (; !consumer_iter.done (); ++ consumer_iter)
  {
    // Try and cast the object to a OpenSplice event consumer.
    ndds_consumer = dynamic_cast <CUTS_RTIDDS_CCM_EventConsumer *> (consumer_iter->item ());

    // Now, configure the servant for this participant.
    if (0 != ndds_consumer)
      ndds_consumer->configure (participant,
                                this->name_.c_str (),
                                consumer_iter->key ().c_str ());
  }

  typename emits_map_type::ITERATOR emits_iter (this->emits_);
  CUTS_RTIDDS_CCM_Subscriber * ndds_subscriber = 0;

  for (; !emits_iter.done (); ++ emits_iter)
  {
    // Try and cast the object to an OpenSplice subscriber.
    ndds_subscriber = dynamic_cast <CUTS_RTIDDS_CCM_Subscriber *> (emits_iter->item ());

    if (0 != ndds_subscriber)
      ndds_subscriber->configure (participant);
  }

  // Pass control to the base class.
  CUTS_CHAOS_Servant::configure (participant);
}
