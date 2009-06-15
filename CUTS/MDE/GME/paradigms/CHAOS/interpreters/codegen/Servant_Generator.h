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

#ifndef _CUTS_BE_OPENSPLICE_SERVANT_HEADER_GENERATOR_H_
#define _CUTS_BE_OPENSPLICE_SERVANT_HEADER_GENERATOR_H_

#include "../../paradigms/CHAOS.h"
#include <fstream>

namespace CUTS_CHAOS
{
/**
 * @class Servant_Generator
 */
class Servant_Generator : public CHAOS::Visitor
{
public:
  Servant_Generator (const std::string & outdir);

  virtual ~Servant_Generator (void);

  virtual void Visit_RootFolder (
    const CHAOS::RootFolder & folder);

  virtual void Visit_ComponentImplementations (
    const CHAOS::ComponentImplementations & folder);

  virtual void Visit_ComponentImplementationContainer (
    const CHAOS::ComponentImplementationContainer & container);

  virtual void Visit_MonolithicImplementation (
    const CHAOS::MonolithicImplementation & monoimpl);

  virtual void Visit_Implements (
    const CHAOS::Implements & implements);

  virtual void Visit_ComponentRef (
    const CHAOS::ComponentRef & ref);

  virtual void Visit_Component (
    const CHAOS::Component & component);

  virtual void Visit_MonolithprimaryArtifact (
    const CHAOS::MonolithprimaryArtifact & primary);

  virtual void Visit_ImplementationArtifactReference (
    const CHAOS::ImplementationArtifactReference & ref);

  virtual void Visit_ComponentServantArtifact (
    const CHAOS::ComponentServantArtifact & artifact);

  virtual void Visit_OutEventPort (
    const CHAOS::OutEventPort & port);

  virtual void Visit_InEventPort (
    const CHAOS::InEventPort & port);

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

#endif  // !defined _CUTS_BE_OPENSPLICE_SERVANT_HEADER_GENERATOR_H_
