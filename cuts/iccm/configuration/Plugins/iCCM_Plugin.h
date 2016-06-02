/**
 * @file iCCM_Plugin.h
 * @author Alan J. Unger
 *
 * Abstract base class for iCCM Plugins
 */
#ifndef ICCM_PLUGIN_H_
#define ICCM_PLUGIN_H_

#include "dance/DAnCE_LocalityManagerC.h"
#include <string>

namespace iCCM
{
  class iCCM_Plugin
  {
  protected:
    iCCM_Plugin (std::string);

  public:
    virtual ~iCCM_Plugin (void);

    std::string name (void);
    virtual void configure (const ::Deployment::Property & prop) = 0;
    void destroy (void);

  private:
    std::string name_;
  };
}

#endif