// $Id$

#include "Servant_Generator.h"
#include "Servant_Header_Include_Generator.h"
#include "Context_Generator.h"

#include "../../ccm/Component_Implementation.h"
#include "../../ccm/Servant_Implementation.h"

#include "../../../UDM_Utility_T.h"
#include "../../../lang/cpp/Cpp.h"
#include "../../../BE_algorithm.h"

#include "boost/bind.hpp"
#include "boost/iterator/filter_iterator.hpp"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_BE_RTIDDS
{
class Servant_Base_Member_Init : public PICML::Visitor
{
public:
  Servant_Base_Member_Init (std::ostream & source, const std::string & servant)
    : source_ (source),
      servant_ (servant)
  {

  }

  virtual ~Servant_Base_Member_Init (void)
  {

  }

  virtual void Visit_InEventPort (const PICML::InEventPort & input)
  {
    std::string name = input.name ();

    this->source_
      << "," << std::endl
      << "   " << name << "_consumer_ (this, &"
      << this->servant_ << "::deserialize_" << name << ")";
  }

private:
  std::ostream & source_;

  const std::string & servant_;
};

class Port_Binder : public PICML::Visitor
{
public:
  Port_Binder (std::ostream & source)
    : source_ (source)
  {

  }

  virtual ~Port_Binder (void)
  {

  }

  virtual void Visit_InEventPort (const PICML::InEventPort & port)
  {
    std::string name = port.name ();

    this->source_
      << "this->consumers_.bind (\"" << name << "\", &this->"
      << name << "_consumer_);";
  }

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port)
  {
    std::string name = port.name ();

    if (port.single_destination ())
    {
      this->source_
        << "this->emits_.bind (\"" << name
        << "\", &this->ctx_->writer_" << name << " ());";
    }
    else
    {
      this->source_
        << "this->publishes_.bind (\"" << name
        << "\", &this->ctx_->writers_" << name << " ());";
    }
  }

private:
  std::ostream & source_;
};

