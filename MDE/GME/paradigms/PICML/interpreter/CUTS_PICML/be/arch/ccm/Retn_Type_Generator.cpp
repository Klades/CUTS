// $Id$

#include "Retn_Type_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Retn_Type_Generator.inl"
#endif

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// is_variable_type
//
bool Retn_Type_Generator::
is_variable_type (const PICML::MemberType_in type)
{
  std::string metaname = type->meta ()->name ();

  if (metaname == PICML::String::impl_type::metaname)
    return true;
  else if (metaname == PICML::GenericValue::impl_type::metaname)
    return true;
  else if (metaname == PICML::Aggregate::impl_type::metaname)
  {
    // Extract the aggregate from the member type.
    const PICML::Aggregate aggr = type;

    for (auto member : aggr->get_Members ())
    {
      if (member->MemberType_is_nil ())
        continue;

      if (this->is_variable_type (member->refers_to_MemberType ()))
        return true;
    }
  }
  else if (metaname == PICML::SwitchedAggregate::impl_type::metaname)
  {
    const PICML::SwitchedAggregate swaggr = type;

    for (auto member : swaggr->get_Members ())
    {
      if (member->MemberType_is_nil ())
        continue;

      if (this->is_variable_type (member->refers_to_MemberType ()))
        return true;
    }
  }
  else if (metaname == PICML::Collection::impl_type::metaname)
  {
    return true;
  }
  else if (metaname == PICML::Alias::impl_type::metaname)
  {
    const PICML::Alias alias = type;
    if (alias->MemberType_is_nil ())
      return false;

    if (this->is_variable_type (alias->refers_to_MemberType ()))
      return true;
  }

  return false;
}

}
}
