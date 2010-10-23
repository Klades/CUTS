// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_HEADER_CONTEXT_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_HEADER_CONTEXT_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Servant_Header_Context_Generator
 */
class Servant_Header_Context_Generator : public PICML::Visitor
{
public:
  Servant_Header_Context_Generator (std::ostream & out);

  virtual ~Servant_Header_Context_Generator (void);

  virtual void Visit_Component (const PICML::Component & component);

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port);

  virtual void Visit_RequiredRequestPort (const PICML::RequiredRequestPort & port);

private:
  /// Target output stream.
  std::ostream & out_;
};
}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_HEADER_CONTEXT_GENERATOR_H_
