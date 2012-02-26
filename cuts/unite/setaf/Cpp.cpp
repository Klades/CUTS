// $Id:

#include "Cpp.h"
#include <sstream>


namespace CUTS_SETAF_CPP
{
//
// include
//
std::string include (const std::string & filename)
{
  std::ostringstream ostr;
  ostr << "#include \"" << filename << ".h\"" << std::endl;

  return ostr.str ();
}

//
// single_line_comment
//
std::string single_line_comment (const std::string & comment)
{
  std::string str ("// ");
  str += comment + "\n";

  return str;
}

//
// function_header
//
std::string function_header (const std::string & func)
{
  std::string str ("//\n");
  str += "// " + func + "\n" + "//\n";
  return str;
}

}