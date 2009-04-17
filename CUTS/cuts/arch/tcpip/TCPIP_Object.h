// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Object.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_OBJECT_H_
#define _CUTS_TCPIP_OBJECT_H_

#include "ace/UUID.h"
#include "config.h"
#include "TCPIP_export.h"

// Forward decl.
class CUTS_TCPIP_Servant_Manager;

/**
 * @class CUTS_TCPIP_Object
 *
 * Base class for all objects. This class defines the required methods
 * for an object. It also defines the required data members, such as
 * the UUID, for all objects.
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Object
{
public:
  /// Increment the reference count.
  virtual void incr_refcount (void) = 0;

  /**
   * Decrement the reference count. Once the reference count reaches
   * zero, then the object is destroyed.
   */
  virtual void decr_refcount (void) = 0;

  /**
   * Get the current reference count.
   *
   * @return        The current reference count.
   */
  virtual size_t refcount (void) const = 0;

protected:
  /// Default constructor.
  CUTS_TCPIP_Object (void);

  /// Destructor
  virtual ~CUTS_TCPIP_Object (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Object.inl"
#endif

#endif  // !defined _CUTS_TCPIP_OBJECT_H_
