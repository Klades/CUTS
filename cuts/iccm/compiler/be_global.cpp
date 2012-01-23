// $Id$

#include "be_global.h"
#include "be_extern.h"

#include "ast_generator.h"
#include "ast_module.h"
#include "ast_component.h"
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

//
// be_global
//
BE_GlobalData * be_global = 0;

//
// BE_GlobalData
//
BE_GlobalData::BE_GlobalData (void)
: output_path_ ("."),
  executor_idl_suffix_ ("_iCCM.idl"),
  dds2ccm_event_suffix_ ("Event")
{

}

//
// ~BE_GlobalData
//
BE_GlobalData::~BE_GlobalData (void)
{
}

//
// spawn_options
//
ACE_CString BE_GlobalData::spawn_options (void)
{
  return idl_global->idl_flags ();
}

//
// parse_args
//
void BE_GlobalData::parse_args (long &i, char **av)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("parse_args ()\n")));

  switch (av[i][1])
  {
  case 'o':
    this->output_path_ = av[i + 1];
    ++i;

    break;

  default:
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s option is unknown\n"),
                av[i]));

    idl_global->set_compile_flags (idl_global->compile_flags () | IDL_CF_ONLY_USAGE);
  }
}

//
// destroy
//
void BE_GlobalData::destroy (void)
{

}

//
// calculate_target_filename
//
const ACE_CString & BE_GlobalData::
get_target_executor_idl_filename (void) const
{
  if (!this->target_executor_idl_file_.empty ())
    return this->target_executor_idl_file_;

  ACE_CString filename, basename;
  BE_GlobalData::get_filename (this->source_file_, filename);
  BE_GlobalData::get_basename (filename, basename);

  this->target_executor_idl_file_ =
    this->output_path_ + '/' + basename + this->executor_idl_suffix_;

  return this->target_executor_idl_file_;
}

//
// get_basename
//
void BE_GlobalData::
get_basename (const ACE_CString & filename, ACE_CString & basename)
{
  size_t pos = filename.rfind ('.');
  basename = pos == ACE_CString::npos ? filename : filename.substring (0, pos);
}

//
// get_filename
//
void BE_GlobalData::
get_filename (const ACE_CString & pathname, ACE_CString & filename)
{
  // Normalize the path name.
  ACE_CString dup_pathname (pathname);
  std::replace (dup_pathname.begin (), dup_pathname.end (), '\\', '/');

  // Extract the filename of the pathname.
  size_t pos = dup_pathname.rfind ('/');
  filename = pos == ACE_CString::npos ? dup_pathname : dup_pathname.substring (pos + 1);
}

//
// normalize
//
void BE_GlobalData::normalize (const ACE_CString & value, ACE_CString & result)
{
  static const std::string tokens (". ");
  static const size_t count = tokens.length ();

  result = value;

  for (size_t i = 0; i < count; ++ i)
    std::replace (result.begin (), result.end (), tokens[i], '_');
}

//
// get_source_filename
//
const ACE_CString & BE_GlobalData::get_source_filename (void) const
{
  if (!this->source_filename_.empty ())
    return this->source_filename_;

  BE_GlobalData::get_filename (this->source_file_, this->source_filename_);
  return this->source_filename_;
}

//
// get_source_basename
//
const ACE_CString & BE_GlobalData::get_source_basename (void) const
{
  if (!this->source_basename_.empty ())
    return this->source_basename_;

  BE_GlobalData::get_basename (this->get_source_filename (), this->source_basename_);
  return this->source_basename_;
}

//
// get_stub_header_filename
//
const ACE_CString & BE_GlobalData::get_stub_header_filename (void) const
{
  if (!this->stub_header_filename_.empty ())
    return this->stub_header_filename_;

  this->stub_header_filename_ = "OpenSplice_" + this->get_source_basename () + "C.h";
  return this->stub_header_filename_;
}

//
// get_stub_source_filename
//
const ACE_CString & BE_GlobalData::get_stub_source_filename (void) const
{
  if (!this->stub_source_filename_.empty ())
    return this->stub_source_filename_;

  this->stub_source_filename_ = "OpenSplice_" + this->get_source_basename () + "C.cpp";
  return this->stub_source_filename_;
}

