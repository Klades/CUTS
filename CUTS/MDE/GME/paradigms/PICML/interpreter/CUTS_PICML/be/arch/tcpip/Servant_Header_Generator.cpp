// $Id$

#include "Servant_Header_Generator.h"
#include "TCPIP_Ctx.h"
#include "Servant_Header_Context_Generator.h"
#include "Servant_Header_Impl_Generator.h"
#include "Servant_Header_Include_Generator.h"

#include "../../lang/cpp/Cpp.h"

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
  std::set <PICML::ComponentImplementations> folders = folder.ComponentImplementations_children ();
  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&PICML::ComponentImplementations::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementations
//
void Servant_Header_Generator::
Visit_ComponentImplementations (const PICML::ComponentImplementations & folder)
{
  std::set <PICML::ComponentImplementationContainer> containers =
    folder.ComponentImplementationContainer_children ();

  std::for_each (containers.begin (),
                 containers.end (),
                 boost::bind (&PICML::ComponentImplementationContainer::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementationContainer
//
void Servant_Header_Generator::
Visit_ComponentImplementationContainer (
const PICML::ComponentImplementationContainer & container)
{
  std::set <PICML::MonolithicImplementation> monoimpls =
    container.MonolithicImplementation_kind_children ();

  if (monoimpls.empty ())
    return;

  std::string name = container.name ();

  // Construct the name of the output file.
  std::string basename ("TCPIP_");
  basename += name + "_svnt";

  std::string filename (this->outdir_);
  filename += "/" + basename + ".h";

  // Open the file for writing.
  this->fout_.open (filename.c_str ());

  if (!this->fout_.is_open ())
    return;

  std::string hash_define ("_TCPIP_");
  hash_define += name + "_SVNT_H_";

  std::transform (hash_define.begin (),
                  hash_define.end (),
                  hash_define.begin (),
                  &::toupper);

  do
  {
    // Indentation implanter.
    Indentation::Implanter <Indentation::Cxx, char> formatter (this->fout_);

    std::string corba_filename (container.name ());
    corba_filename += "C";

    std::string export_filename ("TCPIP_");
    export_filename += name + "_svnt_export";

    // Construct the export macro for this file.
    this->export_macro_ = "TCPIP_" + name + "_SVNT";

    std::transform (this->export_macro_.begin (),
                    this->export_macro_.end (),
                    this->export_macro_.begin (),
                    &::toupper);

    this->export_macro_ += "_Export";

    std::string exec_stub (name);
    exec_stub += "EC";

    // Include the header file.
    this->fout_ << CUTS_BE_CPP::single_line_comment ("-*- C++ -*-")
                << std::endl
                << "#ifndef " << hash_define << std::endl
                << "#define " << hash_define << std::endl
                << std::endl;

    Servant_Header_Include_Generator incl_gen (this->fout_);
    PICML::ComponentImplementationContainer (container).Accept (incl_gen);

    this->fout_ << std::endl
                << CUTS_BE_CPP::include (exec_stub)
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

    std::for_each (monoimpls.begin (),
                   monoimpls.end (),
                   boost::bind (&PICML::MonolithicImplementation::Accept,
                                _1,
                                boost::ref (*this)));

    this->fout_ << std::endl
                << "#endif  // !defined " << hash_define << std::endl;

  } while (0);

  // Close the file.
  this->fout_.close ();
}

//
// Visit_MonolithicImplementation
//
void Servant_Header_Generator::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & monoimpl)
{
  this->monoimpl_ = monoimpl.name ();
  this->fout_ << "namespace TCPIP_" << this->monoimpl_
              << "{";

  // Visit the component we are implementing.
  PICML::Implements impl = monoimpl.dstImplements ();

  if (Udm::null != impl)
    impl.Accept (*this);

  this->fout_ << "}"
              << "extern \"C\" " << this->export_macro_ << std::endl
              << "::PortableServer::Servant" << std::endl;

  std::set <PICML::MonolithprimaryArtifact> artifacts =
    monoimpl.dstMonolithprimaryArtifact ();

  std::for_each (artifacts.begin (),
                 artifacts.end (),
                 boost::bind (&PICML::MonolithprimaryArtifact::Accept,
                              _1,
                              boost::ref (*this)));

  this->fout_ << " (const char * name," << std::endl
              << "CUTS_TCPIP_Servant_Manager * svnt_mgr," << std::endl
              << "::Components::EnterpriseComponent_ptr p);";
}

//
// Visit_Implements
//
void Servant_Header_Generator::
Visit_Implements (const PICML::Implements & implements)
{
  PICML::ComponentRef ref = implements.dstImplements_end ();
  ref.Accept (*this);
}

//
// Visit_ComponentRef
//
void Servant_Header_Generator::
Visit_ComponentRef (const PICML::ComponentRef & ref)
{
  PICML::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
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

  Servant_Header_Impl_Generator impl_gen (this->fout_, this->monoimpl_);
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
