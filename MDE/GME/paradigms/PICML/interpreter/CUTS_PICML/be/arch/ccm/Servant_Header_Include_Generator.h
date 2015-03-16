// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_

#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include <ostream>
#include <set>

namespace CUTS_BE_OpenSplice
{
class Servant_Header_Include_Generator : public PICML::Visitor
{
public:
  Servant_Header_Include_Generator (std::ostream & out);

  virtual ~Servant_Header_Include_Generator (void);

  virtual void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer_in container);

  virtual void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation_in impl);

  virtual void Visit_Implements (
    const PICML::Implements_in impl);

  virtual void Visit_ComponentRef (
    const PICML::ComponentRef_in ref);

  virtual void Visit_Component (
    const PICML::Component_in component);

  virtual void Visit_Package (
    const PICML::Package_in package);

  virtual void Visit_File (
    const PICML::File_in file);

private:
  std::ostream & out_;

  std::set <std::string> seen_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
