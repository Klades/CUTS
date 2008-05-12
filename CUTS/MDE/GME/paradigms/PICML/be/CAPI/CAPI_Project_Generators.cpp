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
  std::string name = node.container_.name ();

  CUTS_BE_CAPI ()->project_file_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl
    << "<project name=\"cuts.capi.client." << name << "\" basedir=\".\" "
    << "default=\"build.all\">" << std::endl
    << "<!-- property for environment variables -->" << std::endl
    << "<property environment=\"env\" />" << std::endl
    << "<property name=\"classpath\"" << std::endl 
    << "value=\".;${env.JBI_ROOT}/lib/capi1.5.jar;"
    << "${env.CUTS_ROOT}/lib/cuts.java.jar;"
    << "${env.CUTS_ROOT}/lib/cuts.java.jbi.client.jar\" />" << std::endl;

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
    << "<target name=\"build.all\" " << std::endl 
    << "depends=\"";

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
// CUTS_BE_Project_Write_T
//
void CUTS_BE_Project_Write_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::
generate_i (const PICML::MonolithicImplementation & monoimpl)
{
  std::string name (monoimpl.name ());

  CUTS_BE_CAPI ()->project_file_
    << std::endl
    << "<target name=\"" << name << ".build\">" << std::endl
    << "<javac srcdir=\".\" classpath=\"${classpath}\">" << std::endl
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
    << "<!-- create the final JAR file. -->" << std::endl
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
// CUTS_BE_Project_File_End_T
//
bool CUTS_BE_Project_File_End_T <
CUTS_BE_Capi, CUTS_BE_Impl_Node>::generate (const CUTS_BE_Impl_Node & node)
{
  std::string name = node.container_.name ();

  CUTS_BE_CAPI ()->project_file_
    << "</project>";

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
