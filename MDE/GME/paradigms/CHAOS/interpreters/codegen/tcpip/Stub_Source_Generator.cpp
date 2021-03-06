// $Id$

#include "StdAfx.h"
#include "Stub_Source_Generator.h"
#include "Input_Stream_Source_Generator.h"
#include "Output_Stream_Source_Generator.h"
#include "../cpp/Cpp.h"

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
Visit_RootFolder (const CHAOS::RootFolder & folder)
{
  std::set <CHAOS::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();

  for (auto folder : folders)
    folder.Accept (*this);
}

//
// Visit_InterfaceDefinitions
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions & folder)
{
  std::set <CHAOS::File> files = folder.File_children ();

  for (auto file : files)
    file.Accept (*this);
}

//
// Visit_File
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_File (const CHAOS::File & file)
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
    std::set <CHAOS::Package> packages = file.Package_children ();

    // Include the header file.
    this->outfile_ << CUTS_BE_CPP::single_line_comment ("$Id$")
                   << std::endl
                   << CUTS_BE_CPP::include (basename) << std::endl
                   << std::endl;

    this->Visit_PackageFile_i (file);
  } while (0);

  // Close the file.
  this->outfile_.close ();
}

//
// Visit_Package
//
void CUTS_BE_TCPIP_Stub_Source_Generator::
Visit_Package (const CHAOS::Package & package)
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
  std::set <CHAOS::Event> events = Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  std::set <CHAOS::Aggregate> aggrs = Udm::ChildrenAttr <CHAOS::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);
  std::set <CHAOS::Collection> colls = Udm::ChildrenAttr <CHAOS::Collection> (obj.__impl (), Udm::NULLCHILDROLE);

  // Write the output stream generators.
  for (auto aggr : aggrs)
    aggr.Accept (osg);

  for (auto event : events)
    event.Accept (osg);

  for (auto coll : colls)
    coll.Accept (osg);

  // Write the input stream generators.
  for (auto aggr : aggrs)
    aggr.Accept (isg);

  for (auto event : events)
    event.Accept (isg);

  for (auto coll : colls)
    coll.Accept (isg);

  std::set <CHAOS::Package> packages =
    Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);

  for (auto package : packages)
    package.Accept (*this);
}
