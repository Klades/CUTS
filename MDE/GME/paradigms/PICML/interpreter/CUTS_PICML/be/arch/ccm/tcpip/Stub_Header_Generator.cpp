// $Id$

#include "Stub_Header_Generator.h"
#include "../../../lang/cpp/Cpp.h"
#include "boost/bind.hpp"
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Uml.h"

#include <algorithm>
#include <iomanip>

namespace CUTS_BE_TCPIP
{
//
// Stub_Header_Generator
//
Stub_Header_Generator::
Stub_Header_Generator (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~Stub_Header_Generator
//
Stub_Header_Generator::~Stub_Header_Generator (void)
{
  if (this->outfile_.is_open ())
    this->outfile_.close ();
}

//
// Visit_RootFolder
//
void Stub_Header_Generator::
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
void Stub_Header_Generator::
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
void Stub_Header_Generator::
Visit_File (const PICML::File & file)
{
  // Construct the name of the output file.
  std::string basename ("TCPIP_");
  basename += std::string (file.name ()) + "C";

  std::string filename (this->outdir_);
  const std::string path = file.Path ();

  if (!path.empty ())
    filename += "/" + path;

  filename += "/" + basename + ".h";

  // Open the file for writing.
  this->outfile_.open (filename.c_str ());
  if (!this->outfile_.is_open ())
    return;

  std::string hash_define ("_TCPIP_");
  hash_define += std::string (file.name ()) + "_H_";

  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  do
  {
    // Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> formatter (this->outfile_);

    std::string corba_filename (file.name ());
    corba_filename += "C";

    std::string export_filename (file.name ());
    export_filename += "_stub_export";

    // Construct the export macro for this file.
    this->export_macro_ = std::string (file.name ()) + "_STUB";

    std::transform (this->export_macro_.begin (),
                    this->export_macro_.end (),
                    this->export_macro_.begin (),
                    &::toupper);

    this->export_macro_ += "_Export";

    // Include the header file.
    this->outfile_ << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
                   << std::endl
                   << "#ifndef " << hash_define << std::endl
                   << "#define " << hash_define << std::endl
                   << std::endl
                   << CUTS_BE_CPP::include (corba_filename)
                   << CUTS_BE_CPP::include (export_filename)
                   << std::endl;

    // Visit all the packages in this file.
    std::set <PICML::Package> packages = file.Package_children ();
    this->Visit_PackageFile_i (file);

    this->outfile_ << "#endif  // !defined " << hash_define << std::endl;
  } while (0);

  // Close the file.
  this->outfile_.close ();
}

//
// Visit_Package
//
void Stub_Header_Generator::
Visit_Package (const PICML::Package & package)
{
  this->Visit_PackageFile_i (package);
}

//
// Visit_PackageFile_i
//
void Stub_Header_Generator::
Visit_PackageFile_i  (const Udm::Object & obj)
{
  // Gather all the necessary elements.
  std::set <PICML::Event> events = Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (events.begin (),
                 events.end (),
                 boost::bind (&PICML::Event::Accept,
                              _1,
                              boost::ref (*this)));

  // Write the output stream generators.
  std::set <PICML::Aggregate> aggrs = Udm::ChildrenAttr <PICML::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (aggrs.begin (),
                 aggrs.end (),
                 boost::bind (&PICML::Aggregate::Accept,
                              _1,
                              boost::ref (*this)));

  std::set <PICML::Collection> colls = Udm::ChildrenAttr <PICML::Collection> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (colls.begin (),
                 colls.end (),
                 boost::bind (&PICML::Collection::Accept,
                              _1,
                              boost::ref (*this)));

  std::set <PICML::Package> packages =
    Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&PICML::Package::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Event
//
void Stub_Header_Generator::
Visit_Event (const PICML::Event & ev)
{
  const std::string fq_type = CUTS_BE_CPP::fq_type (ev, "::");

  this->outfile_
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << CUTS_BE_CPP::single_line_comment ("stream operators for " + fq_type)
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << std::endl
    << this->export_macro_
    << " ACE_CDR::Boolean operator >> (ACE_InputCDR &, " << fq_type << " &);"
    << this->export_macro_
    << " ACE_CDR::Boolean operator << (ACE_OutputCDR &, const " << fq_type << " &);"
    << std::endl;
}

//
// Visit_Aggregate
//
void Stub_Header_Generator::
Visit_Aggregate (const PICML::Aggregate & aggr)
{
  const std::string fq_type = CUTS_BE_CPP::fq_type (aggr, "::");

  this->outfile_
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << CUTS_BE_CPP::single_line_comment ("stream operators for " + fq_type)
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << std::endl
    << this->export_macro_
    << " ACE_CDR::Boolean operator >> (ACE_InputCDR &, " << fq_type << " &);"
    << this->export_macro_
    << " ACE_CDR::Boolean operator << (ACE_OutputCDR &, const "
    << fq_type << " &);"
    << std::endl;
}

//
// Visit_Collection
//
void Stub_Header_Generator::
Visit_Collection (const PICML::Collection & coll)
{
  const std::string fq_type = CUTS_BE_CPP::fq_type (coll, "::");

  this->outfile_
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << CUTS_BE_CPP::single_line_comment ("stream operators for " + fq_type)
    << left << setw (78) << setfill ('=') << "//" << std::endl
    << std::endl
    << this->export_macro_
    << " ACE_CDR::Boolean operator >> (ACE_InputCDR &, " << fq_type << " &);"
    << this->export_macro_
    << " ACE_CDR::Boolean operator << (ACE_OutputCDR &, const " << fq_type << " &);"
    << std::endl;
}

}
