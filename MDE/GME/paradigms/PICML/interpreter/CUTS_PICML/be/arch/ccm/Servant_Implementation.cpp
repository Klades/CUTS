// $Id$

#include "Servant_Implementation.h"
#include "Component_Implementation.h"
#include "In_Type_Generator.h"

#include "../../lang/cpp/Cpp.h"

#include <algorithm>

namespace CUTS_BE_CCM
{
namespace Cpp
{

template <typename BASE>
struct derives_from
{
public:
template <typename T>
bool operator () (const T & derived) const
{
  try
  {
    BASE base = BASE::_narrow (derived);
    return true;
  }
  catch (GAME::Mga::Exception &)
  {
    return false;
  }
}
};

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
visit_Component (PICML::Component_in c)
{
  if (c->get_Attributes ().count () == 0)
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
visit_Component (PICML::Component_in c)
{
  auto attrs = c->get_Attributes ();

  if (attrs.count () == 0)
    return;

  this->out_
    << CUTS_BE_CPP::function_header ("set_attributes")
    << "void " << c->name () << "_Servant::" << std::endl
    << "set_attributes (const ::Components::ConfigValues & config)"
    << "{"
    << "const ::CORBA::ULong length = config.length ();"
    << std::endl
    << "for (::CORBA::ULong i = 0; i < length; ++ i)"
    << "{"
    << CUTS_BE_CPP::single_line_comment ("get the next configuraton value")
    << "const ::Components::ConfigValue * value = config[i];"
    << std::endl;

  bool first = true;
  for (auto attr : attrs)
  {
    if (!first)
      this->out_ << "else ";
    else
      first = false;

    attr->accept (this);
  }

  this->out_
    << "}"
    << "}";
}

//
// visit_Attribute
//
void Servant_Set_Attribute_Impl::
visit_Attribute (PICML::Attribute_in a)
{
  const std::string name (a->name ());

  this->out_
    << "if (0 == ACE_OS::strcmp (value->name (), \"" << name << "\"))"
    << "{";

  PICML::AttributeMember am = a->get_AttributeMember ();
  PICML::MemberType mt = am->refers_to_MemberType ();

  if (derives_from <PICML::PredefinedType> () (mt))
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
      << CUTS_BE_CPP::fq_type (PICML::NamedType::_narrow (mt), "::") << " * ptr = 0;"
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
