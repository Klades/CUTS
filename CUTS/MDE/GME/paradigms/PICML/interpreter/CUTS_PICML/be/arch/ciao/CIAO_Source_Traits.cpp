// $Id$

#include "CIAO_Source_Traits.h"

#if !defined (__CUTS_INLINE__)
#include "CIAO_Source_Traits.inl"
#endif

// CUTS headers
#include "CIAO_Retn_Type.h"
#include "CIAO_In_Type.h"
#include "CIAO_Var_Type.h"
#include "../../BE_Impl_Node.h"
#include "../../BE_Options.h"

// UDM headers
#include "Uml.h"

// STL headers
#include <sstream>


//
// CUTS_CIAO_Source_Traits
//
CUTS_CIAO_Source_Traits::CUTS_CIAO_Source_Traits (void)
{

}

//
// ~CUTS_CIAO_Source_Traits
//
CUTS_CIAO_Source_Traits::~CUTS_CIAO_Source_Traits (void)
{

}

//
// open_file
//
bool CUTS_CIAO_Source_Traits::
open_file (const PICML::ComponentImplementationContainer & container)
{
  // Get the entry point for the node.
  this->get_impl_entry_point (container);

  // Construct the name of the file.
  std::ostringstream ostr;
  ostr
    << CUTS_BE_OPTIONS ()->output_directory_
    << "/" << container.name ()
    << CUTS_BE_OPTIONS ()->exec_suffix_ << ".cpp";

  // Open the file and pass contol to base class.
  this->out_.open (ostr.str ().c_str ());

  if (!this->out_.is_open ())
    return false;

  this->open_file_i ();
  return this->out_.good ();
}

//
// write_ProvidedRequestPort_begin
//
void CUTS_CIAO_Source_Traits::
write_ProvidedRequestPort_begin (const PICML::ProvidedRequestPort & facet)
{
  PICML::Component parent = PICML::Component::Cast (facet.parent ());
  PICML::Object obj = PICML::Object::Cast (facet.ref ());

  if (obj == Udm::null)
    return;

  std::string obj_scope = scope (obj, "::", true);

  this->out_
    << function_header ("Facet: get_" + (std::string)facet.name ())
    << obj_scope << "CCM_" << obj.name () << "_ptr" << std::endl
    << "  " << parent.name () << "::";

  this->_super::write_ProvidedRequestPort_begin (facet);

  this->out_
    << "{";
}

//
// write_ProvidedRequestPort_end
//
void CUTS_CIAO_Source_Traits::
write_ProvidedRequestPort_end (const PICML::ProvidedRequestPort & facet)
{
  this->out_ << "}";
}

//
// write_InEventPort_begin
//
void CUTS_CIAO_Source_Traits::
write_InEventPort_begin (const PICML::InEventPort & sink)
{
  PICML::Component parent = PICML::Component::Cast (sink.parent ());

  this->out_
    << function_header ("EventSink: push_" + (std::string)sink.name ())
    << "void " << parent.name () << "::";

  this->_super::write_InEventPort_begin (sink);

  this->out_
    << "{";
}

//
// write_method
//
void CUTS_CIAO_Source_Traits::
write_method (const PICML::OutEventPort & source)
{
  PICML::Component parent =
    PICML::Component::Cast (source.parent ());

  this->out_
    << function_header ("EventSource: " + (std::string)source.name ())
    << "void " << parent.name () << "_Context_Proxy::" << std::endl;

  this->_super::write_method (source);

  this->out_
    << "{";
}

//
// write_method
//
void CUTS_CIAO_Source_Traits::
write_method (const PICML::RequiredRequestPort & receptacle)
{
  PICML::Component parent =
    PICML::Component::Cast (receptacle.parent ());

  PICML::Object object = PICML::Object::Cast (receptacle.ref ());

  this->out_
    << function_header ("Receptacle: " + (std::string)receptacle.name ())
    << scope (object, "::") << object.name () << "_ptr "
    << parent.name () << "_Context_Proxy::" << std::endl;

  this->_super::write_method (receptacle);

  this->out_
    << "{";
}

//
// write_InEventPort_end
//
void CUTS_CIAO_Source_Traits::
write_InEventPort_end (const PICML::InEventPort & sink)
{
  this->out_
    << "}";
}

//
// write_PeriodicEvent_begin
//
void CUTS_CIAO_Source_Traits::
write_PeriodicEvent_begin (const PICML::PeriodicEvent & periodic)
{
  // Write the getter method for the attribute.
  PICML::Component parent = PICML::Component::Cast (periodic.parent ());

  this->out_
    << function_header (periodic.name ())
    << "void " << parent.name () << "::";

  // Write the class scope resolution.
  this->_super::write_PeriodicEvent_begin (periodic);

  this->out_
    << "{";
}

