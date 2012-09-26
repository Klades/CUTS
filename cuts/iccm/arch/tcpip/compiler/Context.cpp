// $Id$

#include "Context.h"

#include "Stub_File.h"
#include "Push_Event_Visitor.h"
#include "BMI_Visitor.h"
#include "Servant_VTable_Visitor.h"

#include "ast_component.h"
#include "ast_module.h"
#include "ast_root.h"
#include "ast_sequence.h"
#include "ast_typedef.h"

#include "utl_identifier.h"
#include "utl_string.h"

#include "fe_extern.h"
#include "global_extern.h"
#include "nr_extern.h"
#include "idl_defines.h"

#include "ace/OS_NS_stdio.h"
#include "ace/streams.h"

#include <fstream>
#include <sstream>
#include <string>

namespace iCCM
{
namespace TCPIP
{

//
// Context
//
Context::Context (void)
{

}

//
// ~Context
//
Context::~Context (void)
{

}

//
// post_produce
//
void Context::post_produce (void)
{
  iCCM::Stub_File stub_file;
  idl_global->root ()->ast_accept (&stub_file);
}

//
// get_stub_file_prefix
//
const ACE_CString & Context::get_stub_file_prefix (void) const
{
  static const ACE_CString value ("TCPIP_");
  return value;
}

//
// get_context_template_header_filename
//
const ACE_CString & Context::
get_context_template_header_filename (void) const
{
  static const ACE_CString value ("cuts/iccm/servant/Context_T.h");
  return value;
}

//
// get_servant_template_header_filename
//
const ACE_CString & Context::
get_servant_template_header_filename (void) const
{
  static const ACE_CString value ("cuts/iccm/arch/tcpip/servant/TCPIP_Servant_T.h");
  return value;
}

//
// get_context_typename
//
const ACE_CString & Context::get_context_typename (void) const
{
  static const ACE_CString value ("iCCM::Context_T");
  return value;
}

//
// get_servant_template_typename
//
const ACE_CString & Context::get_servant_template_typename (void) const
{
  static const ACE_CString value ("iCCM::TCPIP_Servant_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & Context::get_publisher_template_typename (void) const
{
  static const ACE_CString value ("iCCM::TCPIP_Publisher_T");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_publisher_table_template_typename (void) const
{
  static const ACE_CString value ("iCCM::TCPIP_Publisher_Table_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & Context::get_publisher_typename (void) const
{
  static const ACE_CString value ("iCCM::TCPIP_Publisher");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_publisher_table_typename (void) const
{
  static const ACE_CString value ("iCCM::TCPIP_Publisher_Table");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_consumer_template_typename (void) const
{
  static const ACE_CString value ("iCCM::TCPIP_EventConsumer_T");
  return value;
}

//
// uses_default_bmi
//
bool Context::
uses_default_bmi (AST_Component * node) const
{
  return false;
}

//
// generate_custom_bmi
//
void Context::
generate_custom_bmi (AST_Component * node, std::ofstream & sfile) const
{
  BMI_Visitor bmi (sfile);
  bmi.visit_scope (node);
}

//
// uses_default_push_method
//
bool Context::
uses_default_push_method (AST_Component * node) const
{
  return false;
}

//
// generate_custom_push_method
//
void Context::
generate_custom_push_method (AST_Component * node,
                             std::ofstream & hfile,
                             std::ofstream & sfile,
                             const ACE_CString & servant) const
{
  Push_Event_Visitor pev (hfile, sfile, servant);
  pev.visit_scope (node);
}

//
// generate_constructor_postamble
//
void Context::
generate_constructor_postamble (AST_Component * node, std::ofstream & sfile) const
{
  sfile
   << std::endl
   << "// Guard the initialization of the virtual table." << std::endl
   << "vtable_type::init_guard_type guard (self_type::table_, 1);" << std::endl
   << "if (self_type::table_.is_init ())" << std::endl
   << "  return;" << std::endl;

  Servant_VTable_Visitor svv (sfile);
  svv.visit_scope (node);
}

}
}
