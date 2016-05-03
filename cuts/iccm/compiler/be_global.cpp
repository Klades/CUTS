// $Id$

#include "be_global.h"
#include "idl_defines.h"

#include "ast_generator.h"
#include "ast_module.h"
#include "ast_component.h"
#include "ast_sequence.h"
#include "ast_typedef.h"

#include "utl_identifier.h"
#include "utl_string.h"

#include "ace/OS_NS_stdio.h"
#include "ace/streams.h"

#include <fstream>
#include <sstream>
#include <string>

BE_GlobalData * be_global = 0;

//
// BE_GlobalData
//
BE_GlobalData::BE_GlobalData (void)
: output_path_ ("."),
  executor_idl_suffix_ ("_iCCM.idl"),
  wrapper_event_suffix_ ("Event"),
  generate_lem_ (false),
  generate_svnt_ (false),
  requires_event_stub_ (true),
  has_impl_namespace_ (false)
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
  switch (av[i][1])
  {
  case 'o':
    this->output_path_ = av[i + 1];
    ++i;
    break;

  case 'G':
    {
      const char * arg = av[i] + 2;

      if (0 == ACE_OS::strcmp (arg, "lem"))
        this->generate_lem_ = true;
      else if (0 == ACE_OS::strcmp (arg, "sv"))
        this->generate_svnt_ = true;
    }
    break;

  default:
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s option is unknown\n"),
                av[i]));

    idl_global->set_compile_flags (idl_global->compile_flags () | IDL_CF_ONLY_USAGE);
  }
}

//
// prep_be_arg
//
void BE_GlobalData::prep_be_arg (char * s)
{
  static const char stub_export_macro[] = "stub_export_macro=";
  static const char stub_export_include[] = "stub_export_include=";
  static const char svnt_export_macro[] = "svnt_export_macro=";
  static const char svnt_export_include[] = "svnt_export_include=";

  char* last = 0;

  for (char * arg = ACE_OS::strtok_r (s, ",", &last);
       0 != arg;
       arg = ACE_OS::strtok_r (0, ",", &last))
  {
    if (ACE_OS::strstr (arg, stub_export_macro) == arg)
    {
      char * val = arg + sizeof (stub_export_macro) - 1;
      be_global->stub_export_macro_ = val;
    }
    else if (ACE_OS::strstr (arg, stub_export_include) == arg)
    {
      char * val = arg + sizeof (stub_export_include) - 1;
      be_global->stub_export_macro_filename_ = val;
    }
    else if (ACE_OS::strstr (arg, svnt_export_macro) == arg)
    {
      char * val = arg + sizeof (svnt_export_macro) - 1;
      be_global->svnt_export_macro_ = val;
    }
    else if (ACE_OS::strstr (arg, svnt_export_include) == arg)
    {
      char * val = arg + sizeof (svnt_export_include) - 1;
      be_global->svnt_export_macro_filename_ = val;
    }
  }
}

//
// print_usage
//
void BE_GlobalData::print_usage (void)
{

}

//
// arg_post_proc
//
void BE_GlobalData::arg_post_proc (void)
{

}

//
// post_produce
//
void BE_GlobalData::post_produce (void)
{

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

  this->stub_header_filename_ = this->get_stub_file_prefix () + this->get_source_basename () + "C.h";
  return this->stub_header_filename_;
}

//
// get_stub_source_filename
//
const ACE_CString & BE_GlobalData::get_stub_source_filename (void) const
{
  if (!this->stub_source_filename_.empty ())
    return this->stub_source_filename_;

  this->stub_source_filename_ = this->get_stub_file_prefix () + this->get_source_basename () + "C.cpp";
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
    this->get_stub_file_prefix () + this->get_source_basename () + "C.h";

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
    this->get_stub_file_prefix () + this->get_source_basename () + "C.cpp";

  return this->event_mapping_source_filename_;

}

//
// is_dds_eventtype
//
bool BE_GlobalData::
is_wrapper_eventtype (AST_EventType * node) const
{
  const ACE_CString local_name (node->local_name ()->get_string ());
  const size_t index = local_name.strstr (this->wrapper_event_suffix_);

  return local_name.length () - index == this->wrapper_event_suffix_.length ();
}

//
// get_dds_eventtype
//
bool BE_GlobalData::
get_wrapper_eventtype (AST_EventType * node, ACE_CString & type) const
{
  const ACE_CString local_name (node->local_name ()->get_string ());
  const size_t index = local_name.strstr (this->wrapper_event_suffix_);

  if (index == ACE_CString::npos)
    return false;

  type = local_name.substring (0, index);
  return true;
}

//
// uses_default_bmi
//
bool BE_GlobalData::
uses_default_bmi (AST_Component * node) const
{
  return true;
}

//
// generate_custom_bmi
//
void BE_GlobalData::
generate_custom_bmi (AST_Component * node, std::ofstream & sfile) const
{

}

//
// uses_default_push_method
//
bool BE_GlobalData::
uses_default_push_method (AST_Component * node) const
{
  return true;
}

//
// generate_custom_push_method
//
void BE_GlobalData::
generate_custom_push_method (AST_Component * node,
                             std::ofstream & hfile,
                             std::ofstream & sfile,
                             const ACE_CString & servant) const
{

}

//
// generate_constructor_preamble
//
void BE_GlobalData::
generate_constructor_preamble (AST_Component * node, std::ofstream & sfile) const
{

}

//
// generate_constructor_postamble
//
void BE_GlobalData::
generate_constructor_postamble (AST_Component * node, std::ofstream & sfile) const
{

}

//
// generate_class_preamble
//
void BE_GlobalData::
generate_class_preamble (AST_Component * node,
                         std::ofstream & hfile,
                         std::ofstream & sfile,
                         const ACE_CString & servant) const
{

}

//
// generate_class_postamble
//
void BE_GlobalData::
generate_class_postamble (AST_Component * node,
                          std::ofstream & hfile,
                          std::ofstream & sfile,
                          const ACE_CString & servant) const
{

}

bool BE_GlobalData::has_impl_namespace (void) const
{
  return this->has_impl_namespace_;
}

const std::string & BE_GlobalData::impl_namespace (void) const
{
  return this->impl_namespace_;
}
