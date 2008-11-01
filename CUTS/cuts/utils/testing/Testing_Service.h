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

#ifndef _CUTS_TESTING_SERVICE_H_
#define _CUTS_TESTING_SERVICE_H_

#include "Testing_Service_export.h"
#include "ace/Service_Object.h"

// Forward decl.
class CUTS_Testing_App;

/**
 * @class CUTS_Testing_Service
 */
class CUTS_TESTING_SERVICE_Export CUTS_Testing_Service :
  public ACE_Service_Object
{
  friend class CUTS_Testing_App;
public:
  /// Destructor.
  virtual ~CUTS_Testing_Service (void) = 0;

  /**
   * Handle the startup of a test.
   *
   * @param[in]         app         Parent testing application
   */
  virtual int handle_startup (const ACE_Time_Value & tv);

  /**
   * Handle the shutdown of a test.
   *
   * @param[in]         app         Parent testing application
   */
  virtual int handle_shutdown (const ACE_Time_Value & tv);

  /**
   * Get the pointer to the testing application.
   */
  CUTS_Testing_App * const test_app (void);

protected:
  /// Default constructor.
  CUTS_Testing_Service (void);

private:
  /// Pointer to the testing application.
  CUTS_Testing_App * app_;

  CUTS_Testing_Service (const CUTS_Testing_Service &);
  const CUTS_Testing_Service & operator = (const CUTS_Testing_Service &);
};

#if defined (__CUTS_INLINE__)
#include "Testing_Service.inl"
#endif

#endif  // !defined _CUTS_TESTING_SERVICE_H_
