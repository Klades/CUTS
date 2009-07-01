// $Id$

#include "Java.h"
#include "Uml.h"
#include <sstream>
#include <stack>

namespace CUTS_BE_Java
{
//
// include
//
std::string include (const std::string & filename)
{
  std::ostringstream ostr;
  ostr << "import \"" << filename << ";" << std::endl;

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
std::string scope (const PICML::NamedType & type,
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
std::string fq_type (const PICML::NamedType & type,
                     const std::string & separator,
                     bool leading)
{
  return scope (type, separator, leading) + std::string (type.name ());
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

//
// setter_method
//
std::string setter_method (const std::string & name)
{
  std::string temp (name);
  temp[0] = ::toupper (temp[0]);

  std::string setter ("set");
  setter.append (temp);

  return setter;
}

//
// getter_method
//
std::string getter_method (const std::string & name)
{
  std::string temp (name);
  temp[0] = ::toupper (temp[0]);

  std::string getter ("get");
  getter.append (temp);

  return getter;
}

//
// classname
//
std::string classname (const std::string & str)
{
  std::string name = str;
  name[0] = ::toupper (name[0]);

  return name;
}

//
// import
//
std::string import (const PICML::Worker & worker)
{
  // Initialize the import scope.
  std::stack <std::string> scope;
  scope.push (worker.name ());

  // Move up the tree until we reach a File (i.e., while we
  // are still working with Package elements).
  PICML::MgaObject parent = worker.parent ();

  while (parent.type () != PICML::WorkerFile::meta)
  {
    scope.push (parent.name ());
    parent = ::PICML::MgaObject::Cast (parent.parent ());
  }

  std::ostringstream ostr;

  // Write the top value since the remaining items in the scope
  // will have the '.' prepended.
  ostr << scope.top ();
  scope.pop ();

  // Construct the remainder of the name.
  while (!scope.empty ())
  {
    ostr << '.' << scope.top ();
    scope.pop ();
  }

  return ostr.str ();
}

//
// Context
//
Context::Context (void)
: jbi_anyevent_ (std::make_pair ("cuts.jbi.client.JbiAnyEvent", "cuts/jbi/client/JbiAnyEvent"))
{

}

//
// generate_accessor_methods
//
void Context::
generate_accessor_methods (std::string type, std::string varname)
{
  std::string tmp_varname (varname);
  tmp_varname[0] = ::toupper (tmp_varname[0]);

  this->source_
    << std::endl
    << "public " << type << " get" << tmp_varname << " ()"
    << "{"
    << "return this." << varname << "_;"
    << "}"
    << std::endl
    << "public void set" << tmp_varname
    << " (" << type << " " << varname << ")"
    << "{"
    << "this." << varname << "_ = " << varname << ";"
    << "}";
}

}
