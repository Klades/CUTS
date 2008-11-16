// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Logging_Service.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGING_SERVICE_H_
#define _CUTS_TEST_LOGGING_SERVICE_H_

#include "Test_Logging_Service_export.h"
#include "cuts/utils/testing/TAO_Testing_Service.h"
#include "cuts/utils/logging/server/Logging_Server.h"

/**
 * @class CUTS_Test_Logging_Service
 *
 * Implementation of the logging service for the test manager.
 */
class CUTS_Test_Logging_Service : public CUTS_TAO_Testing_Service
{
public:
  /// Default constructor
  CUTS_Test_Logging_Service (void);

  /// Destructor.
  virtual ~CUTS_Test_Logging_Service (void);

  /**
   * Initialize the service.
   *
   * @param[in]       argc          Number of command-ling arguments
   * @param[in]       argv          Command-line arguments
   */
  virtual int init (int argc, char * argv []);

  /// Finalize the service.
  virtual int fini (void);

private:
  ACE_Auto_Ptr <CUTS_Test_Logging_Server> server_;
};

CUTS_TESTING_SERVICE_DECL (CUTS_TEST_LOGGING_SERVICE_Export, _make_CUTS_Test_Logging_Service);

#if defined (__CUTS_INLINE__)
#include "Test_Logging_Service.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVICE_H_
