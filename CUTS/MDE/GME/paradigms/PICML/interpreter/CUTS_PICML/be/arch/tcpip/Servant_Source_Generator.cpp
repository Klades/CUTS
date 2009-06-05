// $Id$

#include "Servant_Source_Generator.h"
#include "Servant_Source_Context_Generator.h"
#include "Servant_Source_Impl_Generator.h"
#include "TCPIP_Ctx.h"
#include "../../lang/cpp/Cpp.h"
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
void Servant_Source_Generator::
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
void Servant_Source_Generator::
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
  filename += "/" + basename + ".cpp";

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
                << CUTS_BE_CPP::include ("cuts/arch/ccm/CCM_Events_T")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/ccm/TCPIP_CCM_T")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_Connector")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_SPEC")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_Remote_Endpoint")
                << CUTS_BE_CPP::include ("cuts/arch/tcpip/TCPIP_Servant_Manager")
                << std::endl;

    std::for_each (monoimpls.begin (),
                   monoimpls.end (),
                   boost::bind (&PICML::MonolithicImplementation::Accept,
                                _1,
                                boost::ref (*this)));
  } while (0);

  // Close the file.
  this->fout_.close ();
}

//
// Visit_MonolithicImplementation
//
void Servant_Source_Generator::
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
              << "::PortableServer::Servant" << std::endl;

  std::set <PICML::MonolithprimaryArtifact> artifacts =
    monoimpl.dstMonolithprimaryArtifact ();

  std::for_each (artifacts.begin (),
                 artifacts.end (),
                 boost::bind (&PICML::MonolithprimaryArtifact::Accept,
                              _1,
                              boost::ref (*this)));

  this->fout_ << " (const char * name," << std::endl
              << "::Components::EnterpriseComponent_ptr p)"
              << "{"
              << "return ::CUTS_TCPIP::CCM::create_servant <" << std::endl
              << "  ::CIDL_" << this->monoimpl_ << "::"
              << this->component_type_ << "_Exec," << std::endl
              << "  ::TCPIP_" << this->monoimpl_ << "::" << this->component_type_
              << "_Servant > (name, p);"
              << "}"
              << std::endl;
}

//
// Visit_Implements
//
void Servant_Source_Generator::
Visit_Implements (const PICML::Implements & implements)
{
  PICML::ComponentRef ref = implements.dstImplements_end ();
  ref.Accept (*this);
}

//
// Visit_ComponentRef
//
void Servant_Source_Generator::
Visit_ComponentRef (const PICML::ComponentRef & ref)
{
  PICML::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
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

  Servant_Source_Impl_Generator impl_gen (this->fout_, this->monoimpl_);
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
