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
class CUTS_Testing_App;

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
  CUTS_TestManager_i (CUTS_Testing_App & parent);

  /// Destructor.
  virtual ~CUTS_TestManager_i (void);

  /**
   * Get the current test id from this manager.
   *
   * @return        The current test id.
   */
  CORBA::Long test_number (void);

private:
  /// Parent testing application for the manager.
  CUTS_Testing_App & parent_;
};

#endif  // !defined _TESTMANAGER_I_H_
