// -*- C++ -*-

//=============================================================================
/**
 * @file        URI_Tag_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_URI_TAG_PARSER_H_
#define _CUTS_URI_TAG_PARSER_H_

#include <string>

//=============================================================================
/**
 * @class CUTS_URI_Tag_Parser
 */
//=============================================================================

class CUTS_URI_Tag_Parser
{
public:
  /// Default constructor.
  CUTS_URI_Tag_Parser (void);

  /// Destructor.
  ~CUTS_URI_Tag_Parser (void);

  /**
   * Parse the URI. This will either check for the specified URI,
   * or get the current URI.
   *
   * @param[in]       uri         Source URI.
   * @param[inout]    attr        NAOMI attribute
   * @param[out]      gme_attr    The GME attribute.
   */
  bool parse (const std::string & uri, 
              std::string & attr,
              std::string & gme_attr);
};

#endif  // !defined _CUTS_URI_TAG_PARSER_H_
