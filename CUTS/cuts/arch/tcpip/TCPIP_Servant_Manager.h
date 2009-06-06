// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Servant_Manager.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_SERVANT_MANAGER_H_
#define _CUTS_TCPIP_SERVANT_MANAGER_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/UUID.h"
#include "TCPIP_export.h"
#include "config.h"

// Forward decl.
class CUTS_TCPIP_Servant;

// Forward decl.
class CUTS_TCPIP_ORB;

/**
 * @class CUTS_TCPIP_Servant_Manager
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Servant_Manager
{
public:
  /// Default constructor.
  CUTS_TCPIP_Servant_Manager (CUTS_TCPIP_ORB * orb);

  /// Destructor.
  ~CUTS_TCPIP_Servant_Manager (void);

  /**
   * Activate a servant object.
   */
  int activate_object (CUTS_TCPIP_Servant * obj);

  /**
   * Deactivate an object.
   */
  int deactivate_object (const ACE_Utils::UUID & uuid);

  /// Get the UUID of a servant.
  int get_uuid (CUTS_TCPIP_Servant * obj,
                ACE_Utils::UUID & uuid) const;

  /**
   * Locate an object in the manager.
   *
   * @param[in]         uuid          UUID of the object
   * @param[out]        object        Pointer to the object
   * @retval            0             Object found
   * @retval            -1            Object not found
   */
  int find_object (const ACE_Utils::UUID & uuid,
                   CUTS_TCPIP_Servant * & object) const;

private:
  /// ORB that owns the servant manager.
  CUTS_TCPIP_ORB * orb_;

  /// Type definition of the object map.
  typedef
    ACE_Hash_Map_Manager <ACE_Utils::UUID,
                          CUTS_TCPIP_Servant *,
                          ACE_RW_Thread_Mutex> map_type;

  /// Collection of active objects in this manager.
  map_type active_objects_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Servant_Manager.inl"
#endif

#endif  // !defined _CUTS_TCPIP_SERVANT_MANAGER_H_
