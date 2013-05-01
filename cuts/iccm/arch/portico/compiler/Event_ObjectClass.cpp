// $Id:

#include "Event_ObjectClass.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_eventtype.h"
#include "ast_field.h"
#include "ast_module.h"
#include "ast_predefined_type.h"

#include "utl_identifier.h"
#include <iostream>
#include <vector>

/**
 * @class Event_ObjectClass_Ctor
 *
 * Visitor that builds the constructor
 */
class Event_ObjectClass_Ctor : public iCCM::Scope_Visitor
{
public:
  //
  // Event_ObjectClass_Ctor
  //
  Event_ObjectClass_Ctor (std::ofstream & hfile, std::ofstream & sfile, ACE_CString & class_name)
   : hfile_ (hfile),
     sfile_ (sfile),
     class_name_ (class_name)
  {

  }

  //
  // visit_eventtype
  //
  virtual int visit_eventtype (AST_EventType * node)
  {
    this->hfile_
      << "  " << this->class_name_ << " (RTI::ObjectClassHandle type";

    this->sfile_
      << this->class_name_ << "::" << this->class_name_ << " (RTI::ObjectClassHandle type";

    // Identify all the attributes
    this->visit_scope (node);

    // Generate the signature
    std::vector <ACE_CString>::iterator end = this->attributes_.end ();
    for (std::vector <ACE_CString>::iterator it = this->attributes_.begin ();
         it != end;
         ++it)
    {
      this->hfile_
        << "," << std::endl
        << "RTI::AttributeHandle " << *it << "_handle";

      this->sfile_
        << "," << std::endl
        << "RTI::AttributeHandle " << *it << "_handle";
    }

    this->hfile_
      << ");";

    // Generate the BMI
    this->sfile_
      << ")" << std::endl
      << ": Portico_ObjectClass (type)";

    for (std::vector <ACE_CString>::iterator it = this->attributes_.begin ();
         it != end;
         ++it)
    {
      this->sfile_
        << "," << std::endl
        << "  " << *it << "_ (" << *it << "_handle)";
    }

    this->sfile_
      << std::endl
      << "{" << std::endl
      << "}";

    return 0;
  }

  //
  // visit_field
  //
  virtual int visit_field (AST_Field * node)
  {
    ACE_CString local_name (node->local_name ()->get_string ());
    this->attributes_.push_back (local_name);

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString & class_name_;
  std::vector <ACE_CString> attributes_;
};

/**
 * @class Event_ObjectClass_HLA
 *
 * Visitor that builds the HLA write and read methods
 */
class Event_ObjectClass_HLA : public iCCM::Scope_Visitor
{
public:
  //
  // Event_ObjectClass_HLA
  //
  Event_ObjectClass_HLA (std::ofstream & hfile, std::ofstream & sfile, ACE_CString & class_name)
   : hfile_ (hfile),
     sfile_ (sfile),
     class_name_ (class_name)
  {

  }

  //
  // visit_eventtype
  //
  virtual int visit_eventtype (AST_EventType * node)
  {
    this->hfile_
      << "  virtual void __hla_read_attributes (const RTI::AttributeHandleValuePairSet & attrs);"
      << "  virtual void __hla_write_attributes (RTI::AttributeHandleValuePairSet & attrs) const;" << std::endl;

    // Gather the field names
    this->visit_scope (node);

    // Generate __hla_read_attributes broilerplate
    std::vector <ACE_CString>::iterator end = this->attributes_.end ();
    this->sfile_
      << "void " << this->class_name_ << "::" << std::endl
      << "__hla_read_attributes (const RTI::AttributeHandleValuePairSet & attrs)"
      << "{"
      << "const RTI::ULong attr_length = attrs.size ();"
      << "for (RTI::ULong i = 0; i < attr_length; ++ i)"
      << "{"
      << "RTI::Handle handle = attrs.getHandle (i);"
      << "switch (handle)"
      << "{";

    // Generate __hla_read_attributes based on fields
    for (std::vector <ACE_CString>::iterator it = this->attributes_.begin ();
         it != end;
         ++it)
    {
      this->sfile_
        << "case (this->" << *it << "_):" << std::endl
        << "  this->" << *it << "_.read (attrs, i);"
        << "  break;";
    }

    this->sfile_
      << "}"
      << "}"
      << "}";

    // Generate __hla_write_attributes broilerplate
    this->sfile_
      << "void " << this->class_name_ << "::" << std::endl
      << "__hla_write_attributes (RTI::AttributeHandleValuePairSet & attrs) const"
      << "{";

    // Generate __hla_write_attributes based on fields
    for (std::vector <ACE_CString>::iterator it = this->attributes_.begin ();
         it != end;
         ++it)
    {
      this->sfile_
        << "this->" << *it << "_.write (attrs);";
    }

    this->sfile_
      << "}";

    return 0;
  }

