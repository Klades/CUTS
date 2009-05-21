// $Id$

#include "Servant_Source_Context_Generator.h"
#include "TCPIP_Ctx.h"
#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Servant_Source_Context_Generator
//
Servant_Source_Context_Generator::
Servant_Source_Context_Generator (std::ostream & out)
: out_ (out)
{
}

//
// Servant_Source_Context_Generator
//
Servant_Source_Context_Generator::~Servant_Source_Context_Generator (void)
{

}

//
// Visit_Component
//
void Servant_Source_Context_Generator::
Visit_Component (const PICML::Component & component)
{
  std::string name = component.name ();

  std::string servant = name + "_Servant";
  this->context_ = servant + "_Context";

  std::string context_base (this->context_);
  context_base += "_Base";

  // Write the first part of the servant's context.
  this->out_ << this->context_ << "::"
             << this->context_ << " (" << servant << " & parent)" << std::endl
             << ": " << this->context_ << "_Base (parent)"
             << "{"
             << "}"
             << this->context_ << "::~" << this->context_ << " (void)"
             << "{"
             << "}";

  // Visit all the input port for this component.
  std::set <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_OutEventPort
//
void Servant_Source_Context_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  std::string name = port.name ();
  PICML::Event event = port.ref ();

  std::string fq_type = CUTS_BE_TCPIP_Ctx::fq_type (event);

  std::string comment ("push method for output event port: ");
  comment += name;

  this->out_ << "void " << this->context_ << "::push_"
             << name << " (" << fq_type << " * ev)" << std::endl
             << "{"
             << "this->" << port.name () << "_.send_event (ev);"
             << "}";

  if (port.single_destination ())
  {
    this->out_ << "CUTS_TCPIP_CCM_Remote_Endpoint & "
               << this->context_ << "::endpoint_" << name << " (void)"
               << "{"
               << "return this->" << name << "_;"
               << "}";
  }
  else
  {
    this->out_ << "CUTS_TCPIP_CCM_Subscriber_Table & "
               << this->context_ << "::endpoints_" << name << " (void)"
               << "{"
               << "return this->" << name << "_;"
               << "}";
  }
}
}
