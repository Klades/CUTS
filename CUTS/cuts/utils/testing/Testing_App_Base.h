// -*- C++ -*-

//==============================================================================
/**
 * @file        Testing_App_Base.h
 *
 * $Id$
 * 
 * @author      James H. Hill
 */
//==============================================================================                                                                                                                      

#ifndef _CUTS_TESTING_APP_BASE_H_
#define _CUTS_TESTING_APP_BASE_H_

#include "Testing_Service_export.h"

// Forward decl.
class CUTS_Test_Database;

// Forward decl.
class CUTS_Test_Options;

/**
 * @class CUTS_Testing_App_Base
 *
 * Base class for the testing application. This is really the interface
 * that CUTS_Testing_Service objects use to access the CUTS_Testing_App
 * object.
 */
class CUTS_TESTING_SERVICE_Export CUTS_Testing_App_Base
{
public:
  /// Destructor.
  virtual ~CUTS_Testing_App_Base (void) = 0;

  /**
   * Get a reference to the test database.
   *
   * @return        Reference to the test database.
   */
  virtual CUTS_Test_Database & test_db (void) = 0;

  /**
   * Get the test options for the appication.
   *
   * @return        Read-only reference to the options.
   */
  virtual const CUTS_Test_Options & options (void) const = 0;

protected:
  /// Default constructor.
  CUTS_Testing_App_Base (void);
};

#if defined (__CUTS_INLINE__)
#include "Testing_App_Base.inl"
#endif

#endif  // !defined _CUTS_TESTING_APP_BASE_H_  
