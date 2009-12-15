// $Id$

#include "IDL_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_OpenSplice
{
class Has_Events : public PICML::Visitor
{
public:
  Has_Events (void)
  {

  }

  virtual ~Has_Events (void)
  {

  }

  virtual void Visit_File (const PICML::File & file)
  {
    this->has_events_ = false;
    this->Visit_PackageFile_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  virtual void Visit_Event (const PICML::Event & event)
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
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));

    // Gather all the necessary elements.
    std::set <PICML::Event> events = Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

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
  this->predefined_types_.insert (std::make_pair (PICML::Boolean::meta, "boolean"));
  this->predefined_types_.insert (std::make_pair (PICML::Byte::meta, "octet"));
  this->predefined_types_.insert (std::make_pair (PICML::LongInteger::meta, "long"));
  this->predefined_types_.insert (std::make_pair (PICML::ShortInteger::meta, "short"));
  this->predefined_types_.insert (std::make_pair (PICML::String::meta, "string"));
  this->predefined_types_.insert (std::make_pair (PICML::DoubleNumber::meta, "double"));
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
Visit_RootFolder (const PICML::RootFolder & folder)
{
  std::vector <PICML::InterfaceDefinitions> folders = folder.InterfaceDefinitions_children ();

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&PICML::InterfaceDefinitions::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_InterfaceDefinitions
//
void IDL_Generator::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions & folder)
{
  std::vector <PICML::File> files = folder.File_children ();

  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&PICML::File::Accept, _1, boost::ref (*this)));
}

//
// Visit_File
//
void IDL_Generator::
Visit_File (const PICML::File & file)
{
  Has_Events has_events;
  PICML::File (file).Accept (has_events);

  if (!has_events.has_events ())
    return;

  // Construct the name of the output file.
  std::string basename (file.name ());
  basename += "_OPSL";

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
      << "module CUTS_OSPL"
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
Visit_Package (const PICML::Package & package)
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
  std::set <PICML::Package> packages =
    Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&PICML::Package::Accept,
                              _1,
                              boost::ref (*this)));

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

}



//
// Visit_Event
//
void IDL_Generator::
Visit_Event (const PICML::Event & event)
{
  this->idlfile_
    << "struct " << event.name ()
    << "{";

  std::vector <PICML::Member> members = event.Member_children ();
  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&PICML::Member::Accept,
                              _1,
                              boost::ref (*this)));

  this->idlfile_
    << "};"
    << "// define the keylist for the struct/event." << std::endl
    << "#pragma keylist " << event.name () << std::endl;
}

//
// Visit_Member
//
void IDL_Generator::
Visit_Member (const PICML::Member & member)
{
  PICML::MemberType mt = member.ref ();
  std::string name = member.name ();

  if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    this->idlfile_
      << CUTS_BE_CPP::single_line_comment ("data member: " + name)
      << this->predefined_types_[mt.type ()]
      << " " << name << ";"
      << std::endl;
  }
  else
  {
    PICML::NamedType nt = PICML::NamedType::Cast (mt);

    this->idlfile_
      << CUTS_BE_CPP::single_line_comment ("data member: " + name)
      << "::CUTS_OSPL" << CUTS_BE_CPP::fq_type (nt)
      << " " << name << ";"
      << std::endl;
  }
}

//
// Visit_Aggregate
//
void IDL_Generator::
Visit_Aggregate (const PICML::Aggregate & aggr)
{
  this->idlfile_
    << "struct " << aggr.name ()
    << "{";

  std::vector <PICML::Member> members = aggr.Member_children ();
  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&PICML::Member::Accept,
                              _1,
                              boost::ref (*this)));

  this->idlfile_
    << "};";
}

}
