// $Id$

#include "Component_Implementation.h"

#if !defined (__CUTS_INLINE__)
#include "Component_Implementation.inl"
#endif

#include "In_Type_Generator.h"
#include "Retn_Type_Generator.h"

#include "../../BE_Options.h"
#include "../../lang/cpp/Component_Impl_Generator.h"
#include "boost/bind.hpp"
#include "Uml.h"

/**
 * @class Visit_Component_Interface
 */
class Visit_Component_Interface : public PICML::Visitor
{
protected:
  Visit_Component_Interface (void)
  {

  }

  virtual ~Visit_Component_Interface (void)
  {

  }

  void Visit_MonolithicImplementation (const PICML::MonolithicImplementation & impl)
  {
    PICML::Implements implements = impl.dstImplements ();

    if (implements == Udm::null)
      return;

    PICML::ComponentRef ref = implements.dstImplements_end ();
    PICML::Component component = ref.ref ();

    if (ref != Udm::null)
      component.Accept (*this);
  }
};

/**
 * @class Locate_Parent_File
 */
class Locate_Parent_File : public Visit_Component_Interface
{
public:
  Locate_Parent_File (void)
  {

  }

  virtual ~Locate_Parent_File (void)
  {

  }

  void Visit_Component (const PICML::Component & component)
  {
    PICML::MgaObject parent = component.parent ();

    while (parent.type () == PICML::Package::meta)
      parent = PICML::MgaObject::Cast (parent.parent ());

    this->result_ = PICML::File::Cast (parent);
  }

  PICML::File result_;
};

/**
 * @class Include_Worker_Files
 */
class Include_Worker_Files : public Visit_Component_Interface
{
public:
  Include_Worker_Files (std::ostream & out)
    : out_ (out)
  {

  }

  virtual ~Include_Worker_Files (void)
  {

  }

  virtual void Visit_Component (const PICML::Component & component)
  {
    std::set < PICML::WorkerType > workers = component.WorkerType_children ();

    std::for_each (workers.begin (),
                   workers.end (),
                   boost::bind (&PICML::WorkerType::Accept,
                                _1,
                                boost::ref (*this)));
  }

  virtual void Visit_WorkerType (const PICML::WorkerType & wt)
  {
    // Get the parent.
    PICML::Worker worker = wt.ref ();

    if (worker == Udm::null)
      return;

    // Locate the file that contains this worker.
    PICML::MgaObject parent = worker.parent ();

    while (parent.type () == PICML::WorkerPackage::meta)
      parent = PICML::MgaObject::Cast (parent.parent ());

    // Write the file name to the stream.
    this->out_ << CUTS_BE_CPP::include (parent.name ());
  }

private:
  std::ostream & out_;
};

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Open_T

void CUTS_BE_File_Open_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  // Construct the name of the file.
  std::string basename (CUTS_BE_OPTIONS ()->output_directory_);
  basename += "/" + std::string (impl.name ());

  std::string source_name = basename + ".cpp";
  std::string header_name = basename + ".h";

  // Open all the files for writing.
  this->ctx_.source_.open (source_name.c_str ());
  this->ctx_.source_formatter_.reset (new CUTS_BE_CCM::Cpp::Context::formatter_type (this->ctx_.source_));

  this->ctx_.header_.open (header_name.c_str ());
  this->ctx_.header_formatter_.reset (new CUTS_BE_CCM::Cpp::Context::formatter_type (this->ctx_.header_));
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Close_T

void CUTS_BE_File_Close_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  this->ctx_.header_formatter_.reset ();

  if (this->ctx_.header_.is_open ())
    this->ctx_.header_.close ();

  this->ctx_.source_formatter_.reset ();

  if (this->ctx_.source_.is_open ())
    this->ctx_.source_.close ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Include_File_T

