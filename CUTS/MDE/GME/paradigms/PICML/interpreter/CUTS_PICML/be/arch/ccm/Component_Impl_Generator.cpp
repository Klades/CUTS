// $Id$

#include "Component_Impl_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "Uml.h"

namespace CUTS_BE_CCM
{
///////////////////////////////////////////////////////////////////////////////
// Type_System

//
// Type_System
//
Type_System::Type_System (std::ostream & out)
: out_ (out),
  predefined_types_ (this)
{
  this->predefined_types_.insert <PICML::Boolean> ();
  this->predefined_types_.insert <PICML::Byte> ();
  this->predefined_types_.insert <PICML::GenericObject> ();
  this->predefined_types_.insert <PICML::GenericValue> ();
  this->predefined_types_.insert <PICML::LongInteger> ();
  this->predefined_types_.insert <PICML::RealNumber> ();
  this->predefined_types_.insert <PICML::ShortInteger> ();
  this->predefined_types_.insert <PICML::String> ();
  this->predefined_types_.insert <PICML::TypeEncoding> ();
  this->predefined_types_.insert <PICML::TypeKind> ();
}

//
// ~Type_System
//
Type_System::~Type_System (void)
{
}

//
// generate
//
void Type_System::generate (const PICML::MemberType & mt)
{
  if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    PICML::PredefinedType ptype = PICML::PredefinedType::Cast (mt);
    this->predefined_types_.dispatch (ptype);
  }
  else
  {
    PICML::NamedType named = PICML::NamedType::Cast (mt);
    this->out_ << CUTS_BE_CPP::fq_type (named);
  }
}


///////////////////////////////////////////////////////////////////////////////
// In_Type_Generator

//
// In_Type_Generator
//
In_Type_Generator::In_Type_Generator (std::ostream & out)
: Type_System (out)

{
}

//
// ~In_Type_Generator
//
In_Type_Generator::~In_Type_Generator (void)
{

}

//
// Visit_Boolean
//
void In_Type_Generator::
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
void In_Type_Generator::
Visit_Byte (const PICML::Byte & byte)
{
  this->out_ << "::CORBA::Octet";
}

//
// Visit_LongInteger
//
void In_Type_Generator::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "::CORBA::Long";
}

//
// Visit_ShortInteger
//
void In_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short";
}

//
// Visit_String
//
void In_Type_Generator::
Visit_String (const PICML::String & value)
{
  this->out_ << "const char *";
}

//
// Visit_RealNumber
//
void In_Type_Generator::
Visit_RealNumber (const PICML::RealNumber & value)
{
  this->out_ << "::CORBA::Double";
}

//
// Visit_GenericValue
//
void In_Type_Generator::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "const ::CORBA::Any &";
}

//
// Visit_GenericObject
//
void In_Type_Generator::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "::CORBA::Object_ptr";
}

//
// Visit_TypeKind
//
void In_Type_Generator::
Visit_TypeKind (const PICML::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// Visit_TypeEncoding
//
void In_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_ptr";
}

///////////////////////////////////////////////////////////////////////////////
// Out_Type_Generator

//
// Out_Type_Generator
//
Out_Type_Generator::Out_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~Out_Type_Generator
//
Out_Type_Generator::~Out_Type_Generator (void)
{

}

//
// Visit_Boolean
//
void Out_Type_Generator::
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "::CORBA::Boolean_out";
}

//
// Visit_Byte
//
void Out_Type_Generator::
Visit_Byte (const PICML::Byte & byte)
{
  this->out_ << "::CORBA::Octet_out";
}

//
// Visit_LongInteger
//
void Out_Type_Generator::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "::CORBA::Long_out";
}

//
// Visit_ShortInteger
//
void Out_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short_out";
}

//
// Visit_String
//
void Out_Type_Generator::
Visit_String (const PICML::String & value)
{
  this->out_ << "::CORBA::String_out";
}

//
// Visit_RealNumber
//
void Out_Type_Generator::
Visit_RealNumber (const PICML::RealNumber & value)
{
  this->out_ << "::CORBA::Double_out";
}

//
// Visit_GenericValue
//
void Out_Type_Generator::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "::CORBA::Any_out";
}

//
// Visit_GenericObject
//
void Out_Type_Generator::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "::CORBA::Object_out";
}

//
// Visit_TypeKind
//
void Out_Type_Generator::
Visit_TypeKind (const PICML::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind_out";
}

//
// Visit_TypeEncoding
//
void Out_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_out";
}

///////////////////////////////////////////////////////////////////////////////
// In_Out_Type_Generator

//
// In_Out_Type_Generator
//
In_Out_Type_Generator::In_Out_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~In_Out_Type_Generator
//
In_Out_Type_Generator::~In_Out_Type_Generator (void)
{

}

