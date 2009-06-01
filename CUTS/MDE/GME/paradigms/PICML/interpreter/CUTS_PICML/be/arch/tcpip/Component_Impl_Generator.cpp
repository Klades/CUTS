// $Id$

#include "Component_Impl_Generator.h"
#include "TCPIP_Ctx.h"
#include "../../BE_Options.h"

#include "../ccm/Component_Impl_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "../../lang/cpp/Component_Impl_Generator.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

namespace CUTS_BE_TCPIP
{
  static std::auto_ptr < Indentation::Implanter <Indentation::Cxx, char> > header_formatter_;

  static std::auto_ptr < Indentation::Implanter <Indentation::Cxx, char> > source_formatter_;

  static std::string monoimpl_;

/**
 * @class Executor_Include
 */
class Executor_Include : public PICML::Visitor
{
public:
  Executor_Include (std::ostream & out)
    : out_ (out)
  {

  }

  virtual ~Executor_Include (void)
  {

  }

  virtual void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation & monoimpl)
  {
    PICML::Implements implements = monoimpl.dstImplements ();

    if (Udm::null != implements)
      implements.Accept (*this);
  }

  virtual void Visit_Implements (const PICML::Implements & implements)
  {
    PICML::ComponentRef ref = implements.dstImplements_end ();
    ref.Accept (*this);
  }

  virtual void Visit_ComponentRef (const PICML::ComponentRef & ref)
  {
    PICML::Component component = ref.ref ();

    if (Udm::null != component)
      component.Accept (*this);
  }

  virtual void Visit_Component (const PICML::Component & component)
  {
    std::string exec_include (component.name ());
    exec_include += "EC";

    this->out_ << CUTS_BE_CPP::include (exec_include);
  }

private:
  std::ostream & out_;
};
}

//
// CUTS_BE_File_Open_T
//
bool CUTS_BE_File_Open_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & monoimpl)
{
  std::string source_filename =
    CUTS_BE_OPTIONS ()->output_directory_ + "/" +
    std::string (monoimpl.name ()) + ".cpp";

  std::string header_filename =
    CUTS_BE_OPTIONS ()->output_directory_ + "/" +
    std::string (monoimpl.name ()) + ".h";

  CUTS_BE_TCPIP_Ctx::header_.open (header_filename.c_str ());
  CUTS_BE_TCPIP_Ctx::source_.open (source_filename.c_str ());

  CUTS_BE_TCPIP::header_formatter_.reset (
    new Indentation::Implanter <Indentation::Cxx, char> (CUTS_BE_TCPIP_Ctx::header_));

  CUTS_BE_TCPIP::source_formatter_.reset (
    new Indentation::Implanter <Indentation::Cxx, char> (CUTS_BE_TCPIP_Ctx::source_));

  return CUTS_BE_TCPIP_Ctx::header_.is_open () &&
         CUTS_BE_TCPIP_Ctx::source_.is_open ();
}

//
// CUTS_BE_File_Close_T
//
bool CUTS_BE_File_Close_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::ComponentImplementationContainer & ,
          const PICML::MonolithicImplementation &)
{
  CUTS_BE_TCPIP::header_formatter_.reset (0);
  CUTS_BE_TCPIP_Ctx::header_.close ();

  CUTS_BE_TCPIP::source_formatter_.reset (0);
  CUTS_BE_TCPIP_Ctx::source_.close ();
  return true;
}

//
// CUTS_BE_Prologue_T
//
bool CUTS_BE_Prologue_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::ComponentImplementationContainer &,
          const PICML::MonolithicImplementation & monoimpl)
{
  std::string export_filename (monoimpl.name ());
  export_filename += "_export";

  CUTS_BE_TCPIP_Ctx::header_
    << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
    << std::endl;

  CUTS_BE_TCPIP::Executor_Include executor_include (CUTS_BE_TCPIP_Ctx::header_);
  PICML::MonolithicImplementation (monoimpl).Accept (executor_include);

  CUTS_BE_TCPIP_Ctx::header_
    << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Component_T")
    << CUTS_BE_CPP::include (export_filename)
    << std::endl;

  CUTS_BE_TCPIP_Ctx::source_
    << CUTS_BE_CPP::single_line_comment ("$Id$")
    << std::endl
    << CUTS_BE_CPP::include (monoimpl.name ())
    << std::endl;

  return true;
}

