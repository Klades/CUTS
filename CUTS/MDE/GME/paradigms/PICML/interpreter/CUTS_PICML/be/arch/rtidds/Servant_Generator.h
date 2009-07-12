// -*- C++ -*-

//=============================================================================
/**
 * @file        Servant_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_RTIDDS_SERVANT_HEADER_GENERATOR_H_
#define _CUTS_BE_RTIDDS_SERVANT_HEADER_GENERATOR_H_

#include "PICML/PICML.h"
#include <fstream>

namespace CUTS_BE_RTIDDS
{
/**
 * @class Servant_Generator
 */
class Servant_Generator : public PICML::Visitor
{
public:
  Servant_Generator (const std::string & outdir);

  virtual ~Servant_Generator (void);

  virtual void Visit_RootFolder (
    const PICML::RootFolder & folder);

  virtual void Visit_ComponentImplementations (
    const PICML::ComponentImplementations & folder);

  virtual void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer & container);

  virtual void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation & monoimpl);

  virtual void Visit_Implements (
    const PICML::Implements & implements);

  virtual void Visit_ComponentRef (
    const PICML::ComponentRef & ref);

  virtual void Visit_Component (
    const PICML::Component & component);

  virtual void Visit_MonolithprimaryArtifact (
    const PICML::MonolithprimaryArtifact & primary);

  virtual void Visit_ImplementationArtifactReference (
    const PICML::ImplementationArtifactReference & ref);

  virtual void Visit_ComponentServantArtifact (
    const PICML::ComponentServantArtifact & artifact);

  virtual void Visit_OutEventPort (
    const PICML::OutEventPort & port);

  virtual void Visit_InEventPort (
    const PICML::InEventPort & port);

private:
  std::string outdir_;

  std::ofstream header_;

  std::ofstream source_;

  std::string export_macro_;

  std::string monoimpl_;

  std::string servant_;

  std::string component_;
};

}

#endif  // !defined _CUTS_BE_RTIDDS_SERVANT_HEADER_GENERATOR_H_
