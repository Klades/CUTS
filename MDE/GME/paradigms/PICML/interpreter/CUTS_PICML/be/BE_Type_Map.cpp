// $Id$

#include "BE_Type_Map.h"

#if !defined (__CUTS_INLINE__)
#include "BE_Type_Map.inl"
#endif

#include <stack>
#include <sstream>

//
// value
//
std::string CUTS_BE_Type_Map::value (const PICML::MemberType & type)
{
  try
  {
    PICML::PredefinedType ptype = PICML::PredefinedType::Cast (type);
    return this->value (ptype);
  }
  catch (...)
  {
    PICML::NamedType ntype = PICML::NamedType::Cast (type);
    return this->value (ntype);
  }

  return "";
}

//
// value
//
std::string CUTS_BE_Type_Map::value (const PICML::NamedType & type)
{
  std::stack <PICML::MgaObject> scope;

  // Get the initial parent of the type.
  PICML::MgaObject parent = type.parent ();

  // Locate the parent file for this type.
  while (parent.type () != PICML::File::meta)
  {
    // Push the next object onto the scope stack.
    scope.push (parent);

    // Get the next parent object.
    parent = PICML::MgaObject::Cast (parent.parent ());
  }

  std::ostringstream ostr;

  while (!scope.empty ())
  {
    // Get get the next object/scope.
    parent = scope.top ();
    scope.pop ();

    // Append the object's name and the scope separator. We
    // need to parameterize the scope seperator.
    ostr << "::" << parent.name (); 
  }

  // Append the name of the type.
  ostr << "::" << type.name ();

  // Return the scoped name of the type.
  return ostr.str ();
}
