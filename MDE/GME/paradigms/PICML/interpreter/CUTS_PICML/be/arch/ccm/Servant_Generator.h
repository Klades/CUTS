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
#include "PICML/Visitor.h"
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

  virtual void visit_RootFolder (
    PICML::RootFolder_in folder);

  virtual void visit_InterfaceDefinitions (
    PICML::InterfaceDefinitions_in);

  virtual void visit_File (
    PICML::File_in);

  virtual void visit_Package (
    PICML::Package_in);

  virtual void visit_Component (
    PICML::Component_in component);

  virtual void visit_OutEventPort (
    PICML::OutEventPort_in port);

  virtual void visit_InEventPort (
    PICML::InEventPort_in port);

  virtual void visit_Attribute (
    PICML::Attribute_in attr);

  virtual void visit_ReadonlyAttribute (
    PICML::ReadonlyAttribute_in attr);

private:
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