  //
  // visit_field
  //
  virtual int visit_field (AST_Field * node)
  {
    ACE_CString local_name (node->local_name ()->get_string ());
    this->attributes_.push_back (local_name);

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString & class_name_;
  std::vector <ACE_CString> attributes_;
};

/**
 * @class Event_ObjectClass_AttributeHandle
 *
 * Visitor that builds the private AttributeHandle members
 */
class Event_ObjectClass_AttributeHandle : public iCCM::Scope_Visitor
{
public:
  //
  // Event_ObjectClass_AttributeHandle
  //
  Event_ObjectClass_AttributeHandle (std::ofstream & hfile)
   : hfile_ (hfile)
  {

  }

  //
  // visit_eventtype
  //
  virtual int visit_eventtype (AST_EventType * node)
  {
    return this->visit_scope (node);
  }

  //
  // visit_field
  //
  virtual int visit_field (AST_Field * node)
  {
    AST_Type * field_type = node->field_type ();
    const char * local_name = node->local_name ()->get_string ();

    switch (field_type->node_type ())
    {
      case AST_Decl::NT_pre_defined:
        field_type->ast_accept (this);
        this->hfile_
          << local_name << "_;";
        break;
      case AST_Decl::NT_string:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <ACE_CString> " << local_name << "_;";
        break;
    }
    return 0;
  }

