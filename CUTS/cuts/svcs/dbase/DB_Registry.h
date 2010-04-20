// -*- C++ -*-

//=============================================================================
/**
 * @file      DB_Service.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SERVICE_H_
#define _CUTS_DB_SERVICE_H_

#include "DB_export.h"
#include "cuts/Component_Info.h"
#include "cuts/Component_Type.h"
#include "cuts/Host_Table_Entry.h"

namespace ADBC
{
// Forward decl.
class Connection;

// Forward decl.
class Query;
}

//=============================================================================
/**
 * @class CUTS_DB_Registry
 *
 * Implements the common database operations that can be used by any
 * object. The main purpose of this class is to provide resuability
 * so that other objects do not have to worry about managing common
 * information (e.g., host, type, and instance data).
 */
//=============================================================================

class CUTS_DB_Export CUTS_DB_Registry
{
public:
  /// Constructor.
  CUTS_DB_Registry (void);

  /// Destructor.
  ~CUTS_DB_Registry (void);

  /**
   * Attach the database registry to an existing connection. This
   * is really the only way to use this object.
   *
   * @param[in]       conn        The target connection.
   */
  void attach (ADBC::Connection * conn);

  /// Detach the registry from the current database connection.
  void detach (void);

  /**
   * Determine if the database object is has a connection.
   *
   * @retval          true        Has a connection.
   * @retval          false       Does not have a connection.
   */
  bool is_attached (void) const;

  /**
   * Register a component type. This will add the component's type
   * information to the database, including its port ids.
   *
   * @param[in]       type        The component type.
   */
  void register_component_instance (const CUTS_Component_Info & info);

  /**
   * @overload
   *
   * @param[in]       type        The component type.
   * @param[out]      type_id     Registered type id.
   */
  void register_component_type (const CUTS_Component_Type & type);

  /**
   * Register an IP-address and hostname w/ the database. If
   * either the IP-address or hostname already exist, then
   * nothing happens.
   *
   * @param[in]       ipaddr        IP-address
   * @param[in]       hostname      Name of the host.
   * @param[out]      hostid        Buffer to receive host id.
   * @retval          true          Registration succeeded.
   * @retval          false         Registration failed.
   */
  void register_host (const CUTS_Host_Table_Entry & host);

  /**
   * Get the instance id of a component instance. The client does
   * not have to store the instance id. If this is the case, then
   * this method can be used to test for an instance id. The client
   * also has the option of registering the id it is not found.
   *
   * @param[in]       inst        Unique instance name of the component.
   * @param[out]      instid      Registered id for \a inst.
   * @retval          true        Successfully retrieved id.
   * @retval          false       Failed to retrieve id.
   */
  bool get_instance_id (const char * inst, long * instid = 0);

  /**
   * Get the typeid of the component. The typeid is the one
   * stored in the database for the specific component type.
   * It is also the one used to correlate a component instance
   * with a component type.
   *
   * @param[in]       type        Component type.
   * @param[out]      type_id     Output buffer for typeid.
   * @retval          true        Successfully retrieved type.
   * @retval          false       Failed to retrieve type.
   */
  bool get_component_typeid (const char * type,
                             long & type_id);

  /**
   * Get the id of a port.
   *
   * @param[in]     portname    The name of the port.
   * @param[out]    portid      The id of the port.
   * @param[in]     autoreg     Register port if it does not exist.
   */
  bool get_port_id (const char * porttype,
                    const char * portname,
                    long & portid);

  /**
   * Get the unique id of a host given its IP-address.
   *
   * @param[in]     ipaddr      IP-adddress
   * @param[out]    hostid      ID of the host.
   * @retval        true        The operation succeeded.
   * @retval        false       The operation failed.
   */
  bool get_hostid_by_ipaddr (const char * ipaddr,
                             long * hostid);

  /**
   * Get the unique id of a host given its hostname.
   *
   * @param[in]     hostname    Name of the host.
   * @param[out]    hostid      ID of the host.
   * @retval        true        The operation succeeded.
   * @retval        false       The operation failed.
   */
  bool get_hostid_by_hostname (const char * hostname, long * hostid);

protected:
  void insert_component_ports (ADBC::Query & query,
                               const char * porttype,
                               const CUTS_Port_Description_Map & ports);

  /// Pointer the connection for the registry.
  ADBC::Connection * conn_;
};

#if defined (__CUTS_INLINE__)
#include "DB_Registry.inl"
#endif

#endif  // !defined _CUTS_DB_SERVICE_H_
