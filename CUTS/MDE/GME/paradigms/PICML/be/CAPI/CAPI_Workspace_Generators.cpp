// $Id$

#include "CAPI_Workspace_Generators.h"
#include "be/BE_Options.h"
#include "be/BE_Impl_Node.h"
#include <sstream>

//
// CUTS_BE_Workspace_File_Open_T
//
bool CUTS_BE_Workspace_File_Open_T <CUTS_BE_Capi>::
generate (const std::string & name)
{
  std::ostringstream filename;
  filename 
    << CUTS_BE_OPTIONS ()->output_directory_ 
    << "/" << name << ".build";

  CUTS_BE_CAPI ()->workspace_file_.open (filename.str ().c_str ());

  if (!CUTS_BE_CAPI ()->workspace_file_.is_open ())
    return false;

  // Create a formatter for the XML file.
  CUTS_BE_CAPI ()->workspace_formatter_.reset (
    new CUTS_BE_Capi::_project_formatter_type (
    CUTS_BE_CAPI ()->workspace_file_));

  return true;
}

//
// CUTS_BE_Workspace_Begin_T
//
bool CUTS_BE_Workspace_Begin_T <CUTS_BE_Capi>::
generate (const std::string & name)
{
  CUTS_BE_CAPI ()->workspace_file_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<project name=\"" << name << ".build\" basedir=\".\" "
    << "default=\"build.all\">" << std::endl
    << std::endl
    << "<target name=\"build.all\">" << std::endl;

  return true;
}

//
// CUTS_BE_Workspace_Project_Include_T
//
bool CUTS_BE_Workspace_Project_Include_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  std::string name (node.container_.name ());

  // Insert the ANT file for building the project.
  CUTS_BE_CAPI ()->workspace_file_
    << "<ant antfile=\"" << name << ".build\" dir=\".\" />" << std::endl;

  return true;
}

//
// CUTS_BE_Workspace_End_T
//
bool CUTS_BE_Workspace_End_T <CUTS_BE_Capi>::
generate (const std::string & name)
{
  CUTS_BE_CAPI ()->workspace_file_
    << "</target>" << std::endl
    << "</project>" << std::endl
    << std::endl
    << "<!-- end of auto-generated file -->" << std::endl;

  return true;
}

//
// CUTS_BE_Workspace_File_Close_T
//
void CUTS_BE_Workspace_File_Close_T <CUTS_BE_Capi>::generate (void)
{
  if (CUTS_BE_CAPI ()->workspace_file_.is_open ())
  {
    CUTS_BE_CAPI ()->workspace_formatter_.reset ();
    CUTS_BE_CAPI ()->workspace_file_.close ();
  }
}