//
// Servant_Generator
//
Servant_Generator::
Servant_Generator (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~Servant_Generator
//
Servant_Generator::~Servant_Generator (void)
{

}

//
// Visit_RootFolder
//
void Servant_Generator::
Visit_RootFolder (const PICML::RootFolder & folder)
{
  std::set <PICML::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();
  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&PICML::InterfaceDefinitions::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_InterfaceDefinitions
//
void Servant_Generator::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions & folder)
{
  std::vector <PICML::File> files = folder.File_children ();
  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&PICML::File::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementations
//
void Servant_Generator::Visit_File (const PICML::File & file)
{
  if (!CUTS_BE::has_component (file))
    return;

  // Construct the name of the output file.
  std::string name = file.name ();
  std::string basename = name + "_svnt";

  std::string source_filename (this->outdir_);
  source_filename += "/" + basename + ".cpp";

  std::string header_filename (this->outdir_);
  header_filename += "/" + basename + ".h";


  // Open the file for writing.
  this->header_.open (header_filename.c_str ());
  this->source_.open (source_filename.c_str ());

  if (!this->header_.is_open () && !this->source_.is_open ())
    return;

  std::string hash_define = "_" + name + "_SVNT_H_";

  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  // Construct the exp macro for this file.
  std::string export_filename = std::string (file.name ()) + "_svnt_export";
  this->export_macro_ = name + "_SVNT";

  std::transform (this->export_macro_.begin (),
                  this->export_macro_.end (),
                  this->export_macro_.begin (),
                  &::toupper);

  this->export_macro_ += "_Export";

  do
  {
    // Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> header_formatter (this->header_);
    Indentation::Implanter <Indentation::Cxx, char> soruce_formatter (this->source_);

    // Include the header file.
    this->header_
      << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
      << std::endl
      << "#ifndef " << hash_define << std::endl
      << "#define " << hash_define << std::endl
      << std::endl
      << CUTS_BE_CPP::include (name + "EC")
      << CUTS_BE_CPP::include (name + "S")
      << CUTS_BE_CPP::include ("RTIDDS_" + name + "C")
      << std::endl
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Context_T")
      << CUTS_BE_CPP::include ("cuts/arch/rtidds/ccm/RTIDDS_CCM_Servant_T")
      << CUTS_BE_CPP::include ("cuts/arch/rtidds/ccm/RTIDDS_EventConsumer_T")
      << CUTS_BE_CPP::include ("cuts/arch/rtidds/ccm/RTIDDS_Subscriber_T")
      << CUTS_BE_CPP::include ("cuts/arch/rtidds/ccm/RTIDDS_Subscriber_Table_T")
      << std::endl
      << CUTS_BE_CPP::include (export_filename)
      << std::endl;

    this->source_
      << "// $" << "Id" << "$" << std::endl
      << std::endl
      << CUTS_BE_CPP::include (basename)
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_T")
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Events_T")
      << std::endl;

    this->Visit_FilePackage_i (file);

    this->header_ << std::endl
                  << "#endif  // !defined " << hash_define << std::endl;

  } while (0);

  // Close the file.
  this->header_.close ();
  this->source_.close ();
}

//
// Visit_Package
//
void Servant_Generator::
Visit_Package (const PICML::Package & package)
{
  std::string name = package.name ();

  this->source_ << "namespace " << name << "{";
  this->header_ << "namespace " << name << "{";

  this->Visit_FilePackage_i (package);

  this->source_ << "}";
  this->header_ << "}";
}

//
// Visit_FilePackage_i
//
void Servant_Generator::
Visit_FilePackage_i (const Udm::Object & obj)
{
  std::set <PICML::Component> components =
    Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (components.begin (),
                 components.end (),
                 boost::bind (&PICML::Component::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit the remaining packages.
  std::set <PICML::Package> packages =
    Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&PICML::Package::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Component
//
void Servant_Generator::
Visit_Component (const PICML::Component & component)
{
  // First, generate the context for the component.
  Context_Generator ctx_gen (this->header_, this->source_);
  PICML::Component (component).Accept (ctx_gen);

  std::string name = component.name ();
  this->component_ = component.name ();
  std::string context = ctx_gen.context ();
  std::string fq_type = CUTS_BE_CPP::fq_type (component, "::", false);

  this->servant_ = name + "_Servant";

  std::vector <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();
  std::vector <PICML::InEventPort> inputs = component.InEventPort_kind_children ();

  std::string ns = "::CIAO_" + CUTS_BE_CPP::fq_type (component, "_", false) + "_Impl";

  this->header_
    << "typedef CUTS_RTIDDS_CCM_Servant_T < " << std::endl
    << "  " << this->servant_ << "," << std::endl
    << "  " << context << "," << std::endl
    << "  " << ns << "::" << name << "_Exec," << std::endl
    << "  ::POA_" << fq_type << " > " << this->servant_ << "_Base;"
    << std::endl
    << "class " << this->servant_ << " : public " << this->servant_ << "_Base"
    << "{"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("Initializing constructor")
    << this->servant_ << " (const char * name," << std::endl
    << "::PortableServer::POA_ptr poa," << std::endl
    << ns << "::" << name << "_Exec_ptr executor);"
    << std::endl
    << "virtual ~" << this->servant_ << " (void);"
    << std::endl;

  this->source_
    << CUTS_BE_CPP::function_header (this->servant_)
    << this->servant_ << "::" << std::endl
    << this->servant_ << " (const char * name," << std::endl
    << "::PortableServer::POA_ptr poa," << std::endl
    << ns << "::" << name << "_Exec_ptr executor)" << std::endl
    << " : " << this->servant_ << "_Base (name, poa, executor)";

  Servant_Base_Member_Init bmi (this->source_, this->servant_);

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (bmi)));

  this->source_
    << "{";

  Port_Binder port_binder (this->source_);

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (port_binder)));

  this->source_
    << std::endl;

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (port_binder)));

  this->source_
    << "}"
    << CUTS_BE_CPP::function_header ("~" + this->servant_)
    << this->servant_ << "::~" << this->servant_ << " (void)"
    << "{"
    << "}";

  // Visit all the Attribute elements of the <component>.
  typedef std::vector <PICML::Attribute> Attribute_Set;
  Attribute_Set attrs = component.Attribute_kind_children ();

  std::for_each (attrs.begin (),
                 attrs.end (),
                 boost::bind (&PICML::Attribute::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit all the ReadonlyAttribute elements of the <component>.
  typedef std::vector <PICML::ReadonlyAttribute> ReadonlyAttribute_Set;
  ReadonlyAttribute_Set ro_attrs = component.ReadonlyAttribute_kind_children ();

  typedef is_type <PICML::ReadonlyAttribute> ReadonlyAttribute_Type;

  std::for_each (boost::make_filter_iterator <ReadonlyAttribute_Type> (ro_attrs.begin (), ro_attrs.end ()),
                 boost::make_filter_iterator <ReadonlyAttribute_Type> (ro_attrs.end (), ro_attrs.end ()),
                 boost::bind (&PICML::ReadonlyAttribute::Accept, _1, boost::ref (*this)));


  // Make sure we generate the set_attribute () method since it is
  // used by the deployment tools to configure a component.
  CUTS_BE_CCM::Cpp::Servant_Set_Attribute_Decl set_attribute_decl_gen (this->header_);
  CUTS_BE_CCM::Cpp::Servant_Set_Attribute_Impl set_attribute_gen (this->source_);

  PICML::Component (component).Accept (set_attribute_decl_gen);
  PICML::Component (component).Accept (set_attribute_gen);

  // Write methods for each of the event sources.
  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  // Write methods for each of the event sinks.
  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (*this)));
  this->header_
    << "};";


  std::string entrypoint = "create" + CUTS_BE_CPP::fq_type (component, "_") + "_Servant";

  this->header_
    << std::endl
    << "extern \"C\" " << this->export_macro_ << std::endl
    << "::PortableServer::Servant" << std::endl
    << entrypoint << " (const char * name," << std::endl
    << "::PortableServer::POA_ptr poa," << std::endl
    << "::Components::EnterpriseComponent_ptr p);";

  this->source_
    << "extern \"C\" ::PortableServer::Servant" << std::endl
    << entrypoint << " (const char * name," << std::endl
    << "::PortableServer::POA_ptr poa," << std::endl
    << "::Components::EnterpriseComponent_ptr p)"
    << "{"
    << "return ::CUTS::CCM::create_servant <" << std::endl
    << "  " << ns << "::"
    << this->component_ << "_Exec, " << std::endl
    << "  " << CUTS_BE_CPP::fq_type (component) << "_Servant > (name, poa, p);"
    << "}";
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_InEventPort (const PICML::InEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  PICML::Event ev = PICML::Event::Cast (et);
  std::string name = port.name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  this->header_
    << "public:" << std::endl
    << fq_type << "Consumer_ptr get_consumer_" << name << " (void);"
    << std::endl
    << "private:" << std::endl
    << "static void deserialize_" << name << " (" << this->servant_ << " *," << std::endl
    << "const ::CUTS_NDDS" << fq_type << "& dds_event);"
    << std::endl
    << "CUTS_RTIDDS_CCM_EventConsumer_T < " << std::endl
    << "  " << this->servant_ << "," << std::endl
    << "  " << "::CUTS_NDDS" << fq_type << " > " << name << "_consumer_;"
    << std::endl;

  this->source_
    << CUTS_BE_CPP::function_header ("get_consumer_" + name)
    << fq_type << "Consumer_ptr " << this->servant_ << "::" << std::endl
    << "get_consumer_" << name << " (void)"
    << "{"
    << "throw ::CORBA::NO_IMPLEMENT ();"
    << "}"
    << CUTS_BE_CPP::function_header ("deserialize_" + name)
    << "void " << this->servant_ << "::" << std::endl
    << "deserialize_" << name << " (" << this->servant_ << " * servant," << std::endl
    << "const ::CUTS_NDDS" << fq_type << " & dds_event)"
    << "{"
    << CUTS_BE_CPP::single_line_comment ("First, extract the ev.")
    << "CUTS_CCM_Event_T < ::OBV_" << CUTS_BE_CPP::fq_type (ev, "::", false) << " > ev;"
    << "*ev.in () <<= dds_event;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("Now, puch the ev to the implemetation.")
    << "if (servant->impl_)" << std::endl
    << "  servant->impl_->push_" << name << " (ev.in ());"
    << "}";
}

