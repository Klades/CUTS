// $Id$

#include "CAPI_Workspace_Generators.h"
#include "../BE_Options.h"
#include "../BE_Impl_Node.h"
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
    << "<target name=\"build.all\" depends=\"build.impl\" />" << std::endl
    << std::endl
    << "<target name=\"build.impl\" depends=\"build.events\">" << std::endl;

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
  // Force the generation of the project that will
  CUTS_BE_CAPI ()->workspace_file_
    << "</target>" << std::endl
    << std::endl
    << "<target name=\"build.events\">" << std::endl;

  CUTS_BE_Workspace_End_T <CUTS_BE_Capi>::generate_eventtypes_project ();

  CUTS_BE_CAPI ()->workspace_file_
    << "</target>" << std::endl
    << "</project>" << std::endl
    << std::endl
    << "<!-- end of auto-generated file -->" << std::endl;

  return true;
}

//
// CUTS_BE_Workspace_End_T::generate_eventtypes_project
//
void CUTS_BE_Workspace_End_T <CUTS_BE_Capi>::
generate_eventtypes_project (void)
{
  if (CUTS_BE_CAPI ()->workspace_events_.empty ())
    return;

  // Construct the name of the build file for events.
  std::ostringstream filename;
  filename
    << CUTS_BE_OPTIONS ()->output_directory_
    << "/" << "jbi.eventtypes.build";

  // Open the file for writing.
  std::ofstream outfile;
  outfile.open (filename.str ().c_str ());

  if (!outfile.is_open ())
    return;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::XML, char> formatter_type;

  /// Pointer to the formatter.
  formatter_type formatter (outfile);

  // Write the preamble to the log file.
  outfile
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<project name=\"jbi.eventtypes.build\" basedir=\".\" default=\"build.all\">" << std::endl
    << "<property environment=\"env\" />" << std::endl
    << "<property name=\"jbi.schemas.dir\" value=\".\" />" << std::endl
    << std::endl
    << "<!-- import necessary external files -->" << std::endl
    << "<import file=\"${env.CUTS_ROOT}/etc/ANT/include/cuts.build\" />" << std::endl
    << "<import file=\"${env.CUTS_ROOT}/etc/ANT/include/castor.build\" />" << std::endl
    << std::endl
    << "<!-- build all the implementations -->" << std::endl
    << "<target name=\"build.all\" depends=\"eventtypes.jar.build\" />" << std::endl;

  // Generate the predetermined targets.
  generate_target_eventtypes_srcgen (outfile);
  generate_target_eventtypes_build (outfile);
  generate_target_eventtypes_jar_build (outfile);

  // Write the postamble for the project.
  outfile
    << "</project>" << std::endl
    << std::endl
    << "<!-- end of auto generated file -->" << std::endl
    << std::endl;

  // Close the opened file.
  outfile.close ();

  // Place the jbi.eventtype.build file in the top-level ANT script.
  CUTS_BE_CAPI ()->workspace_file_
    << "<ant antfile=\"jbi.eventtypes.build\" dir=\".\" />" << std::endl;
}

//
// CUTS_BE_Workspace_End_T::generate_target_eventtypes_srcgen
//
void CUTS_BE_Workspace_End_T <CUTS_BE_Capi>::
generate_target_eventtypes_srcgen (std::ofstream & outfile)
{
  std::set <PICML::Event>::const_iterator
    iter = CUTS_BE_CAPI ()->workspace_events_.begin (),
    iter_end = CUTS_BE_CAPI ()->workspace_events_.end ();

  std::string pathname, scope_name;

  outfile
    << std::endl
    << "<target name=\"eventtypes.srcgen\">";

  for ( ; iter != iter_end; ++ iter)
  {
    pathname = CUTS_BE_CAPI ()->fq_name (*iter, '/');
    scope_name = CUTS_BE_CAPI ()->fq_name (*iter, '.');

    outfile
      << std::endl
      << "<!-- eventtype : " << scope_name << ".xsd -->" << std::endl
      << "<delete includeemptydirs=\"true\" verbose=\"true\">" << std::endl
      << "<fileset dir=\".\">" << std::endl
      << "<include name=\"" << pathname << "/*.java\" />" << std::endl
      << "<include name=\"" << pathname << "/*.class\" />" << std::endl
      << "<exclude name=\"" << pathname << "/*Impl.java\" />" << std::endl
      << "</fileset>" << std::endl
      << "</delete>" << std::endl
      << std::endl
      << "<java" << std::endl
      << "classname=\"org.exolab.castor.builder.SourceGeneratorMain\"" << std::endl
      << "classpathref=\"castor.srcgen.classpath\"" << std::endl
      << "failonerror=\"true\">" << std::endl
      << "<arg line=\"-i ${jbi.schemas.dir}/" << pathname
      << "/" << scope_name << ".xsd\" />" << std::endl
      << "<arg line=\"-package " << scope_name << "\" />" << std::endl
      << "<arg line=\"-f -nodesc -nomarshall\" />" << std::endl
      << "</java>" << std::endl;
  }

  outfile
    << "</target>" << std::endl;

}

//
// CUTS_BE_Workspace_End_T::generate_target_eventtypes_build
//
void CUTS_BE_Workspace_End_T <CUTS_BE_Capi>::
generate_target_eventtypes_build (std::ofstream & outfile)
{
  std::set <PICML::Event>::const_iterator
    iter = CUTS_BE_CAPI ()->workspace_events_.begin (),
    iter_end = CUTS_BE_CAPI ()->workspace_events_.end ();

  std::string pathname;

  outfile
    << std::endl
    << "<target name=\"eventtypes.build\" depends=\"eventtypes.srcgen\">" << std::endl
    << "<javac srcdir=\".\" classpathref=\"cuts.build.classpath\">" << std::endl;

  for ( ; iter != iter_end; ++ iter)
  {
    pathname = CUTS_BE_CAPI ()->fq_name (*iter, '/');

    outfile
      << "<include name=\"" << pathname << "/*.java\" />";
  }

  outfile
    << "</javac>" << std::endl
    << "</target>" << std::endl;
}

//
// CUTS_BE_Workspace_End_T::generate_target_eventtypes_jar_build
//
void CUTS_BE_Workspace_End_T <CUTS_BE_Capi>::
generate_target_eventtypes_jar_build (std::ofstream & outfile)
{
  std::set <PICML::Event>::const_iterator
    iter = CUTS_BE_CAPI ()->workspace_events_.begin (),
    iter_end = CUTS_BE_CAPI ()->workspace_events_.end ();

  std::string pathname, scope_name;

  outfile
    << std::endl
    << "<target name=\"eventtypes.jar.build\" depends=\"eventtypes.build\">" << std::endl
    << "<!-- create the library directory -->" << std::endl
    << "<mkdir dir=\"./lib\" />" << std::endl
    << std::endl
    << "<!-- create the final jar file -->" << std::endl
    << "<jar destfile=\"./lib/jbi.eventtypes.jar\" basedir=\".\">";

  for ( ; iter != iter_end; ++ iter)
  {
    pathname = CUTS_BE_CAPI ()->fq_name (*iter, '/');
    scope_name = CUTS_BE_CAPI ()->fq_name (*iter, '.');

    outfile
      << std::endl
      << "<include name=\"" << pathname << "/*.class\" />" << std::endl
      << "<include name=\"" << pathname << "/mapping.xml\" />" << std::endl;
  }

  outfile
    << "</jar>" << std::endl
    << "</target>" << std::endl;
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
