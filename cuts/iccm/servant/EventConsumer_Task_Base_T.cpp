#include "EventConsumer_Task_Base_T.h"
#include "cuts/iccm/configuration/iCCM_Plugin_Manager.h"
#include "cuts/iccm/configuration/Plugins/CPUAffinity.h"

namespace iCCM
{

template <typename EVENT>
EventConsumer_Task_Base_T<EVENT>::EventConsumer_Task_Base_T (void)
  : max_threads_(1)
{
}
template <typename EVENT>
EventConsumer_Task_Base_T<EVENT>::EventConsumer_Task_Base_T (int max_threads)
  : max_threads_ (max_threads)
{
}

template <typename EVENT>
EventConsumer_Task_Base_T<EVENT>::EventConsumer_Task_Base_T (int max_threads, CPU_Mask mask)
  : max_threads_ (max_threads),
    mask_ (mask)
{
}

template <typename EVENT>
EventConsumer_Task_Base_T<EVENT>::~EventConsumer_Task_Base_T (void)
{
}

template <typename EVENT>
void EventConsumer_Task_Base_T<EVENT>::set_max_threads (int max_threads)
{
  max_threads_ = max_threads;
}

template <typename EVENT>
void EventConsumer_Task_Base_T<EVENT>::set_cpu_mask (CPU_Mask mask)
{
  mask_ = mask;
}

template <typename EVENT>
int EventConsumer_Task_Base_T<EVENT>::open (void *)
{
  return this->activate (THR_NEW_LWP, this->max_threads_);
}

template <typename EVENT>
int EventConsumer_Task_Base_T<EVENT>::close (u_long)
{
  if (!this->thr_count ())
  {
    delete this;
  }
  return 0;
}

template <typename EVENT>
void EventConsumer_Task_Base_T<EVENT>::set_affinity (void)
{
  std::string name ("edu.vanderbilt.dre.DAnCE.LocalityManager.CPUAffinity");
  CPU_Affinity * affinity_plugin = 
    reinterpret_cast<CPU_Affinity*>(PLUGIN_MANAGER::instance ()->get_plugin (name));

  affinity_plugin->set_affinity (&mask_);
}
}
