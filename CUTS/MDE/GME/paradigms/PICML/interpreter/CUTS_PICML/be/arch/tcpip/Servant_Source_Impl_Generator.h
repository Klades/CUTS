// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_SOURCE_IMPL_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_SOURCE_IMPL_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Servant_Source_Impl_Generator
 */
class Servant_Source_Impl_Generator : public PICML::Visitor
{
public:
  Servant_Source_Impl_Generator (std::ostream & out,
                                 const std::string & monoimpl);

  virtual ~Servant_Source_Impl_Generator (void);

  virtual void Visit_Component (const PICML::Component & component);

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port);

  virtual void Visit_InEventPort (const PICML::InEventPort & port);

  virtual void Visit_Attribute (const PICML::Attribute & attr);

  virtual void Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr);

private:
  std::ostream & out_;

  std::string monoimpl_;

  std::string servant_;
};
}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_SOURCE_IMPL_GENERATOR_H_
