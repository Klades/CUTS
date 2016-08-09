#ifndef _CUTS_EVENTCONSUMER_TASK_BASE_
#define _CUTS_EVENTCONSUMER_TASK_BASE_

namespace iCCM
{
class CPU_Mask;

class EventConsumer_Task_Base
{
public:
  virtual void set_max_threads (int max_threads) = 0;
  virtual void set_cpu_mask (CPU_Mask * mask) = 0;
};
}
#endif
