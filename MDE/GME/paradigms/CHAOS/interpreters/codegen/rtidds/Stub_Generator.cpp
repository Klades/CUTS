// $Id$

#include "StdAfx.h"
#include "Stub_Generator.h"
#include "Input_Stream_Generator.h"
#include "Output_Stream_Generator.h"
#include "Event_Traits_Generator.h"
#include "boost/bind.hpp"
#include "cpp/Cpp.h"
#include "Uml.h"
#include <algorithm>

namespace CUTS_CHAOS
{
namespace RTIDDS
{
class Include_Events : public CHAOS::Visitor
{
public:
  Include_Events (std::ostream & source)
    : source_ (source),
      has_events_ (false)
  {

  }

  virtual ~Include_Events (void)
  {

  }

  virtual void Visit_File (const CHAOS::File & file)
  {
    this->Visit_PackageFile_i (file);

    if (this->has_events_)
    {
      std::string filename ("rtidds/");
      filename += std::string (file.name ()) + "_DDSSupport";

      this->source_ << CUTS_BE_CPP::include (filename);

      if (this->includes_.empty ())
      {
        this->source_
          << CUTS_BE_CPP::include ("cuts/arch/rtidds/RTIDDS_Traits_T");
      }
    }
  }

  virtual void Visit_Package (const CHAOS::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  virtual void Visit_Component (const CHAOS::Component & component)
  {
    // Visit all the input event ports.
    std::vector <CHAOS::InEventPort> inputs = component.InEventPort_kind_children ();

    for (auto input : inputs)
      input.Accept (*this);

    // Visit all the ouptut event ports.
    std::vector <CHAOS::OutEventPort> outputs = component.OutEventPort_kind_children ();

    for (auto output : outputs)
      output.Accept (*this);
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

    std::string filename ("RTIDDS_");
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

    for (auto package : packages)
      package.Accept (*this);


    // Does this level contain any events.
    std::vector <CHAOS::Event> events =
      Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty () && !this->has_events_)
      this->has_events_ = true;

    // Visit all the components.
    std::vector <CHAOS::Component> components =
      Udm::ChildrenAttr <CHAOS::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto component : components)
      component.Accept (*this);
  }

  std::ostream & source_;

  std::set <std::string> includes_;

  bool has_events_;
};

//
// Stub_Generator
//
Stub_Generator::
Stub_Generator (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~Stub_Generator
//
Stub_Generator::~Stub_Generator (void)
{
  if (this->header_.is_open ())
    this->header_.close ();

  if (this->source_.is_open ())
    this->source_.close ();
}

//
// Visit_RootFolder
//
void Stub_Generator::
Visit_RootFolder (const CHAOS::RootFolder & folder)
{
  std::vector <CHAOS::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();

  for (auto folder : folders)
    folders.Accept (*this);
}

//
// Visit_InterfaceDefinitions
//
void Stub_Generator::
Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions & folder)
{
  std::vector <CHAOS::File> files = folder.File_children ();

  for (auto file : files)
    file.Accept (*this);
}

//
// Visit_File
//
void Stub_Generator::
Visit_File (const CHAOS::File & file)
{
  // Construct the name of the output file.
  std::string basename ("RTIDDS_");
  basename += std::string (file.name ()) + "C";

  std::string header_filename = this->outdir_ + "/" + basename + ".h";
  std::string source_filename = this->outdir_ + "/" + basename + ".cpp";

  // Open the file for writing.
  this->source_.open (source_filename.c_str ());
  this->header_.open (header_filename.c_str ());

  if (!this->header_.is_open () && this->source_.is_open ())
    return;

  // Construct the name of the exp macro.
  std::string corba_filename (file.name ());
  corba_filename += "C";

  // Construct the exp macro for this file.
  this->export_macro_ = std::string (file.name ()) + "_STUB";

  std::transform (this->export_macro_.begin (),
                  this->export_macro_.end (),
                  this->export_macro_.begin (),
                  &::toupper);

  this->export_macro_ += "_Export";

  // Construct the name of the hash define for the header.
  std::string hash_define = "_" + basename + "_H_";
  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  std::string dds_filename ("rtidds/");
  dds_filename += std::string (file.name ()) + "_DDS";

  do
  {
    /// Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> source_formatter (this->source_);
    Indentation::Implanter <Indentation::Cxx, char> header_formatter (this->header_);

    // Include the header file.
    this->source_
      << "// $" << "Id" << "$" << std::endl
      << std::endl
      << CUTS_BE_CPP::include (basename) << std::endl
      << std::endl;

    this->header_
      << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
      << std::endl
      << "#ifndef " << hash_define << std::endl
      << "#define " << hash_define << std::endl
      << std::endl
      << CUTS_BE_CPP::include (corba_filename);

    Include_Events include_events (this->header_);
    CHAOS::File (file).Accept (include_events);

    this->header_
      << std::endl;

    if (!this->events_.empty ())
      this->events_.clear ();

    this->Visit_PackageFile_i (file);

    Event_Traits_Generator traits_generator (this->header_, this->export_macro_);

    for (auto event : this->events_)
      event.Accept (traits_generator);

    this->header_
      << "#endif  // " << hash_define << std::endl
      << std::endl;
  } while (0);

  // Close the file.
  this->source_.close ();
  this->header_.close ();
}

//
// Visit_Package
//
void Stub_Generator::
Visit_Package (const CHAOS::Package & package)
{
  this->header_
    << "namespace " << package.name ()
    << "{";

  this->source_
    << "namespace " << package.name ()
    << "{";

  this->Visit_PackageFile_i (package);

  this->header_
    << "}";

  this->source_
    << "}";
}

//
// Visit_PackageFile_i
//
void Stub_Generator::
Visit_PackageFile_i  (const Udm::Object & obj)
{
  // Gather all the necessary elements.
  std::set <CHAOS::Event> events = Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  for (auto event : events)
    event.Accept (*this);

  // Write the output stream generators.
  std::set <CHAOS::Aggregate> aggrs = Udm::ChildrenAttr <CHAOS::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);
  for (auto aggr : aggrs)
    aggr.Accept (*this);

