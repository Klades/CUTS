// $Id:
#ifndef _CUTS_SETAF_PARSER_H_
#define _CUTS_SETAF_PARSER_H_

#include "Setaf_Interpreter.h"
#include <fstream>


/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Parser
 *
 * Represent the parser for the SETAFA interpreter.
 */


typedef std::vector <std::string> string_vector;

class CUTS_SETAF_Export CUTS_Setaf_Parser
{

public:
  /// Default Constructor
  CUTS_Setaf_Parser (void);

  /// Destructor
  ~CUTS_Setaf_Parser (void);

  /**
   * Parse the specification.
   * @param[in]     input           The input stream from the spec.
   * @param[in]     interpreter     The interpreter object need to be populated.
   */
  bool parse_spec (std::istream & input,
                   CUTS_Setaf_Interpreter * interpreter);
};

#endif // !defined _CUTS_SETAF_PARSER_H_