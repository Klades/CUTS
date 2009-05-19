// $Id$

#include "Stub_Source_Generator.h"
#include "Input_Stream_Source_Generator.h"
#include "Output_Stream_Source_Generator.h"
#include "TCPIP_Ctx.h"

#include "boost/bind.hpp"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include <algorithm>

//
// CUTS_BE_TCPIP_Stub_Source_Generator
//
CUTS_BE_TCPIP_Stub_Source_Generator::
CUTS_BE_TCPIP_Stub_Source_Generator (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~CUTS_BE_TCPIP_Stub_Source_Generator
//
CUTS_BE_TCPIP_Stub_Source_Generator::~CUTS_BE_TCPIP_Stub_Source_Generator (void)
{
  if (this->outfile_.is_open ())
    this->outfile_.close ();
}

//
// Visit_RootFolder
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_RootFolder (const PICML::RootFolder & folder)
{
  std::set <PICML::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&PICML::InterfaceDefinitions::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_InterfaceDefinitions
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions & folder)
{
  std::set <PICML::File> files = folder.File_children ();

  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&PICML::File::Accept, _1, boost::ref (*this)));
}

//
// Visit_File
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_File (const PICML::File & file)
{
  // Construct the name of the output file.
  std::string basename ("TCPIP_");
  basename += std::string (file.name ()) + "C";

  std::string filename (this->outdir_);
  filename += "/" + basename + ".cpp";

  // Open the file for writing.
  this->outfile_.open (filename.c_str ());
  if (!this->outfile_.is_open ())
    return;

  do
  {
    /// Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> formatter (this->outfile_);

    // Visit all the packages in this file.
    std::set <PICML::Package> packages = file.Package_children ();

    // Include the header file.
    this->outfile_ << CUTS_BE_TCPIP_Ctx::single_line_comment ("$Id$")
                   << std::endl
                   << CUTS_BE_TCPIP_Ctx::include (basename) << std::endl
                   << std::endl;

    this->Visit_PackageFile_i (file);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept, _1, boost::ref (*this)));
  } while (0);

  // Close the file.
  this->outfile_.close ();
}

//
// Visit_Package
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_Package (const PICML::Package & package)
{
  this->outfile_ << "namespace " << package.name ()
                 << "{";

  this->Visit_PackageFile_i (package);

  this->outfile_ << "}";
}

//
// Visit_PackageFile_i
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_PackageFile_i  (const Udm::Object & obj)
{
  CUTS_BE_TCPIP::Output_Stream_Source_Generator osg (this->outfile_);
  CUTS_BE_TCPIP::Input_Stream_Source_Generator isg (this->outfile_);

  // Gather all the necessary elements.
  std::set <PICML::Event> events = Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  std::set <PICML::Aggregate> aggrs = Udm::ChildrenAttr <PICML::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);
  std::set <PICML::Collection> colls = Udm::ChildrenAttr <PICML::Collection> (obj.__impl (), Udm::NULLCHILDROLE);

  // Write the output stream generators.
  std::for_each (aggrs.begin (),
                 aggrs.end (),
                 boost::bind (&PICML::Aggregate::Accept, _1, osg));

  std::for_each (events.begin (),
                 events.end (),
                 boost::bind (&PICML::Event::Accept, _1, osg));

  std::for_each (colls.begin (),
                 colls.end (),
                 boost::bind (&PICML::Collection::Accept, _1, osg));

  // Write the input stream generators.
  std::for_each (aggrs.begin (),
                 aggrs.end (),
                 boost::bind (&PICML::Aggregate::Accept, _1, isg));

  std::for_each (events.begin (),
                 events.end (),
                 boost::bind (&PICML::Event::Accept, _1, isg));

  std::for_each (colls.begin (),
                 colls.end (),
                 boost::bind (&PICML::Collection::Accept, _1, isg));
}
