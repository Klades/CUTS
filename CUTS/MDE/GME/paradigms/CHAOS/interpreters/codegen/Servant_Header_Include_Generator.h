// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_

#include "../../paradigms/CHAOS.h"
#include <ostream>

namespace CUTS_CHAOS
{
class Servant_Header_Include_Generator : public CHAOS::Visitor
{
public:
  Servant_Header_Include_Generator (std::ostream & out);

  virtual ~Servant_Header_Include_Generator (void);

  virtual void Visit_ComponentImplementationContainer (
    const CHAOS::ComponentImplementationContainer & container);

  virtual void Visit_MonolithicImplementation (
    const CHAOS::MonolithicImplementation & impl);

  virtual void Visit_Implements (
    const CHAOS::Implements & impl);

  virtual void Visit_ComponentRef (
    const CHAOS::ComponentRef & ref);

  virtual void Visit_Component (
    const CHAOS::Component & component);

  virtual void Visit_Package (
    const CHAOS::Package & package);

  virtual void Visit_File (
    const CHAOS::File & file);

private:
  std::ostream & out_;

  std::set <std::string> seen_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
