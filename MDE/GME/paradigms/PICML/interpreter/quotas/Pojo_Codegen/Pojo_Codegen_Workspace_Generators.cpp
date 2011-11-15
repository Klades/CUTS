// $Id$

#include "stdafx.h"
#include "Pojo_Codegen_Workspace_Generators.h"

#if !defined (__CUTS_INLINE__)
#include "Pojo_Codegen_Workspace_Generators.inl"
#endif

#include "be/BE_Options.h"
#include "be/BE_Impl_Node.h"
#include <sstream>

//
// CUTS_BE_Workspace_File_Open_T
//
void CUTS_BE_Workspace_File_Open_T <Quotas::Pojo::Codegen::Context>::
generate (const std::string & name)
{
  std::ostringstream filename;
  filename
    << CUTS_BE_OPTIONS ()->output_directory_
    << "/" << name << ".build";

  this->ctx_.workspace_file_.open (filename.str ().c_str ());

  if (!this->ctx_.workspace_file_.is_open ())
    return;

  // Create a formatter for the XML file.
  this->ctx_.workspace_formatter_.reset (
    new Quotas::Pojo::Codegen::Context::xml_formatter_type (this->ctx_.workspace_file_));
}

//
// CUTS_BE_Workspace_Begin_T
//
void CUTS_BE_Workspace_Begin_T <Quotas::Pojo::Codegen::Context>::generate (const std::string & name)
{
  this->ctx_.workspace_file_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<project name=\"" << name << ".build\" basedir=\".\" "
    << "default=\"build.all\">" << std::endl
    << std::endl
    << "<target name=\"build.all\" depends=\"build.impl\" />" << std::endl
    << std::endl
    << "<target name=\"build.impl\"";

  this->ctx_.workspace_file_
    << ">" << std::endl;
}

//
// CUTS_BE_Workspace_Project_Include_T
//
void CUTS_BE_Workspace_Project_Include_T <Quotas::Pojo::Codegen::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  std::string name (node.container_.name ());

  // Insert the ANT file for building the project.
  this->ctx_.workspace_file_
    << "<ant antfile=\"" << name << ".build\" dir=\".\" />" << std::endl;
}

//
// CUTS_BE_Workspace_End_T
//
void CUTS_BE_Workspace_End_T <Quotas::Pojo::Codegen::Context>::
generate (const std::string & name)
{
  // Force the generation of the project that will
  this->ctx_.workspace_file_
      << "</target>" << std::endl
    << "</project>" << std::endl
    << std::endl
    << "<!-- end of auto-generated file -->" << std::endl;
}

//
// CUTS_BE_Workspace_File_Close_T
//
void CUTS_BE_Workspace_File_Close_T <Quotas::Pojo::Codegen::Context>::generate (void)
{
  this->ctx_.workspace_formatter_.reset ();
  this->ctx_.workspace_file_.close ();
}
