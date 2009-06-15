// $Id$

#include "StdAfx.h"
#include "Servant_Generator.h"
#include "Servant_Header_Include_Generator.h"
#include "Context_Generator.h"
#include "cpp/Cpp.h"
#include "boost/bind.hpp"
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_CHAOS
{
class Servant_Base_Member_Init : public CHAOS::Visitor
{
public:
  Servant_Base_Member_Init (std::ostream & source, const std::string & servant)
    : source_ (source),
      servant_ (servant),
      tcpip_id_ (0)
  {

  }

  virtual ~Servant_Base_Member_Init (void)
  {

  }

  virtual void Visit_InEventPort (const CHAOS::InEventPort & input)
  {
    std::string name = input.name ();
    std::string conntype = input.ConnectionType ();

    if (conntype == "TCPIP")
    {
      this->source_
        << "," << std::endl
        << "   " << name << "_consumer_ (this, " << (this->tcpip_id_ ++) << ")";
    }
    else
    {
      this->source_
        << "," << std::endl
        << "   " << name << "_consumer_ (this, &"
        << this->servant_ << "::upcall_" << name << ")";
    }
  }

private:
  std::ostream & source_;

  const std::string & servant_;

  size_t tcpip_id_;
};

class Port_Binder : public CHAOS::Visitor
{
public:
  Port_Binder (std::ostream & source)
    : source_ (source)
  {

  }

  virtual ~Port_Binder (void)
  {

  }

  virtual void Visit_InEventPort (const CHAOS::InEventPort & port)
  {
    std::string name = port.name ();

    this->source_
      << "this->consumers_.bind (\"" << name << "\", &this->"
      << name << "_consumer_);";
  }

  virtual void Visit_OutEventPort (const CHAOS::OutEventPort & port)
  {
    std::string name = port.name ();

    if (port.single_destination ())
    {
      this->source_
        << "this->emits_.bind (\"" << name
        << "\", &this->ctx_->subscriber_" << name << " ());";
    }
    else
    {
      this->source_
        << "this->publishes_.bind (\"" << name
        << "\", &this->ctx_->subscribers_" << name << " ());";
    }
  }

private:
  std::ostream & source_;
};

/**
 * @class Register_Value_Type
 */
class Register_Value_Type : public CHAOS::Visitor
{
public:
  Register_Value_Type (std::ostream & source)
    : source_ (source)
  {
  }

  virtual ~Register_Value_Type (void)
  {

  }

  virtual void Visit_InEventPort (const CHAOS::InEventPort & port)
  {
    std::string conntype = port.ConnectionType ();

    if (conntype == "CORBA")
    {
      CHAOS::Event event = port.ref ();
      std::string fq_type = CUTS_BE_CPP::fq_type (event);

      if (this->seen_.find (fq_type) == this->seen_.end ())
      {
        this->source_
          << "TAO_OBV_REGISTER_FACTORY (" << fq_type << "_init," << std::endl
          << fq_type << ");";

        this->seen_.insert (fq_type);
      }
    }
  }

private:
  std::ostream & source_;

  std::set <std::string> seen_;
};

/**
 * @class Virtual_Table_Init
 */
class Virtual_Table_Init : public CHAOS::Visitor
{
public:
  Virtual_Table_Init (std::ostream & source, const std::string & servant)
    : source_ (source),
      servant_ (servant),
      tcpip_id_ (0)
  {
  }

  virtual ~Virtual_Table_Init (void)
  {

  }

  virtual void Visit_InEventPort (const CHAOS::InEventPort & port)
  {
    std::string conntype = port.ConnectionType ();

    if (conntype == "TCPIP")
    {
      this->source_
        << this->servant_ << "::table_[" << (this->tcpip_id_ ++) << "] = "
        << "&" << this->servant_ << "::upcall_" << port.name () << ";";
    }
  }

private:
  std::ostream & source_;

  const std::string & servant_;

  size_t tcpip_id_;
};

/**
 * @class TCPIP_Port_Count
 */
class TCPIP_Port_Count : public CHAOS::Visitor
{
public:
  TCPIP_Port_Count (void)
    : count_ (0)
  {
  }

  virtual ~TCPIP_Port_Count (void)
  {

  }

  virtual void Visit_InEventPort (const CHAOS::InEventPort & port)
  {
    std::string conntype = port.ConnectionType ();

    if (conntype == "TCPIP")
      ++ this->count_;
  }

  size_t count (void) const
  {
    return this->count_;
  }

private:
  size_t count_;
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
Visit_RootFolder (const CHAOS::RootFolder & folder)
{
  std::set <CHAOS::ComponentImplementations> folders = folder.ComponentImplementations_children ();
  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&CHAOS::ComponentImplementations::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementations
//
void Servant_Generator::
Visit_ComponentImplementations (const CHAOS::ComponentImplementations & folder)
{
  std::set <CHAOS::ComponentImplementationContainer> containers =
    folder.ComponentImplementationContainer_children ();

  std::for_each (containers.begin (),
                 containers.end (),
                 boost::bind (&CHAOS::ComponentImplementationContainer::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementationContainer
//
void Servant_Generator::
Visit_ComponentImplementationContainer (
const CHAOS::ComponentImplementationContainer & container)
{
  std::set <CHAOS::MonolithicImplementation> monoimpls =
    container.MonolithicImplementation_kind_children ();

  if (monoimpls.empty ())
    return;

  std::string name = container.name ();

  // Construct the name of the output file.
  std::string basename ("CHAOS_");
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

  std::string hash_define ("_CHAOS_");
  hash_define += name + "_SVNT_H_";

  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

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
      << CUTS_BE_CPP::include ("cuts/arch/chaos/ccm/CHAOS_CCM_Servant_T")
      << CUTS_BE_CPP::include ("cuts/arch/chaos/ccm/CHAOS_CCM_Single_Subscriber")
      << CUTS_BE_CPP::include ("cuts/arch/chaos/ccm/CHAOS_CCM_Subscriber_Table")
      << CUTS_BE_CPP::include ("cuts/arch/chaos/ccm/CHAOS_CCM_EventConsumer")
      << std::endl;

    this->source_
      << "// $" << "Id" << "$" << std::endl
      << std::endl
      << CUTS_BE_CPP::include (basename)
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_T")
      << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Events_T")
      << std::endl;


    Servant_Header_Include_Generator incl_gen (this->header_);
    CHAOS::ComponentImplementationContainer (container).Accept (incl_gen);

    std::for_each (monoimpls.begin (),
                   monoimpls.end (),
                   boost::bind (&CHAOS::MonolithicImplementation::Accept,
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
Visit_MonolithicImplementation (const CHAOS::MonolithicImplementation & monoimpl)
{
  this->monoimpl_ = monoimpl.name ();
  this->header_
    << "namespace CHAOS_" << this->monoimpl_
    << "{";

  this->source_
    << "namespace CHAOS_" << this->monoimpl_
    << "{";

  // Visit the component we are implementing.
  CHAOS::Implements impl = monoimpl.dstImplements ();

  if (Udm::null != impl)
    impl.Accept (*this);

  this->header_
    << "}";


  this->source_
    << "}";

  std::set <CHAOS::MonolithprimaryArtifact> artifacts =
    monoimpl.dstMonolithprimaryArtifact ();

  std::for_each (artifacts.begin (),
                 artifacts.end (),
                 boost::bind (&CHAOS::MonolithprimaryArtifact::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Implements
//
void Servant_Generator::
Visit_Implements (const CHAOS::Implements & implements)
{
  CHAOS::ComponentRef ref = implements.dstImplements_end ();
  ref.Accept (*this);
}

//
// Visit_ComponentRef
//
void Servant_Generator::
Visit_ComponentRef (const CHAOS::ComponentRef & ref)
{
  CHAOS::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
}

//
// Visit_Component
//
void Servant_Generator::
Visit_Component (const CHAOS::Component & component)
{
  // First, generate the context for the component.
  Context_Generator ctx_gen (this->header_, this->source_);
  CHAOS::Component (component).Accept (ctx_gen);

  std::string name = component.name ();
  this->component_ = component.name ();
  std::string context = ctx_gen.context ();
  std::string fq_type = CUTS_BE_CPP::fq_type (component, "::", false);

  this->servant_ = name + "_Servant";

  std::vector <CHAOS::OutEventPort> outputs = component.OutEventPort_kind_children ();
  std::vector <CHAOS::InEventPort> inputs = component.InEventPort_kind_children ();

  this->header_
    << "typedef CUTS_CHAOS_CCM_Servant_T < " << std::endl
    << "  " << this->servant_ << "," << std::endl
    << "  " << context << "," << std::endl
    << "  ::CIDL_" << this->monoimpl_ << "::" << name << "_Exec," << std::endl
    << "  ::POA_" << fq_type << " > " << this->servant_ << "_Base;"
    << std::endl
    << "class " << this->servant_ << " : public " << this->servant_ << "_Base"
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
                 boost::bind (&CHAOS::InEventPort::Accept,
                              _1,
                              boost::ref (bmi)));

  this->source_
    << "{";

  Port_Binder port_binder (this->source_);

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&CHAOS::OutEventPort::Accept,
                              _1,
                              boost::ref (port_binder)));

  this->source_
    << std::endl;

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&CHAOS::InEventPort::Accept,
                              _1,
                              boost::ref (port_binder)));

  // Register the CORBA value types.
  Register_Value_Type register_value_type (this->source_);

  this->source_
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("register CORBA value types");

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&CHAOS::InEventPort::Accept,
                              _1,
                              boost::ref (register_value_type)));

  // Count the number of TCP/IP input ports.
  TCPIP_Port_Count tcpip_port_count;

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&CHAOS::InEventPort::Accept,
                              _1,
                              boost::ref (tcpip_port_count)));

  this->source_
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("Guard initialization of TCP/IP virtual table")
    << "virtual_table_type::init_guard_type guard (" << this->servant_ << "::table_, "
    << tcpip_port_count.count () << ");"
    << std::endl
    << "if (" << this->servant_ << "::table_.is_init ())" << std::endl
    << "  return;"
    << std::endl;

  Virtual_Table_Init vti (this->source_, this->servant_);

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&CHAOS::InEventPort::Accept,
                              _1,
                              boost::ref (vti)));

  this->source_
    << "}"
    << CUTS_BE_CPP::function_header ("~" + this->servant_)
    << this->servant_ << "::~" << this->servant_ << " (void)"
    << "{"
    << "}";

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&CHAOS::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&CHAOS::InEventPort::Accept,
                              _1,
                              boost::ref (*this)));
  this->header_
    << "};";
}

