// -*- C++ -*-

//=============================================================================
/**
 *  @file       TCPIP_Manager.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TCPIP_MANAGER_H_
#define _CUTS_BE_TCPIP_MANAGER_H_

#include "Preprocessor_Handlers.h"
#include "TCPIP_Generator.h"

#include "../../../BE_Manager_T.h"
#include "../../../BE_MPC_Workspace.h"

namespace CUTS_BE_TCPIP
{
/**
 * @class Manager
 *
 * Implementation of the CIAO backend manager.
 */
class CUTS_BE_TCPIP_Export Manager :
  public CUTS_BE_Manager_T <Manager, CUTS_BE_TCPIP_Ctx>
{
public:
  /// Default constructor.
  Manager (void);

  /// Destructor.
  virtual ~Manager (void);
};

}

#endif  // !defined _CUTS_BE_TCPIP_MANAGER_H_
