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
  CUTS_OpenSplice_CCM_EventConsumer * consumer = 0;

  for (; !consumer_iter.done (); ++ consumer_iter)
    {
      // Try and cast the object to a OpenSplice event consumer.
      consumer = dynamic_cast <CUTS_OpenSplice_CCM_EventConsumer *> (consumer_iter->item ());

      if (0 != consumer)
        {
          // Now, configure the servant for this participant.
	  consumer->configure (participant,
                               this->name_.c_str (),
                               consumer_iter->key ().c_str ());
        }
    }

  typename emits_map_type::ITERATOR emits_iter (this->emits_);
  CUTS_OpenSplice_CCM_Subscriber * subscriber = 0;

  for (; !emits_iter.done (); ++ emits_iter)
    {
      // Try and cast the object to an OpenSplice subscriber.
      subscriber = dynamic_cast <CUTS_OpenSplice_CCM_Subscriber *> (emits_iter->item ());

      if (0 != subscriber)
	subscriber->configure (participant);
    }

  // Pass control to the base class.
  CUTS_OpenSplice_Servant::configure (participant);
}
