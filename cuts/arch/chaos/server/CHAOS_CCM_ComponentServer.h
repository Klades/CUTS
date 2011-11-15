// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_COMPONENTSERVER_H_
#define _CUTS_CHAOS_CCM_COMPONENTSERVER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "cuts/arch/ccm/CCM_ComponentServer_T.h"
#include "CHAOS_CCM_ComponentServer.h"
#include "CHAOS_CCM_Container.h"
#include "cuts/arch/tcpip/TCPIP_ComponentServer.h"

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
class CUTS_CHAOS_CCM_COMPONENTSERVER_Export CUTS_CHAOS_CCM_ComponentServer :
  public CUTS_CHAOS_CCM_ComponentServer_Base,
  public CUTS_TCPIP_ComponentServer
{
public:
  /// Type definition of the base type.
  typedef CUTS_CHAOS_CCM_ComponentServer_Base base_type;

  /**
   * Initializing constructor.
   *
   * Application that containers the component server implementation.
   */
  CUTS_CHAOS_CCM_ComponentServer (
    CUTS_CHAOS_CCM_ComponentServer_App * app);

  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_ComponentServer (void);

  virtual int init (int argc, char * argv []);

  /// Activate the component server.
  virtual int activate (void);

  /// Shutdown the component server.
  virtual void shutdown (void);
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_CHAOS_CCM_COMPONENTSERVER_H_
