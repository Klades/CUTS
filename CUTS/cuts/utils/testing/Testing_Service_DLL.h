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

// Forward decl.
class CUTS_Testing_Service;

/**
 * @class CUTS_Testing_Service_DLL
 *
 * Helper class for managing a testing service's DLL, or shared library.
 */
class CUTS_Testing_Service_DLL
{
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
  CUTS_Testing_Service * get_svc (void);

private:
  /// The actual DLL for the testing service.
  ACE_DLL dll_;

  /// The factory for the testing service.
  factory_type factory_;

  /// Pointer to the loaded testing service.
  CUTS_Testing_Service * svc_;
};

#if defined (__CUTS_INLINE__)
#include "Testing_Service_DLL.inl"
#endif

#endif  // !defined _CUTS_TESTING_SERVICE_DLL_H
