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

#include "PICML/PICML.h"
#include <fstream>

namespace CUTS_BE_OpenSplice
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

  virtual void Visit_InterfaceDefinitions (
    const PICML::InterfaceDefinitions & folder);

  virtual void Visit_File (const PICML::File & file);

  virtual void Visit_Package (const PICML::Package & package);

  virtual void Visit_Component (
    const PICML::Component & component);

  virtual void Visit_OutEventPort (
    const PICML::OutEventPort & port);

  virtual void Visit_InEventPort (
    const PICML::InEventPort & port);

  virtual void Visit_Attribute (
    const PICML::Attribute & attr);

  virtual void Visit_ReadonlyAttribute (
    const PICML::ReadonlyAttribute & attr);

private:
  void Visit_FilePackage_i (const Udm::Object & obj);

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
