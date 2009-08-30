// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_SERVANT_HEADER_IMPL_GENERATOR_H_
#define _CUTS_BE_TCPIP_SERVANT_HEADER_IMPL_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Servant_Header_Context_Generator
 */
class Servant_Header_Impl_Generator : public PICML::Visitor
{
public:
  Servant_Header_Impl_Generator (std::ostream & out,
                                 const std::string & export_macro);

  virtual ~Servant_Header_Impl_Generator (void);

  virtual void Visit_Component (const PICML::Component & component);

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port);

  virtual void Visit_InEventPort (const PICML::InEventPort & port);

  virtual void Visit_Attribute (const PICML::Attribute & attr);

  virtual void Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr);

private:
  std::ostream & out_;

  const std::string & export_macro_;

  std::string servant_;
};
}

#endif  // !defined _CUTS_BE_TCPIP_SERVANT_HEADER_CONTEXT_GENERATOR_H_
