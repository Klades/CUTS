// $Id$

#include "Servant_Implementation.h"
#include "Component_Implementation.h"
#include "In_Type_Generator.h"

#include "../../lang/cpp/Cpp.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_CCM
{
namespace Cpp
{

///////////////////////////////////////////////////////////////////////////////
// Servant_Set_Attribute_Decl

//
// Servant_Set_Attribute_Decl
//
Servant_Set_Attribute_Decl::Servant_Set_Attribute_Decl (std::ostream & out)
: out_ (out)
{

}

//
// ~Servant_Set_Attribute_Decl
//
Servant_Set_Attribute_Decl::~Servant_Set_Attribute_Decl (void)
{

}

void Servant_Set_Attribute_Decl::
Visit_Component (const PICML::Component & c)
{
  std::vector <PICML::Attribute> attrs = c.Attribute_kind_children ();

  if (attrs.empty ())
    return;

  this->out_
    << CUTS_BE_CPP::single_line_comment ("Set the component's attributes")
    << "virtual void set_attributes (const ::Components::ConfigValues & config);";
}

///////////////////////////////////////////////////////////////////////////////
// Servant_Set_Attribute_Impl

//
// Servant_Set_Attribute_Impl
//
Servant_Set_Attribute_Impl::Servant_Set_Attribute_Impl (std::ostream & out)
: out_ (out)
{

}

//
// ~Servant_Set_Attribute_Impl
//
Servant_Set_Attribute_Impl::~Servant_Set_Attribute_Impl (void)
{

}

void Servant_Set_Attribute_Impl::
Visit_Component (const PICML::Component & c)
{
  std::vector <PICML::Attribute> attrs = c.Attribute_kind_children ();

  if (attrs.empty ())
    return;

  this->out_
    << CUTS_BE_CPP::function_header ("set_attributes")
    << "void " << c.name () << "_Servant::" << std::endl
    << "set_attributes (const ::Components::ConfigValues & config)"
    << "{"
    << "const ::CORBA::ULong length = config.length ();"
    << std::endl
    << "for (::CORBA::ULong i = 0; i < length; ++ i)"
    << "{"
    << CUTS_BE_CPP::single_line_comment ("get the next configuraton value")
    << "const ::Components::ConfigValue * value = config[i];"
    << std::endl;

  std::vector <PICML::Attribute>::iterator
    iter = attrs.begin (), iter_end = attrs.end ();

  // Visit the first attribute since we are going to create a series
  // of if-else statements.
  iter->Accept (*this);

  for (++ iter; iter != iter_end; ++ iter)
  {
    // Visit the next attribute in the collection.
    this->out_ << "else ";
    iter->Accept (*this);
  }

  this->out_
    << "}"
    << "}";
}

//
// Visit_Attribute
//
void Servant_Set_Attribute_Impl::
Visit_Attribute (const PICML::Attribute & a)
{
  const std::string name (a.name ());

  this->out_
    << "if (0 == ACE_OS::strcmp (value->name (), \"" << name << "\"))"
    << "{";

  PICML::AttributeMember am = a.AttributeMember_child ();
  PICML::MemberType mt = am.ref ();

  if (::Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    CUTS_BE_CCM::Cpp::In_Type_Generator type_gen (this->out_);
    type_gen.generate (mt);

    this->out_
      << " tmp_value;"
      << std::endl
      << "if (!(value->value () >>= tmp_value))" << std::endl
      << "  throw ::Components::InvalidConfiguration ();"
      << std::endl
      << "this->" << name << " (tmp_value);";
  }
  else
  {
    this->out_
      << CUTS_BE_CPP::fq_type (PICML::NamedType::Cast (mt), "::") << " * ptr = 0;"
      << std::endl
      << "if (!(value->value () >>= ptr))"
      << std::endl
      << "  throw ::CIAO::InvalidConfiguration ();"
      << std::endl
      << "this->" << name << " (ptr);";
  }

  this->out_
    << "}";
}

}
}
