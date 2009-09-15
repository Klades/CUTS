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

  virtual void Visit_InterfaceDefinitions (
    const CHAOS::InterfaceDefinitions & folder);

  virtual void Visit_File (
    const CHAOS::File & file);

  virtual void Visit_Package (
    const CHAOS::Package & package);

  virtual void Visit_Component (
    const CHAOS::Component & component);

  virtual void Visit_OutEventPort (
    const CHAOS::OutEventPort & port);

  virtual void Visit_InEventPort (
    const CHAOS::InEventPort & port);

private:
  void Visit_FilePackage_i (const Udm::Object & obj);

  std::string outdir_;

  std::ofstream header_;

  std::ofstream source_;

  std::string export_macro_;

  std::string servant_;

  std::string component_;
};

}

#endif  // !defined _CUTS_BE_OPENSPLICE_SERVANT_HEADER_GENERATOR_H_
