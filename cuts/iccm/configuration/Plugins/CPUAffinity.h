/**
 * @file CPUAffinity.h
 * @author Alan J. Unger
 *
 * Configuration plugin that will set the affinity of the current thread
 */

#ifndef ICCM_CPU_AFFINITY_H_
#define ICCM_CPU_AFFINITY_H_

#include "ace/pre.h"

#include "dance/DAnCE_LocalityManagerC.h"
#include "iCCM_Plugin.h"
#include "iCCM_Plugins_export.h"
#include "CPU_Mask.h"

namespace iCCM
{
  class CPU_Affinity : public Plugin
  {
  public:
    /// Constructor
    CPU_Affinity (void);

    /// Destructor
    virtual ~CPU_Affinity (void);

    /*
     * Processes a Deployment::Property
     * @param[in]   prop    Property to process
     */
    virtual void configure (const ::Deployment::Property & prop);
    /*
     * Sets the CPU affinity of the current process
     * @param[in]   mask    The CPU affinity to set
     */
    int set_affinity (CPU_Mask * mask);
  };
}

extern "C" ICCM_PLUGINS_Export iCCM::Plugin * create_CPUAffinity_plugin (void);

#include "ace/post.h"
#endif