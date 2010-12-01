// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CONFIGURATOR_H_
#define _CUTS_RTIDDS_CONFIGURATOR_H_

#include "ccm/CCM_StandardConfiguratorC.h"

// Forward decl.
class CUTS_RTIDDS_Servant;

/**
 * @class CUTS_RTIDDS_Configurator
 */
class CUTS_RTIDDS_Configurator
{
public:
  /// Default constructor.
  CUTS_RTIDDS_Configurator (void);

  /// Destructor.
  ~CUTS_RTIDDS_Configurator (void);

  int configure (CUTS_RTIDDS_Servant * servant,
                 const ::Components::ConfigValues & config);
};

#endif  // !defined _CUTS_RTIDDS_CONFIGURATOR_
