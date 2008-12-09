// -*- C++ -*-

//=============================================================================
/**
 * @file        DAnCE_Deployment_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _DANCE_DEPLOYMENT_GENERATOR_H_
#define _DANCE_DEPLOYMENT_GENERATOR_H_

#include "DAnCE_Deployment_Generator_export.h"
#include "../../Naomi_Generator.h"

/**
 * @class DAnCE_Deployment_Generator
 *
 * Adapter for generating DAnCE deployments using Naomi.
 */
class DAnCE_Deployment_Generator : public GME_Naomi_Generator
{
public:
  /// Default constructor.
  DAnCE_Deployment_Generator (void);

  /// Destructor.
  virtual ~DAnCE_Deployment_Generator (void);

  // Run the generator.
  virtual int run (const std::string & attr,
                   const std::string & attr_path,
                   GME::Object & target);
};

GME_NAOMI_CREATE_GENERATOR_DECLARE (DANCE_DEPLOYMENT_GENERATOR_Export);

#endif  // !defined _DANCE_DEPLOYMENT_GENERATOR_H_
