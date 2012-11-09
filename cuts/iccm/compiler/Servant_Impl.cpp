// $Id$

#include "Servant_Impl.h"
#include "be_extern.h"
#include "be_global.h"

#include "ast_component.h"
#include "ast_publishes.h"
#include "ast_emits.h"
#include "ast_consumes.h"
#include "ast_attribute.h"

#include "utl_identifier.h"

namespace iCCM
{
/**
 * @class Attribute_Method
 */
class Attribute_Method : public Scope_Visitor
{
public:
  Attribute_Method (std::ofstream & hfile,
                    std::ofstream & sfile,
                    const ACE_CString & servant)
    : hfile_ (hfile),
      sfile_ (sfile),
      servant_ (servant)
  {

  }

  virtual ~Attribute_Method (void)
  {

  }

  //
  // visit_consumes
  //
  virtual int visit_attribute (AST_Attribute * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    // Generate the getter method.
    this->hfile_
      << "virtual " << field_type << " " << local_name << " (void);";

    this->sfile_
      << field_type << " " << this->servant_
      << "::" << local_name << " (void)"
      << "{"
      << "if (0 != this->impl_)" << std::endl
      << "  return this->impl_->" << local_name << " ();"
      << std::endl
      << "throw ::CORBA::INTERNAL ();"
      << "}";

    if (!node->readonly ())
    {
      AST_Type * field_type = node->field_type ();
      ACE_CString type_name;

      if (field_type->node_type () != AST_Type::NT_pre_defined)
        type_name += "const ";

      type_name += field_type->full_name ();

      // Generate the setter method.
      this->hfile_
        << "virtual void " << local_name << " (" << type_name << " val);";

      this->sfile_
        << "void " << this->servant_
        << "::" << local_name << " (" << type_name << " val)"
        << "{"
        << "if (0 != this->impl_)" << std::endl
        << "  this->impl_->" << local_name << " (val);"
        << "else" << std::endl
        << "  throw ::CORBA::INTERNAL ();"
        << "}";
    }

    this->hfile_
      << std::endl;

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

/**
 * @class Get_Consumer_Method
 */
class Get_Consumer_Method : public Scope_Visitor
{
public:
  Get_Consumer_Method (std::ofstream & hfile,
                       std::ofstream & sfile,
                       const ACE_CString & servant)
    : hfile_ (hfile),
      sfile_ (sfile),
      servant_ (servant)
  {

  }

  virtual ~Get_Consumer_Method (void)
  {

  }

  //
  // visit_consumes
  //
  virtual int visit_consumes (AST_Consumes * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << "virtual ::" << field_type << "Consumer_ptr get_" << local_name << "_consumer (void);"
      << std::endl;

    this->sfile_
      << "::" << field_type << "Consumer_ptr "
      << this->servant_ << "::get_" << local_name << "_consumer (void)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}";

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

/**
 * @class Get_Consumer_Method
 */
class Consumer_Variable : public Scope_Visitor
{
public:
  Consumer_Variable (std::ofstream & hfile, const ACE_CString & servant)
    : hfile_ (hfile),
      servant_ (servant)
  {

  }

  virtual ~Consumer_Variable (void)
  {

  }

  //
  // visit_consumes
  //
  virtual int visit_consumes (AST_Consumes * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << be_global->get_consumer_template_typename ()
      << " < " << this->servant_ << ", ::" << field_type << " > "
      << local_name << "_consumer_;";

    return 0;
  }

private:
  std::ofstream & hfile_;
  const ACE_CString & servant_;
};

/**
 * @class Servant_Push_Method
 *
 * Visitor responsible for generating the push_ methods for a
 * publish/emit event port.
 */
class Servant_Push_Method : public Scope_Visitor
{
public:
  Servant_Push_Method (std::ofstream & hfile,
                       std::ofstream & sfile,
                       const ACE_CString & servant)
    : hfile_ (hfile),
      sfile_ (sfile),
      servant_ (servant)
  {

  }

  virtual ~Servant_Push_Method (void)
  {

  }

  //
  // visit_consumes
  //
  virtual int visit_consumes (AST_Consumes * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << "virtual void push_" << local_name << " (::" << field_type << " *ev);"
      << std::endl;

    this->sfile_
      << "void " << this->servant_ << "::"
      << "push_" << local_name << " (::" << field_type << " *ev)"
      << "{"
      << "if (0 != this->impl_)" << std::endl
      << "  this->impl_->push_" << local_name << " (ev);"
      << "}";

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

/**
 * @class Subscribe_Method
 *
 * Visitor responsible for generating the new_*_event methods for
 * a publish/emit event port. This method is an iCCM extension!
 */
class Subscribe_Method : public Scope_Visitor
{
public:
  Subscribe_Method (std::ofstream & hfile,
                    std::ofstream & sfile,
                    const ACE_CString & servant)
    : hfile_ (hfile),
      sfile_ (sfile),
      servant_ (servant)
  {

  }

  virtual ~Subscribe_Method (void)
  {

  }

  //
  // visit_publishes
  //
  virtual int visit_publishes (AST_Publishes * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    // Method for subscribing a consumer.
    this->hfile_
      << "virtual ::Components::Cookie * subscribe_" << local_name
      << " (::" << field_type << "Consumer_ptr);"
      << "virtual ::" << field_type << "Consumer_ptr unsubscribe_" << local_name
      << " (::Components::Cookie *);"
      << std::endl;

    this->sfile_
      << "::Components::Cookie * " << this->servant_
      << "::subscribe_" << local_name << " (::" << field_type << "Consumer_ptr)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}"
      << "::" << field_type << "Consumer_ptr " << this->servant_
      << "::unsubscribe_" << local_name << " (::Components::Cookie *)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}";

    return 0;
  }

  //
  // visit_emits
  //
  virtual int visit_emits (AST_Emits * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    // Connect a consumer to the port.
    this->hfile_
      << "virtual void connect_" << local_name
      << " (::" << field_type << "Consumer_ptr);"
      << "virtual ::" << field_type << "Consumer_ptr disconnect_" << local_name << " (void);"
      << std::endl;

    this->sfile_
      << "void " << this->servant_
      << "::connect_" << local_name << " (::" << field_type << "Consumer_ptr)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}"
      << "::" << field_type << "Consumer_ptr " << this->servant_
      << "::disconnect_" << local_name << " (void)"
      << "{"
      << "throw ::CORBA::NO_IMPLEMENT ();"
      << "}";

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

/**
 * @class New_Event_Method
 *
 * Visitor responsible for generating the new_*_event methods for
 * a publish/emit event port. This method is an iCCM extension!
 */
class Bind_Port : public Scope_Visitor
{
public:
  Bind_Port (std::ofstream & sfile)
    : sfile_ (sfile)
  {

  }

  virtual ~Bind_Port (void)
  {

  }

  //
  // visit_publishes
  //
  virtual int visit_publishes (AST_Publishes * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    this->sfile_
      << "this->publishes_.bind (\"" << local_name << "\", &this->ctx_->"
      << "get_" << local_name << "_publisher_table ());";

    return 0;
  }

  //
  // visit_emits
  //
  virtual int visit_emits (AST_Emits * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    this->sfile_
      << "this->emits_.bind (\"" << local_name << "\", &this->ctx_->"
      << "get_" << local_name << "_publisher ());";

    return 0;
  }

  //
  // visit_consumes
  //
  virtual int visit_consumes (AST_Consumes * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    this->sfile_
      << "this->consumers_.bind (\"" << local_name << "\", &this->"
      << local_name << "_consumer_);";

    return 0;
  }

private:
  std::ofstream & sfile_;
};

/**
 * @class Base_Member_Init
 */
class Base_Member_Init : public Scope_Visitor
{
public:
  Base_Member_Init (std::ofstream & sfile, const ACE_CString & servant)
    : sfile_ (sfile),
      servant_ (servant)
  {

  }

  virtual ~Base_Member_Init (void)
  {

  }

  virtual int visit_consumes (AST_Consumes * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    this->sfile_
      << "," << std::endl
      << "  " << local_name << "_consumer_ (this, &"
      << this->servant_ << "::push_" << local_name << ")";

    return 0;
  }

private:
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

/**
 * @class Set_Attributes
 */
class Set_Attributes : public Scope_Visitor
{
public:
  Set_Attributes (std::ofstream & hfile,
                  std::ofstream & sfile,
                  const ACE_CString & servant)
    : hfile_ (hfile),
      sfile_ (sfile),
      servant_ (servant),
      is_first_ (true)
  {
  }

  virtual ~Set_Attributes (void)
  {

  }

  virtual int visit_component (AST_Component * node)
  {
    this->hfile_
      << "virtual void set_attributes (const ::Components::ConfigValues &);"
      << std::endl;

    this->sfile_
      << "void " << this->servant_
      << "::set_attributes (const ::Components::ConfigValues & config){"
      << "const ::CORBA::ULong length = config.length ();"
      << std::endl
      << "for (::CORBA::ULong i = 0; i < length; ++ i)"
      << "{"
      << "// Get the next configuraton value" << std::endl
      << "const ::Components::ConfigValue * value = config[i];"
      << std::endl;

    if (!this->is_first_)
      this->is_first_ = true;

    int retval = this->visit_scope (node);

    this->sfile_
      << "}"
      << "}";

    return retval;
  }

  //
  // visit_publishes
  //
  virtual int visit_attribute (AST_Attribute * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    AST_Type * field_type = node->field_type ();
    const char * field_name = field_type->full_name ();

    if (!this->is_first_)
      this->sfile_ << "else ";

    this->sfile_
      << "if (0 == ACE_OS::strcmp (value->name (), \"" << local_name << "\"))"
      << "{";

    switch (field_type->node_type ())
    {
    case AST_Type::NT_string:
      this->sfile_ << "const ";
      break;
    }

    this->sfile_
      << field_name << " tmp_value;"
      << std::endl
      << "if (!(value->value () >>= tmp_value))" << std::endl
      << "  throw ::Components::InvalidConfiguration ();"
      << std::endl
      << "this->" << local_name << " (tmp_value);"
      << "}";

    if (this->is_first_)
      this->is_first_ = false;

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
  bool is_first_;
};


//
// Servant_Impl
//
Servant_Impl::
Servant_Impl (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Servant_Impl
//
Servant_Impl::~Servant_Impl (void)
{

}

//
// visit_component
//
int Servant_Impl::visit_component (AST_Component * node)
{
  const ACE_CString context =
    ACE_CString (node->local_name ()->get_string ()) + "_Context";

  const ACE_CString servant =
    ACE_CString (node->local_name ()->get_string ()) + "_Servant";

  const char * local_name = node->local_name ()->get_string ();
  const char * flat_name = node->flat_name ();
  const char * full_name = node->full_name ();

  this->hfile_
    << "// Type definition of the servant base type." << std::endl
    << "typedef "
    << be_global->get_servant_template_typename ()
    << " < " << std::endl
    << "  " << servant << "," << std::endl
    << "  " << context << "," << std::endl
    << "  ::CIAO_" <<  flat_name << "_Impl::" << local_name << "_Exec," << std::endl
    << "  ::POA_" << full_name << " > " << servant << "_Base;"
    << std::endl
    << "class ";

  if (!be_global->svnt_export_macro_.empty ())
    this->hfile_ << be_global->svnt_export_macro_ << " ";

  this->hfile_
    << servant << std::endl
    << "  : public " << servant << "_Base"
    << "{";

  be_global->generate_class_preamble (node, this->hfile_, this->sfile_, servant);

  this->hfile_
    << "/// typedef for generated implementation code" << std::endl
    << "typedef " << servant << " self_type;" << std::endl
    << "/// Default constructor" << std::endl
    << "public:" << std::endl
    << servant << " (const char * name," << std::endl
    << "::PortableServer::POA_ptr poa," << std::endl
    << "::CIAO_" << flat_name << "_Impl::" << local_name << "_Exec_ptr executor);"
    << std::endl
    << "/// Destructor" << std::endl
    << "virtual ~" << servant << " (void);"
    << std::endl;

  this->sfile_
    << servant << "::" << std::endl
    << servant << " (const char * name," << std::endl
    << "::PortableServer::POA_ptr poa," << std::endl
    << "::CIAO_" << flat_name << "_Impl::" << local_name << "_Exec_ptr executor)" << std::endl
    << ": " <<  servant << "_Base (this, name, poa, executor)";

  if (be_global->uses_default_bmi (node))
  {
    Base_Member_Init bmi (this->sfile_, servant);
    bmi.visit_scope (node);
  }
  else
  {
    be_global->generate_custom_bmi (node, this->sfile_);
  }

  this->sfile_
    << "{";

  be_global->generate_constructor_preamble (node, this->sfile_);

  Bind_Port bind_port (this->sfile_);
  bind_port.visit_scope (node);

  // Allow backend to generate any additionl initialization code
  be_global->generate_constructor_postamble (node, this->sfile_);

  this->sfile_
    << "}"
    << servant << "::~" << servant << " (void)"
    << "{"
    << "}";

  // Write the function for setting the implementations attribute
  // values via the configuration file.
  Set_Attributes set_attributes (this->hfile_, this->sfile_, servant);
  node->ast_accept (&set_attributes);

  // Write the remaining set of the methods that are based on the
  // names and types of defined ports.
  Subscribe_Method sm (this->hfile_, this->sfile_, servant);
  sm.visit_scope (node);

  if (be_global->uses_default_push_method (node))
  {
    Servant_Push_Method spm (this->hfile_, this->sfile_, servant);
    spm.visit_scope (node);
  }
  else
  {
    be_global->generate_custom_push_method (node, this->hfile_, this->sfile_, servant);
  }

  Get_Consumer_Method gcm (this->hfile_, this->sfile_, servant);
  gcm.visit_scope (node);

  Attribute_Method attr_method (this->hfile_, this->sfile_, servant);
  attr_method.visit_scope (node);

  Consumer_Variable consumer_variables (this->hfile_, servant);
  consumer_variables.visit_scope (node);

  be_global->generate_class_postamble (node, this->hfile_, this->sfile_, servant);

  // Factory method for the servant. This is a C-style function
  // that is exported from the binary.
  this->hfile_
    << "};";

  if (!be_global->svnt_export_macro_.empty ())
  {
    this->hfile_
      << "extern \"C\" " << be_global->svnt_export_macro_
      << " ::PortableServer::Servant" << std::endl
      << "create_" << flat_name << "_Servant (const char * name," << std::endl
      << "::PortableServer::POA_ptr poa," << std::endl
      << "::Components::EnterpriseComponent_ptr p);"
      << std::endl;

    this->sfile_
      << "::PortableServer::Servant" << std::endl
      << "create_" << flat_name << "_Servant (const char * name," << std::endl
      << "::PortableServer::POA_ptr poa," << std::endl
      << "::Components::EnterpriseComponent_ptr p)"
      << "{"
      << "return ::iCCM::create_servant <"
      << " CIAO_" << flat_name << "_Impl::" << local_name << "_Exec, "
      << servant << " > (name, poa, p);"
      << "}";
  }

  return 0;
}

}
