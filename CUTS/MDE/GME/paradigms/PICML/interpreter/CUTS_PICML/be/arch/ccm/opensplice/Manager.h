// -*- C++ -*-

//=============================================================================
/**
 * @file      OpenSplice_Manager.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_OPENSPLICE_MANAGER_H_
#define _CUTS_BE_OPENSPLICE_MANAGER_H_

#include "Preprocessor_Handlers.h"
#include "Generators.h"
#include "../../../BE_Manager_T.h"
#include "../../../BE_MPC_Workspace.h"

/// Type definition for the CIAO backend manager.
typedef CUTS_BE_Manager_T <CUTS_BE_OpenSplice::Context> CUTS_BE_OpenSplice_Manager;

#endif  // !defined _CUTS_BE_CIAO_MANAGER_H_
