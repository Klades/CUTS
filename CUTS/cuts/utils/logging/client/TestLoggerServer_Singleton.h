// $Id$

///=============================================================================
/**
 * @file          TestLoggerServer_Singleton.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTLOGGERSERVER_SINGLETON_H_
#define _CUTS_TESTLOGGERSERVER_SINGLETON_H_

#include "clientC.h"
#include "Logging_Client_export.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"

/**
 * @class CUTS_TestLoggerServer_Singleton
 */
class CUTS_TestLoggerServer_Singleton
{
public:
  /// Default constructor
  CUTS_TestLoggerServer_Singleton (void);

  /// Destructor.
  ~CUTS_TestLoggerServer_Singleton (void);

  /**
   * Reset the reference to the server.
   *
   * @param[in]       server        New server reference.
   */
  void reset (CUTS::TestLoggerServer_ptr server = CUTS::TestLoggerServer::_nil ());

  /**
   * Get a reference to the server.
   */
  CUTS::TestLoggerServer_ptr get (void);

private:
  /// Reference to the server.
  CUTS::TestLoggerServer_var server_;
};

#define CUTS_TESTLOGGERSERVER \
  ACE_Singleton <CUTS_TestLoggerServer_Singleton, ACE_Null_Mutex>::instance ()

#if defined (__CUTS_INLINE__)
#include "TestLoggerServer_Singleton.inl"
#endif

#endif  // !defined _CUTS_TESTLOGGERSERVER_SINGLETON_H_