//
// CUTS_BE_Component_Impl_Begin_T
//
bool CUTS_BE_Component_Impl_Begin_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::MonolithicImplementation & monoimpl,
          const PICML::Component & component)
{
  CUTS_BE_TCPIP::monoimpl_ = monoimpl.name ();
  std::string component_name = component.name ();

  CUTS_BE_TCPIP_Ctx::header_
    << "typedef CUTS_CCM_Component_T <" << std::endl
    << "  ::CIDL_" << CUTS_BE_TCPIP::monoimpl_ << "::" << component_name << "_Exec," << std::endl
    << "  " << CUTS_BE_CPP::scope(component) << "CCM_"
    << component_name << "_Context > " << std::endl
    << "  " << CUTS_BE_TCPIP::monoimpl_ << "_Base;"
    << std::endl
    << "class " << CUTS_BE_TCPIP::monoimpl_ << " : public " << CUTS_BE_TCPIP::monoimpl_ << "_Base"
    << "{"
    << CUTS_BE_CPP::single_line_comment ("Consturctor")
    << CUTS_BE_TCPIP::monoimpl_ << " (void);"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("Destructor")
    << "virtual ~" << CUTS_BE_TCPIP::monoimpl_ << " (void);"
    << std::endl;

  CUTS_BE_TCPIP_Ctx::source_
    << CUTS_BE_CPP::function_header (CUTS_BE_TCPIP::monoimpl_)
    << CUTS_BE_TCPIP::monoimpl_ << "::" << CUTS_BE_TCPIP::monoimpl_ << " (void)";

  // Write the base member initialization section.
  CUTS_BE_CPP::Base_Member_Init bmi (CUTS_BE_TCPIP_Ctx::source_);
  PICML::Component (component).Accept (bmi);

  CUTS_BE_TCPIP_Ctx::source_
    << "{"
    << "}"
    // Write the destructor fro the component.
    << CUTS_BE_CPP::function_header ("~" + CUTS_BE_TCPIP::monoimpl_)
    << CUTS_BE_TCPIP::monoimpl_ << "::~" << CUTS_BE_TCPIP::monoimpl_ << " (void)"
    << "{"
    << "}";

  return true;
}

//
// CUTS_BE_Component_Impl_End_T
//
bool CUTS_BE_Component_Impl_End_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::MonolithicImplementation & monoimpl,
          const PICML::Component & component)
{
  CUTS_BE_TCPIP_Ctx::header_
    << "};";

  return true;
}

//
// CUTS_BE_Environment_Method_Begin_T
//
bool CUTS_BE_Environment_Method_Begin_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::MultiInputAction & action)
{
  std::string name = action.name ();

  if (name == "activate" ||
      name == "passivate" ||
      name == "remove")
  {
    CUTS_BE_TCPIP_Ctx::header_
      << CUTS_BE_CPP::single_line_comment ("environment: " + name)
      << "virtual void ccm_" << name << " (void);";

    CUTS_BE_TCPIP_Ctx::source_
      << CUTS_BE_CPP::function_header ("ccm_" + name)
      << "void " << CUTS_BE_TCPIP::monoimpl_ << "::ccm_" << name << " (void)"
      << "{";
  }
  else if (name == "configuration_complete")
  {
    CUTS_BE_TCPIP_Ctx::header_
      << CUTS_BE_CPP::single_line_comment ("environment: " + name)
      << "virtual void configuration_complete " << name << " (void);";

    CUTS_BE_TCPIP_Ctx::source_
      << CUTS_BE_CPP::single_line_comment ("environment: " + name)
      << "void " << CUTS_BE_TCPIP::monoimpl_ << "::configuration_complete " << name << " (void)"
      << "{";
  }

  return true;
}

//
// CUTS_BE_Environment_Method_End_T
//
bool CUTS_BE_Environment_Method_End_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::MultiInputAction & action)
{
  std::string name = action.name ();

  if (name == "activate" ||
      name == "passivate" ||
      name == "remove" ||
      name == "configuration_complete")
  {
    CUTS_BE_TCPIP_Ctx::source_ << "}";
  }

  return true;
}

//
// CUTS_BE_InEventPort_Begin_T
//
bool CUTS_BE_InEventPort_Begin_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
{
  PICML::Event event = sink.ref ();
  std::string fq_type = CUTS_BE_CPP::fq_type (event);

  std::string method ("push_");
  method += sink.name ();

  CUTS_BE_TCPIP_Ctx::header_
    << CUTS_BE_CPP::single_line_comment (method)
    << "virtual void " << method << " (" << fq_type << " * ev);"
    << std::endl;

  CUTS_BE_TCPIP_Ctx::source_
    << CUTS_BE_CPP::function_header (method)
    << "void " << CUTS_BE_TCPIP::monoimpl_ << "::"
    << method << " (" << fq_type << " * ev)"
    << "{";

  return true;
}

//
// CUTS_BE_InEventPort_End_T
//
bool CUTS_BE_InEventPort_End_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
{
  CUTS_BE_TCPIP_Ctx::source_
    << "ACE_UNUSED_ARG (ev);"
    << "}";

  return true;
}

