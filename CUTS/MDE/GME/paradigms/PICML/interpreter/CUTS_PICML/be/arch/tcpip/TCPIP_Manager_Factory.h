// -*- C++ -*-

//=============================================================================
/**
 *  @file     TCPIP_Manager_Factory.h
 *
 *  $Id$
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TCPIP_MANAGER_FACTORY_H_
#define _CUTS_BE_TCPIP_MANAGER_FACTORY_H_

#include "BE_TCPIP_export.h"
#include "../../BE_Manager_Factory.h"

/**
 * @class CUTS_BE_TCPIP_Manager_Factory
 *
 * Implementation of the factory object for the TCP/IP backend
 * source code generator.
 */
class CUTS_BE_TCPIP_Manager_Factory : public CUTS_BE_Manager_Factory
{
public:
  /// Default constructor.
  CUTS_BE_TCPIP_Manager_Factory (void);

  /// Destructor.
  virtual ~CUTS_BE_TCPIP_Manager_Factory (void);

  /// Method for creating the manager.
  CUTS_BE_Manager * create_manager (void);

  /// Name of the manager.
  const char * name (void) const;

  /// Description of the backend
  const char * description (void) const;
};

CUTS_BE_CREATE_MANAGER_FACTORY_DECLARE (CUTS_BE_TCPIP_Export);

#endif  // !defined _CUTS_BE_TCPIP_MANAGER_FACTORY_H_
