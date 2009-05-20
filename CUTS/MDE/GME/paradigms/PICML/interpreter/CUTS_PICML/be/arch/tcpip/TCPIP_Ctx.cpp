// $Id$

#include "TCPIP_Ctx.h"
#include "Uml.h"
#include <sstream>
#include <stack>

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

//
// scope
//
std::string CUTS_BE_TCPIP_Ctx::scope (const PICML::NamedType & type,
                                      const std::string & separator,
                                      bool leading)
{
  std::string scope;
  std::stack <PICML::MgaObject> temp_stack;

  // Continue walking up the tree until we reach a File object.
  PICML::MgaObject parent = PICML::MgaObject::Cast (type.parent ());

  while (PICML::File::meta != parent.type () )
  {
    temp_stack.push (parent);
    parent = PICML::MgaObject::Cast (parent.parent ());
  }

  // Insert the leading separator, if applicable.
  if (leading)
    scope += separator;

  // Empty the remainder of the stack.
  while (!temp_stack.empty ())
  {
    parent = temp_stack.top ();
    temp_stack.pop ();

    scope += std::string (parent.name ()) + separator;
  }

  return scope;
}

//
// fq_type
//
std::string CUTS_BE_TCPIP_Ctx::fq_type (const PICML::NamedType & type,
                                        const std::string & separator,
                                        bool leading)
{
  return
    CUTS_BE_TCPIP_Ctx::scope (type, separator, leading) +
    std::string (type.name ());
}
