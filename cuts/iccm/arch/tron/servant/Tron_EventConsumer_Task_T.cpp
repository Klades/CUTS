#include "Tron_EventConsumer_Task_T.h"

namespace iCCM 
{
 
template<typename SERVANT, typename EVENT>
Tron_EventConsumer_Task_T<SERVANT, EVENT>::Tron_EventConsumer_Task_T (
    SERVANT * servant, CALLBACK_METHOD callback, int max_threads)
  : EventConsumer_Task_Base_T<EVENT>(max_threads)
  , servant_(servant)
  , callback_(callback)
{}

template<typename SERVANT, typename EVENT>
Tron_EventConsumer_Task_T<SERVANT, EVENT>::Tron_EventConsumer_Task_T (
    SERVANT * servant, CALLBACK_METHOD callback, CPU_Mask * mask, int max_threads)
  : EventConsumer_Task_Base_T<EVENT>(max_threads, mask)
  , servant_(servant)
  , callback_(callback)
{}

template<typename SERVANT, typename EVENT>
int Tron_EventConsumer_Task_T<SERVANT, EVENT>::svc (void)
{
  this->set_affinity();

  EVENT * ev;

  while (getq(ev))
  {
    (*this->servant_.*this->callback_) (ev);
    CORBA::remove_ref(ev);
  }

  return 0;
}

}
