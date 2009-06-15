// $Id$

#include "StdAfx.h"
#include "Stub_Header_Generator.h"
#include "../cpp/Cpp.h"
#include "boost/bind.hpp"
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_BE_TCPIP
{
class Include_Stubs : public CHAOS::Visitor
{
public:
  Include_Stubs (std::ostream & source)
    : source_ (source)
  {

  }

  virtual ~Include_Stubs (void)
  {

  }

  virtual void Visit_File (const CHAOS::File & file)
  {
    this->Visit_PackageFile_i (file);
  }

  virtual void Visit_Package (const CHAOS::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  virtual void Visit_Component (const CHAOS::Component & component)
  {
    // Visit all the input event ports.
    std::vector <CHAOS::InEventPort> inputs = component.InEventPort_kind_children ();

    std::for_each (inputs.begin (),
                   inputs.end (),
                   boost::bind (&CHAOS::InEventPort::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the ouptut event ports.
    std::vector <CHAOS::OutEventPort> outputs = component.OutEventPort_kind_children ();

    std::for_each (outputs.begin (),
                   outputs.end (),
                   boost::bind (&CHAOS::OutEventPort::Accept,
                                _1,
                                boost::ref (*this)));
  }

  virtual void Visit_InEventPort (const CHAOS::InEventPort & port)
  {
    CHAOS::Event event = port.ref ();

    if (Udm::null != event)
      event.Accept (*this);
  }

  virtual void Visit_OutEventPort (const CHAOS::OutEventPort & port)
  {
    CHAOS::Event event = port.ref ();

    if (Udm::null != event)
      event.Accept (*this);
  }

  virtual void Visit_Event (const CHAOS::Event & event)
  {
    CHAOS::MgaObject parent = CHAOS::MgaObject::Cast (event.parent ());

    while (CHAOS::File::meta != parent.type ())
      parent = CHAOS::MgaObject::Cast (parent.parent ());

    std::string name = parent.name ();

    if (this->includes_.find (name) != this->includes_.end ())
      return;

    std::string filename ("TCPIP_");
    filename += name + "C";

    this->source_ << CUTS_BE_CPP::include (filename);
    this->includes_.insert (name);
  }

private:
  void Visit_PackageFile_i (const Udm::Object & obj)
  {
    // Visit all the packages.
    std::vector <CHAOS::Package> packages =
      Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&CHAOS::Package::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the components.
    std::vector <CHAOS::Component> components =
      Udm::ChildrenAttr <CHAOS::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (components.begin (),
                   components.end (),
                   boost::bind (&CHAOS::Component::Accept,
                                _1,
                                boost::ref (*this)));
  }

  std::ostream & source_;

  std::set <std::string> includes_;

  bool has_events_;
};

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
Visit_RootFolder (const CHAOS::RootFolder & folder)
{
  std::set <CHAOS::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&CHAOS::InterfaceDefinitions::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_InterfaceDefinitions
//
void Stub_Header_Generator::
Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions & folder)
{
  std::set <CHAOS::File> files = folder.File_children ();

  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&CHAOS::File::Accept, _1, boost::ref (*this)));
}

//
// Visit_File
//
void Stub_Header_Generator::
Visit_File (const CHAOS::File & file)
{
  // Construct the name of the output file.
  std::string basename ("TCPIP_");
  basename += std::string (file.name ()) + "C";

  std::string filename (this->outdir_);
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
                   << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_InputCDR")
                   << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_OutputCDR")
                   << CUTS_BE_CPP::include (export_filename);

    Include_Stubs include_stubs (this->outfile_);
    CHAOS::File (file).Accept (include_stubs);

    this->outfile_ << std::endl;

    // Visit all the packages in this file.
    std::set <CHAOS::Package> packages = file.Package_children ();
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
void Stub_Header_Generator::
Visit_PackageFile_i  (const Udm::Object & obj)
{
  // Gather all the necessary elements.
  std::set <CHAOS::Event> events = Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (events.begin (),
                 events.end (),
                 boost::bind (&CHAOS::Event::Accept,
                              _1,
                              boost::ref (*this)));

  // Write the output stream generators.
  std::set <CHAOS::Aggregate> aggrs = Udm::ChildrenAttr <CHAOS::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (aggrs.begin (),
                 aggrs.end (),
                 boost::bind (&CHAOS::Aggregate::Accept,
                              _1,
                              boost::ref (*this)));

  std::set <CHAOS::Collection> colls = Udm::ChildrenAttr <CHAOS::Collection> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (colls.begin (),
                 colls.end (),
                 boost::bind (&CHAOS::Collection::Accept,
                              _1,
                              boost::ref (*this)));

  std::set <CHAOS::Package> packages =
    Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&CHAOS::Package::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Event
//
void Stub_Header_Generator::
Visit_Event (const CHAOS::Event & event)
{
  this->outfile_ << "ACE_CDR::Boolean " << this->export_macro_
                 << " operator >> (CUTS_TCPIP_InputCDR &, "
                 << event.name () << " &);"
                 << "ACE_CDR::Boolean " << this->export_macro_
                 << " operator << (CUTS_TCPIP_OutputCDR &, const "
                 << event.name () << " &);"
                 << std::endl;
}

//
// Visit_Aggregate
//
void Stub_Header_Generator::
Visit_Aggregate (const CHAOS::Aggregate & aggr)
{
  this->outfile_ << "ACE_CDR::Boolean " << this->export_macro_
                 << " operator >> (CUTS_TCPIP_InputCDR &, "
                 << aggr.name () << " &);"
                 << "ACE_CDR::Boolean " << this->export_macro_
                 << " operator << (CUTS_TCPIP_OutputCDR &, const "
                 << aggr.name () << " &);"
                 << std::endl;
}

//
// Visit_Collection
//
void Stub_Header_Generator::
Visit_Collection (const CHAOS::Collection & coll)
{
  this->outfile_ << "ACE_CDR::Boolean " << this->export_macro_
                 << " operator >> (CUTS_TCPIP_InputCDR &, "
                 << coll.name () << " &);"
                 << "ACE_CDR::Boolean " << this->export_macro_
                 << " operator << (CUTS_TCPIP_OutputCDR &, const "
                 << coll.name () << " &);"
                 << std::endl;
}

}
