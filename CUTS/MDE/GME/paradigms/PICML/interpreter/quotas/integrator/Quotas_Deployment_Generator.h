// -*- C++ -*-

//=============================================================================
/**
 *  @file           Quotas_Deployment_Generator.h
 *
 *  $Id$
 *
 *  @author         James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_DEPLOYMENT_GENERATOR_H_
#define _QUOTAS_DEPLOYMENT_GENERATOR_H_

#include "game/Folder.h"
#include "game/Model.h"
#include "game/Transaction.h"

/**
 * @class Quotas_Deployment_Generator
 *
 * Utility class that is responsible for generating a deployment. The
 * generation logic is very basic.
 */
class Quotas_Deployment_Generator
{
public:
  /// Default constructor.
  Quotas_Deployment_Generator (void);

  /// Destructor.
  ~Quotas_Deployment_Generator (void);

  bool generate (GAME::Folder_in folder,
                 const std::string & name,
                 const GAME::Model & domain,
                 const GAME::Model & assembly,
                 GAME::Model & deployment);
};

#endif  // !defined _QUOTAS_DEPLOYMENT_GENERATOR_H_
