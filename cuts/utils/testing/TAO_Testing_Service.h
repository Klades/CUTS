// -*- C++ -*-

//=============================================================================
/**
 * @file        Testing_Service.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TAO_TESTING_SERVICE_H_
#define _CUTS_TAO_TESTING_SERVICE_H_

#include "TAO_Testing_Service_export.h"
#include "Testing_Service.h"
#include "tao/corba.h"

/**
 * @class CUTS_TAO_Testing_Service
 *
 * Base class for TAO-based testing service.
 */
class CUTS_TAO_TESTING_SERVICE_Export CUTS_TAO_Testing_Service :
  public CUTS_Testing_Service
{
public:
  /// Default constructor.
  CUTS_TAO_Testing_Service (void);

  /// Destructor.
  virtual ~CUTS_TAO_Testing_Service (void);

  virtual int init (int argc, char * argv []);

  virtual int fini (void);

protected:
  /// The ORB for the testing service.
  CORBA::ORB_var orb_;
};

#if defined (__CUTS_INLINE__)
#include "TAO_Testing_Service.inl"
#endif

#endif  // !defined _CUTS_TAO_TESTING_SERVICE_H_
