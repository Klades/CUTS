// $Id$

#include "CAPI_Project_Generators.h"
#include "be/BE_Impl_Node.h"
#include "be/BE_Options.h"
#include "boost/bind.hpp"
#include <algorithm>
#include <sstream>

//
// CUTS_BE_Project_File_Open_T
//
bool CUTS_BE_Project_File_Open_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  std::ostringstream pathname;
  pathname
    << CUTS_BE_OPTIONS ()->output_directory_
    << "/" << node.name_ << ".build";

  CUTS_BE_CAPI ()->project_file_.open (pathname.str ().c_str ());

  if (!CUTS_BE_CAPI ()->project_file_.is_open ())
    return false;

  // Create a formatter for the XML file.
  CUTS_BE_CAPI ()->project_formatter_.reset (
    new CUTS_BE_Capi::_project_formatter_type (
    CUTS_BE_CAPI ()->project_file_));

  return true;
}

//
// CUTS_BE_Project_File_Begin_T
//
bool CUTS_BE_Project_File_Begin_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  // Save the current implementation's node. This is bad, but it's
  // the way we are going to do it for now.
  CUTS_BE_CAPI ()->impl_node_ =
    const_cast <CUTS_BE_Impl_Node *> (&node);

  // Get the name of the container for later usage.
  std::string name = node.container_.name ();

  CUTS_BE_CAPI ()->project_file_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<project name=\"cuts.capi.client." << name << "\" basedir=\".\" "
    << "default=\"build.all\">" << std::endl
    << "<property environment=\"env\" />" << std::endl
    << std::endl
    << "<!-- import necessary external files -->" << std::endl
    << "<import file=\"${env.CUTS_ROOT}/etc/ANT/include/cuts.build\" />" << std::endl;

  // If we have any events in this implementation, then we need to
  // include the build file for using Castor within CUTS and ANT.
  if (!CUTS_BE_CAPI ()->impl_node_->maplist_["events"].empty ())
  {
    CUTS_BE_CAPI ()->project_file_
      << "<import file=\"${env.CUTS_ROOT}/etc/ANT/include/castor.build\" />" << std::endl
      << std::endl;
  }

  // Get all the monolithic implementations defined in this container.
  // We need to specify each one in the "build.all" target.
  typedef
    std::vector <PICML::MonolithicImplementation>
    MonolithicImplementation_Set;

  MonolithicImplementation_Set monoimpls =
    node.container_.MonolithicImplementation_kind_children ();

  CUTS_BE_CAPI ()->project_file_
    << std::endl
    << "<!-- build all the implementations -->" << std::endl
    << "<target name=\"build.all\" depends=\"";

  // Write the depends statement for the target, which is
  // all the monolithic task defined in this monolithic impl.
  if (!monoimpls.empty ())
  {
    MonolithicImplementation_Set::iterator
      iter = monoimpls.begin (), iter_end = monoimpls.end ();

    CUTS_BE_CAPI ()->project_file_
      << iter->name () << ".jar.build";

    for (++ iter; iter != iter_end; ++ iter)
    {
      CUTS_BE_CAPI ()->project_file_
        << " " << iter->name () << ".jar.build";
    }
  }

  CUTS_BE_CAPI ()->project_file_
    << "\" />" << std::endl;

  return true;
}

//
// CUTS_BE_Project_Write_T
//
bool CUTS_BE_Project_Write_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  // Get all the monolithic implementations defined in this container.
  // We need to specify each one in the "build.all" target.
  typedef
    std::vector <PICML::MonolithicImplementation>
    MonolithicImplementation_Set;

  MonolithicImplementation_Set monoimpls =
    node.container_.MonolithicImplementation_kind_children ();

  // Generate build scripts for each of the implemenations.
  std::for_each (monoimpls.begin (),
                 monoimpls.end (),
                 boost::bind (&CUTS_BE_Project_Write_T <
                                CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate_i,
                              _1));
  return true;
}

