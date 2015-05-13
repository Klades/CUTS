// $Id$

#include "Context.h"

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
namespace CHAOS
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

}

//
// get_stub_file_prefix
//
const ACE_CString & Context::get_stub_file_prefix (void) const
{
  static const ACE_CString value ("CHAOS_");
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
  static const ACE_CString value ("cuts/iccm/arch/chaos/servant/CHAOS_Servant_T.h");
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
  static const ACE_CString value ("iCCM::CHAOS_Servant_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & Context::get_publisher_template_typename (void) const
{
  static const ACE_CString value ("iCCM::CHAOS_Publisher_T");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_publisher_table_template_typename (void) const
{
  static const ACE_CString value ("iCCM::CHAOS_Publisher_Table_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & Context::get_publisher_typename (void) const
{
  static const ACE_CString value ("iCCM::CHAOS_Publisher");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & Context::
get_publisher_table_typename (void) const
{
  static const ACE_CString value ("iCCM::CHAOS_Publisher_Table");
  return value;
}

//
// get_consumer_template_typename
//
const ACE_CString & Context::
get_consumer_template_typename (void) const
{
  static const ACE_CString value ("iCCM::CHAOS_EventConsumer_T");
  return value;
}

}
}
