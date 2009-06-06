// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_COMPONENTSERVER_H_
#define _CUTS_CHAOS_CCM_COMPONENTSERVER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "cuts/arch/ccm/CCM_ComponentServer_T.h"
#include "CHAOS_CCM_ComponentServer.h"
#include "CHAOS_CCM_Container.h"

// Forward decl.
class CUTS_CHAOS_CCM_ComponentServer_App;

/// Type definition of the base type.
typedef
  CUTS_CCM_ComponentServer_T <
    CUTS_CHAOS_CCM_ComponentServer,
    CUTS_CHAOS_CCM_Container> CUTS_CHAOS_CCM_ComponentServer_Base;

/**
 * @class CUTS_CHAOS_CCM_ComponentServer
 *
 * Implementation of the CCM component server for CHAOS.
 */
class CUTS_CHAOS_CCM_ComponentServer :
  public CUTS_CHAOS_CCM_ComponentServer_Base
{
public:
  /**
   * Initializing constructor.
   *
   * Application that containers the component server implementation.
   */
  CUTS_CHAOS_CCM_ComponentServer (
    CUTS_CHAOS_CCM_ComponentServer_App * app);

  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_ComponentServer (void);
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_CHAOS_CCM_COMPONENTSERVER_H_
