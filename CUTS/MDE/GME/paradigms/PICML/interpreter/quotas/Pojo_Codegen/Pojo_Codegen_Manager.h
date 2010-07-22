// -*- C++ -*-

//=============================================================================
/**
 * @file        Pojo_Codegen_Manager.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_POJO_CODEGEN_MANAGER_H_
#define _QUOTAS_POJO_CODEGEN_MANAGER_H_

#include "Pojo_Codegen_Preprocessor_Handlers.h"
#include "Pojo_Codegen_Generators.h"
#include "Pojo_Codegen_Project_Generators.h"
#include "Pojo_Codegen_Workspace_Generators.h"
#include "be/BE_Manager_T.h"

/// Type definition for this generator's manager.
typedef
  CUTS_BE_Manager_T <Quotas::Pojo::Codegen::Context>
  Quotas_Pojo_Codegen_Manager;

#endif  // !defined _QUOTAS_POJO_CODEGEN_MANAGER_H_
