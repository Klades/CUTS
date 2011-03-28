// -*- C++ -*-

//=============================================================================
/**
 * @file        OpenSplice_Configurator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CONFIGURATOR_H_
#define _CUTS_OPENSPLICE_CONFIGURATOR_H_

#include "ccm/CCM_StandardConfiguratorC.h"
#include "dds_dcps_interfacesC.h"

#include "OpenSplice_Deployment_Handlers_export.h"

// Forward decl.
class CUTS_OpenSplice_Servant;

/**
 * @class CUTS_OpenSplice_Configurator
 */
class CUTS_OSPL_DEPLOYMENT_HANDLERS_Export CUTS_OpenSplice_Configurator
{
public:
  /// Default constructor.
  CUTS_OpenSplice_Configurator (void);

  /// Destructor.
  ~CUTS_OpenSplice_Configurator (void);

  /**
   * Configure an OpenSplice servant.
   */
  int configure (CUTS_OpenSplice_Servant * servant,
                 const ::Components::ConfigValues & config);

private:
  /// Configure the servant's QoS.
  int configure (const char * file, CUTS_OpenSplice_Servant * servant);
};

#endif  // !defined _CUTS_OPENSPLICE_CONFIGURATOR_
