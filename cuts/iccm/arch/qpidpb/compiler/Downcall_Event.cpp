// $Id$

#include "Downcall_Event.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_eventtype.h"
#include "ast_field.h"
#include "ast_module.h"

#include "utl_identifier.h"
#include <iostream>

namespace iCCM
{

//
// Downcall_Event
//
Downcall_Event::Downcall_Event (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Downcall_Event
//
Downcall_Event::~Downcall_Event (void)
{

}

//
// visit_module
//
int Downcall_Event::visit_module (AST_Module * node)
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
int Downcall_Event::visit_eventtype (AST_EventType * node)
{
  if (!be_global->is_wrapper_eventtype (node))
    return 0;

  const char * local_name = node->local_name ()->get_string ();
  const char * full_name = node->full_name ();
  this->downcall_event_ = ACE_CString (local_name) + "Downcall";

  ACE_CString protobuf_event;
  be_global->get_wrapper_eventtype (node, protobuf_event);

  this->hfile_
    << "class ";

  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  this->hfile_
    << this->downcall_event_ << " :" << std::endl
    << "  public virtual " << local_name << "," << std::endl
    << "  public virtual ::CORBA::DefaultValueRefCountBase" << std::endl
    << "{"
    << "public:" << std::endl
    << this->downcall_event_ << " (void);"
    << "virtual ~" << this->downcall_event_ << " (void);"
    << std::endl
    << "const qpidpb::" << protobuf_event << " & protobuf_event (void) const;"
    << std::endl;

  this->sfile_
    << this->downcall_event_ << "::" << this->downcall_event_ << " (void)" << std::endl
    << "{"
    << "}"
    << this->downcall_event_ << "::~" << this->downcall_event_ << " (void)"
    << "{"
    << "}"
    << "const qpidpb::" << protobuf_event << " & " << this->downcall_event_ << "::"
    << "protobuf_event (void) const{"
    << "return this->protobuf_event_;"
    << "}";

  this->visit_scope (node);

  this->hfile_
    << "private:" << std::endl
    << "qpidpb::" << protobuf_event << " protobuf_event_;"
    << std::endl
    << "::CORBA::Boolean _tao_marshal__" << this->marshal_scope_ << local_name << " (TAO_OutputCDR &, TAO_ChunkInfo &) const;"
    << "::CORBA::Boolean _tao_unmarshal__" << this->marshal_scope_ << local_name << " (TAO_InputCDR &, TAO_ChunkInfo &);"
    << "};";

  this->sfile_
    << "::CORBA::Boolean " << this->downcall_event_
    << "::_tao_marshal__" << this->marshal_scope_ << local_name << " (TAO_OutputCDR &, TAO_ChunkInfo &) const{return false;}"
    << "::CORBA::Boolean " << this->downcall_event_
    << "::_tao_unmarshal__" << this->marshal_scope_ << local_name << " (TAO_InputCDR &, TAO_ChunkInfo &){return false;}";

  return 0;
}

//
// visit_attribute
//
int Downcall_Event::visit_field (AST_Field * node)
{
  AST_Type * field_type = node->field_type ();
  const char * local_name = node->local_name ()->get_string ();
  const char * param_type = field_type->full_name ();
  ACE_CString qpidpb_name = local_name;
  std::transform (qpidpb_name.begin (),
                  qpidpb_name.end (),
                  qpidpb_name.begin (),
                  &::tolower);

  switch (field_type->node_type ())
  {
  case AST_Decl::NT_pre_defined:
    this->hfile_
      << "virtual void " << local_name << " (const ::" << param_type << ");"
      << "virtual " << param_type << " " << local_name << " (void) const;"
      << std::endl;

    this->sfile_
      << "void " << this->downcall_event_ << "::"
      << local_name << " (const ::" << param_type << " val){"
      << "this->protobuf_event_.set_" << qpidpb_name << " (val);"
      << "}"
      << param_type << " " << this->downcall_event_ << "::"
      << local_name << " (void) const{"
      << "return this->protobuf_event_." << qpidpb_name << " ();"
      << "}";
    break;

  case AST_Decl::NT_enum:
    this->hfile_
      << "virtual void " << local_name << " (const ::" << param_type << ");"
      << "virtual " << param_type << " " << local_name << " (void) const;"
      << std::endl;

    this->sfile_
      << "void " << this->downcall_event_ << "::"
      << local_name << " (const ::" << param_type << " val){"
      << "this->protobuf_event_.set_" << qpidpb_name << " (val);"
      << "}"
      << param_type << " " << this->downcall_event_ << "::"
      << local_name << " (void) const{"
      << "return this->protobuf_event_." << qpidpb_name << " ();"
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
      << "void " << this->downcall_event_
      << "::" << local_name << " (" << param_type << " val){"
      << "this->protobuf_event_.set_" << qpidpb_name << " (val);"
      << "}"
      << "void " << this->downcall_event_
      << "::" << local_name << " (const " << param_type << " val){"
      << "this->protobuf_event_.set_" << qpidpb_name << " (CORBA::string_dup (val));"
      << "}"
      << "void " << this->downcall_event_
      << "::" << local_name << " (const ::CORBA::String_var & val){"
      << "::CORBA::String_var dup = val;"
      << "this->protobuf_event_.set_" << qpidpb_name << " (dup._retn ());"
      << "}"
      << "const " << param_type << " " << this->downcall_event_
      << "::" << local_name << " (void) const {"
      << "return this->protobuf_event_." << qpidpb_name << " ().c_str ();"
      << "}";
    break;

  default:
    this->hfile_
      << "virtual void " << local_name << " (const ::" << param_type << " &);"
      << "virtual const " << param_type << " & " << local_name << " (void) const;"
      << "virtual " << param_type << " & " << local_name << " (void);"
      << std::endl;

    this->sfile_
      << "void " << this->downcall_event_
      << "::" << local_name << " (const ::" << param_type << " & val){"
      << "this->protobuf_event_.set_" << qpidpb_name << " (val);"
      << "}"
      << "const " << param_type << " & "
      << this->downcall_event_ << "::" << local_name << " (void) const{"
      << "return this->protobuf_event_." << qpidpb_name << " ();"
      << "}"
      << param_type << " & " << this->downcall_event_
      << "::" << local_name << " (void){"
      << "return this->protobuf_event_." << qpidpb_name << " ();"
      << "}";
  }

  return 0;
}

}
