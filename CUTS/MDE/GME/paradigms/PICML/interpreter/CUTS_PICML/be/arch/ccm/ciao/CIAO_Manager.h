// -*- C++ -*-

//=============================================================================
/**
 * @file      CIAO_Manager.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CIAO_MANAGER_H_
#define _CUTS_BE_CIAO_MANAGER_H_

#include "CIAO_Preprocessor_Handlers.h"
#include "CIAO_Generators.h"
#include "../../../BE_Manager_T.h"
#include "../../../BE_MPC_Workspace.h"

namespace CUTS_BE_CIAO
{
/**
 * @class Manager
 *
 * Implementation of the CIAO backend manager.
 */
class CUTS_BE_CIAO_Export Manager :
  public CUTS_BE_Manager_T <Manager, Context>
{
public:
  /// Default constructor.
  Manager (void);

  /// Destructor.
  virtual ~Manager (void);
};

}

#endif  // !defined _CUTS_BE_CIAO_MANAGER_H_
