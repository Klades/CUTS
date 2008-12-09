// -*- C++ -*-

//=============================================================================
/**
 * @file        Isislab_Emulation_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _DANCE_DEPLOYMENT_GENERATOR_H_
#define _DANCE_DEPLOYMENT_GENERATOR_H_

#include "Isislab_Emulation_Generator_export.h"
#include "../../Naomi_Generator.h"

/**
 * @class Isislab_Emulation_Generator
 *
 * Adapter for generating DAnCE deployments using Naomi.
 */
class Isislab_Emulation_Generator : public GME_Naomi_Generator
{
public:
  /// Default constructor.
  Isislab_Emulation_Generator (void);

  /// Destructor.
  virtual ~Isislab_Emulation_Generator (void);

  // Run the generator.
  virtual int run (const std::string & attr,
                   const std::string & attr_path,
                   GME::Object & target);
};

GME_NAOMI_CREATE_GENERATOR_DECLARE (ISISLAB_EMULATION_GENERATOR_Export);

#endif  // !defined _DANCE_DEPLOYMENT_GENERATOR_H_