//
// CUTS_BE_ReadonlyAttribute_Begin_T
//
bool CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_TCPIP_Ctx> ::
generate (const PICML::ReadonlyAttribute & attr)
{
  std::string name (attr.name ());
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType mtype = member.ref ();

  // Write the getter method for the attribute (header).
  CUTS_BE_TCPIP_Ctx::header_
    << CUTS_BE_CPP::single_line_comment ("Getter method for " + name)
    << "virtual ";

  CUTS_BE_CCM::Retn_Type_Generator retn_type_gen_header (CUTS_BE_TCPIP_Ctx::header_);
  retn_type_gen_header.generate (mtype);

  CUTS_BE_TCPIP_Ctx::header_
    << " " << name << " (void);" << std::endl;

  // Write the getter method for the attribute (source).
  CUTS_BE_TCPIP_Ctx::source_
    << CUTS_BE_CPP::function_header (name);

  CUTS_BE_CCM::Retn_Type_Generator retn_type_gen_source (CUTS_BE_TCPIP_Ctx::source_);
  retn_type_gen_source.generate (mtype);

  CUTS_BE_TCPIP_Ctx::source_
    << " " << CUTS_BE_TCPIP::monoimpl_ << "::" << name <<  " (void)"
    << "{";

  return true;
}

//
// CUTS_BE_ReadonlyAttribute_End_T
//
bool CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType mtype = member.ref ();
  Uml::Class metatype = mtype.type ();
  std::string name = attr.name ();

  if (metatype == PICML::String::meta)
  {
    // Strings are special case. We need to return a duplicate
    // copy of the string, or we will have major problems.
    CUTS_BE_TCPIP_Ctx::source_
      << "::CORBA::String_var s =" << std::endl
      << "  ::CORBA::string_dup (this->"
      << name << "_.c_str ());"
      << "return s._retn ();";
  }
  else if (metatype == PICML::GenericValue::meta)
  {
    // We need to create an <Any::_var_type> for temporary
    // storage and give control to the client using the
    // _retn () method.
    CUTS_BE_TCPIP_Ctx::source_
      << "CORBA::Any * temp = 0;"
      << "ACE_NEW_THROW_EX (temp, ::CORBA::Any (this->"
      << name << "_), ::CORBA::NO_MEMORY ());"
      << std::endl
      << "return temp;";
  }
  else if (metatype == PICML::GenericObject::meta)
  {
    CUTS_BE_TCPIP_Ctx::source_
      << "return ::CORBA::Object::_duplicate (this->"
      << name << "_.in ());";
  }
  else if (metatype == PICML::TypeEncoding::meta)
  {
    CUTS_BE_TCPIP_Ctx::source_
      << "return ::CORBA::TypeCode::_duplicate (this->"
      << name << "_.in ());";
  }
  else
  {
    CUTS_BE_TCPIP_Ctx::source_ << "return this->" << name << "_;";
  }

  CUTS_BE_TCPIP_Ctx::source_ << "}";

  return true;
}



//
// CUTS_BE_Attribute_Begin_T
//
bool CUTS_BE_Attribute_Begin_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::Attribute & attr)
{
  std::string name (attr.name ());
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType mtype = member.ref ();

  // Write the getter method for the attribute (header).
  CUTS_BE_TCPIP_Ctx::header_
    << CUTS_BE_CPP::single_line_comment ("Setter method for " + name)
    << "virtual void " << name << " (";

  CUTS_BE_CCM::In_Type_Generator in_type_gen_header (CUTS_BE_TCPIP_Ctx::header_);
  in_type_gen_header.generate (mtype);

  CUTS_BE_TCPIP_Ctx::header_
    << " " << name << ");"
    << std::endl;

  // Write the getter method for the attribute (source).
  CUTS_BE_TCPIP_Ctx::source_
    << CUTS_BE_CPP::function_header (name)
    << "void " << CUTS_BE_TCPIP::monoimpl_ << "::" << name
    << " (";

  CUTS_BE_CCM::In_Type_Generator in_type_gen_source (CUTS_BE_TCPIP_Ctx::source_);
  in_type_gen_source.generate (mtype);

  CUTS_BE_TCPIP_Ctx::source_
    << " " << name << ")"
    << "{";

  return true;
}

//
// CUTS_BE_Attribute_End_T
//
bool CUTS_BE_Attribute_End_T <CUTS_BE_TCPIP_Ctx>::
generate (const PICML::Attribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType mtype = member.ref ();
  Uml::Class metatype = mtype.type ();
  std::string name (attr.name ());

  CUTS_BE_TCPIP_Ctx::source_ << "this->" << name << "_ = ";

  if (metatype == PICML::GenericObject::meta)
  {
    // We need to create a duplicate copy of the interface
    // before we store it.
    CUTS_BE_TCPIP_Ctx::source_
      << std::endl
      << "  ::CORBA::Object::_duplicate (" << name << ");";
  }
  else if (metatype == PICML::TypeEncoding::meta)
  {
    // We need to create a duplicate copy of the typecode
    // interface before we store it.
    CUTS_BE_TCPIP_Ctx::source_
      << std::endl
      << "  ::CORBA::TypeCode::_duplicate (" << name << ");";
  }
  else
  {
    CUTS_BE_TCPIP_Ctx::source_
      << name << ";";
  }

  CUTS_BE_TCPIP_Ctx::source_ << "}";

  // Pass control the readonly-attributes.
  CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_TCPIP_Ctx>::generate (attr);
  CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_TCPIP_Ctx>::generate (attr);

  return true;
}

