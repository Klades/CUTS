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

#include "iCCM_CPU_Affinity_export.h"

namespace iCCM
{
  class ICCM_CPU_AFFINITY_Export iCCM_CPU_Affinity : public virtual DAnCE::LocalityConfiguration
  {
  public:
    iCCM_CPU_Affinity (void);

    virtual ~iCCM_CPU_Affinity (void);

    virtual char * type (void);

    virtual void configure (const ::Deployment::Property & prop);
  };
}

extern "C"
{
  DAnCE::LocalityConfiguration_ptr ICCM_CPU_AFFINITY_Export create_CPUAffinity_plugin (void);
}

#include "ace/post.h"
#endif