  std::set <CHAOS::Collection> colls = Udm::ChildrenAttr <CHAOS::Collection> (obj.__impl (), Udm::NULLCHILDROLE);
  for (auto coll : colls)
    coll.Accept (*this);

  std::set <CHAOS::Package> packages =
    Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);
  for (auto package : packages)
    package.Accept (*this);
}

//
// Visit_Event
//
void Stub_Generator::
Visit_Event (const CHAOS::Event & event)
{
  std::string name (event.name ());
  std::string fq_name (CUTS_BE_CPP::fq_type (event));

  this->header_
    << this->export_macro_
    << " bool operator <<= (" << name << " &, const ::CUTS_NDDS" << fq_name << " & );"
    << this->export_macro_
    << " bool operator >>= (const " << name << " &, ::CUTS_NDDS" << fq_name << " & );"
    << std::endl;

  std::vector <CHAOS::Member> members = event.Member_children ();

  this->source_
    << "bool operator <<= (" << name << " & corba, const ::CUTS_NDDS" << fq_name << " & dds)"
    << "{";

  Input_Stream_Generator input_stream (this->source_, false);

  for (auto member : members)
    member.Accept (input_stream);

  this->source_
    << "return true;"
    << "}"
    << "bool operator >>= (const " << name << " & corba, ::CUTS_NDDS" << fq_name << " & dds)"
    << "{";

  Output_Stream_Generator output_stream (this->source_, false);

  for (auto member : members)
    member.Accept (output_stream);

  this->source_
    << "return true;"
    << "}";

  this->events_.insert (event);
}

//
// Visit_Event
//
void Stub_Generator::
Visit_Aggregate (const CHAOS::Aggregate & aggr)
{
  std::string name (aggr.name ());
  std::string fq_name (CUTS_BE_CPP::fq_type (aggr));

  this->header_
    << this->export_macro_
    << " bool operator <<= (" << name << " &, const ::CUTS_NDDS" << fq_name << " & );"
    << this->export_macro_
    << " bool operator >>= (const " << name << " &, ::CUTS_NDDS" << fq_name << " & );"
    << std::endl;

  std::vector <CHAOS::Member> members = aggr.Member_children ();

  this->source_
    << "bool operator <<= (" << name << " & corba, const ::CUTS_NDDS" << fq_name << " & dds)"
    << "{";

  Input_Stream_Generator input_stream (this->source_, true);
  for (auto member : members)
    member.Accept (input_stream);

  this->source_
    << "return true;"
    << "}"
    << "bool operator >>= (const " << name << " & corba, ::CUTS_NDDS" << fq_name << " & dds)"
    << "{";

  Output_Stream_Generator output_stream (this->source_, true);
  for (auto member : members)
    member.Accept (output_stream);

  this->source_
    << "return true;"
    << "}";
}
}
}
