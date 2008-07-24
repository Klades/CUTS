// -*- C++ -*-

//=============================================================================
/**
 * @file        T2M_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _GME_T2M_PARSER_H_
#define _GME_T2M_PARSER_H_

#include "T2M_Parser_export.h"
#include "cuts/config.h"
#include <string>

namespace GME
{
  // Forward decl.
  class Object;
}

/**
 * @class GME_T2M_Parser
 *
 * Base class for all Text-2-Model parsers for GME.
 */
class GME_T2M_PARSER_Export GME_T2M_Parser
{
public:
  /// Destructor.
  virtual ~GME_T2M_Parser (void);

  /**
   * Parse the specified file and populate the model using \@parent as
   * the root element.
   *
   * @param[in]         filename            Name of the file.
   * @param[in]         project             Target project
   */
  virtual bool parse (const std::string & filename,
                      GME::Object & parent) = 0;

  /// Destroy the parser.
  virtual void destroy (void);

protected:
  /// Default constructor.
  GME_T2M_Parser (void);
};

/**
 *
 */
#define GME_T2M_CREATE_PARSER_FUNC \
  GME_T2M_create_parser

/**
 *
 */
#define GME_T2M_CREATE_PARSER_FUNC_STR \
  "GME_T2M_create_parser"

/**
 *
 */
#define GME_T2M_CREATE_PARSER_DECLARE(export_macro) \
  extern "C" export_macro GME_T2M_Parser * \
    GME_T2M_CREATE_PARSER_FUNC (void)

/**
 *
 */
#define GME_T2M_CREATE_PARSER_IMPLEMENT(parser_type) \
  GME_T2M_Parser * GME_T2M_CREATE_PARSER_FUNC (void) \
  { \
    return new parser_type (); \
  }

#if defined (__CUTS_INLINE__)
#include "T2M_Parser.inl"
#endif

#endif  // !defined _GME_T2M_PARSER_H_