//
// write_ReadonlyAttribute_begin
//
void CUTS_CIAO_Source_Traits::
write_ReadonlyAttribute_begin (const PICML::ReadonlyAttribute & ro_attr)
{
  PICML::AttributeMember member = ro_attr.AttributeMember_child ();
  PICML::MemberType mtype = member.ref ();

  // Write the getter method for the attribute.
  this->out_
    << function_header ((std::string)ro_attr.name () + " [getter]")
    << CIAO_RETURN_TYPE (mtype);

  if (this->is_variable_type (mtype))
    this->out_ << " *";

  PICML::Component parent = ro_attr.Component_parent ();

  this->out_
    << " " << parent.name () << "::";

  // Write the class scope resolution.
  this->_super::write_ReadonlyAttribute_begin (ro_attr);

  this->out_
    << "{";
}

//
// write_method_end [ReadonlyAttribute]
//
void CUTS_CIAO_Source_Traits::
write_ReadonlyAttribute_end (const PICML::ReadonlyAttribute & ro_attr)
{
  this->out_
    << "}";
}

//
// write_method_begin [Attribute]
//
void CUTS_CIAO_Source_Traits::
write_Attribute_begin (const PICML::Attribute & attr)
{
  // Generate the getter method for the attribute.
  PICML::Attribute temp_attr (attr);
  PICML::ReadonlyAttribute ro = PICML::ReadonlyAttribute::Cast (temp_attr);

  this->write_ReadonlyAttribute_begin (ro);
  this->write_ReadonlyAttribute_end (ro);

  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType mtype = member.ref ();
  PICML::Component parent = attr.Component_parent ();

  // Close the getter method and generate the setter method
  // for the current attribute.
  this->out_
    << function_header ((std::string)attr.name () + " [setter]")
    << "void " << parent.name () << "::";

  this->_super::write_Attribute_begin (attr);

  this->out_
    << "{";
}

//
// write_method_end [Attribute]
//
void CUTS_CIAO_Source_Traits::
write_Attribute_end (const PICML::Attribute & attr)
{
  this->out_
    << "}";
}

//
// write_set_session_context
//
void CUTS_CIAO_Source_Traits::
write_set_session_context (const PICML::Component & component)
{
  this->out_
    << function_header ("Environment: session context")
    << "void " << component.name () << "::";

  this->_super::write_set_session_context (component);
}

//
// write_ciao_preactivate
//
void CUTS_CIAO_Source_Traits::
write_ciao_preactivate (const PICML::Component & component)
{
  this->out_
    << function_header ("Environment: preactivate")
    << "void " << component.name () << "::";

  this->_super::write_ciao_preactivate (component);
}

//
// write_ccm_activate
//
void CUTS_CIAO_Source_Traits::
write_ccm_activate (const PICML::Component & component)
{
  // Write the function declartion for the method.
  this->out_
    << function_header ("Environment: activate")
    << "void " << component.name () << "::";

  this->_super::write_ccm_activate (component);
}

//
// write_ciao_postactivate
//
void CUTS_CIAO_Source_Traits::
write_ciao_postactivate (const PICML::Component & component)
{
  this->out_
    <<  function_header ("Environment: postactivate")
    << "void " << component.name () << "::";

  this->_super::write_ciao_postactivate (component);
}

//
// write_ccm_passivate
//
void CUTS_CIAO_Source_Traits::
write_ccm_passivate (const PICML::Component & component)
{
  // Write the function declaration.
  this->out_
    << function_header ("Environment: passivate")
    << "void " << component.name () << "::";

  this->_super::write_ccm_passivate (component);
}

//
// write_ccm_remove
//
void CUTS_CIAO_Source_Traits::
write_ccm_remove (const PICML::Component & component)
{
  // Write the function declartion for the method.
  this->out_
    << function_header ("Environment: remove")
    << "void " << component.name () << "::";

  this->_super::write_ccm_remove (component);
}

//
// function_header
//
std::string CUTS_CIAO_Source_Traits::
function_header (const std::string & func)
{
  std::ostringstream ostr;
  ostr
    << "//" << std::endl
    << "// " << func << std::endl
    << "//" << std::endl;
  return ostr.str ();
}

