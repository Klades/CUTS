// $Id$

#include "Context.h"

#include "Stub_File.h"
#include "DDL_File.h"

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
namespace CoreDX
{

//
// Context
//
Context::Context (void)
: generate_ddl_ (false),
  ddl_filename_ ()
{

}

//
// ~Context
//
Context::~Context (void)
{

}

void Context::prep_be_arg (char * s)
{
  base_type::prep_be_arg (s);

  static const char generate_ddl[] = "generate_ddl";

  char * last = 0;

  for (char * arg = ACE_OS::strtok_r (s, ",", &last);
       0 != arg;
       arg = ACE_OS::strtok_r (0, ",", &last))
  {
    if (ACE_OS::strstr (arg, generate_ddl) == arg)
    {
      // Only generate the DDL, avoid executors or servants
      this->generate_ddl_ = true;
      this->generate_lem_ = false;
      this->generate_svnt_ = false;
    }
  }
}

//
// post_produce
//
void Context::post_produce (void)
{
  if (this->generate_ddl_)
  {
    iCCM::DDL_File ddl_file;
    idl_global->root ()->ast_accept (&ddl_file);
  }
  else
  {
    iCCM::Stub_File stub_file;
    idl_global->root ()->ast_accept (&stub_file);
  }
}

const ACE_CString & Context::get_ddl_filename (void) const
{
  if (!this->ddl_filename_.empty ())
    return this->ddl_filename_;

  this->ddl_filename_ = "CoreDX_" + this->get_source_basename () + ".ddl";
  return this->ddl_filename_;
}

//
// get_stub_file_prefix
//
const ACE_CString & Context::get_stub_file_prefix (void) const
{
  static const ACE_CString value ("CoreDX_");
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
  static const ACE_CString value ("cuts/iccm/arch/coredx/servant/CoreDX_Servant_T.h");
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
  static const ACE_CString value ("iCCM::CoreDX_Servant_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & Context::get_publisher_template_typename (void) const
{
  static const ACE_CString value ("iCCM::CoreDX_Publisher_T");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_publisher_table_template_typename (void) const
{
  static const ACE_CString value ("iCCM::CoreDX_Publisher_Table_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & Context::get_publisher_typename (void) const
{
  static const ACE_CString value ("iCCM::CoreDX_Publisher");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_publisher_table_typename (void) const
{
  static const ACE_CString value ("iCCM::CoreDX_Publisher_Table");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_consumer_template_typename (void) const
{
  static const ACE_CString value ("iCCM::CoreDX_EventConsumer_T");
  return value;
}

}
}
