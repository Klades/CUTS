// $Id$

#include "Servant_Generator.h"
#include "Servant_Header_Include_Generator.h"
#include "Context_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "boost/bind.hpp"
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_BE_OpenSplice
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
  std::set <PICML::ComponentImplementations> folders = folder.ComponentImplementations_children ();
  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&PICML::ComponentImplementations::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementations
//
void Servant_Generator::
Visit_ComponentImplementations (const PICML::ComponentImplementations & folder)
{
  std::set <PICML::ComponentImplementationContainer> containers =
    folder.ComponentImplementationContainer_children ();

  std::for_each (containers.begin (),
                 containers.end (),
                 boost::bind (&PICML::ComponentImplementationContainer::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementationContainer
//
void Servant_Generator::
Visit_ComponentImplementationContainer (
const PICML::ComponentImplementationContainer & container)
{
  std::set <PICML::MonolithicImplementation> monoimpls =
    container.MonolithicImplementation_kind_children ();

  if (monoimpls.empty ())
    return;

  std::string name = container.name ();

  // Construct the name of the output file.
  std::string basename ("OpenSplice_");
  basename += name + "_svnt";

  std::string source_filename (this->outdir_);
  source_filename += "/" + basename + ".cpp";

  std::string header_filename (this->outdir_);
  header_filename += "/" + basename + ".h";


  // Open the file for writing.
  this->header_.open (header_filename.c_str ());
  this->source_.open (source_filename.c_str ());

  if (!this->header_.is_open () && !this->source_.is_open ())
    return;

  std::string hash_define ("_OPENSPLICE_");
  hash_define += name + "_SVNT_H_";

  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  std::string export_filename ("OpenSplice_");
  export_filename += std::string (container.name ()) + "_svnt_export";

  // Construct the export macro for this file.
  this->export_macro_ = "OPENSPLICE_" + name + "_SVNT";

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

    std::string exec_stub (name);
    exec_stub += "EC";

    // Include the header file.
    this->header_
      << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
      << std::endl
      << "#ifndef " << hash_define << std::endl
      << "#define " << hash_define << std::endl
      << std::endl
      << CUTS_BE_CPP::include (exec_stub)
      << std::endl
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Context_T")
      << CUTS_BE_CPP::include ("cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant_T")
      << CUTS_BE_CPP::include ("cuts/arch/opensplice/ccm/OpenSplice_EventConsumer_T")
      << CUTS_BE_CPP::include ("cuts/arch/opensplice/ccm/OpenSplice_Subscriber_T")
      << CUTS_BE_CPP::include ("cuts/arch/opensplice/ccm/OpenSplice_Subscriber_Table_T")
      << std::endl
      << CUTS_BE_CPP::include (export_filename)
      << std::endl;

    this->source_
      << "// $" << "Id" << "$" << std::endl
      << std::endl
      << CUTS_BE_CPP::include (basename)
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Events_T")
      << std::endl;


    Servant_Header_Include_Generator incl_gen (this->header_);
    PICML::ComponentImplementationContainer (container).Accept (incl_gen);

    std::for_each (monoimpls.begin (),
                   monoimpls.end (),
                   boost::bind (&PICML::MonolithicImplementation::Accept,
                                _1,
                                boost::ref (*this)));

    this->header_ << std::endl
                << "#endif  // !defined " << hash_define << std::endl;

  } while (0);

  // Close the file.
  this->header_.close ();
}

//
// Visit_MonolithicImplementation
//
void Servant_Generator::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & monoimpl)
{
  this->monoimpl_ = monoimpl.name ();
  this->header_
    << "namespace " << this->monoimpl_
    << "{";

  this->source_
    << "namespace " << this->monoimpl_
    << "{";

  // Visit the component we are implementing.
  PICML::Implements impl = monoimpl.dstImplements ();

  if (Udm::null != impl)
    impl.Accept (*this);

  this->header_
    << "}"
    << "extern \"C\" " << this->export_macro_ << std::endl
    << "::PortableServer::Servant" << std::endl;

  std::set <PICML::MonolithprimaryArtifact> artifacts =
    monoimpl.dstMonolithprimaryArtifact ();

  std::for_each (artifacts.begin (),
                 artifacts.end (),
                 boost::bind (&PICML::MonolithprimaryArtifact::Accept,
                              _1,
                              boost::ref (*this)));

  this->header_ << " (const char * name," << std::endl
              << "::Components::EnterpriseComponent_ptr p);";

  this->source_
    << "}";
}

//
// Visit_Implements
//
void Servant_Generator::
Visit_Implements (const PICML::Implements & implements)
{
  PICML::ComponentRef ref = implements.dstImplements_end ();
  ref.Accept (*this);
}

//
// Visit_ComponentRef
//
void Servant_Generator::
Visit_ComponentRef (const PICML::ComponentRef & ref)
{
  PICML::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
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
  std::string context = ctx_gen.context ();
  std::string fq_type = CUTS_BE_CPP::fq_type (component, "::", false);

  this->servant_ = name + "_Servant";

  std::vector <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();
  std::vector <PICML::InEventPort> inputs = component.InEventPort_kind_children ();

  this->header_
    << "typedef CUTS_OpenSplice_CCM_Servant_T < " << std::endl
    << "  " << this->servant_ << "," << std::endl
    << "  " << context << "," << std::endl
    << "  ::CIDL_" << this->monoimpl_ << "::" << name << "_Exec," << std::endl
    << "  ::POA_" << fq_type << " > " << this->servant_ << "_Base;"
    << std::endl
    << "class " << this->servant_ << " : " << this->servant_ << "_Base"
    << "{"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("Initializing constructor")
    << this->servant_ << " (const char * name," << std::endl
    << "::CIDL_" << this->monoimpl_ << "::" << name << "_Exec_ptr executor);"
    << std::endl
    << "virtual ~" << this->servant_ << " (void);"
    << std::endl;

  this->source_
    << CUTS_BE_CPP::function_header (this->servant_)
    << this->servant_ << "::" << std::endl
    << this->servant_ << " (const char * name," << std::endl
    << "::CIDL_" << this->monoimpl_ << "::" << name << "_Exec_ptr executor)" << std::endl
    << " : " << this->servant_ << "_Base (name, executor)";

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

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (*this)));
  this->header_
    << "};";
}

