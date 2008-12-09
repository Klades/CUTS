// -*- C++ -*-

//=============================================================================
/**
 * @file          Naomi_Parser.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _GME_NAOMI_PARSER_H_
#define _GME_NAOMI_PARSER_H_

#include "GNC_Base_export.h"
#include <string>

namespace GME
{
  /// Forward decl.
  class Object;
}

/**
 * @class GME_Naomi_Parser
 *
 * Base case for parsers used by the GME connector for NAOMI.
 */
class GNC_BASE_Export GME_Naomi_Parser
{
public:
  /// Destructor.
  virtual ~GME_Naomi_Parser (void);

  /**
   * Handle a resource in the input file.
   *
   * @param[in]         name            Name of the resource.
   * @param[in]         uri             URI of the resource.
   */
  virtual int handle_resource (const std::string & name,
                               const std::string & uri) = 0;

  /**
   * Run the parser on the target object. This should populate the
   * project using \a target as the starting point.
   *
   * @param[in]         target          The target object.
   * @param[in]         attr_path       Attribute path.
   */
  virtual int run (GME::Object & target,
                   const std::string & attr_path) = 0;

  /// Delete the parser. This function should only be used if the parser
  /// was created dynamcially and in a different memory space.
  virtual void destroy (void);

protected:
  /// Default constructor.
  GME_Naomi_Parser (void);
};

/**
 *
 */
#define GME_NAOMI_CREATE_PARSER_FUNC \
  GME_NAOMI_create_parser

/**
 *
 */
#define GME_NAOMI_CREATE_PARSER_FUNC_STR \
  "GME_NAOMI_create_parser"

/**
 *
 */
#define GME_NAOMI_CREATE_PARSER_DECLARE(export_macro) \
  extern "C" export_macro GME_Naomi_Parser * \
    GME_NAOMI_CREATE_PARSER_FUNC (void)

/**
 *
 */
#define GME_NAOMI_CREATE_PARSER_IMPLEMENT(parser_type) \
  GME_Naomi_Parser * GME_NAOMI_CREATE_PARSER_FUNC (void) \
  { \
    return new parser_type (); \
  }

#endif  // !defined _GME_NAOMI_PARSER_H_
