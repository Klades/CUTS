/**
 * @file    iCCM_Plugin_Manager.h
 *
 * @author  Alan J. Unger
 */

#ifndef CUTS_ICCM_PLUGIN_MANAGER_H_
#define CUTS_ICCM_PLUGIN_MANAGER_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif

#include "ace/Singleton.h"

#include "dance/Deployment/Deployment_BaseC.h"
#include "dance/DAnCE_LocalityManagerC.h"
#include "iCCM_Plugin_Manager_export.h"
#include <map>
#include <string>

namespace iCCM
{
  // Forward declaration
  class Plugin;

  /**
   * @class iCCM_Plugin_Manager
   * Manages plugins and handles Deployment Properties for Locality Managers, containers, and components
   */
  class ICCM_PLUGIN_MANAGER_Export Plugin_Manager
  {
  public:
    typedef std::map <std::string, Plugin *> PLUGIN_MAP;

    Plugin_Manager (void);
    ~Plugin_Manager (void);

    /**
     * Register a plugin
     * @param[in]   artifact    Name of shared library
     * @param[in]   entrypoint  Name of plugin
     */
    void register_plugin (const char * artifact,
                          const char * entrypoint);

    /**
     * Process a set of properties for the current context
     * Will process each property that a plugin exists to handle
     * @param[in]   props     Collection of properties to process
     */
    void handle_properties (const ::Deployment::Properties & props);

  private:
    /// Plugin collection
    PLUGIN_MAP plugins_;
  };

  typedef ACE_Singleton <Plugin_Manager, ACE_SYNCH_MUTEX> PLUGIN_MANAGER;
}

ACE_EXPORT_SINGLETON_DECLARE (ACE_Singleton, iCCM::Plugin_Manager, ACE_SYNCH_MUTEX)
#endif