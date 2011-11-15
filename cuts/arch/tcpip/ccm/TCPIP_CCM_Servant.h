// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_SERVANT_H_
#define _CUTS_TCPIP_CCM_SERVANT_H_

#include "cuts/arch/ccm/CCM_Servant.h"
#include "cuts/arch/tcpip/TCPIP_Servant.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Servant
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Servant :
  public CUTS_TCPIP_Servant,
  public CUTS_CCM_Servant
{
public:
  /**
   * Default constructor.
   */
  CUTS_TCPIP_CCM_Servant (const char * name);

protected:
  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Servant (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_H_
