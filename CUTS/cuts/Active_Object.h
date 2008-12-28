// -*- C++ -*-

//=============================================================================
/**
 * @file      Active_Object.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ACTIVE_OBJECT_H_
#define _CUTS_ACTIVE_OBJECT_H_

#include "CUTS_export.h"

/**
 * @class CUTS_Active_Object
 *
 * Base class for all active objects that are managed by the
 * CUTS_Component object.
 */
class CUTS_Export CUTS_Active_Object
{
public:
  /// Destructor.
  virtual ~CUTS_Active_Object (void) = 0;

  /// Activate the object.
  virtual int activate (void) = 0;

  /// Deactivate the object.
  virtual int deactivate (void) = 0;

protected:
  /// Default constructor.
  CUTS_Active_Object (void);
};

#if defined (__CUTS_INLINE__)
#include "Active_Object.inl"
#endif

#endif  // !defined _CUTS_ACTIVE_OBJECT_H_
