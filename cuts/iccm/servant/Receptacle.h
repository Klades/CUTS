// -*- C++ -*-

//==============================================================================
/**
 *  @file        Receptacle.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_RECEPTACLE_H_
#define _ICCM_RECEPTACLE_H_

#include "cuts/config.h"
#include "ace/UUID.h"
#include "Cookie.h"
#include "ccm/CCM_ObjectS.h"
#include "Servant_export.h"

namespace iCCM
{

/**
 * @class Receptacle
 *
 * Abstraction for a CCM receptacle
 */
class ICCM_SERVANT_Export Receptacle
{
public:
  /// Default constructor.
  Receptacle (void);

  /// Destructor.
  virtual ~Receptacle (void);

  // Connect the receptacle to the provided facet
  virtual ::Components::Cookie * connect (::CORBA::Object_ptr) = 0;

  // Disconnect the receptacle
  virtual ::CORBA::Object_ptr disconnect (::Components::Cookie *) = 0;
};

} // namespace iCCM

#if defined (__CUTS_INLINE__)
#include "Receptacle.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _ICCM_RECEPTACLE_H_
