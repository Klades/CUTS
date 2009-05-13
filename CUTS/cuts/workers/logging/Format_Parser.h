// -*- C++ -*-

//=============================================================================
/**
 * @file            Format_Parser.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_FORMAT_PARSER_H_
#define _CUTS_TEST_LOGGER_FORMAT_PARSER_H_

#include <sstream>

/**
 * @class CUTS_Format_Parser
 */
class CUTS_Format_Parser
{
public:
  /// Default constructor.
  CUTS_Format_Parser (void);

  /// Destructor.
  ~CUTS_Format_Parser (void);

  /**
   * Parse a format string. This will replace all the tokens with
   * their corresponding argument.
   *
   */
  bool parse (const char * format, va_list args, std::ostringstream & out);
};

#endif  // !defined _CUTS_TEST_LOGGER_FORMAT_PARSER_H_
