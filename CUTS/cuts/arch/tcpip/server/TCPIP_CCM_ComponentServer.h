// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_ComponentServer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_COMPONENTSERVER_H_
#define _CUTS_TCPIP_CCM_COMPONENTSERVER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "cuts/arch/ccm/CCM_ComponentServer_T.h"
#include "cuts/arch/tcpip/TCPIP_ComponentServer.h"
#include "TCPIP_CCM_Container.h"

// Forward decl.
class CUTS_TCPIP_CCM_ComponentServer_App;

/**
 * @class CUTS_TCPIP_CCM_ComponentServer
 *
 * Implementation of the CIAO component server for TCP/IP.
 */
class CUTS_TCPIP_CCM_COMPONENTSERVER_Export CUTS_TCPIP_CCM_ComponentServer :
  public CUTS_TCPIP_ComponentServer,
  public CUTS_CCM_ComponentServer_T <CUTS_TCPIP_CCM_ComponentServer,
                                     CUTS_TCPIP_CCM_Container>
{
public:
  /// Type definition of the base type.
  typedef
    CUTS_CCM_ComponentServer_T <CUTS_TCPIP_CCM_ComponentServer,
                                CUTS_TCPIP_CCM_Container> base_type;
  /**
   * Initializing constructor.
   *
   * Application that containers the component server implementation.
   */
  CUTS_TCPIP_CCM_ComponentServer (CUTS_TCPIP_CCM_ComponentServer_App * app);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_ComponentServer (void);

  virtual int init (int argc, char * argv []);

  /// Activate the component server.
  virtual int activate (void);

  /// Shutdown the component server.
  virtual void shutdown (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_COMPONENTSERVER_H_