//
// Visit_Boolean
//
void In_Out_Type_Generator::
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "::CORBA::Boolean &";
}

//
// Visit_Byte
//
void In_Out_Type_Generator::
Visit_Byte (const PICML::Byte & byte)
{
  this->out_ << "::CORBA::Octet &";
}

//
// Visit_LongInteger
//
void In_Out_Type_Generator::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "::CORBA::Long &";
}

//
// Visit_ShortInteger
//
void In_Out_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short &";
}

//
// Visit_String
//
void In_Out_Type_Generator::
Visit_String (const PICML::String & value)
{
  this->out_ << "::CORBA::String * &";
}

//
// Visit_RealNumber
//
void In_Out_Type_Generator::
Visit_RealNumber (const PICML::RealNumber & value)
{
  this->out_ << "::CORBA::Double &";
}

//
// Visit_GenericValue
//
void In_Out_Type_Generator::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "::CORBA::Any &";
}

//
// Visit_GenericObject
//
void In_Out_Type_Generator::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "::CORBA::Object_ptr &";
}

//
// Visit_TypeKind
//
void In_Out_Type_Generator::
Visit_TypeKind (const PICML::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind &";
}

//
// Visit_TypeEncoding
//
void In_Out_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_ptr &";
}

///////////////////////////////////////////////////////////////////////////////
// Retn_Type_Generator

//
// Retn_Type_Generator
//
Retn_Type_Generator::Retn_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~Retn_Type_Generator
//
Retn_Type_Generator::~Retn_Type_Generator (void)
{

}

//
// generate
//
void Retn_Type_Generator::
generate (const PICML::MemberType & type)
{
  Type_System::generate (type);

  if (this->is_variable_type (type))
    this->out_ << " *";
}

//
// Visit_Boolean
//
void Retn_Type_Generator::
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
void Retn_Type_Generator::
Visit_Byte (const PICML::Byte & byte)
{
  this->out_ << "::CORBA::Octet";
}

//
// Visit_LongInteger
//
void Retn_Type_Generator::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "::CORBA::Long";
}

//
// Visit_ShortInteger
//
void Retn_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short";
}

//
// Visit_String
//
void Retn_Type_Generator::
Visit_String (const PICML::String & value)
{
  this->out_ << "char";
}

//
// Visit_RealNumber
//
void Retn_Type_Generator::
Visit_RealNumber (const PICML::RealNumber & value)
{
  this->out_ << "::CORBA::Double";
}

//
// Visit_GenericValue
//
void Retn_Type_Generator::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "::CORBA::Any";
}

//
// Visit_GenericObject
//
void Retn_Type_Generator::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "::CORBA::Object_ptr";
}

//
// Visit_TypeKind
//
void Retn_Type_Generator::
Visit_TypeKind (const PICML::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// Visit_TypeEncoding
//
void Retn_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_ptr";
}

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


///////////////////////////////////////////////////////////////////////////////
// Attribute_Method_Generator

//
// Attribute_Method_Generator
//
Attribute_Method_Generator::Attribute_Method_Generator (std::ostream & out)
: out_ (out)
{

}

//
// ~Attribute_Method_Generator
//
Attribute_Method_Generator::~Attribute_Method_Generator (void)
{

}

//
// Visit_Attribute
//
void Attribute_Method_Generator::
Visit_Attribute (const PICML::Attribute & attr)
{
  // Write the name of the attribute method.
  std::string name = attr.name ();
  this->out_ << name << " (";

  PICML::AttributeMember member = attr.AttributeMember_child ();

  if (Udm::null != member)
    member.Accept (*this);

  this->out_ << " " << name << ")";
}

//
// Visit_AttributeMember
//
void Attribute_Method_Generator::
Visit_AttributeMember (const PICML::AttributeMember & member)
{
  PICML::MemberType mtype = member.ref ();

  if (Udm::null != mtype)
  {
    In_Type_Generator intype (this->out_);
    intype.generate (mtype);
  }
}

//
// Visit_ReadonlyAttribute
//
void Attribute_Method_Generator::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & ro_attr)
{
  this->out_ << ro_attr.name () << " (void)";
}

//
// InEvent_Method_Generator
//
InEvent_Method_Generator::
InEvent_Method_Generator (std::ostream & out)
: out_ (out)
{

}

//
// ~InEvent_Method_Generator
//
InEvent_Method_Generator::~InEvent_Method_Generator (void)
{

}

//
// Visit_InEventPort
//
void InEvent_Method_Generator::
Visit_InEventPort (const PICML::InEventPort & port)
{
  this->out_ << "push_" << port.name () << " (";

}

}
