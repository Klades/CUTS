// -*- C++ -*-

#ifndef _CUTS_TEST_SUMMARY_SERVICE_H_
#define _CUTS_TEST_SUMMARY_SERVICE_H_

#include "Test_Summary_export.h"
#include "cuts/utils/testing/Testing_Service.h"
#include "ace/Auto_Ptr.h"

// Forward decl.
class CUTS_Test_Summary_Impl;

/**
 * @class CUTS_Test_Summary_Service
 *
 * Test summary service for the CUTS test engine.
 */
class CUTS_Test_Summary_Service : public CUTS_Testing_Service
{
public:
  /// Default constructor
  CUTS_Test_Summary_Service (void);

  /// Destructor
  virtual ~CUTS_Test_Summary_Service (void);

  virtual int init (int argc, char * argv []);

  virtual int handle_shutdown (const ACE_Time_Value & tv);

private:
  /// Pointer to the concrete implementation.
  ACE_Auto_Ptr <CUTS_Test_Summary_Impl> impl_;
};

CUTS_TESTING_SERVICE_DECL (CUTS_TESTING_SUMMARY_Export, _make_CUTS_Test_Summary_Service);

#if defined (__CUTS_INLINE__)
#include "Test_Summary_Service.inl"
#endif

#endif  // !defined _CUTS_TEST_SUMMARY_SERVICE_H_
