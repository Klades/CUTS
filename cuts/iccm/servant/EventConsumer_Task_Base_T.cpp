#include "EventConsumer_Task_Base_T.h"
#include "cuts/iccm/configuration/iCCM_Plugin_Manager.h"
#include "cuts/iccm/configuration/Plugins/CPUAffinity.h"

namespace iCCM
{
template <typename EVENT>
EventConsumer_Task_Base_T::EventConsumer_Task_Base_T (int max_threads)
  : setting_affinity_ (false)
  , max_threads_ (max_threads)
  , mask_ (0)
{
}

template <typename EVENT>
EventConsumer_Task_Base_T::EventConsumer_Task_Base_T (int max_threads, CPU_Mask * mask)
  : setting_affinity_ (true)
  , max_threads_ (max_threads)
  , mask_ (mask)
{
}

template <typename EVENT>
EventConsumer_Task_Base_T::~EventConsumer_Task_Base_T (void)
{
  delete mask_;
}

template <typename EVENT>
int EventConsumer_Task_Base_T::open (void * args = 0)
{
  return activate (THR_NEW_LWP, this->max_threads_);
}

template <typename EVENT>
int EventConsumer_Task_Base_T::close (u_long flags = 0)
{
  if (!thr_count ())
  {
    delete this;
  }
  return 0;
}

template <typename EVENT>
void EventConsumer_Task_Base_T::set_affinity (void)
{
  std::string name ("edu.vanderbilt.dre.DAnCE.LocalityManager.CPUAffinity");
  CPU_Affinity * affinity_plugin = 
    reinterpret_cast<CPU_Affinity*>(PLUGIN_MANAGER::instance ()->get_plugin (name));

  affinity_plugin->set_affinity (mask_);
}
}