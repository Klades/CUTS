// -*- C++ -*-

//=============================================================================
/**
 * @file      CoreDX_Manager.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_COREDX_MANAGER_H_
#define _CUTS_BE_COREDX_MANAGER_H_

#include "Preprocessor_Handlers.h"
#include "Generators.h"
#include "../../../BE_Manager_T.h"
#include "../../../BE_MPC_Workspace.h"

namespace CUTS_BE_CoreDX
{
/**
 * @class Manager
 *
 * Implementation of the CoreDX backend manager.
 */
class CUTS_BE_COREDX_Export Manager :
  public CUTS_BE_Manager_T <Manager, CUTS_BE_CoreDX::Context>
{
public:
  /// Default constructor.
  Manager (void);

  /// Destructor.
  virtual ~Manager (void);
};

}

#endif  // !defined _CUTS_BE_CIAO_MANAGER_H_
