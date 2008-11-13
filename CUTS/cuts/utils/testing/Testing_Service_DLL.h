// -*- C++ -*-

//=============================================================================
/**
 * @file          Testing_Service_DLL.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_SERVICE_DLL_H_
#define _CUTS_TESTING_SERVICE_DLL_H_

#include "Test_export.h"
#include "ace/DLL.h"
#include "ace/Service_Config.h"

// Forward decl.
class CUTS_Testing_Service;

// Forward decl.
class CUTS_Testing_Service_DLL_Guard;

/**
 * @class CUTS_Testing_Service_DLL
 *
 * Helper class for managing a testing service's DLL, or shared library.
 */
class CUTS_Testing_Service_DLL
{
  friend class CUTS_Testing_Service_DLL_Guard;

public:
  /// Type definition of the factory type.
  typedef CUTS_Testing_Service * (* factory_type) (void);

  /// Default constructor.
  CUTS_Testing_Service_DLL (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       module        Location of the module
   * @param[in]       symbol        Symbol for creating testing service
   */
  CUTS_Testing_Service_DLL (const char * module, const char * symbol);

  /// Destructor
  ~CUTS_Testing_Service_DLL (void);

  int open (const char * module, const char * symbol);

  /// Close the DLL.
  int close (void);

  /**
   * Get a pointer to the testing service loaded from the module.
   */
  CUTS_Testing_Service * operator -> (void);

private:
  int init (void);

  /// The actual DLL for the testing service.
  ACE_DLL dll_;

  /// Pointer to the loaded testing service.
  CUTS_Testing_Service * svc_;

  /// Service configurator for this DLL.
  ACE_Intrusive_Auto_Ptr <ACE_Service_Gestalt> svc_config_;
};

/**
 * @class CUTS_Testing_Service_DLL_Service_Guard
 *
 * Guard that ensures service configuration of a CUTS_Testing_Service_DLL
 * is ACE_Service_Config::current (). This is useful when loading DLL
 * that may contain static services and controlling which configuration
 * it is installed.
 */
class CUTS_Testing_Service_DLL_Guard
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_Testing_Service_DLL_Guard (CUTS_Testing_Service_DLL & dll);

  /// Destructor.
  ~CUTS_Testing_Service_DLL_Guard (void);

private:
  /// Service configuration guard.
  ACE_Service_Config_Guard guard_;
};

#if defined (__CUTS_INLINE__)
#include "Testing_Service_DLL.inl"
#endif

#endif  // !defined _CUTS_TESTING_SERVICE_DLL_H
