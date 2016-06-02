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
#include "iCCM_CPU_Affinity_export.h"

namespace iCCM
{
  class iCCM_CPU_Affinity : public iCCM_Plugin
  {
  public:
    iCCM_CPU_Affinity (void);

    virtual ~iCCM_CPU_Affinity (void);

    virtual void configure (const ::Deployment::Property & prop);
  };
}

extern "C" ICCM_CPU_AFFINITY_Export iCCM::iCCM_Plugin * create_CPUAffinity_plugin (void);

#include "ace/post.h"
#endif