void CUTS_BE_Include_File_T <CUTS_BE_CCM::Cpp::Context>::
generate (const std::string & include)
{
  this->ctx_.header_ << CUTS_BE_CPP::include (include);
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Prologue_T

void CUTS_BE_Prologue_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  std::string name (impl.name ());

  // Generate the hash definition for this file.
  std::string hashdef = "_" + name + "_H_";
  std::transform (hashdef.begin (),
                  hashdef.end (),
                  hashdef.begin (),
                  &::toupper);

  Locate_Parent_File locator;
  PICML::MonolithicImplementation (impl).Accept (locator);

  // Construct the pathname of the executor include file.
  std::string pathname = locator.result_.Path ();

  if (!pathname.empty ())
    pathname += "/";

  pathname += locator.result_.name ();

  this->ctx_.header_
    << "// -*- C++ -*-" << std::endl
    << std::endl
    << "#ifndef " << hashdef << std::endl
    << "#define " << hashdef << std::endl
    << std::endl
    << "#if !defined (ACE_LACKS_PRAGMA_ONCE)" << std::endl
    << "#pragma once" << std::endl
    << "#endif /* ACE_LACKS_PRAGMA_ONCE */" << std::endl
    << std::endl
    << CUTS_BE_CPP::include ("ace/pre")
    << CUTS_BE_CPP::include (pathname + "EC")
    << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Component_T")
    << std::endl;

  // Write the includes for the worker files.
  Include_Worker_Files includes (this->ctx_.header_);
  PICML::MonolithicImplementation (impl).Accept (includes);

  this->ctx_.source_
    << CUTS_BE_CPP::single_line_comment ("This file was generated by:")
    << CUTS_BE_CPP::single_line_comment ("$Id$")
    << std::endl
    << CUTS_BE_CPP::include (name)
    /// @todo We should only include the following header if there are
    ///       are output events (or output ports) for this component.
    ///       Otherwise, we can leave this include out of this source.
    << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Events_T")
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Epilogue_T

void CUTS_BE_Epilogue_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ComponentImplementationContainer & container,
          const PICML::MonolithicImplementation & impl)
{
  // Generate the hash definition for this file.
  std::string name (container.name ());
  std::string hashdef = "_" + name + "_H_";
  std::transform (hashdef.begin (),
                  hashdef.end (),
                  hashdef.begin (),
                  &::toupper);

  this->ctx_.header_
    << CUTS_BE_CPP::include ("ace/post")
    << std::endl
    << "#endif  // !defined " << hashdef << std::endl
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("end of auto-generated file")
    << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::single_line_comment ("end of auto-generated file")
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Begin_T

void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::MonolithicImplementation & impl,
          const PICML::Component & component)
{
  // This part of the code generates the header file.
  std::string namespace_name (impl.name ());
  std::string implname (component.name ());

  std::vector <PICML::PeriodicEvent> periodics =
    component.PeriodicEvent_kind_children ();

  if (!periodics.empty ())
    this->ctx_.header_ << CUTS_BE_CPP::include ("cuts/Periodic_Event_T");

  this->ctx_.header_
    << std::endl
    << "namespace " << namespace_name
    << "{";

  typedef std::vector <PICML::OutEventPort> OutEventPort_Set;
  OutEventPort_Set outevents = component.OutEventPort_kind_children ();

  std::for_each (outevents.begin (),
                 outevents.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  std::vector <PICML::ProvidedRequestPort> facets =
    component.ProvidedRequestPort_kind_children ();

  std::for_each (facets.begin (),
                 facets.end (),
                 boost::bind (&PICML::ProvidedRequestPort::Accept,
                              _1,
                              boost::ref (*this)));

  std::string destructor = "~" + implname;

  // Construct the name of the executor.
  std::string exec =
    "CIAO" + CUTS_BE_CPP::fq_type (component, "_") +
    "_Impl::" + implname + "_Exec";

  // Construct the name of the context.
  std::string context (CUTS_BE_CPP::scope (component));
  context += "CCM_" + implname + "_Context";

  std::string basetype ("CUTS_CCM_Component_T < ");
  basetype += exec + ", " + context + " >";

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("Type definition of the implentation base type")
    << "typedef " << basetype << " " << implname << "_Base;"
    << std::endl
    << "/**" << std::endl
    << " * @class " << implname << std::endl
    << " *" << std::endl
    << " * Implementation of the " << exec << " component executor" << std::endl
    << " */" << std::endl
    << "class " << implname << " :" << std::endl
    << "  public " << implname << "_Base {"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("Type definition of the base component type")
    << "typedef " << implname << "_Base base_type;"
    << std::endl

    // Write the default constructor.
    << CUTS_BE_CPP::single_line_comment ("Default constructor")
    << implname << " (void);"
    << std::endl

    // Write the destructor.
    << CUTS_BE_CPP::single_line_comment ("Destructor")
    << "virtual " << destructor << " (void);"
    << std::endl;

  // This part of the code generates the source file.
  this->ctx_.source_
    << "namespace " << namespace_name
    << "{";

  // This part of the code generates the source file.
  this->ctx_.source_
    << CUTS_BE_CPP::function_header (implname)
    << implname << "::" << implname << " (void)";

  CUTS_BE_CPP::Base_Member_Init base_member_init (this->ctx_.source_);
  PICML::Component (component).Accept (base_member_init);

  this->ctx_.source_
    << "{";

  std::vector <PICML::InEventPort> input_events = component.InEventPort_kind_children ();

  CUTS_BE_CPP::Initialize_Entity entity (this->ctx_.source_);
  std::for_each (periodics.begin (),
                 periodics.end (),
                 boost::bind (&PICML::PeriodicEvent::Accept,
                              _1,
                              boost::ref (entity)));

  std::for_each (input_events.begin (),
                 input_events.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (entity)));

  // Finish the constructor.
  this->ctx_.source_
    << "}"
    // Write the destructor's implementation.
    << CUTS_BE_CPP::function_header (destructor)
    << implname << "::" << destructor << " (void)"
    << "{"
    << "}";
}

