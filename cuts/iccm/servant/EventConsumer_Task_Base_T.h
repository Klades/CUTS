#ifndef _CUTS_EVENTCONSUMER_TASK_BASE_T_H_
#define _CUTS_EVENTCONSUMER_TASK_BASE_T_H_

#include "ace/Task_Ex_T.h"
#include "ace/Synch.h"
#include "cuts/iccm/configuration/Plugins/CPU_Mask.h"

namespace iCCM 
{
template <typename EVENT>
class EventConsumer_Task_Base_T : public ACE_Task_Ex<ACE_MT_SYNCH, EVENT>
{
public:
  /**
   * Non-CPU binding constructor
   * @param[in]   max_threads   Maximum number of threads for this task to spawn
   */
  EventConsumer_Task_Base_T (int max_threads);

  /**
   * CPU binding constructor
   * @param[in]   max_threads   Maximum number of threads for this task to spawn
   * @param[in]   mask          CPU mask to bind threads to. The task takes ownership.
   */
  EventConsumer_Task_Base_T (int max_threads, CPU_Mask * mask);
  
  /// Destructor
  virtual ~EventConsumer_Task_Base_T (void);

  /// Begin the task
  int open (void * args = 0);

  /// Method for the threads to run
  virtual int svc (void) = 0;

protected:
  /// Flag indicating if CPU affinity should be set
  bool setting_affinity_;

  /// To be called in svc to set each thread's CPU affinity
  void set_affinity (void);

  /// Called by threads which have exited
  int close (u_long flags = 0);

private:
  /// Maximum number of threads to spawn
  int max_threads_;

  /// Mask to use when setting CPU affinity
  CPU_Mask * mask_;
};
}

#include "EventConsumer_Task_Base_T.cpp"
#endif
