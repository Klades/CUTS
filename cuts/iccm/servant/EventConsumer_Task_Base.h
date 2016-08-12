#ifndef _CUTS_EVENTCONSUMER_TASK_BASE_
#define _CUTS_EVENTCONSUMER_TASK_BASE_

#include "cuts/iccm/configuration/Plugins/CPU_Mask.h"
namespace iCCM
{

class EventConsumer_Task_Base
{
public:
  virtual ~EventConsumer_Task_Base (void);

  virtual void set_max_threads (int max_threads) = 0;
  virtual void set_cpu_mask (CPU_Mask * mask) = 0;
  virtual int open (void * args = 0) = 0;
};
}
#endif
