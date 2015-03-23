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

  virtual void visit_ComponentImplementationContainer (
    PICML::ComponentImplementationContainer_in container);

  virtual void visit_MonolithicImplementation (
    PICML::MonolithicImplementation_in impl);

  virtual void visit_Implements (
    PICML::Implements_in impl);

  virtual void visit_ComponentRef (
    PICML::ComponentRef_in ref);

  virtual void visit_Component (
    PICML::Component_in component);

  virtual void visit_Package (
    PICML::Package_in package);

  virtual void visit_File (
    PICML::File_in file);

private:
  std::ostream & out_;

  std::set <std::string> seen_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_HEADER_INCLUDE_GENERATOR_H_
