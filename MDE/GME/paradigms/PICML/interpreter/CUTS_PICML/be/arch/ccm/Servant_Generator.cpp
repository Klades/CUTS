// $Id$

#include "Servant_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Servant_Generator.inl"
#endif

#include "Servant_Header_Include_Generator.h"
#include "Context_Generator.h"

#include "Component_Implementation.h"
#include "Servant_Implementation.h"
#include "In_Type_Generator.h"
#include "Retn_Type_Generator.h"

#include "../../lang/cpp/Cpp.h"
#include "../../BE_algorithm.h"

#include "boost/bind.hpp"
#include "boost/iterator/filter_iterator.hpp"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include <algorithm>

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Servant_Base_Member_Init
 *
 * Helper class that generates the base member initialization section of
 * a CCM servant class.
 */
class Servant_Base_Member_Init : public PICML::Visitor
{
public:
  Servant_Base_Member_Init (std::ostream & source, const std::string & servant)
    : source_ (source),
      servant_ (servant)
  {

  }

  /// Destructor.
  virtual ~Servant_Base_Member_Init (void) { }

  virtual void Visit_InEventPort (const PICML::InEventPort_in input)
  {
    std::string name = input->name ();

    this->source_
      << "," << std::endl
      << "   " << name << "_consumer_ (this, &"
      << this->servant_ << "::_push_" << name << ")";
  }

private:
  /// Target output stream.
  std::ostream & source_;

  /// The name of the servant.
  const std::string & servant_;
};

class Port_Binder : public PICML::Visitor
{
public:
  Port_Binder (std::ostream & source)
    : source_ (source)
  {

  }

  /// Destructor.
  virtual ~Port_Binder (void) { }

  virtual void Visit_InEventPort (const PICML::InEventPort_in port)
  {
    std::string name = port->name ();

    this->source_
      << "this->consumers_.bind (\"" << name << "\", &this->"
      << name << "_consumer_);";
  }

  virtual void Visit_OutEventPort (const PICML::OutEventPort_in port)
  {
    std::string name = port->name ();

    if (port->single_destination ())
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
  /// Target output stream.
  std::ostream & source_;
};

//
// Visit_RootFolder
//
void Servant_Generator::
Visit_RootFolder (const PICML::RootFolder_in root)
{
  for (auto folder : root->get_InterfaceDefinitions ())
    folder->accept (this);
}

//
// Visit_InterfaceDefinitions
//
void Servant_Generator::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions_in folder)
{
  for (auto file : folder->get_Files ())
    file->accept (this);
}

