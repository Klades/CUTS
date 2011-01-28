// $Id$

#include "Stub_Generator.h"
#include "Event_Traits_Generator.h"
#include "../../../arch/ccm/CCM.h"

#include "boost/bind.hpp"
#include "Uml.h"

#include <algorithm>

namespace CUTS_BE_RTIDDS
{
/**
 * Helper visitor that determine what files need to be included
 * based on which files contain events.
 */
class Include_Events : public PICML::Visitor
{
public:
  //
  // Include_Events
  //
  Include_Events (std::ostream & header)
    : header_ (header),
      has_events_ (false)
  {

  }

  //
  // ~Include_Events
  //
  virtual ~Include_Events (void)
  {

  }

  //
  // Visit_File
  //
  virtual void Visit_File (const PICML::File & file)
  {
    this->this_file_ = file;
    this->Visit_PackageFile_i (file);

    //if (this->has_events_)
    //{
    //  // Make sure we include the NDDS support file.
    //  std::string filename ("rtidds/");
    //  filename += std::string (file.name ()) + "Support";

    //  // Include the header file for this source file.
    //  this->header_ << CUTS_BE_CPP::include (filename);
    //}

    this->header_ << CUTS_BE_CPP::include ("cuts/arch/rtidds/RTIDDS_Traits_T");
  }

  //
  // Visit_Package
  //
  virtual void Visit_Package (const PICML::Package & package)
  {
    this->Visit_PackageFile_i (package);
  }

  //
  // Visit_Component
  //
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

  //
  // Visit_InEventPort
  //
  virtual void Visit_InEventPort (const PICML::InEventPort & port)
  {
    PICML::EventType et = port.ref ();

    if (et != Udm::null && et.type () == PICML::Event::meta)
      PICML::Event::Cast (et).Accept (*this);
  }

  //
  // Visit_OutEventPort
  //
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
    PICML::File file = this->get_parent_file (ev);

    if (this->includes_.find (file) == this->includes_.end ())
    {
      // Make sure we do not visit this file again.
      this->includes_.insert (file);

      // Include the CORBA stub file.
      const std::string name = file.name ();
      this->header_ << CUTS_BE_CPP::include (name + "C");

      if (this->this_file_ != file)
      {
        const std::string filename = "RTIDDS_" + name + "C";
        this->header_ << CUTS_BE_CPP::include (filename);
      }

      // Make sure we set the event flag if there is a DDS event
      // in this file.
      if (CUTS_BE_CCM::Cpp::Context::is_dds_event_wrapper (ev))
        this->has_events_ |= true;
    }
  }

private:
  //
  // get_parent_file
  //
  PICML::File get_parent_file (const Udm::Object & obj)
  {
    Udm::Object parent = obj.GetParent ();

    while (parent.type () != PICML::File::meta)
      parent = parent.GetParent ();

    return PICML::File::Cast (parent);
  }

  //
  // Visit_PackageFile_i
  //
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

    // Visit all the components.
    std::vector <PICML::Component> components =
      Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (components.begin (),
                   components.end (),
                   boost::bind (&PICML::Component::Accept,
                                _1,
                                boost::ref (*this)));
  }

  /// Output stream for the header file.
  std::ostream & header_;

  /// Set of include strings.
  std::set <PICML::File> includes_;

  /// Flag that determine if a file has events.
  bool has_events_;

  /// Reference to the current file.
  PICML::File this_file_;
};


//
// Stub_Generator
//
Stub_Generator::Stub_Generator (const std::string & outdir)
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
void Stub_Generator::Visit_File (const PICML::File & file)
{
  // Construct the name of the output file.
  const std::string name = file.name ();
  const std::string basename = "RTIDDS_" + name + "C";

  std::string header_filename = this->outdir_ + "/" + basename + ".h";
  std::string source_filename = this->outdir_ + "/" + basename + ".cpp";

  // Open the file for writing.
  this->source_.open (source_filename.c_str ());
  this->header_.open (header_filename.c_str ());

  if (!this->header_.is_open () && this->source_.is_open ())
    return;

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
      << std::endl;

    Include_Events include_events (this->header_);
    PICML::File (file).Accept (include_events);

    this->header_
      << CUTS_BE_CPP::include (name + "C")
      << std::endl;

    // Locate all the events in the file.
    this->Visit_PackageFile_i (file);

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
void Stub_Generator::Visit_Package (const PICML::Package & package)
{
  this->Visit_PackageFile_i (package);
}

//
// Visit_PackageFile_i
//
void Stub_Generator::Visit_PackageFile_i  (const Udm::Object & obj)
{
  // Gather all the necessary elements.
  std::set <PICML::Event> events = Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);
  std::for_each (events.begin (),
                 events.end (),
                 boost::bind (&PICML::Event::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit the remaining packages.
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
void Stub_Generator::Visit_Event (const PICML::Event & ev)
{
  Event_Traits_Generator traits_generator (this->header_, this->export_macro_);
  PICML::Event (ev).Accept (traits_generator);
}

}
