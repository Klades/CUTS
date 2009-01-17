// -*- C++ -*-

//=============================================================================
/**
 * @file        PICML_Assembly_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _PICML_ASSEMBLY_PARSER_H_
#define _PICML_ASSEMBLY_PARSER_H_

#include "PICML_Assembly_Parser_export.h"
#include "GME/T2M/parsers/T2M_Parser.h"

/**
 * @class PICML_Assembly_Parser
 */
class PICML_Assembly_Parser : public GME_T2M_Parser
{
public:
  /// Default constructor.
  PICML_Assembly_Parser (void);

  /// Destructor.
  virtual ~PICML_Assembly_Parser (void);

  /**
   * Parse the specified file and populate the model using \@parent as
   * the root element.
   *
   * @param[in]         filename            Name of the file.
   * @param[in]         project             Target project
   */
  virtual bool parse (const std::string & filename, GME::Object & parent);
};


GME_T2M_CREATE_PARSER_DECLARE (PICML_ASSEMBLY_PARSER_Export);

#if defined (__CUTS_INLINE__)
#include "PICML_Assembly_Parser.inl"
#endif

#endif  // !defined _PICML_ASSEMBLY_PARSER_H_
