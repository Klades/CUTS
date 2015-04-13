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
std::string CUTS_BE_Type_Map::value (const PICML::MemberType_in type)
{
  try
  {
    PICML::PredefinedType ptype = PICML::PredefinedType::_narrow (type);
    return this->value (ptype);
  }
  catch (...)
  {
    PICML::NamedType ntype = PICML::NamedType::_narrow (type);
    return this->value (ntype);
  }

  return "";
}

//
// value
//
std::string CUTS_BE_Type_Map::value (const PICML::NamedType_in type)
{
  std::stack <GAME::Mga::Object> scope;

  // Get the initial parent of the type.
  GAME::Mga::Object parent = type->parent ();

  // Locate the parent file for this type.
  while (parent->meta ()->name () != PICML::File::impl_type::metaname)
  {
    // Push the next object onto the scope stack.
    scope.push (parent);

    // Get the next parent object.
    parent = parent->parent ();
  }

  std::ostringstream ostr;

  while (!scope.empty ())
  {
    // Get get the next object/scope.
    parent = scope.top ();
    scope.pop ();

    // Append the object's name and the scope separator. We
    // need to parameterize the scope seperator.
    ostr << "::" << parent->name (); 
  }

  // Append the name of the type.
  ostr << "::" << type->name ();

  // Return the scoped name of the type.
  return ostr.str ();
}
