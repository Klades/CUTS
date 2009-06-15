// -*- C++ -*-

//=============================================================================
/**
 *  @file       Stub_Header_Generator.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TCPIP_STUB_HEADER_GENERATOR_H_
#define _CUTS_BE_TCPIP_STUB_HEADER_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include "boost/bind.hpp"
#include <fstream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Stub_Header_Generator
 *
 * Visitor responsible for generating the stub source file.
 */
class Stub_Header_Generator : public CHAOS::Visitor
{
public:
  Stub_Header_Generator (const std::string & outdir);

  virtual ~Stub_Header_Generator (void);

  virtual void Visit_RootFolder (const CHAOS::RootFolder & folder);

  virtual void Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions & folder);

  virtual void Visit_File (const CHAOS::File & file);

  virtual void Visit_Package (const CHAOS::Package & package);

  virtual void Visit_Event (const CHAOS::Event & event);

  virtual void Visit_Aggregate (const CHAOS::Aggregate & aggr);

  virtual void Visit_Collection (const CHAOS::Collection & coll);

private:
  void Visit_PackageFile_i (const Udm::Object & obj);

  /// Output directory for the files.
  std::string outdir_;

  /// Target output file for the stub source files.
  std::ofstream outfile_;

  /// Export macro for the current file.
  std::string export_macro_;
};
}

#endif  // !defined _CUTS_BE_TCPIP_STUB_HEADER_GENERATOR_H_
