// -*- C++ -*-

//=============================================================================
/**
 * @file      Naomi_Generator.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _GME_NAOMI_GENERATOR_H_
#define _GME_NAOMI_GENERATOR_H_

#include "GNC_Base_export.h"
#include "Resource_List.h"

namespace GME
{
  // Forward decl.
  class Object;
}

/**
 * @class GME_Naomi_Generator
 *
 * Base class for the GME generators that integrate with NAOMI.
 */
class GNC_BASE_Export GME_Naomi_Generator
{
public:
  /// Destructor
  virtual ~GME_Naomi_Generator (void);

  /**
   * Get the list of resources produced by this generator.
   *
   * @return          List of resources.
   */
  virtual const GME_Naomi_Resource_List & resources (void) const;

  /**
   * Run the generator on the specified object.
   *
   * @param[in]       attr          Name of the attribute.
   * @param[in]       target        Target object for generator
   * @retval          0             Successfully run generator
   * @retval          -1            Failed to run generator
   */
  virtual int run (const std::string & attr,
                   const std::string & attr_path,
                   GME::Object & target) = 0;

  /// Delete the parser. This function should only be used if the parser
  /// was created dynamcially and in a different memory space.
  virtual void destroy (void);

  /**
   * Get the description of the interpreter.
   *
   * @return        Description of the interpreter.
   */
  virtual const std::string & documentation (void) const;

protected:
  /// Default constructor.
  GME_Naomi_Generator (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       desc          Description of the attribute.
   */
  GME_Naomi_Generator (const std::string & desc);

  /**
   * Helper method to run the generator.
   *
   * @param[in]       attr          Name of NAOMI attribute
   * @param[in]       attr_path     Location of NOAMI attribute
   * @param[in]       target        Target GME object to interpret
   * @param[in]       prog_id       COM program id of the interpreter
   */
  static int run_i (const std::string & attr,
                    const std::string & attr_path,
                    GME::Object & target,
                    const std::string & prog_id);

  /// List of resources produced by this generator.
  GME_Naomi_Resource_List resources_;

  /// Documentation for the attribute.
  std::string documentation_;
};

/**
 *
 */
#define GME_NAOMI_CREATE_GENERATOR_FUNC \
  GME_NAOMI_create_generator

/**
 *
 */
#define GME_NAOMI_CREATE_GENERATOR_FUNC_STR \
  "GME_NAOMI_create_generator"

/**
 *
 */
#define GME_NAOMI_CREATE_GENERATOR_DECLARE(export_macro) \
  extern "C" export_macro GME_Naomi_Generator * \
    GME_NAOMI_CREATE_GENERATOR_FUNC (void)

/**
 *
 */
#define GME_NAOMI_CREATE_GENERATOR_IMPLEMENT(generator_type) \
  GME_Naomi_Generator * GME_NAOMI_CREATE_GENERATOR_FUNC (void) \
  { \
    return new generator_type (); \
  }


#endif
