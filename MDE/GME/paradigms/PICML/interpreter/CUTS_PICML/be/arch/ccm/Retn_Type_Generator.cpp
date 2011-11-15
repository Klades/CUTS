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
is_variable_type (const PICML::MemberType & type)
{
  bool result;
  Uml::Class meta_type = type.type ();

  if (Udm::IsDerivedFrom (meta_type, PICML::PredefinedType::meta))
  {
    result = (meta_type == PICML::String::meta || meta_type == PICML::GenericValue::meta);
  }
  else if (meta_type == PICML::Aggregate::meta)
  {
    // Extract the aggregate from the member type.
    const PICML::Aggregate aggr = PICML::Aggregate::Cast (type);

    // Get the members of the aggregate.
    typedef std::vector <PICML::Member> Member_Set;
    Member_Set members = aggr.Member_children ();

    Member_Set::const_iterator
      iter = members.begin (),
      iter_end = members.end ();

    // Initialize the result.
    result = false;

    for (; iter != iter_end; iter ++)
    {
      // Get the next member in the data structure.
      PICML::MemberType mtype = iter->ref ();

      // Determine if it is a variable type.
      if (mtype != Udm::null)
        result |= this->is_variable_type (mtype);

      // We can quit once we have found one.
      if (result)
        break;
    }
  }
  else if (meta_type == PICML::SwitchedAggregate::meta)
  {
    const PICML::SwitchedAggregate swaggr = PICML::SwitchedAggregate::Cast (type);

    // Get the members of the aggregate.
    typedef std::vector <PICML::Member> Member_Set;
    Member_Set members = swaggr.Member_children ();

    Member_Set::const_iterator
      iter = members.begin (),
      iter_end = members.end ();

    // Initialize the result.
    result = false;

    for (; iter != iter_end; iter ++)
    {
      // Get the next member in the data structure.
      PICML::MemberType mtype = iter->ref ();

      // Determine if it is a variable type.
      if (mtype != Udm::null)
        result |= this->is_variable_type (mtype);

      // We can quit once we have found one.
      if (result)
        break;
    }
  }
  else if (meta_type == PICML::Collection::meta)
  {
    result = true;
  }
  else if (meta_type == PICML::Alias::meta)
  {
    const PICML::Alias alias = PICML::Alias::Cast (type);
    PICML::MemberType mtype = alias.ref ();

    if (mtype != Udm::null)
      result = this->is_variable_type (mtype);
  }
  else
  {
    result = false;
  }

  return result;
}

}
}