//
// Visit_OutEventPort
//
void Servant_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  PICML::Event ev = PICML::Event::Cast (et);

  std::string name = port.name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  if (port.single_destination ())
  {
    this->header_
      << CUTS_BE_CPP::single_line_comment ("Connect to " + name)
      << "void connect_" << name << " (" << fq_type << "Consumer_ptr);"
      << std::endl
      << CUTS_BE_CPP::single_line_comment ("Disconnect from " + name)
      << fq_type << "Consumer_ptr disconnect_" << name << " (void);"
      << std::endl;

    this->source_
      << CUTS_BE_CPP::function_header ("connect_" + name)
      << "void " << this->servant_ << "::" << std::endl
      << "connect_" << name << " (" << fq_type << "Consumer_ptr)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}"
      << CUTS_BE_CPP::function_header ("disconnect_" + name)
      << fq_type << "Consumer_ptr " << this->servant_ << "::" << std::endl
      << "disconnect_" << name << " (void)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}";
  }
  else
  {
    this->header_
      << CUTS_BE_CPP::single_line_comment ("Subscribe to " + name)
      << "::Components::Cookie * subscribe_" << name << " (" << fq_type << "Consumer_ptr);"
      << std::endl
      << CUTS_BE_CPP::single_line_comment ("Subscribe from " + name)
      << fq_type << "Consumer_ptr unsubscribe_" << name << " (::Components::Cookie *);"
      << std::endl;

    this->source_
      << CUTS_BE_CPP::function_header ("subscribe_" + name)
      << "::Components::Cookie * " << this->servant_ << "::" << std::endl
      << "subscribe_" << name << " (" << fq_type << "Consumer_ptr)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}"
      << CUTS_BE_CPP::function_header ("unsubscribe_" + name)
      << fq_type << "Consumer_ptr " << this->servant_ << "::" << std::endl
      << "unsubscribe_" << name << "(::Components::Cookie *)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}";
  }
}

