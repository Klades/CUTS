// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_SOURCE_CONTEXT_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_SOURCE_CONTEXT_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Servant_Source_Context_Generator
 */
class Servant_Source_Context_Generator : public PICML::Visitor
{
public:
  Servant_Source_Context_Generator (std::ostream & out);

  virtual ~Servant_Source_Context_Generator (void);

  virtual void Visit_Component (const PICML::Component & component);

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port);

private:
  std::ostream & out_;

  std::string context_;
};
}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_SOURCE_CONTEXT_GENERATOR_H_
