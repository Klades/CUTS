// $Id$

#include "Stub_Source_Generator.h"
#include "Input_Stream_Source_Generator.h"
#include "Output_Stream_Source_Generator.h"
#include "TCPIP_Ctx.h"
#include "../../../lang/cpp/Cpp.h"

#include "boost/bind.hpp"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include <algorithm>
#include <iomanip>

class Include_Stubs : public PICML::Visitor
{
public:
  Include_Stubs (std::ostream & source)
    : source_ (source)
  {

  }

  virtual ~Include_Stubs (void)
  {

  }

  virtual void Visit_File (const PICML::File & file)
  {
    this->includes_.insert (std::string (file.name ()));
    this->Visit_PackageFile_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  virtual void Visit_Component (const PICML::Component & component)
  {
    // Visit all the input event ports.
    std::vector <PICML::InEventPort> inputs = component.InEventPort_kind_children ();

    std::for_each (inputs.begin (),
                   inputs.end (),
                   boost::bind (&PICML::InEventPort::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the ouptut event ports.
    std::vector <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();

    std::for_each (outputs.begin (),
                   outputs.end (),
                   boost::bind (&PICML::OutEventPort::Accept,
                                _1,
                                boost::ref (*this)));
  }

  virtual void Visit_InEventPort (const PICML::InEventPort & port)
  {
    PICML::EventType et = port.ref ();

    if (et != Udm::null && et.type () == PICML::Event::meta)
      PICML::Event::Cast (et).Accept (*this);
  }

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port)
  {
    PICML::EventType et = port.ref ();

    if (et != Udm::null && et.type () == PICML::Event::meta)
      PICML::Event::Cast (et).Accept (*this);
  }

  //
  // Visit_Event
  //
  virtual void Visit_Event (const PICML::Event & ev)
  {
    std::vector <PICML::Member> members = ev.Member_children ();
    std::for_each (members.begin (),
                   members.end (),
                   boost::bind (&PICML::Member::Accept,
                                _1,
                                boost::ref (*this)));
  }

  //
  // Visit_Member
  //
  virtual void Visit_Member (const PICML::Member & m)
  {
    PICML::MemberType mt = m.ref ();

    if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
      return;

    PICML::MgaObject parent = PICML::MgaObject::Cast (mt.parent ());

    while (PICML::File::meta != parent.type ())
      parent = PICML::MgaObject::Cast (parent.parent ());

    std::string name = parent.name ();
    if (this->includes_.find (name) != this->includes_.end ())
      return;

    PICML::File file = PICML::File::Cast (parent);
    std::string filename = file.Path ();

    if (!filename.empty ())
      filename += "/";

    filename += "TCPIP_" + name + "C";

    this->source_ << CUTS_BE_CPP::include (filename);
    this->includes_.insert (name);
  }

private:
  void Visit_PackageFile_i (const Udm::Object & obj)
  {
    // Visit all the events.
    std::vector <PICML::Event> events =
      Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (events.begin (),
                   events.end (),
                   boost::bind (&PICML::Event::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the events.
    std::vector <PICML::Aggregate> aggrs =
      Udm::ChildrenAttr <PICML::Aggregate> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (aggrs.begin (),
                   aggrs.end (),
                   boost::bind (&PICML::Aggregate::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the packages.
    std::vector <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

  std::ostream & source_;

  std::set <std::string> includes_;

  bool has_events_;
};

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
  const std::string path = file.Path ();

  if (!path.empty ())
    filename += "/" + path;

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
    this->outfile_
      << CUTS_BE_CPP::single_line_comment ("This file was generated by")
      << CUTS_BE_CPP::single_line_comment (__FILE__)
      << std::endl
      << CUTS_BE_CPP::include (basename)
      << CUTS_BE_CPP::include ("ace/SString") << std::endl
      << std::endl;

    // Generate the other stub include files.
    Include_Stubs include_stubs (this->outfile_);
    PICML::File (file).Accept (include_stubs);

    this->Visit_PackageFile_i (file);
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
  this->Visit_PackageFile_i (package);
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

  std::set <PICML::Package> packages =
    Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&PICML::Package::Accept,
                              _1,
                              boost::ref (*this)));
}
