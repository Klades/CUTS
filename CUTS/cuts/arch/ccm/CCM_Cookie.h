// -*- C++ -*-

//=============================================================================
/**
 *  @file       CCM_Cookie
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_COOKIE_H_
#define _CUTS_CCM_COOKIE_H_

#include "ccm/CCM_CookieC.h"
#include "ace/UUID.h"
#include "CCM_export.h"

/**
 * @class CUTS_CCM_Cookie
 */
class CUTS_CCM_Export CUTS_CCM_Cookie :
  public ::OBV_Components::Cookie
{
public:
  CUTS_CCM_Cookie (void);

  CUTS_CCM_Cookie (const ACE_Utils::UUID & uuid);

  virtual ~CUTS_CCM_Cookie (void);

  void extract (ACE_Utils::UUID & uuid);
};

/**
 * @class CUTS_TCPIP_CCM_Cookie_Factory
 */
class CUTS_CCM_Export CUTS_CCM_Cookie_Factory :
  public ::Components::Cookie_init
{
public:
  /// Default constructor.
  CUTS_CCM_Cookie_Factory (void);

  /// Destructor.
  virtual ~CUTS_CCM_Cookie_Factory (void);

  virtual ::CORBA::ValueBase * create_for_unmarshal (void);
};

#if defined (__CUTS_INLINE__)
#include "CCM_Cookie.inl"
#endif

#endif
