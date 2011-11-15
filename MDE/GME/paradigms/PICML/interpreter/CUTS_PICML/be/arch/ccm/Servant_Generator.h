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

#ifndef _CUTS_BE_SERVANT_HEADER_GENERATOR_H_
#define _CUTS_BE_SERVANT_HEADER_GENERATOR_H_

#include "PICML/PICML.h"
#include "Traits.h"

#include <fstream>

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Servant_Generator
 *
 * Custom generic servant generator for the CCM++ implementation.
 */
class CUTS_BE_CCM_Export Servant_Generator : public PICML::Visitor
{
public:
  Servant_Generator (const std::string & outdir, Traits * const traits);

  virtual ~Servant_Generator (void);

  virtual void Visit_RootFolder (
    const PICML::RootFolder & folder);

  virtual void Visit_InterfaceDefinitions (
    const PICML::InterfaceDefinitions &);

  virtual void Visit_File (
    const PICML::File &);

  virtual void Visit_Package (
    const PICML::Package &);

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
  // Visit a File and Package element.
  virtual void Visit_FilePackage_i (const Udm::Object & obj);

  /// The target output directory.
  std::string outdir_;

  /// Pointer to the CCM++ traits.
  Traits * const traits_;

  std::ofstream header_;

  std::ofstream source_;

  std::string export_macro_;

  std::string servant_;

  std::string component_;
};

}
}

#if defined (__CUTS_INLINE__)
#include "Servant_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_RTIDDS_SERVANT_HEADER_GENERATOR_H_