//
// CUTS_BE_Project_Write_T::generate_i
//
void CUTS_BE_Project_Write_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::
generate_i (const PICML::MonolithicImplementation & monoimpl)
{
  std::string name = monoimpl.name ();

  const CUTS_String_Set & eventset =
    CUTS_BE_CAPI ()->impl_node_->maplist_["events"];

  const CUTS_String_Set & classpath =
    CUTS_BE_CAPI ()->impl_node_->maplist_["classpath"];

  CUTS_BE_CAPI ()->project_file_
    << std::endl
    << "<target name=\"" << name << ".build\">" << std::endl
    << "<javac srcdir=\".\" classpathref=\"cuts.build.classpath\">" << std::endl;

  if (!classpath.empty ())
  {
    CUTS_BE_CAPI ()->project_file_
      << "<classpath>" << std::endl;

    CUTS_String_Set::const_iterator 
      iter = classpath.begin (), iter_end = classpath.end ();

    for (; iter != iter_end; ++ iter)
    {
      CUTS_BE_CAPI ()->project_file_
        << "<pathelement location=\"" << *iter << "\" />" << std::endl;
    }

    CUTS_BE_CAPI ()->project_file_
      << "</classpath>" << std::endl;
  }
  
  CUTS_BE_CAPI ()->project_file_
    << std::endl
    << "<!-- main class file (contains child classes) -->" << std::endl
    << "<include name=\"" << name << ".java\" />" << std::endl
    << "</javac>" << std::endl
    << "</target>" << std::endl
    << std::endl
    << "<target name=\"" << name << ".jar.build\" "
    << "depends=\"" << name << ".build\">" << std::endl
    << "<!-- create the library directory -->" << std::endl
    << "<mkdir dir=\"./lib\" />" << std::endl
    << std::endl
    << "<!-- create the final jar file -->" << std::endl
    << "<jar destfile=\"./lib/" << name << ".jar\" basedir=\".\">" << std::endl
    << std::endl
    << "<!-- main class -->" << std::endl
    << "<include name=\"" << name << ".class\" />" << std::endl
    << std::endl
    << "<!-- private child classes -->" << std::endl
    << "<include name=\"" << name << "$*.class\" />" << std::endl
    << "</jar>" << std::endl
    << "</target>" << std::endl;
}

//
// CUTS_BE_Project_Write_T::generate_i
//
void CUTS_BE_Project_Write_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate_target_events_srcgen (void)
{
  CUTS_BE_CAPI ()->project_file_
    << std::endl
    << "<target name=\"events.srcgen\">";

  const CUTS_String_Set & eventset =
    CUTS_BE_CAPI ()->impl_node_->maplist_["events"];

  std::string path;

  CUTS_String_Set::const_iterator
    iter = eventset.begin (), iter_end = eventset.end ();

  for ( ; iter != iter_end; ++ iter)
  {
    path = *iter;
    std::replace (path.begin (), path.end (), '.', '/');

    CUTS_BE_CAPI ()->project_file_
      << std::endl
      << "<!-- eventtype : " << *iter << ".xsd -->" << std::endl
      << "<delete includeemptydirs=\"true\" verbose=\"true\">" << std::endl
      << "<fileset dir=\".\">" << std::endl
      << "<include name=\"" << path << "/*.java\" />" << std::endl
      << "<include name=\"" << path << "/*.class\" />" << std::endl
      << "</fileset>" << std::endl
      << "</delete>" << std::endl
      << std::endl
      << "<java" << std::endl
      << "classname=\"org.exolab.castor.builder.SourceGeneratorMain\"" << std::endl
      << "classpathref=\"castor.srcgen.classpath\"" << std::endl
      << "failonerror=\"true\">" << std::endl
      << "<arg line=\"-i ${jbi.schemas.dir}/" << path
      << "/" << *iter << ".xsd\" />" << std::endl
      << "<arg line=\"-package " << *iter << "\" />" << std::endl
      << "<arg line=\"-f -nodesc -nomarshall\" />" << std::endl
      << "</java>" << std::endl;
  }

  CUTS_BE_CAPI ()->project_file_
    << "</target>" << std::endl;
}

//
// CUTS_BE_Project_File_End_T
//
bool CUTS_BE_Project_File_End_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  std::string name = node.container_.name ();

  CUTS_BE_CAPI ()->project_file_
    << "</project>" << std::endl
    << std::endl
    << "<!-- end of auto-generated file -->" << std::endl;

  return true;
}

//
// CUTS_BE_Project_File_Close_T
//
void CUTS_BE_Project_File_Close_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (void)
{
  if (CUTS_BE_CAPI ()->project_file_.is_open ())
  {
    CUTS_BE_CAPI ()->project_formatter_.reset ();
    CUTS_BE_CAPI ()->project_file_.close ();
  }
}
