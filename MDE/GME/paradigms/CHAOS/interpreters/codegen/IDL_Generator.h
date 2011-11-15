// -*- C++ -*-

//=============================================================================
/**
 * @file          IDL_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_OPENSPLICE_IDL_GENERATOR_H_
#define _CUTS_BE_OPENSPLICE_IDL_GENERATOR_H_

#include <fstream>
#include <map>
#include "../../paradigms/CHAOS.h"
#include "Uml.h"

namespace CUTS_CHAOS
{
/**
 * @class IDL_Generator
 */
class IDL_Generator : public CHAOS::Visitor
{
public:
  IDL_Generator (const std::string & outdir);

  virtual ~IDL_Generator (void);

  virtual void Visit_RootFolder (
    const CHAOS::RootFolder & folder);

  virtual void Visit_InterfaceDefinitions (
    const CHAOS::InterfaceDefinitions &);

  virtual void Visit_File (const CHAOS::File &);

  virtual void Visit_Package (
    const CHAOS::Package & package);

  virtual void Visit_Event (
    const CHAOS::Event & event);

  virtual void Visit_Member (
    const CHAOS::Member & member);

  virtual void Visit_Aggregate (
    const CHAOS::Aggregate & aggr);

private:
  void Visit_PackageFile_i (const Udm::Object & obj);

  /// Target output directory
  std::string outdir_;

  /// Target output for the IDL file.
  std::ofstream idlfile_;

  std::map <Uml::Class, std::string> predefined_types_;
};

}

#endif  // !defined _CUTS_BE_OPENSPLICE_IDL_GENERATOR_H_