//
// Visit_ComponentImplementations
//
void Servant_Generator::Visit_File (const PICML::File_in file)
{
  if (!CUTS_BE::has_component (file))
    return;

  // Construct the name of the output file.
  std::string name = file->name ();
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
  std::string export_filename = std::string (file->name ()) + "_svnt_export";
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
      << CUTS_BE_CPP::include (this->traits_->custom_stub_prefix () + name + "C")
      << std::endl
      << CUTS_BE_CPP::include (this->traits_->ccm_context_template_type_header ())
      << CUTS_BE_CPP::include (this->traits_->ccm_servant_template_type_header ())
      << CUTS_BE_CPP::include (this->traits_->ccm_eventconsumer_template_type_header ())
      << CUTS_BE_CPP::include (this->traits_->ccm_publisher_template_type_header ())
      << CUTS_BE_CPP::include (this->traits_->ccm_publisher_table_template_type_header ())
      << std::endl
      << CUTS_BE_CPP::include (export_filename)
      << std::endl;

    this->source_
      << "// $" << "Id" << "$" << std::endl
      << std::endl
      << CUTS_BE_CPP::include (basename)
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_T")
      << std::endl;

    for (auto subcomponent : file->get_Components ())
      subcomponent->accept (this);

    for (auto subpackage : file->get_Packages ())
      subpackage->accept (this);

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
Visit_Package (const PICML::Package_in package)
{
  std::string name = package->name ();

  this->source_ << "namespace " << name << "{";
  this->header_ << "namespace " << name << "{";

  for (auto subcomponent : package->get_Components ())
    subcomponent->accept (this);

  for (auto subpackage : package->get_Packages ())
    subpackage->accept (this);

  this->source_ << "}";
  this->header_ << "}";
}

//
// Visit_Component
//
void Servant_Generator::
Visit_Component (const PICML::Component_in component)
{
  // First, generate the context for the component.
  Context_Generator ctx_gen (this->header_, this->source_, this->traits_);
  component->accept (&ctx_gen);

  std::string name = component->name ();
  this->component_ = component->name ();
  std::string context = ctx_gen.context ();
  std::string fq_type = CUTS_BE_CPP::fq_type (component, "::", false);

  this->servant_ = name + "_Servant";

  std::string ns = "::CIAO_" + CUTS_BE_CPP::fq_type (component, "_", false) + "_Impl";

  this->header_
    << CUTS_BE_CPP::single_line_comment ("Type definition of the servant type.")
    << "typedef " << this->traits_->ccm_servant_template_type ()
    << " < " << std::endl
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

  auto outputs = component->get_OutEventPorts ();
  auto inputs = component->get_InEventPorts ();


  Servant_Base_Member_Init bmi (this->source_, this->servant_);
  for (auto input : inputs)
    input->accept (&bmi);

  this->source_
    << "{";

  Port_Binder port_binder (this->source_);

  for (auto output : outputs)
    output->accept (&port_binder);

  this->source_
    << std::endl;

  for (auto input : inputs)
    input->accept (&port_binder);

  this->source_
    << "}"
    << CUTS_BE_CPP::function_header ("~" + this->servant_)
    << this->servant_ << "::~" << this->servant_ << " (void)"
    << "{"
    << "}";

  // Visit all the Attribute elements of the <component>.
  for (auto attr : component->get_Attributes ())
    attr->accept (this);

  // Visit all the ReadonlyAttribute elements of the <component>.
  for (auto ro_attr : component->get_ReadonlyAttributes ())
    ro_attr->accept (this);

  // Make sure we generate the set_attribute () method since it is
  // used by the deployment tools to configure a component.
  CUTS_BE_CCM::Cpp::Servant_Set_Attribute_Decl set_attribute_decl_gen (this->header_);
  CUTS_BE_CCM::Cpp::Servant_Set_Attribute_Impl set_attribute_gen (this->source_);

  component->accept (&set_attribute_decl_gen);
  component->accept (&set_attribute_gen);

  // Write methods for each of the event sources.
  for (auto output : outputs)
    output->accept (this);

  // Write methods for each of the event sinks.
  for (auto input : inputs)
    input->accept (this);

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
Visit_InEventPort (const PICML::InEventPort_in port)
{
  if (port->EventType_is_nil ())
    return;

  PICML::EventType et = port->refers_to_EventType ();

  if (et->meta ()->name () != PICML::Event::impl_type::metaname)
    return;

  PICML::Event ev = et;
  std::string name = port->name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  this->header_
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("Get the event consumer for " + fq_type + ".")
    << fq_type << "Consumer_ptr get_consumer_" << name << " (void);"
    << std::endl
    << "private:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("Upcall method for " + fq_type + ".")
    << "static void _push_" << name << " (" << this->servant_ << " *," << std::endl
    << fq_type << " *);"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The event consumer for " + fq_type + ".")
    << this->traits_->ccm_eventconsumer_template_type () << " < " << std::endl
    << "  " << this->servant_ << "," << std::endl
    << "  " << fq_type << " > " << name << "_consumer_;"
    << std::endl;

  this->source_
    << CUTS_BE_CPP::function_header ("get_consumer_" + name)
    << fq_type << "Consumer_ptr " << this->servant_ << "::" << std::endl
    << "get_consumer_" << name << " (void)"
    << "{"
    << "throw ::CORBA::NO_IMPLEMENT ();"
    << "}"
    << CUTS_BE_CPP::function_header ("_push_" + name)
    << "void " << this->servant_ << "::" << std::endl
    << "_push_" << name << " (" << this->servant_ << " * servant," << std::endl
    << fq_type << " * ev)"
    << "{"
    << CUTS_BE_CPP::single_line_comment ("Push the event to the implemetation.")
    << "if (0 != servant->impl_)" << std::endl
    << "  servant->impl_->push_" << name << " (ev);"
    << "}";
}

//
// Visit_OutEventPort
//
void Servant_Generator::
Visit_OutEventPort (const PICML::OutEventPort_in port)
{
  if (port->EventType_is_nil ())
    return;

  PICML::EventType et = port->refers_to_EventType ();

  if (et->meta ()->name () != PICML::Event::impl_type::metaname)
    return;

  PICML::Event ev = et;
  std::string name = port->name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  if (port->single_destination ())
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
Visit_Attribute (const PICML::Attribute_in attr)
{
  PICML::AttributeMember member = attr->get_AttributeMember ();
  PICML::MemberType type = member->refers_to_MemberType ();
  const std::string name (attr->name ());

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
  readonly->accept (this);
}

//
// Visit_ReadonlyAttribute
//
void Servant_Generator::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute_in attr)
{
  PICML::AttributeMember member = attr->get_AttributeMember ();
  PICML::MemberType type = member->refers_to_MemberType ();
  const std::string name (attr->name ());

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
}