//
// Visit_Attribute
//
void Servant_Generator::
Visit_Attribute (const PICML::Attribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();
  const std::string name (attr.name ());

  // Write the attribute in the header file.
  this->header_
    << CUTS_BE_CPP::single_line_comment ("attribute setter: " + name)
    << "virtual void " << name << " (";

  CUTS_BE_CCM::Cpp::In_Type_Generator in_type_header_gen (this->header_);
  in_type_header_gen.generate (type);

  this->header_ << " " << name << ");" << std::endl;

  // Write the attribute in the source file.
  this->source_
    << CUTS_BE_CPP::function_header ("attribute setter: " + name)
    << "void " << this->servant_ << "::" << name << " (";

  CUTS_BE_CCM::Cpp::In_Type_Generator in_type_source_gen (this->source_);
  in_type_source_gen.generate (type);

  this->source_
    << " " << name << ")"
    << "{"
    << "if (this->impl_)" << std::endl
    << "  this->impl_->" << name << " (" << name << ");"
    << "else" << std::endl
    << "  throw ::CORBA::INTERNAL ();"
    << "}";

  // Write the getter method for this attribute.
  PICML::ReadonlyAttribute readonly (attr);
  readonly.Accept (*this);
}

//
// Visit_ReadonlyAttribute
//
void Servant_Generator::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();
  const std::string name (attr.name ());

  // Write the getter method's declaration.
  this->header_
    << CUTS_BE_CPP::single_line_comment ("attribute getter: " + name)
    << "virtual ";

  CUTS_BE_CCM::Cpp::Retn_Type_Generator retn_type_header_gen (this->header_);
  retn_type_header_gen.generate (type);

  this->header_
    << " " << name << " (void);" << std::endl;

  // Write the getter method's implementation.
  this->source_
    << CUTS_BE_CPP::function_header ("attribute getter: " + name);

  CUTS_BE_CCM::Cpp::Retn_Type_Generator retn_type_source_gen (this->source_);
  retn_type_source_gen.generate (type);

  this->source_
    << " " << this->servant_ << "::"
    << name << " (void)"
    << "{"
    << "if (this->impl_)" << std::endl
    << "  return this->impl_->" << name << " ();"
    << "else" << std::endl
    << "  throw ::CORBA::INTERNAL ();"
    << "}";
}

}
