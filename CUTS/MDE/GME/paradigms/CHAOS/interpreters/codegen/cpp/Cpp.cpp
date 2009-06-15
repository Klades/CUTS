// $Id$

#include "StdAfx.h"
#include "Cpp.h"
#include "Uml.h"
#include <sstream>
#include <stack>

namespace CUTS_BE_CPP
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
// scope
//
std::string scope (const CHAOS::NamedType & type,
                   const std::string & separator,
                   bool leading)
{
  std::string scope;
  std::stack <CHAOS::MgaObject> temp_stack;

  // Continue walking up the tree until we reach a File object.
  CHAOS::MgaObject parent = CHAOS::MgaObject::Cast (type.parent ());

  while (CHAOS::File::meta != parent.type () )
  {
    temp_stack.push (parent);
    parent = CHAOS::MgaObject::Cast (parent.parent ());
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
std::string fq_type (const CHAOS::NamedType & type,
                     const std::string & separator,
                     bool leading)
{
  return
    scope (type, separator, leading) +
    std::string (type.name ());
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
