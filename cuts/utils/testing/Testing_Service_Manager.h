// -*- C++ -*-

//=============================================================================
/**
 * @file          Testing_Service_Manager.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_SERVICE_MANAGER_H_
#define _CUTS_TESTING_SERVICE_MANAGER_H_

#include "Test_export.h"
#include "Testing_Service.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Hash_Map_Manager_T.h"
#include "ace/Singleton.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_Testing_App_Base;

// Forward decl.
class CUTS_Testing_Service_DLL;

namespace CUTS
{
  // Forward decl.
  class serviceDescription;

  // Forward decl.
  class serviceList;
}

/**
 * @class CUTS_Testing_Service_Manager
 */
class CUTS_Testing_Service_Manager
{
public:
  /// Type definition of the map type.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Testing_Service_DLL *,
                                ACE_RW_Thread_Mutex> map_type;

  /**
   * Initializing constructor
   *
   * @param[in]       app         Testing application
   */
  CUTS_Testing_Service_Manager (CUTS_Testing_App_Base * app);

  /// Destructor
  ~CUTS_Testing_Service_Manager (void);

  int load_service (const CUTS::serviceDescription & svc);

  int load_service (const char * name,
                    const char * location,
                    const char * entry,
                    const char * params = 0);

  int load_services (const CUTS::serviceList & svcs);

  int close (void);

  int handle_startup (const ACE_Time_Value & tv);

  int handle_shutdown (const ACE_Time_Value & tv);


private:
  /// Testing application
  CUTS_Testing_App_Base * test_app_;

  /// Service map for the testing application.
  map_type svc_map_;

  /// The open state of the manager.
  bool is_open_;
};

#if defined (__CUTS_INLINE__)
#include "Testing_Service_Manager.inl"
#endif

#endif  // !defined _CUTS_TESTING_SERVICE_MANAGER_H_
