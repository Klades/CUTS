// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_ComponentServer_Callback.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_COMPONENTSERVER_CALLBACK_H_
#define _CUTS_CCM_COMPONENTSERVER_CALLBACK_H_

#include "CCM_export.h"

/**
 * @class CUTS_CCM_ComponentServer_Callback
 */
class CUTS_CCM_Export CUTS_CCM_ComponentServer_Callback
{
public:
  /// Destructor.
  virtual ~CUTS_CCM_ComponentServer_Callback (void);

  /// Notify the object of shutdown.
  virtual void shutdown (bool notify);

protected:
  /// Default constructor.
  CUTS_CCM_ComponentServer_Callback (void);
};

#if defined (__CUTS_INLINE__)
#include "CCM_ComponentServer_Callback.inl"
#endif

#endif  // !defined _CUTS_CCM_COMPONENTSERVER_CALLBACK_H_
