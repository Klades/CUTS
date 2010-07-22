// -*- C++ -*-

//=============================================================================
/**
 * @class       Javap_Output_Parser.hpp
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_JAVA_OUTPUT_PARSER_HPP_
#define _QUOTAS_JAVA_OUTPUT_PARSER_HPP_

#include <istream>
#include <map>

namespace GAME
{
namespace XME
{
class Folder;
class FCO;

}
}

/**
 * @class Quotas_Javap_Output_Parser
 *
 * Parser class for parsing Javap output.
 */
class Quotas_Javap_Output_Parser
{
public:
  /// Default constructor.
  Quotas_Javap_Output_Parser (void);

  /// Destructor.
  ~Quotas_Javap_Output_Parser (void);

  /**
   * Parse the specified input stream.
   */
  bool parse (std::istream & stream,
              std::map <std::string, GAME::XME::FCO> & symbols,
              GAME::XME::Folder & idl_folder);
};

#endif  // !defined _JAVA_OUTPUT_PARSER_HPP_