//
// write_entrypoint
//
void CUTS_CIAO_Source_Traits::
write_entrypoint (const PICML::MonolithicImplementation & monoimpl,
                  const PICML::ComponentImplementationArtifact & artifact)
{
  this->out_
    << function_header (artifact.EntryPoint ())
    << "::Components::EnterpriseComponent_ptr " << std::endl
    << artifact.EntryPoint () << " (void)"
    << "{"
    << "::Components::EnterpriseComponent_ptr retval =" << std::endl
    << "  ::Components::EnterpriseComponent::_nil ();"
    << std::endl
    << "ACE_NEW_RETURN (retval," << std::endl
    << "::" << monoimpl.name () << " ()," << std::endl
    << "::Components::EnterpriseComponent::_nil ());"
    << std::endl
    << "return retval;"
    << "}"
    << std::endl;
}

//
// write_TwowayOperation_begin
//
void CUTS_CIAO_Source_Traits::
write_TwowayOperation_begin (const PICML::TwowayOperation & twoway)
{
  PICML::ReturnType return_type = twoway.ReturnType_child ();

  this->out_
    << function_header ("twoway: " + (std::string) twoway.name ());

  if (return_type != Udm::null)
  {
    PICML::MemberType type = return_type.ref ();

    if (type != Udm::null)
    {
      this->out_ << CIAO_RETURN_TYPE (type);

      if (this->is_variable_type (type))
        this->out_ << " *";
    }
  }
  else
  {
    this->out_ << "void";
  }

  this->out_
    << " " << this->object_impl_ << "::";

  this->_super::write_TwowayOperation_begin (twoway);

  this->out_
    << "{";
}

//
// write_OnewayOperation_begin
//
void CUTS_CIAO_Source_Traits::
write_OnewayOperation_begin (const PICML::OnewayOperation & oneway)
{
  PICML::Object parent = PICML::Object::Cast (oneway.parent ());

  this->out_
    << function_header ("oneway: " + (std::string) oneway.name ())
    << "void " << this->object_impl_ << "::";

  this->_super::write_OnewayOperation_begin (oneway);

  this->out_
    << "{";
}

//
// write_OnewayOperation_end
//
void CUTS_CIAO_Source_Traits::
write_OnewayOperation_end (const PICML::OnewayOperation & oneway)
{
  this->out_
    << "}";
}

//
// write_object_impl_begin
//
void CUTS_CIAO_Source_Traits::
write_object_impl_begin (const PICML::Component & component,
                         const PICML::ProvidedRequestPort & facet)
{
  this->object_impl_ = (std::string) facet.name () + "_i";

  this->out_
    // Write the constructor.
    << function_header (this->object_impl_)
    << this->object_impl_ << "::" << this->object_impl_ << " (void)"
    << "{"
    << std::endl
    << "}"

    // Write the destructor.
    << function_header ("~" + this->object_impl_)
    << this->object_impl_ << "::~" << this->object_impl_ << " (void)"
    << "{"
    << std::endl
    << "}";
}

//
// write_object_impl_end
//
void CUTS_CIAO_Source_Traits::
write_object_impl_end (const PICML::Component & component,
                       const PICML::ProvidedRequestPort & facet)
{
  this->object_impl_.empty ();
}

//
// write_TwowayOperation_end
//
void CUTS_CIAO_Source_Traits::
write_TwowayOperation_end (const PICML::TwowayOperation & twoway)
{
  // Get the return type. If we don't have a return type, then we
  // can assume the return type is 'void'.
  PICML::ReturnType return_type = twoway.ReturnType_child ();

  if (return_type != Udm::null)
  {
    PICML::MemberType type = return_type.ref ();

    try
    {
      PICML::PredefinedType pretype = PICML::PredefinedType::Cast (type);
      Uml::Class classtype = pretype.type ();

      if (classtype == PICML::LongInteger::meta ||
          classtype == PICML::ShortInteger::meta ||
          classtype == PICML::Byte::meta)
      {
        this->out_
          << "return 0;";
      }
      else if (classtype == PICML::String::meta)
      {
        this->out_
          << "::CORBA::String_var str = ::CORBA::string_dup (\"\");"
          << "return str._retn ();";
      }
      else if (classtype == PICML::RealNumber::meta)
      {
        this->out_
          << "return 0.0;";
      }
      else if (classtype == PICML::Boolean::meta)
      {
        this->out_
          << "return true;";
      }
      else
      {
        this->out_
          << "/* unsupported type [" << classtype.name ()
          << "] */" << std::endl;
      }
    }
    catch (...)
    {

    }
  }

  this->out_
    << "}";
}
