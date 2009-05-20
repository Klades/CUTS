// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
class Servant_Header_Include_Generator : public PICML::Visitor
{
public:
  Servant_Header_Include_Generator (std::ostream & out);

  virtual ~Servant_Header_Include_Generator (void);

  virtual void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer & container);

  virtual void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation & impl);

  virtual void Visit_Implements (
    const PICML::Implements & impl);

  virtual void Visit_ComponentRef (
    const PICML::ComponentRef & ref);

  virtual void Visit_Component (
    const PICML::Component & component);

  virtual void Visit_Package (
    const PICML::Package & package);

  virtual void Visit_File (
    const PICML::File & file);

private:
  std::ostream & out_;

  std::set <std::string> seen_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
