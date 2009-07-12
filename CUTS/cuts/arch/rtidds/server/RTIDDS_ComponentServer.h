// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_CCM_ComponentServer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RTIDDS_CCM_COMPONENTSERVER_H_
#define _CUTS_RTIDDS_CCM_COMPONENTSERVER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "cuts/arch/ccm/CCM_ComponentServer_T.h"
#include "RTIDDS_ComponentServer.h"
#include "RTIDDS_Container.h"

// Forward decl.
class CUTS_RTIDDS_CCM_ComponentServer_App;

/**
 * @class CUTS_RTIDDS_CCM_ComponentServer
 *
 * Implementation of the CCM component server for RTIDDS.
 */
class CUTS_RTIDDS_COMPONENTSERVER_Export CUTS_RTIDDS_CCM_ComponentServer :
  public CUTS_CCM_ComponentServer_T <CUTS_RTIDDS_CCM_ComponentServer,
                                     CUTS_RTIDDS_CCM_Container>
{
public:
  /// Type definition of the base type.
  typedef
    CUTS_CCM_ComponentServer_T <CUTS_RTIDDS_CCM_ComponentServer,
                                CUTS_RTIDDS_CCM_Container> base_type;
  /**
   * Initializing constructor.
   *
   * Application that containers the component server implementation.
   */
  CUTS_RTIDDS_CCM_ComponentServer (CUTS_RTIDDS_CCM_ComponentServer_App * app);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_ComponentServer (void);
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_RTIDDS_CCM_COMPONENTSERVER_H_
