#ifndef _DDS_EVENTCONSUMER_TASK_T_H_
#define _DDS_EVENTCONSUMER_TASK_T_H_

#include "cuts/iccm/servant/EventConsumer_Task_Base_T.h"
#include "EventPackage.h"
#include "cuts/iccm/configuration/Plugins/CPU_Mask.h"

namespace iCCM
{
  class DDS_Event_Listener_T;

  template <typename SERVANT, typename EVENT, typename PACKAGE, typename UPCALL>
  class DDS_EventConsumer_Task_T : public EventConsumer_Task_Base_T<PACKAGE>
  {
    public:
      typedef void (SERVANT::*DESERIALIZE_METHOD) (EVENT *);

      DDS_EventConsumer_Task_T (SERVANT * servant, DESERIALIZE_METHOD callback, int max_threads = 1);

      DDS_EventConsumer_Task_T (SERVANT * servant, DESERIALIZE_METHOD callback, CPU_Mask * mask, int max_threads = 1);

      virtual ~DDS_EventConsumer_Task_T (void);

      int svc (void);

    private:
      SERVANT * servant_;
      DESERIALIZE_METHOD callback_;
  };

}

#include "DDS_EventConsumer_Task_T.cpp"
#endif
