// $Id$

#include "StdAfx.h"
#include "IDL_Generator.h"
#include "cpp/Cpp.h"
#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_CHAOS
{
class Has_Events : public CHAOS::Visitor
{
public:
  Has_Events (void)
  {

  }

  virtual ~Has_Events (void)
  {

  }

  virtual void Visit_File (const CHAOS::File & file)
  {
    this->has_events_ = false;
    this->Visit_PackageFile_i (file);
  }

  virtual void Visit_Package (const CHAOS::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  virtual void Visit_Event (const CHAOS::Event & event)
  {
    this->has_events_ = true;
  }

  bool has_events (void) const
  {
    return this->has_events_;
  }

private:
  void Visit_PackageFile_i (const Udm::Object & obj)
  {
    std::set <CHAOS::Package> packages =
      Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    for (auto package : packages)
      package.Accept (*this);

    // Gather all the necessary elements.
    std::set <CHAOS::Event> events = Udm::ChildrenAttr <CHAOS::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty ())
      this->has_events_ = true;
  }

  bool has_events_;
};

//
// IDL_Generator
//
IDL_Generator::IDL_Generator (const std::string & outdir)
: outdir_ (outdir)
{
  this->predefined_types_.insert (std::make_pair (CHAOS::Boolean::meta, "boolean"));
  this->predefined_types_.insert (std::make_pair (CHAOS::Byte::meta, "octet"));
  this->predefined_types_.insert (std::make_pair (CHAOS::LongInteger::meta, "long"));
  this->predefined_types_.insert (std::make_pair (CHAOS::ShortInteger::meta, "short"));
  this->predefined_types_.insert (std::make_pair (CHAOS::String::meta, "string"));
  this->predefined_types_.insert (std::make_pair (CHAOS::RealNumber::meta, "double"));
}

//
// IDL_Generator
//
IDL_Generator::~IDL_Generator (void)
{
  if (this->idlfile_.is_open ())
    this->idlfile_.close ();
}

//
// Visit_RootFolder
//
void IDL_Generator::
Visit_RootFolder (const CHAOS::RootFolder & folder)
{
  std::vector <CHAOS::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();

  for (auto folder : folders)
    folder.Accept (*this);
}

//
// Visit_InterfaceDefinitions
//
void IDL_Generator::
Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions & folder)
{
  std::vector <CHAOS::File> files = folder.File_children ();

  for (auto file : files)
    file.Accept (*this);
}

//
// Visit_File
//
void IDL_Generator::
Visit_File (const CHAOS::File & file)
{
  Has_Events has_events;
  CHAOS::File (file).Accept (has_events);

  if (!has_events.has_events ())
    return;

  // Construct the name of the output file.
  std::string basename (file.name ());
  basename += "_DDS";

  std::string idl_filename = this->outdir_ + "/" + basename + ".idl";

  // Open the file for writing.
  this->idlfile_.open (idl_filename.c_str ());

  if (!this->idlfile_.is_open ())
    return;

  // Construct the name of the hash define for the header.
  std::string hash_define = "_" + basename + "_IDL_";
  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  do
  {
    /// Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> formatter (this->idlfile_);

    // Include the header file.
    this->idlfile_
      << CUTS_BE_CPP::single_line_comment ("-*- IDL -*-")
      << std::endl
      << "#ifndef " << hash_define << std::endl
      << "#define " << hash_define << std::endl
      << std::endl
      << "#if defined (__NDDS__)" << std::endl
      << "#define CUTS_DDS CUTS_NDDS" << std::endl
      << "#elif defined (__OSPL__)" << std::endl
      << "#define CUTS_DDS CUTS_OSPL" << std::endl
      << "#endif" << std::endl
      << std::endl
      << "module CUTS_DDS" << std::endl
      << "{";

    this->Visit_PackageFile_i (file);

    this->idlfile_
      << "};"
      << "#endif  // " << hash_define << std::endl
      << std::endl;
  } while (0);

  // Close the file.
  this->idlfile_.close ();
}

//
// Visit_Package
//
void IDL_Generator::
Visit_Package (const CHAOS::Package & package)
{
  this->idlfile_
    << "module " << package.name ()
    << "{";

  this->Visit_PackageFile_i (package);

  this->idlfile_
    << "};";
}

//
// Visit_PackageFile_i
//
void IDL_Generator::
Visit_PackageFile_i  (const Udm::Object & obj)
{
  std::set <CHAOS::Package> packages =
    Udm::ChildrenAttr <CHAOS::Package> (obj.__impl (), Udm::NULLCHILDROLE);
  for (auto package : packages)
    package.Accept (*this);

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
}



//
// Visit_Event
//
void IDL_Generator::
Visit_Event (const CHAOS::Event & event)
{
  this->idlfile_
    << "struct " << event.name ()
    << "{";

  std::vector <CHAOS::Member> members = event.Member_children ();
  for (auto member : members)
    member.Accept (*this);

  this->idlfile_
    << "};"
    << "#if defined (__OSPL__)" << std::endl
    << "// define the keylist for the struct/event." << std::endl
    << "#pragma keylist " << event.name () << std::endl
    << "#endif" << std::endl;
}

//
// Visit_Member
//
void IDL_Generator::
Visit_Member (const CHAOS::Member & member)
{
  CHAOS::MemberType mt = member.ref ();
  std::string name = member.name ();

  if (Udm::IsDerivedFrom (mt.type (), CHAOS::PredefinedType::meta))
  {
    this->idlfile_
      << CUTS_BE_CPP::single_line_comment ("data member: " + name)
      << this->predefined_types_[mt.type ()]
      << " " << name << ";"
      << std::endl;
  }
  else
  {
    CHAOS::NamedType nt = CHAOS::NamedType::Cast (mt);

    this->idlfile_
      << CUTS_BE_CPP::single_line_comment ("data member: " + name)
      << "::CUTS_DDS" << CUTS_BE_CPP::fq_type (nt)
      << " " << name << ";"
      << std::endl;
  }
}

//
// Visit_Aggregate
//
void IDL_Generator::
Visit_Aggregate (const CHAOS::Aggregate & aggr)
{
  this->idlfile_
    << "struct " << aggr.name ()
    << "{";

  std::vector <CHAOS::Member> members = aggr.Member_children ();
  for (auto member : members)
    member.Accept (*this);

  this->idlfile_
    << "};";
}

}
