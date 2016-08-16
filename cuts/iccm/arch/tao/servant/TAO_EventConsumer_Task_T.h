#ifndef _TAO_EVENTCONSUMER_TASK_H_
#define _TAO_EVENTCONSUMER_TASK_H_

#include "cuts/iccm/servant/EventConsumer_Task_Base_T.h"

namespace iCCM
{
  template <typename SERVANT, typename EVENT>
  class TAO_EventConsumer_Task_T : public EventConsumer_Task_Base_T<EVENT>
  {
  public:
    typedef void (SERVANT::*CALLBACK_METHOD) (EVENT *);

    TAO_EventConsumer_Task_T (SERVANT * servant, CALLBACK_METHOD callback);

    int svc (void);

  private:
    SERVANT * servant_;

    CALLBACK_METHOD callback_;
  };
}

#include "TAO_EventConsumer_Task_T.cpp"
#endif