//
// get_svnt_header_filename
//
const ACE_CString & BE_GlobalData::get_svnt_header_filename (void) const
{
  if (!this->svnt_header_filename_.empty ())
    return this->svnt_header_filename_;

  this->svnt_header_filename_ = this->get_source_basename () + "_svnt.h";
  return this->svnt_header_filename_;
}

//
// get_svnt_source_filename
//
const ACE_CString & BE_GlobalData::get_svnt_source_filename (void) const
{
  if (!this->svnt_source_filename_.empty ())
    return this->svnt_source_filename_;

  this->svnt_source_filename_ = this->get_source_basename () + "_svnt.cpp";
  return this->svnt_source_filename_;
}

//
// get_event_mapping_header_filename
//
const ACE_CString & BE_GlobalData::
get_event_mapping_header_filename (void) const
{
  if (!this->event_mapping_header_filename_.empty ())
    return this->event_mapping_header_filename_;

  this->event_mapping_header_filename_ =
    "OpenSplice_" + this->get_source_basename () + "C.h";

  return this->event_mapping_header_filename_;
}

//
// get_event_mapping_source_filename
//
const ACE_CString & BE_GlobalData::
get_event_mapping_source_filename (void) const
{
  if (!this->event_mapping_source_filename_.empty ())
    return this->event_mapping_source_filename_;

  this->event_mapping_source_filename_ =
    "OpenSplice_" + this->get_source_basename () + "C.cpp";

  return this->event_mapping_source_filename_;

}

//
// get_context_template_header_filename
//
const ACE_CString & BE_GlobalData::
get_context_template_header_filename (void) const
{
  static const ACE_CString value ("cuts/iccm/servant/Context_T.h");
  return value;
}

//
// get_servant_template_header_filename
//
const ACE_CString & BE_GlobalData::
get_servant_template_header_filename (void) const
{
  static const ACE_CString value ("cuts/iccm/arch/opensplice/servant/OpenSplice_Servant_T.h");
  return value;
}

//
// get_context_typename
//
const ACE_CString & BE_GlobalData::get_context_typename (void) const
{
  static const ACE_CString value ("iCCM::Context_T");
  return value;
}

//
// get_servant_template_typename
//
const ACE_CString & BE_GlobalData::get_servant_template_typename (void) const
{
  static const ACE_CString value ("iCCM::OpenSplice_Servant_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & BE_GlobalData::get_publisher_template_typename (void) const
{
  static const ACE_CString value ("iCCM::OpenSplice_Publisher_T");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & BE_GlobalData::
get_publisher_table_template_typename (void) const
{
  static const ACE_CString value ("iCCM::OpenSplice_Publisher_Table_T");
  return value;
}

//
// get_publisher_template_typename
//
const ACE_CString & BE_GlobalData::get_publisher_typename (void) const
{
  static const ACE_CString value ("iCCM::OpenSplice_Publisher");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & BE_GlobalData::
get_publisher_table_typename (void) const
{
  static const ACE_CString value ("iCCM::OpenSplice_Publisher_Table");
  return value;
}

//
// get_publisher_table_template_typename
//
const ACE_CString & BE_GlobalData::
get_consumer_template_typename (void) const
{
  static const ACE_CString value ("iCCM::OpenSplice_EventConsumer_T");
  return value;
}

//
// is_dds_eventtype
//
bool BE_GlobalData::is_dds_eventtype (AST_EventType * node) const
{
  const ACE_CString local_name (node->local_name ()->get_string ());
  const size_t index = local_name.strstr (this->dds2ccm_event_suffix_);

  return local_name.length () - index == this->dds2ccm_event_suffix_.length ();
}

//
// get_dds_eventtype
//
bool BE_GlobalData::
get_dds_eventtype (AST_EventType * node, ACE_CString & type) const
{
  const ACE_CString local_name (node->local_name ()->get_string ());
  const size_t index = local_name.strstr (this->dds2ccm_event_suffix_);

  if (index == ACE_CString::npos)
    return false;

  type = local_name.substring (0, index);
  return true;

}