  //
  // visit_predefined_type
  //
  virtual int visit_predefined_type (AST_PredefinedType * node)
  {
    const char * param_type = node->full_name ();
    switch (node->pt ())
    {
      case AST_PredefinedType::PT_long:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <long> ";
        break;
      case AST_PredefinedType::PT_ulong:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <unsigned long> ";
        break;
      case AST_PredefinedType::PT_longlong:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <long long> ";
        break;
      case AST_PredefinedType::PT_ulonglong:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <unsigned long long> ";
        break;
      case AST_PredefinedType::PT_short:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <short> ";
        break;
      case AST_PredefinedType::PT_ushort:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <ushort> ";
        break;
      case AST_PredefinedType::PT_float:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <float> ";
        break;
      case AST_PredefinedType::PT_double:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <double> ";
        break;
      case AST_PredefinedType::PT_longdouble:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <long double> ";
        break;
      case AST_PredefinedType::PT_char:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <char> ";
        break;
      case AST_PredefinedType::PT_wchar:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <wchar> ";
        break;
      case AST_PredefinedType::PT_boolean:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <boolean> ";
        break;
      case AST_PredefinedType::PT_octet:
        this->hfile_
          << "::iCCM::Portico_AttributeHandle_T <octet> ";
        break;
    }

    return 0;
  }
private:
  std::ofstream & hfile_;
};

namespace iCCM
{

//
// Event_ObjectClass
//
Event_ObjectClass::Event_ObjectClass (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Event_ObjectClass
//
Event_ObjectClass::~Event_ObjectClass (void)
{

}

//
// visit_module
//
int Event_ObjectClass::visit_module (AST_Module * node)
{
  ACE_CString local_name (node->local_name ()->get_string ());
  ACE_CString backup (this->marshal_scope_);
  this->marshal_scope_ += local_name + "_";

  if (0 != this->visit_scope (node))
    return -1;

  this->marshal_scope_ = backup;
  return 0;
}

//
// visit_eventtype
//
int Event_ObjectClass::visit_eventtype (AST_EventType * node)
{
  const char * local_name = node->local_name ()->get_string ();
  this->event_objectclass_ = ACE_CString (local_name) + "_ObjectClass";

  // Define the class with constructor and destructor
  this->hfile_
    << "class ";

  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  this->hfile_
    << this->event_objectclass_ << " :" << std::endl
    << "  public ::iCCM::Portico_ObjectClass," << std::endl
    << "  public virtual " << local_name << "," << std::endl
    << "  public virtual ::CORBA::DefaultValueRefCountBase" << std::endl
    << "{"
    << "public:" << std::endl;

  Event_ObjectClass_Ctor ctor (this->hfile_, this->sfile_, this->event_objectclass_);
  node->ast_accept (&ctor);

  this->hfile_
    << "  virtual ~" << this->event_objectclass_ << " (void);" << std::endl;

  // Implement the destructor
  this->sfile_
    << this->event_objectclass_ << "::~" << this->event_objectclass_ << " (void)"
    << "{"
    << "}";

  Event_ObjectClass_HLA hla (this->hfile_, this->sfile_, this->event_objectclass_);
  node->ast_accept (&hla);

  // Generate CCM getters/setters
  this->visit_scope (node);

  this->hfile_
    << "private:" << std::endl
    << "  ::CORBA::Boolean _tao_marshal__" << this->marshal_scope_ << local_name << " (TAO_OutputCDR &, TAO_ChunkInfo &) const;"
    << "  ::CORBA::Boolean _tao_unmarshal__" << this->marshal_scope_ << local_name << " (TAO_InputCDR &, TAO_ChunkInfo &);" << std::endl;

  this->sfile_
    << "::CORBA::Boolean " << std::endl
    << this->event_objectclass_ << "::_tao_marshal__" << this->marshal_scope_ << local_name << " (TAO_OutputCDR &, TAO_ChunkInfo &) const{ return false; }"
    << "::CORBA::Boolean " << std::endl
    << this->event_objectclass_ << "::_tao_unmarshal__" << this->marshal_scope_ << local_name << " (TAO_InputCDR &, TAO_ChunkInfo &){ return false; }";

  Event_ObjectClass_AttributeHandle attribute (this->hfile_);
  node->ast_accept (&attribute);

  this->hfile_
    << "};";

  return 0;
}

//
// visit_field
//
int Event_ObjectClass::visit_field (AST_Field * node)
{
  AST_Type * field_type = node->field_type ();
  const char * local_name = node->local_name ()->get_string ();
  const char * param_type = field_type->full_name ();

  switch (field_type->node_type ())
  {
  case AST_Decl::NT_pre_defined:
    this->hfile_
      << "virtual void " << local_name << " (const ::" << param_type << ");"
      << "virtual " << param_type << " " << local_name << " (void) const;"
      << std::endl;

    this->sfile_
      << "void " << this->event_objectclass_ << "::"
      << local_name << " (const ::" << param_type << " val){"
      << "this->" << local_name << "_.value (val);"
      << "}"
      << param_type << " " << this->event_objectclass_ << "::"
      << local_name << " (void) const{"
      << "return this->" << local_name << "_.value ();"
      << "}";
    break;

  case AST_Decl::NT_enum:
    this->hfile_
      << "virtual void " << local_name << " (const ::" << param_type << ");"
      << "virtual " << param_type << " " << local_name << " (void) const;"
      << std::endl;

    this->sfile_
      << "void " << this->event_objectclass_ << "::"
      << local_name << " (const ::" << param_type << " val){"
      << "this->" << local_name << "_.value (val);"
      << "}"
      << param_type << " " << this->event_objectclass_ << "::"
      << local_name << " (void) const{"
      << "return this->" << local_name << "_.value ();"
      << "}";
    break;

  case AST_Decl::NT_string:
    this->hfile_
      << "virtual void " << local_name << " (" << param_type << ");"
      << "virtual void " << local_name << " (const " << param_type << ");"
      << "virtual void " << local_name << " (const ::CORBA::String_var &);"
      << "virtual const " << param_type << " " << local_name << " (void) const;"
      << std::endl;

    this->sfile_
      << "void " << this->event_objectclass_
      << "::" << local_name << " (" << param_type << " val){"
      << "this->" << local_name << "_.value (val);"
      << "}"
      << "void " << this->event_objectclass_
      << "::" << local_name << " (const " << param_type << " val){"
      << "this->" << local_name << "_.value (val);"
      << "}"
      << "void " << this->event_objectclass_
      << "::" << local_name << " (const ::CORBA::String_var & val){"
      << "this->" << local_name << "_.value (val.in ());"
      << "}"
      << "const " << param_type << " " << this->event_objectclass_
      << "::" << local_name << " (void) const {"
      << "return this->" << local_name << "_.value ().c_str ();"
      << "}";
    break;

  default:
    this->hfile_
      << "virtual void " << local_name << " (const ::" << param_type << " &);"
      << "virtual const " << param_type << " & " << local_name << " (void) const;"
      << "virtual " << param_type << " & " << local_name << " (void);"
      << std::endl;

    this->sfile_
      << "void " << this->event_objectclass_
      << "::" << local_name << " (const ::" << param_type << " & val){"
      << "this->" << local_name << "_.value (val);"
      << "}"
      << "const " << param_type << " & "
      << this->event_objectclass_ << "::" << local_name << " (void) const{"
      << "return this->" << local_name << "_.value ();"
      << "}"
      << param_type << " & " << this->event_objectclass_
      << "::" << local_name << " (void){"
      << "return this->" << local_name << ").value ();"
      << "}";
  }

  return 0;
}

}
