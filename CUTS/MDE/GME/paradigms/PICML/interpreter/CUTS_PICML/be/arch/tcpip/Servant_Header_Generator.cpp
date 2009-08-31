// $Id$

#include "Servant_Header_Generator.h"
#include "TCPIP_Ctx.h"
#include "Servant_Header_Context_Generator.h"
#include "Servant_Header_Impl_Generator.h"
#include "Servant_Header_Include_Generator.h"

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
// Servant_Header_Generator
//
Servant_Header_Generator::
Servant_Header_Generator (const std::string & outdir)
: outdir_ (outdir)
{

}

//
// ~Servant_Header_Generator
//
Servant_Header_Generator::~Servant_Header_Generator (void)
{

}

//
// Visit_RootFolder
//
void Servant_Header_Generator::
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
void Servant_Header_Generator::
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
void Servant_Header_Generator::Visit_File (const PICML::File & file)
{
  if (!CUTS_BE::has_component (file))
    return;

  // Construct the name of the output file.
  std::string name (file.name ());
  std::string basename = name + "_svnt";

  std::string filename (this->outdir_);
  filename += "/" + basename + ".h";

  // Open the file for writing.
  this->fout_.open (filename.c_str ());

  if (!this->fout_.is_open ())
    return;

  std::string hash_define ("_");
  hash_define += name + "_SVNT_H_";

  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  do
  {
    // Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> formatter (this->fout_);

    std::string corba_filename (name);
    corba_filename += "C";

    // Construct strings related the export macro.
    std::string export_filename = name + "_svnt_export";
    this->export_macro_ = name + "_SVNT";

    std::transform (this->export_macro_.begin (),
                    this->export_macro_.end (),
                    this->export_macro_.begin (),
                    &::toupper);

    this->export_macro_ += "_Export";

    // Include the header file.
    this->fout_ << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
                << std::endl
                << "#ifndef " << hash_define << std::endl
                << "#define " << hash_define << std::endl
                << std::endl
                << CUTS_BE_CPP::include (name + "EC")
                << CUTS_BE_CPP::include (name + "S")
                << std::endl
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/ccm/TCPIP_CCM_Context_T")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/ccm/TCPIP_CCM_Remote_Endpoint_T")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/ccm/TCPIP_CCM_Servant_T")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/ccm/TCPIP_CCM_Subscriber_Table_T")
                << std::endl
                << CUTS_BE_CPP::include (export_filename)
                << std::endl
                << CUTS_BE_CPP::single_line_comment ("Forward decl.")
                << "class CUTS_TCPIP_Servant_Manager;"
                << std::endl;

    // Visit all the components in this file.
    this->Visit_FilePackage_i (file);

    this->fout_ << std::endl
                << "#endif  // !defined " << hash_define << std::endl;

  } while (0);

  // Close the file.
  this->fout_.close ();
}

//
// Visit_FilePackage_i
//
void Servant_Header_Generator::
Visit_Package (const PICML::Package & package)
{
  this->Visit_FilePackage_i (package);
}

//
// Visit_FilePackage_i
//
void Servant_Header_Generator::
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
void Servant_Header_Generator::
Visit_Component (const PICML::Component & component)
{
  PICML::Component non_const (component);

  // Generate the context for the servant.
  Servant_Header_Context_Generator ctx_gen (this->fout_);
  non_const.Accept (ctx_gen);

  Servant_Header_Impl_Generator impl_gen (this->fout_, this->export_macro_);
  non_const.Accept (impl_gen);
}

//
// Visit_MonolithprimaryArtifact
//
void Servant_Header_Generator::
Visit_MonolithprimaryArtifact (const PICML::MonolithprimaryArtifact & primary)
{
  PICML::ImplementationArtifactReference ref = primary.dstMonolithprimaryArtifact_end ();
  ref.Accept (*this);
}

//
// Visit_ImplementationArtifactReference
//
void Servant_Header_Generator::
Visit_ImplementationArtifactReference (const PICML::ImplementationArtifactReference & ref)
{
  if (PICML::ComponentServantArtifact::meta != ref.type ())
    return;

  PICML::ComponentServantArtifact artifact = PICML::ComponentServantArtifact::Cast (ref);
  artifact.Accept (*this);
}

//
// Visit_ComponentServantArtifact
//
void Servant_Header_Generator::
Visit_ComponentServantArtifact (const PICML::ComponentServantArtifact & artifact)
{
  this->fout_ << artifact.EntryPoint ();
}

}
