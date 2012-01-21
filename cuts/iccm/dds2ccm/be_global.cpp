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
  suffix_ ("_events.idl")
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
const ACE_CString & BE_GlobalData::get_target_filename (void) const
{
  if (!this->target_filename_.empty ())
    return this->target_filename_;

  this->target_filename_ =
    this->output_path_ + '/' +
    this->get_target_basename ();

  return this->target_filename_;
}

//
// get_target_basename
//
const ACE_CString & BE_GlobalData::get_target_basename (void) const
{
  if (!this->target_basename_.empty ())
    return this->target_basename_;

  // Normalize the source file name.
  ACE_CString dup_src_file (this->source_file_);
  std::replace (dup_src_file.begin (), dup_src_file.end (), '\\', '/');

  // Extract the basename of the source file. This include removing
  // the path from the source file, and removing its extension.
  size_t pos = dup_src_file.rfind ('/');
  ACE_CString filename;
  BE_GlobalData::get_filename (dup_src_file, filename);

  pos = filename.rfind ('.');
  this->target_basename_ = pos == ACE_CString::npos ? filename : filename.substring (0, pos);
  this->target_basename_ += this->suffix_;

  return this->target_basename_;
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
ACE_CString & BE_GlobalData::normalize (ACE_CString & string_value)
{
  static const std::string tokens (". ");
  static const size_t count = tokens.length ();

  for (size_t i = 0; i < count; ++ i)
    std::replace (string_value.begin (), string_value.end (), tokens[i], '_');

  return string_value;
}


