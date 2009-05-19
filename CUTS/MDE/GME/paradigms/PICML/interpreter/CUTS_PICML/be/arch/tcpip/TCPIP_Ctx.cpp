// $Id$

#include "TCPIP_Ctx.h"
#include <sstream>

//
// include
//
std::string CUTS_BE_TCPIP_Ctx::include (const std::string & filename)
{
  std::ostringstream ostr;
  ostr << "#include \"" << filename << ".h\"" << std::endl;

  return ostr.str ();
}

//
// single_line_comment
//
std::string CUTS_BE_TCPIP_Ctx::single_line_comment (const std::string & comment)
{
  std::string str ("// ");
  str += comment + "\n";

  return str;
}
