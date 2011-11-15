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

#ifndef _CUTS_OPENSPLICE_STUB_GENERATOR_H_
#define _CUTS_OPENSPLICE_STUB_GENERATOR_H_

#include "PICML/PICML.h"
#include <fstream>

namespace CUTS_BE_OpenSplice
{

/**
 * @class Stub_Generator
 */
class Stub_Generator : public PICML::Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       outdir        Target output directory
   */
  Stub_Generator (const std::string & outdir);

  /// Destructor.
  virtual ~Stub_Generator (void);

  /// Visit the RootFolder element.
  virtual void Visit_RootFolder (
    const PICML::RootFolder & folder);

  /// Visit an InterfaceDefinitions folder.
  virtual void Visit_InterfaceDefinitions (
    const PICML::InterfaceDefinitions & files);

  /// Visit a File element.
  virtual void Visit_File (const PICML::File & file);

  /// Visit a Package element.
  virtual void Visit_Package (const PICML::Package & package);

  /// Visit an Event element.
  virtual void Visit_Event (const PICML::Event & ev);

private:
  /// Visit the contents of a package.
  void Visit_PackageFile_i (const Udm::Object & obj);

  /// The target output directory.
  std::string outdir_;

  /// Target output file for the source.
  std::ofstream source_;

  /// Target output file for the header.
  std::ofstream header_;

  /// Export macro for the current file.
  std::string export_macro_;
};

}

#endif  // !defined _CUTS_OPENSPLICE_STUB_GENERATOR_H_
