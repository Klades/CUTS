// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_SOURCE_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_SOURCE_GENERATOR_H_

#include "PICML/PICML.h"
#include <fstream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Servant_Source_Generator
 */
class Servant_Source_Generator : public PICML::Visitor
{
public:
  Servant_Source_Generator (const std::string & outdir);

  virtual ~Servant_Source_Generator (void);

  virtual void Visit_RootFolder (
    const PICML::RootFolder & folder);

  virtual void Visit_InterfaceDefinitions (
    const PICML::InterfaceDefinitions & folder);

  virtual void Visit_File (
    const PICML::File & file);

  virtual void Visit_Package (
    const PICML::Package & package);

  virtual void Visit_Component (
    const PICML::Component & component);

  virtual void Visit_MonolithprimaryArtifact (
    const PICML::MonolithprimaryArtifact & primary);

  virtual void Visit_ImplementationArtifactReference (
    const PICML::ImplementationArtifactReference & ref);

  virtual void Visit_ComponentServantArtifact (
    const PICML::ComponentServantArtifact & artifact);

private:
  void Visit_FilePackage_i (const Udm::Object & obj);

  std::string outdir_;

  std::ofstream fout_;

  std::string monoimpl_;

  std::string component_type_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_SOURCE_GENERATOR_H_
