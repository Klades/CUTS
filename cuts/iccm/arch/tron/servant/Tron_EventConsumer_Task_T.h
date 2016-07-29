#ifndef _TRON_EVENTCONSUMER_TASK_H_
#define _TRON_EVENTCONSUMER_TASK_H_

#include "cuts/iccm/servant/EventConsumer_Task_Base_T.h"

namespace iCCM
{
  template <typename SERVANT, typename EVENT>
  class Tron_EventConsumer_Task_T : public EventConsumer_Task_Base_T<EVENT>
  {
    public:
      typedef void (SERVANT::*CALLBACK_METHOD) (EVENT *);

      Tron_EventConsumer_Task_T (SERVANT * servant, CALLBACK_METHOD callback, int max_threads = 1);

      Tron_EventConsumer_Task_T (SERVANT * servant, CALLBACK_METHOD callback, CPU_Mask * mask, int max_threads = 1);

      int svc (void);

    private:
      SERVANT * servant_;
      CALLBACK_METHOD callback_;
  };
}

#include "Tron_EventConsumer_Task_T.cpp"
#endif
