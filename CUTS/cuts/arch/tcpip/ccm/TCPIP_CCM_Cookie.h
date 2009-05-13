// -*- C++ -*-

//=============================================================================
/**
 *  @file       TCPIP_CCM_Cookie
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_COOKIE_H_
#define _CUTS_TCPIP_CCM_COOKIE_H_

#include "ccm/CCM_CookieC.h"
#include "ace/UUID.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Cookie
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Cookie :
  public ::OBV_Components::Cookie
{
public:
  CUTS_TCPIP_CCM_Cookie (void);

  CUTS_TCPIP_CCM_Cookie (const ACE_Utils::UUID & uuid);

  virtual ~CUTS_TCPIP_CCM_Cookie (void);

  void extract (ACE_Utils::UUID & uuid);
};

/**
 * @class CUTS_TCPIP_CCM_Cookie_Factory
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Cookie_Factory :
  public ::Components::Cookie_init
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_Cookie_Factory (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Cookie_Factory (void);

  virtual ::CORBA::ValueBase * create_for_unmarshal (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Cookie.inl"
#endif

#endif
