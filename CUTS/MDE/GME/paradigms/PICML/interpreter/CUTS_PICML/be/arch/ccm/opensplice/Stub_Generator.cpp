// $Id$

#include "Stub_Generator.h"
#include "Event_Traits_Generator.h"
#include "../../../lang/cpp/Cpp.h"

#include "boost/bind.hpp"
#include "Uml.h"

#include <algorithm>

namespace CUTS_BE_OpenSplice
{
class Include_Events : public PICML::Visitor
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

  virtual void Visit_File (const PICML::File & file)
  {
    this->this_file_ = file;
    this->Visit_PackageFile_i (file);

    if (this->has_events_)
    {
      if (this->includes_.empty ())
        this->source_ << CUTS_BE_CPP::include ("cuts/arch/opensplice/OpenSplice_Traits_T");
    }
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  virtual void Visit_Component (const PICML::Component & component)
  {
    // Visit all the input ev ports.
    std::vector <PICML::InEventPort> inputs = component.InEventPort_kind_children ();

    std::for_each (inputs.begin (),
                   inputs.end (),
                   boost::bind (&PICML::InEventPort::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the ouptut ev ports.
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

  virtual void Visit_Event (const PICML::Event & ev)
  {
    PICML::File file = this->get_parent_file (ev);
    const std::string name = file.name ();

    if (this->includes_.find (name) != this->includes_.end ())
      return;


    if (this->this_file_ != this->get_parent_file (ev))
    {
      const std::string filename = "OpenSplice_" + name + "C";
      this->source_ << CUTS_BE_CPP::include (filename);
      this->includes_.insert (name);
    }
  }

private:
  PICML::File get_parent_file (const Udm::Object & obj)
  {
    Udm::Object parent = obj.GetParent ();

    while (parent.type () != PICML::File::meta)
      parent = parent.GetParent ();

    return PICML::File::Cast (parent);
  }

  void Visit_PackageFile_i (const Udm::Object & obj)
  {
    // Visit all the packages.
    std::vector <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));

    // Does this level contain any events.
    std::vector <PICML::Event> events =
      Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty () && !this->has_events_)
      this->has_events_ = true;

    // Visit all the components.
    std::vector <PICML::Component> components =
      Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (components.begin (),
                   components.end (),
                   boost::bind (&PICML::Component::Accept,
                                _1,
                                boost::ref (*this)));
  }

  PICML::File this_file_;

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
void Stub_Generator::
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
void Stub_Generator::
Visit_File (const PICML::File & file)
{
  // Construct the name of the output file.
  std::string basename ("OpenSplice_");
  basename += std::string (file.name ()) + "C";

  std::string header_filename = this->outdir_ + "/" + basename + ".h";
  std::string source_filename = this->outdir_ + "/" + basename + ".cpp";

  // Open the file for writing.
  this->source_.open (source_filename.c_str ());
  this->header_.open (header_filename.c_str ());

  if (!this->header_.is_open () && this->source_.is_open ())
    return;

  // Construct the name of the export macro.
  std::string corba_filename (file.name ());
  corba_filename += "C";

  // Construct the export macro for this file.
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

  std::string dds_filename ("opensplice/");
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
    PICML::File (file).Accept (include_events);

    // Gather all the events in this file.
    this->Visit_PackageFile_i (file);

    this->header_
      << std::endl
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
Visit_Package (const PICML::Package & package)
{
  this->Visit_PackageFile_i (package);
}

//
// Visit_PackageFile_i
//
void Stub_Generator::
Visit_PackageFile_i  (const Udm::Object & obj)
{
  // Gather all the necessary elements.
  std::set <PICML::Event> events = Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (events.begin (),
                 events.end (),
                 boost::bind (&PICML::Event::Accept,
                              _1,
                              boost::ref (*this)));

  std::set <PICML::Package> packages = Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&PICML::Package::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Event
//
void Stub_Generator::
Visit_Event (const PICML::Event & ev)
{
  Event_Traits_Generator tg (this->header_, this->export_macro_);
  PICML::Event (ev).Accept (tg);
}

}
