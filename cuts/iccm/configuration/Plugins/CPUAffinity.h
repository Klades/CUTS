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

namespace iCCM
{
  class CPU_Affinity : public Plugin
  {
  public:
    CPU_Affinity (void);

    virtual ~CPU_Affinity (void);

    virtual void configure (const ::Deployment::Property & prop);
  };
}

extern "C" ICCM_PLUGINS_Export iCCM::Plugin * create_CPUAffinity_plugin (void);

#include "ace/post.h"
#endif