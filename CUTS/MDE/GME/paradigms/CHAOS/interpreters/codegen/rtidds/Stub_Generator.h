// -*- C++ -*-

//=============================================================================
/**
 * @file          Stub_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CHAOS_RTIDDS_STUB_GENERATOR_H_
#define _CUTS_CHAOS_RTIDDS_STUB_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include <fstream>

namespace CUTS_CHAOS
{
namespace RTIDDS
{
/**
 * @class Stub_Generator
 */
class Stub_Generator : public CHAOS::Visitor
{
public:
  Stub_Generator (const std::string & outdir);

  virtual ~Stub_Generator (void);

  virtual void Visit_RootFolder (
    const CHAOS::RootFolder & folder);

  virtual void Visit_InterfaceDefinitions (
    const CHAOS::InterfaceDefinitions & files);

  virtual void Visit_File (const CHAOS::File & file);

  virtual void Visit_Package (const CHAOS::Package & package);

  virtual void Visit_Event (const CHAOS::Event & event);

  virtual void Visit_Aggregate (const CHAOS::Aggregate & aggr);

private:
  void Visit_PackageFile_i (const Udm::Object & obj);

  /// The target output directory.
  std::string outdir_;

  /// Target output file for the source.
  std::ofstream source_;

  /// Target output file for the header.
  std::ofstream header_;

  /// Export macro for the current file.
  std::string export_macro_;

  std::set <CHAOS::Event> events_;
};

}
}

#endif  // !defined _CUTS_CHAOS_RTIDDS_STUB_GENERATOR_H_
