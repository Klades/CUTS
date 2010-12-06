// $Id$

#include "Servant_Source_Generator.h"
#include "Servant_Source_Context_Generator.h"
#include "Servant_Source_Impl_Generator.h"
#include "TCPIP_Ctx.h"
#include "../../lang/cpp/Cpp.h"
#include "../../BE_algorithm.h"

#include "boost/bind.hpp"
#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Servant_Source_Generator
//
Servant_Source_Generator::
Servant_Source_Generator (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~Servant_Source_Generator
//
Servant_Source_Generator::~Servant_Source_Generator (void)
{

}

//
// Visit_RootFolder
//
void Servant_Source_Generator::
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
// Visit_ComponentImplementations
//
void Servant_Source_Generator::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions & folder)
{
  std::set <PICML::File> files = folder.File_children ();

  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&PICML::File::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_File
//
void Servant_Source_Generator::Visit_File (const PICML::File & file)
{
  if (!CUTS_BE::has_component (file))
    return;

  std::string name (file.name ());
  std::string basename = name + "_svnt";

  std::string filename (this->outdir_);
  filename += "/" + CUTS_BE::get_pathname (file, "/", "", "_svnt.cpp");

  // Open the file for writing.
  this->fout_.open (filename.c_str ());

  if (!this->fout_.is_open ())
    return;

  do
  {

    // Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> formatter (this->fout_);

    this->fout_ << CUTS_BE_CPP::single_line_comment ("$Id$")
                << std::endl
                << CUTS_BE_CPP::include (basename)
                << CUTS_BE_CPP::include ("TCPIP_" + name + "C")
                << std::endl
                << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_T")
                << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Events_T")
                << std::endl
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_Connector")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_SPEC")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_Remote_Endpoint")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_Servant_Manager")
                << std::endl;

    // Visit the contents of the file and package.
    this->Visit_FilePackage_i (file);
  } while (0);

  // Close the file.
  this->fout_.close ();
}

//
// Visit_Package
//
void Servant_Source_Generator::
Visit_Package (const PICML::Package & package)
{
  this->Visit_FilePackage_i (package);
}

//
// Visit_FilePackage_i
//
void Servant_Source_Generator::
Visit_FilePackage_i (const Udm::Object & obj)
{
  std::set <PICML::Component> components =
    Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

  std::for_each (components.begin (),
                 components.end (),
                 boost::bind (&PICML::Component::Accept,
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
// Visit_Component
//
void Servant_Source_Generator::
Visit_Component (const PICML::Component & component)
{
  this->component_type_ = component.name ();
  PICML::Component non_const (component);

  // Generate the context for the servant.
  Servant_Source_Context_Generator ctx_gen (this->fout_);
  non_const.Accept (ctx_gen);

  Servant_Source_Impl_Generator impl_gen (this->fout_);
  non_const.Accept (impl_gen);
}

//
// Visit_MonolithprimaryArtifact
//
void Servant_Source_Generator::
Visit_MonolithprimaryArtifact (const PICML::MonolithprimaryArtifact & primary)
{
  PICML::ImplementationArtifactReference ref = primary.dstMonolithprimaryArtifact_end ();
  ref.Accept (*this);
}

//
// Visit_ImplementationArtifactReference
//
void Servant_Source_Generator::
Visit_ImplementationArtifactReference (const PICML::ImplementationArtifactReference & ref)
{
  if (PICML::ComponentServantArtifact::meta != ref.type ())
    return;

  PICML::ComponentServantArtifact artifact = PICML::ComponentServantArtifact::Cast (ref);
  artifact.Accept (*this);
}

//
// Visit_ComponentImplementationArtifact
//
void Servant_Source_Generator::
Visit_ComponentServantArtifact (const PICML::ComponentServantArtifact & artifact)
{
  this->fout_ << artifact.EntryPoint ();
}

}
