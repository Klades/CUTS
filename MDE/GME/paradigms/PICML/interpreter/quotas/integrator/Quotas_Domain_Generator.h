// -*- C++ -*-

//=============================================================================
/**
 *  @file           Quotas_Domain_Generator.h
 *
 *  $Id$
 *
 *  @author         James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_DOMAIN_GENERATOR_H_
#define _QUOTAS_DOMAIN_GENERATOR_H_

#include "game/Folder.h"
#include "game/Model.h"

/**
 * @class Quotas_Domain_Generator
 *
 * Utility class for generating a domain. The domain is the set of
 * nodes in the target environment, their interconnects, and the
 * configuration for each entity.
 */
class Quotas_Domain_Generator
{
public:
  /// Default constructor.
  Quotas_Domain_Generator (void);

  /// Destructor.
  ~Quotas_Domain_Generator (void);

  bool generate (GAME::Folder_in folder,
                 const std::string & name,
                 size_t hosts);

  /// Get the collection od generated hosts.
  GAME::Model generated_domain (void);

private:
  /// The generated domain.
  GAME::Model domain_;
};

#endif  // !defined _QUOTAS_DOMAIN_GENERATOR_H_
