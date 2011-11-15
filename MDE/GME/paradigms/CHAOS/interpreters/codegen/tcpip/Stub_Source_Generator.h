// -*- C++ -*-

//=============================================================================
/**
 *  @file       Stub_Source_Generator.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TCPIP_STUB_SOURCE_GENERATOR_H_
#define _CUTS_BE_TCPIP_STUB_SOURCE_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include "boost/bind.hpp"
#include <fstream>

/**
 * @class CUTS_BE_TCPIP_Stub_Source_Generator
 *
 * Visitor responsible for generating the stub source file.
 */
class CUTS_BE_TCPIP_Stub_Source_Generator : public CHAOS::Visitor
{
public:
  CUTS_BE_TCPIP_Stub_Source_Generator (const std::string & outdir);

  virtual ~CUTS_BE_TCPIP_Stub_Source_Generator (void);

  virtual void Visit_RootFolder (const CHAOS::RootFolder & folder);

  virtual void Visit_InterfaceDefinitions (const CHAOS::InterfaceDefinitions & folder);

  virtual void Visit_File (const CHAOS::File & file);

  virtual void Visit_Package (const CHAOS::Package & package);

private:
  void Visit_PackageFile_i (const Udm::Object & obj);

  /// Output directory for the files.
  std::string outdir_;

  /// Target output file for the stub source files.
  std::ofstream outfile_;
};

#endif  // !defined _CUTS_BE_TCPIP_STUB_SOURCE_GENERATOR_H_