// -*- C++ -*-

//=============================================================================
/**
 * @file        TestManager_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTMANAGER_I_H_
#define _CUTS_TESTMANAGER_I_H_

#include "testingS.h"

// Forward decl.
class CUTS_Testing_Server;

/**
 * @class TestManager_i
 *
 * Default implementation of the CUTS::TestManager interface.
 */
class CUTS_TestManager_i :
  public POA_CUTS::TestManager
{
public:
  /// Default constructor.
  CUTS_TestManager_i (CUTS_Testing_Server & server);

  /// Destructor.
  virtual ~CUTS_TestManager_i (void);

  /**
   * Get the details of the currently executing test.
   *
   * @return        Current test details.
   */
  virtual CUTS::TestDetails * details (void);

  /// Shutdown the current test.
  virtual void shutdown (void);

private:
  /// Parent testing application for the manager.
  CUTS_Testing_Server & server_;
};

#endif  // !defined _TESTMANAGER_I_H_
