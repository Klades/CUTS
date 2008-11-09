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
#include "ace/Time_Value.h"
#include "ace/OS_Memory.h"

// Forward decl.
class CUTS_Testing_App;

// Forward decl.
class CUTS_Testing_Service_Manager;

/**
 * @class CUTS_Testing_Service
 */
class CUTS_TESTING_SERVICE_Export CUTS_Testing_Service
{
  friend class CUTS_Testing_Service_Manager;

public:
  /// Default constructor.
  CUTS_Testing_Service (void);

  virtual int init (int argc, char * argv []);

  virtual int fini (void);

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
  virtual CUTS_Testing_App * const test_app (void);

  /// Destroy the service.
  virtual void destroy (void);

protected:
  /// Destructor.
  virtual ~CUTS_Testing_Service (void) ;

private:
  /// Pointer to the testing application.
  CUTS_Testing_App * app_;

  CUTS_Testing_Service (const CUTS_Testing_Service &);
  const CUTS_Testing_Service & operator = (const CUTS_Testing_Service &);
};

/**
 *
 */
#define CUTS_TESTING_SERVICE_DECL(export_macro, symbol) \
  extern "C" export_macro CUTS_Testing_Service * symbol (void)

/**
 *
 */
#define CUTS_TESTING_SERVICE_IMPL(classname, symbol) \
  CUTS_Testing_Service  * symbol (void) \
  { \
    classname * service = 0; \
    ACE_NEW_RETURN (service, classname (), 0); \
    return service; \
  }

#if defined (__CUTS_INLINE__)
#include "Testing_Service.inl"
#endif

#endif  // !defined _CUTS_TESTING_SERVICE_H_