void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_CCM::Cpp::Context>::
Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & facet)
{
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("Forward decl.")
    << "class " << facet.name () << "_i;"
    << std::endl;
}

void CUTS_BE_Component_Impl_Begin_T <CUTS_BE_CCM::Cpp::Context>::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  this->ctx_.outevent_mgr_.insert (PICML::OutEventPort (port));
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_End_T

void CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::MonolithicImplementation & impl,
          const PICML::Component & component)
{
  // This part of the code generates the header file.
  this->ctx_.header_
    << "};"
    << "}";

  // This part of the code generates the source file.
  this->ctx_.source_
    << "}";

  this->ctx_.outevent_mgr_.clear ();
}

void CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
Visit_InEventPort (const PICML::InEventPort & port)
{
  PICML::Input input = port.dstInput ();
  this->sink_name_ = port.name ();

  if (Udm::null != input)
    input.Accept (*this);
}

void CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
Visit_PeriodicEvent (const PICML::PeriodicEvent & periodic)
{
  std::string name ("periodic_");
  name += periodic.name ();

  // Configure the periodic event.
  this->ctx_.header_
    << "this->" << name << "_.init (this, &type::" << name << ");"
    << "this->register_object   (&this->" << name << "_);";
}

void CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
Visit_Input (const PICML::Input & input)
{
  PICML::InputAction action = input.dstInput_end ();
  action.Accept (*this);
}

void CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
Visit_InputAction (const PICML::InputAction & action)
{
  std::vector <PICML::SimpleProperty> properties = action.SimpleProperty_kind_children ();

  std::vector <PICML::SimpleProperty>::const_iterator iter =
    std::find_if (properties.begin (),
                  properties.end (),
                  boost::bind (std::equal_to <std::string> (),
                               "asynchronous",
                               boost::bind (&PICML::Property::name, _1)));

  std::string varname ("push_");
  varname += this->sink_name_ + "_";

  this->ctx_.source_
    << "this->" << varname << ".init (this, "
    << "&type::push_" << this->sink_name_ << "_i);"
    << "this->register_object (&this->" << varname << ");";

  std::for_each (properties.begin (),
                 properties.end (),
                 boost::bind (&PICML::Property::Accept, _1, boost::ref (*this)));
}

void CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
Visit_Property (const PICML::Property & prop)
{
  std::string name (prop.name ());

  if (name == "threadCount")
  {
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);

    this->ctx_.source_
      << "this->push_" << name << "_.thread_count ("
      << simple.Value () << ");";
  }
  else if (name == "threadAffinity")
  {
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);

    this->ctx_.source_
      << "this->push_" << name << "_.affinity_mask ("
      << simple.Value () << ");";
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_End_T

void CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::MonolithicImplementation & monoimpl,
          const PICML::ComponentImplementationArtifact & artifact)
{
  std::string entrypoint (artifact.EntryPoint ());
  PICML::ImplementationArtifact ia = artifact.ref ();

  // Construct the export macro and export filename.
  std::string export_basename (ia.name ());
  std::string export_macro (export_basename);

  std::transform (export_macro.begin (),
                  export_macro.end (),
                  export_macro.begin (),
                  &toupper);

  this->ctx_.header_
    << CUTS_BE_CPP::include (export_basename + "_export")
    << std::endl
    << CUTS_BE_CPP::function_header (entrypoint)
    << "extern \"C\" " << export_macro << "_Export" << std::endl
    << "::Components::EnterpriseComponent_ptr " << entrypoint << " (void);"
    << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::function_header (entrypoint)
    << "::Components::EnterpriseComponent_ptr " << std::endl
    << entrypoint << " (void)"
    << "{"
    << "::Components::EnterpriseComponent_ptr retval =" << std::endl
    << "  ::Components::EnterpriseComponent::_nil ();"
    << std::endl
    << "ACE_NEW_RETURN (retval, " << std::endl
    << "::" << monoimpl.name () << "::";

  PICML::Implements implements = monoimpl.dstImplements ();

  if (Udm::null != implements)
    implements.Accept (*this);

  this->ctx_.source_
    << " ()," << std::endl
    << "::Components::EnterpriseComponent::_nil ());"
    << std::endl
    << "return retval;"
    << "}"
    << std::endl;
}

void CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_CCM::Cpp::Context>::
Visit_Implements (const PICML::Implements & implements)
{
  PICML::ComponentRef ref = implements.dstImplements_end ();
  PICML::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
}

void CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_CCM::Cpp::Context>::
Visit_Component (const PICML::Component & component)
{
  this->ctx_.source_
    << component.name ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_Begin_T

void CUTS_BE_Environment_Method_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::MultiInputAction & action)
{
  std::string name (action.name ());
  PICML::Component parent = PICML::Component::Cast (action.parent ());
  std::string parent_name = parent.name ();

  if ("activate" == name)
  {
    this->ctx_.header_
      << "virtual void ccm_activate (void);"
      << std::endl;

    this->ctx_.source_
      << CUTS_BE_CPP::function_header ("ccm_activate")
      << "void " << parent_name << "::ccm_activate (void)"
      << "{";
  }
  else if ("configuration_complete" == name)
  {
    this->ctx_.header_
      << "virtual void configuration_complete (void);"
      << std::endl;

    this->ctx_.source_
      << CUTS_BE_CPP::function_header ("configuration_complete")
      << "void " << parent_name << "::configuration_complete (void)"
      << "{";
  }
  else if ("passivate" == name || "remove" == name)
  {
    const std::string function_name ("ccm_" + name);

    this->ctx_.header_
      << "virtual void " << function_name << " (void);"
      << std::endl;

    this->ctx_.source_
      << CUTS_BE_CPP::function_header (function_name)
      << "void " << parent_name << "::" << function_name << " (void)"
      << "{"
      << "this->base_type::" << function_name << " ();";
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_End_T

void CUTS_BE_Environment_Method_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::MultiInputAction & action)
{
  std::string name (action.name ());
  PICML::Component parent = PICML::Component::Cast (action.parent ());

  if ("activate" == name)
  {
    this->ctx_.source_
      << "this->base_type::ccm_activate ();"
      << "}";
  }
  else if ("configuration_complete" == name)
  {
    this->ctx_.source_
      << "this->base_type::configuration_complete ();"
      << "}";
  }
  else if ("passivate" == name || "remove" == name)
  {
    this->ctx_.source_
      << "}";
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Begin_T

void CUTS_BE_Attribute_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::Attribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();

  if (Udm::null == member)
    return;

  PICML::MemberType member_type = member.ref ();

  if (Udm::null == member_type)
    return;

  std::string name (attr.name ());
  PICML::Component parent = PICML::Component::Cast (attr.parent ());
  std::string parent_name (parent.name ());

  // This part generates the header information.
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("attribute setter: " + name)
    << "virtual void " << name << " (";

  CUTS_BE_CCM::Cpp::In_Type_Generator in_type_header_gen (this->ctx_.header_);
  in_type_header_gen.generate (member_type);

  this->ctx_.header_
    << " " << name << ");"
    << std::endl;

  // This part generates the source information.
  this->ctx_.source_
    << CUTS_BE_CPP::function_header ("attribute setter: " + name)
    << "void " << parent_name << "::" << name << " (";

  CUTS_BE_CCM::Cpp::In_Type_Generator in_type_source_gen (this->ctx_.source_);
  in_type_source_gen.generate (member_type);

  this->ctx_.source_
    << " " << name << ")"
    << "{";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_End_T

void CUTS_BE_Attribute_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::Attribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  if (Udm::null == member)
    return;

  PICML::MemberType type = member.ref ();
  if (Udm::null == type)
    return;

  Uml::Class meta = type.type ();
  std::string attr_name (attr.name ());

  this->ctx_.source_
    << "this->" << attr_name << "_ = ";

  if (meta == PICML::GenericObject::meta)
  {
    // We need to create a duplicate copy of the interface
    // before we store it.
    this->ctx_.source_
      << std::endl
      << "  ::CORBA::Object::_duplicate (" << attr_name << ");";
  }
  else if (meta == PICML::TypeEncoding::meta)
  {
    // We need to create a duplicate copy of the typecode
    // interface before we store it.
    this->ctx_.source_
      << std::endl
      << "  ::CORBA::TypeCode::_duplicate (" << attr_name << ");";
  }
  else
  {
    this->ctx_.source_ << attr_name << ";";
  }

  this->ctx_.source_
    << "}";

  // Make sure we generate the <readonly> variant.
  this->readonly_begin_.generate (attr);
  this->readonly_end_.generate (attr);
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_Begin_T

void CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  if (member == Udm::null)
    return;

  PICML::MemberType type = member.ref ();
  if (type == Udm::null)
    return;

  std::string attr_name (attr.name ());
  PICML::Component parent = PICML::Component::Cast (attr.parent ());

  // This part of the code generate to the header file.
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("attribute getter: " + attr_name)
    << "virtual ";

  CUTS_BE_CCM::Cpp::Retn_Type_Generator retn_header_gen (this->ctx_.header_);
  retn_header_gen.generate (type);

  this->ctx_.header_
    << " " << attr_name << " (void);"
    << std::endl;

  // This part of the code generate to the source file.
  this->ctx_.source_
    << CUTS_BE_CPP::function_header ("attribute getter: " + attr_name);

  CUTS_BE_CCM::Cpp::Retn_Type_Generator retn_source_gen (this->ctx_.source_);
  retn_source_gen.generate (type);

  this->ctx_.source_
    << " " << parent.name () << "::" << attr_name << " (void)"
    << "{";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_End_T

void CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();

  if (member == Udm::null)
    return;

  PICML::MemberType type = member.ref ();

  if (type == Udm::null)
    return;

  Uml::Class meta = type.type ();
  std::string attr_name (attr.name ());

  // This section of the code write the source file.

  if (meta == PICML::String::meta)
  {
    // Strings are special case. We need to return a duplicate
    // copy of the string, or we will have major problems.
    this->ctx_.source_
      << "::CORBA::String_var s =" << std::endl
      << "  ::CORBA::string_dup (this->"
      << attr_name << "_.c_str ());"
      << "return s._retn ();";
  }
  else if (meta == PICML::GenericValue::meta)
  {
    // We need to create an <Any::_var_type> for temporary
    // storage and give control to the client using the
    // _retn () method.
    this->ctx_.source_
      << "CORBA::Any * temp = 0;"
      << "ACE_NEW_THROW_EX (temp," << std::endl
      << "::CORBA::Any (this->" << attr_name << "_)," << std::endl
      << "::CORBA::NO_MEMORY ());"
      << "return temp;";
  }
  else if (meta == PICML::GenericObject::meta)
  {
    this->ctx_.source_
      << "return ::CORBA::Object::_duplicate (this->"
      << attr_name << "_.in ());";
  }
  else if (meta == PICML::TypeEncoding::meta)
  {
    this->ctx_.source_
      << "return ::CORBA::TypeCode::_duplicate (this->"
      << attr_name << "_.in ());";
  }
  else
  {
    this->ctx_.source_
      << "return this->" << attr.name () << "_;";
  }

  this->ctx_.source_
    << "}";
}


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Begin_T

void CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::PeriodicEvent & periodic)
{
  std::string name = periodic.name ();
  std::string func_name = "periodic_" + name;

  PICML::Component parent (PICML::Component::Cast (periodic.parent ()));
  std::string parent_name (parent.name ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("PeriodicEvent: " + name)
    << "void " << func_name << " (void);"
    << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::function_header ("PeriodicEvent: " + name)
    << "void " << parent_name << "::" << func_name << " (void)"
    << "{";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_End_T

void CUTS_BE_PeriodicEvent_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::PeriodicEvent & periodic)
{
  this->ctx_.source_
    << "}";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_Begin_T

void CUTS_BE_InEventPort_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::InEventPort & sink,
          const std::vector <PICML::Property> & properties)
{
  // Make sure this is not a template event port.
  PICML::EventType et = sink.ref ();
  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  // Determine if this input event is asynchronous.
  std::vector <PICML::Property>::const_iterator iter =
    std::find_if (properties.begin (),
                  properties.end (),
                  boost::bind (std::equal_to <std::string> (),
                               "asynchronous",
                               boost::bind (&PICML::Property::name, _1)));

  bool is_async = iter != properties.end ();

  // Generate the appropriate methods.
  PICML::Event ev = PICML::Event::Cast (et);
  PICML::Component parent = PICML::Component::Cast (sink.parent ());
  std::string parent_name (parent.name ());
  std::string name (sink.name ());
  std::string fq_name (CUTS_BE_CPP::fq_type (ev));

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("sink: " + name)
    << "virtual void push_" << name << " (" << fq_name << " * ev);"
    << std::endl;

  if (is_async)
  {
    this->ctx_.header_
      << "private:" << std::endl
      << CUTS_BE_CPP::single_line_comment ("async event handler variable: " + name)
      << "CUTS_CCM_Event_Handler_T < "
      << parent_name << ", " << fq_name << " > " << name << "_event_handler_;"
      << std::endl
      << "public:" << std::endl
      << CUTS_BE_CPP::single_line_comment ("sink impl: " + name)
      << "void push_" << name << "_i (" << fq_name << " * ev);"
      << std::endl;
  }

  this->ctx_.source_
    << CUTS_BE_CPP::function_header ("sink: " + name)
    << "void " << parent_name << "::push_" << name << " (" << fq_name << " * ev)"
    << "{";

  if (is_async)
  {
    this->ctx_.source_
      << "this->" << name << "_event_handler_.handle_event (ev);"
      << "}"
      << CUTS_BE_CPP::function_header ("sink: " + name)
      << "void " << parent_name << "::push_" << name << "_i (" << fq_name << " * ev)"
      << "{";
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_End_T

void CUTS_BE_InEventPort_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::InEventPort & attr,
          const std::vector <PICML::Property> & properties)
{
  this->ctx_.source_
    << "ACE_UNUSED_ARG (ev);"
    << "}";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_Begin_T

void CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ProvidedRequestPort & facet)
{
  PICML::Object obj = PICML::Object::Cast (facet.ref ());

  if (Udm::null == obj)
    return;

  PICML::Component parent (PICML::Component::Cast (facet.parent ()));
  const std::string parent_name (parent.name ());
  const std::string scope (CUTS_BE_CPP::scope (obj));
  const std::string name (facet.name ());
  const std::string func ("get_" + name);
  const std::string obj_name (obj.name ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("facet: " + name)
    << "virtual " << scope << "CCM_" << obj_name << "_ptr" << std::endl
    << "  " << func << " (void);"
    << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::function_header ("facet: " + name)
    << scope << "CCM_" << obj_name << "_ptr" << std::endl
    << "  " << parent_name << "::" << func << " (void)"
    << "{";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_End_T

void CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_CCM::Cpp::Context>::
generate (const PICML::ProvidedRequestPort & port)
{
  PICML::Object obj = PICML::Object::Cast (port.ref ());

  if (obj == Udm::null)
    return;

  std::string obj_scope (CUTS_BE_CPP::scope (obj));
  std::string name (obj.name ());

  this->ctx_.source_
    << "return " << obj_scope << "CCM_" << name << "::_nil ();"
    << "}";
}

namespace CUTS_BE_CCM
{

namespace Cpp
{

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

}   // namespace Cpp
}   // namespace CUTS_BE_CCM