//
// Visit_MonolithprimaryArtifact
//
void Servant_Generator::
Visit_MonolithprimaryArtifact (const PICML::MonolithprimaryArtifact & primary)
{
  PICML::ImplementationArtifactReference ref = primary.dstMonolithprimaryArtifact_end ();
  ref.Accept (*this);
}

//
// Visit_ImplementationArtifactReference
//
void Servant_Generator::
Visit_ImplementationArtifactReference (const PICML::ImplementationArtifactReference & ref)
{
  if (PICML::ComponentServantArtifact::meta != ref.type ())
    return;

  PICML::ComponentServantArtifact artifact = PICML::ComponentServantArtifact::Cast (ref);
  artifact.Accept (*this);
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_ComponentServantArtifact (const PICML::ComponentServantArtifact & artifact)
{
  this->header_ << artifact.EntryPoint ();
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_InEventPort (const PICML::InEventPort & port)
{
  std::string name = port.name ();
  PICML::Event event = port.ref ();
  std::string fq_type = CUTS_BE_CPP::fq_type (event);

  this->header_
    << "public:" << std::endl
    << fq_type << "Consumer_ptr get_consumer_" << name << " (void);"
    << std::endl
    << "private:" << std::endl
    << "static void deserialize_" << name << " (" << this->servant_ << " *," << std::endl
    << "const ::CUTS_DDS" << fq_type << "& dds_event);"
    << std::endl
    << "CUTS_OpenSplice_CCM_EventConsumer_T < " << std::endl
    << "  " << this->servant_ << "," << std::endl
    << "  " << "::CUTS_DDS" << fq_type << " > " << name << "_consumer_;"
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
    << "const ::CUTS_DDS" << fq_type << " & dds_event)"
    << "{"
    << CUTS_BE_CPP::single_line_comment ("First, extract the event.")
    << "CUTS_CCM_Event_T < ::OBV_" << CUTS_BE_CPP::fq_type (event, "::", false) << " > event;"
    << "*event.in () <<= dds_event;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("Now, puch the event to the implemetation.")
    << "if (servant->impl_)" << std::endl
    << "  servant->impl_->push_" << name << " (event.in ());"
    << "}";
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  std::string name = port.name ();
  PICML::Event event = port.ref ();
  std::string fq_type = CUTS_BE_CPP::fq_type (event);

  if (port.single_destination ())
  {
    this->header_
      << "void connect_" << name << " (" << fq_type << "Consumer_ptr);"
      << std::endl
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
      << "::Components::Cookie * subscribe_" << name << " (" << fq_type << "Consumer_ptr);"
      << std::endl
      << fq_type << "Consumer_ptr unsubscribe_" << name << "(::Components::Cookie *);"
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

}
