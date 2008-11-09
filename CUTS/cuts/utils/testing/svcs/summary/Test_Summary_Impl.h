// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Summary_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_SUMMARY_IMPL_H_
#define _CUTS_TEST_SUMMARY_IMPL_H_

#include "Test_Summary_export.h"
#include "ace/streams.h"

// Forward decl.
class CUTS_Testing_App;

/**
 * @class CUTS_Test_Summary_Impl
 *
 * Base class that all test summary generators must implement.
 */
class CUTS_Test_Summary_Impl
{
public:
  /// Default constructor
  CUTS_Test_Summary_Impl (void);

  /// Destructor
  virtual ~CUTS_Test_Summary_Impl (void);

  /**
   * Generate the summary for the application.
   *
   * @param[in]     out         Output stream
   * @param[in]     app         Testing application
   */
  virtual int generate (std::ostream & out,
                        const CUTS_Testing_App & app) const = 0;
};

#if defined (__CUTS_INLINE__)
#include "Test_Summary_Impl.inl"
#endif

#endif