//
// Visit_MonolithprimaryArtifact
//
void Servant_Generator::
Visit_MonolithprimaryArtifact (const CHAOS::MonolithprimaryArtifact & primary)
{
  CHAOS::ImplementationArtifactReference ref = primary.dstMonolithprimaryArtifact_end ();
  ref.Accept (*this);
}

//
// Visit_ImplementationArtifactReference
//
void Servant_Generator::
Visit_ImplementationArtifactReference (const CHAOS::ImplementationArtifactReference & ref)
{
  if (CHAOS::ComponentServantArtifact::meta != ref.type ())
    return;

  CHAOS::ComponentServantArtifact artifact = CHAOS::ComponentServantArtifact::Cast (ref);
  artifact.Accept (*this);
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_ComponentServantArtifact (const CHAOS::ComponentServantArtifact & ref)
{
  CHAOS::ImplementationArtifact artifact = ref.ref ();
  std::string entrypoint = ref.EntryPoint ();
  std::string export_macro = artifact.name ();

  std::transform (export_macro.begin (),
                  export_macro.end (),
                  export_macro.begin (),
                  &::toupper);

  export_macro += "_Export";

  std::string export_filename (artifact.name ());
  export_filename += "_export";

  this->header_
    << CUTS_BE_CPP::include (export_filename)
    << std::endl
    << "extern \"C\" " << export_macro << std::endl
    << "::PortableServer::Servant" << std::endl
    << entrypoint << " (const char * name," << std::endl
    << "::Components::EnterpriseComponent_ptr p);";

  this->source_
    << "extern \"C\" ::PortableServer::Servant" << std::endl
    << entrypoint << " (const char * name, ::Components::EnterpriseComponent_ptr p)"
    << "{"
    << "return ::CUTS::CCM::create_servant <" << std::endl
    << "  ::CIDL_" << this->monoimpl_ << "::"
    << this->component_ << "_Exec, " << std::endl
    << "  ::CHAOS_" << this->monoimpl_ << "::" << this->servant_
    << " > (name, p);"
    << "}";
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_InEventPort (const CHAOS::InEventPort & port)
{
  std::string name = port.name ();
  CHAOS::Event event = port.ref ();
  std::string fq_type = CUTS_BE_CPP::fq_type (event);

  this->header_
    << "public:" << std::endl
    << fq_type << "Consumer_ptr get_consumer_" << name << " (void);"
    << std::endl
    << "private:" << std::endl;

  std::string conntype = port.ConnectionType ();

  if (conntype == "CORBA")
  {
    this->header_
      << "static int upcall_" << name << " (" << this->servant_ << " *," << std::endl
      << fq_type << " *);"
      << std::endl
      << "CUTS_CCM_EventConsumer_T < " << fq_type
      << ", " << this->servant_ << " > " << name << "_consumer_;"
      << std::endl;
  }
  else if (conntype == "TCPIP")
  {
    this->header_
      << "static int upcall_" << name << " (" << this->servant_ << " *," << std::endl
      << "CUTS_TCPIP_InputCDR &);"
      << std::endl
      << "CUTS_TCPIP_CCM_EventConsumer " << name << "_consumer_;"
      << std::endl;
  }
  else if (conntype == "OpenSpliceDDS")
  {
    this->header_
      << "static void upcall_" << name << " (" << this->servant_ << " *," << std::endl
      << "const ::CUTS_DDS" << fq_type << "& dds_event);"
      << std::endl
      << "CUTS_OpenSplice_CCM_EventConsumer_T < " << std::endl
      << "  " << this->servant_ << "," << std::endl
      << "  " << "::CUTS_DDS" << fq_type << " > " << name << "_consumer_;"
      << std::endl;
  }

  this->source_
    << CUTS_BE_CPP::function_header ("get_consumer_" + name)
    << fq_type << "Consumer_ptr " << this->servant_ << "::" << std::endl
    << "get_consumer_" << name << " (void)"
    << "{"
    << "throw ::CORBA::NO_IMPLEMENT ();"
    << "}";

  if (conntype == "CORBA")
  {
    this->source_
      << CUTS_BE_CPP::function_header ("upcall_" + name)
      << "int " << this->servant_ << "::" << std::endl
      << "upcall_" << name << " (" << this->servant_ << " * servant," << std::endl
      << fq_type << " * event)"
      << "{"
      << "if (servant->impl_)" << std::endl
      << "  servant->impl_->push_" << name << " (event);"
      << std::endl
      << "return 0;"
      << "}";
  }
  else if (conntype == "TCPIP")
  {
    this->source_
      << CUTS_BE_CPP::function_header ("upcall_" + name)
      << "int " << this->servant_ << "::" << std::endl
      << "upcall_" << name << " (" << this->servant_ << " * servant," << std::endl
      << "CUTS_TCPIP_InputCDR & stream)"
      << "{"
      << CUTS_BE_CPP::single_line_comment ("Extract the event from the stream.")
      << "CUTS_CCM_Event_T < ::OBV_" << CUTS_BE_CPP::fq_type (event, "::", false) << " > event;"
      << std::endl
      << "if (!(stream >> *event.in ()))"
      << "{"
      << "ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to extract %s from stream\\n\")," << std::endl
      << "ACE_TEXT (\"" << fq_type << "\"))," << std::endl
      << "-1);"
      << "}"
      << CUTS_BE_CPP::single_line_comment ("Push the message to the implementation.")
      << "if (servant->impl_)" << std::endl
      << "  servant->impl_->push_" << name << " (event.in ());"
      << std::endl
      << "return 0;"
      << "}";
  }
  else if (conntype == "OpenSpliceDDS")
  {
    this->source_
      << CUTS_BE_CPP::function_header ("upcall_" + name)
      << "void " << this->servant_ << "::" << std::endl
      << "upcall_" << name << " (" << this->servant_ << " * servant," << std::endl
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
}

//
// Visit_ComponentServantArtifact
//
void Servant_Generator::
Visit_OutEventPort (const CHAOS::OutEventPort & port)
{
  std::string name = port.name ();
  CHAOS::Event event = port.ref ();
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
