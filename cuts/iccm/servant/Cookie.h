// -*- C++ -*-

//=============================================================================
/**
 *  @file       Cookie
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_COOKIE_H_
#define _CUTS_ICCM_COOKIE_H_

#include "ccm/CCM_CookieC.h"
#include "ace/UUID.h"

#include "Servant_export.h"

namespace iCCM
{

/**
 * @class Cookie
 *
 * Implementation of the Cookie value
 */
class ICCM_SERVANT_Export Cookie :
  public ::OBV_Components::Cookie
{
public:
  /// Default constructor.
  Cookie (void);

  /**
   * Initialize the cookie with a UUID.
   *
   * @param[in]       uuid        Initial UUID
   */
  Cookie (const ACE_Utils::UUID & uuid);

  /// Destructor.
  virtual ~Cookie (void);

  /**
   * Extract the cookie's value (i.e., its UUID).
   *
   * @param[out]      uuid        Contained UUID
   */
  void extract (ACE_Utils::UUID & uuid);
};

/**
 * @class Cookie_Factory
 *
 * Implementation of the Cookie value type factory.
 */
class ICCM_SERVANT_Export Cookie_Factory :
  public ::Components::Cookie_init
{
public:
  /// Default constructor.
  Cookie_Factory (void);

  /// Destructor.
  virtual ~Cookie_Factory (void);

  /// Create a Cookie for unmarshalling the value type.
  virtual ::CORBA::ValueBase * create_for_unmarshal (void);
};

}

#if defined (__CUTS_INLINE__)
#include "Cookie.inl"
#endif

#endif  // !defined _CUTS_ICCM_COOKIE_H_
