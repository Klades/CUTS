// $Id$

#include "Servant_Source_Context_Generator.h"
#include "TCPIP_Ctx.h"

#include "../../../lang/cpp/Cpp.h"

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

  // Visit all output events for this component.
  std::set <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();
  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit all the facets for this component.
  std::set <PICML::RequiredRequestPort> receptacles = component.RequiredRequestPort_kind_children ();
  std::for_each (receptacles.begin (),
                 receptacles.end (),
                 boost::bind (&PICML::RequiredRequestPort::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_OutEventPort
//
void Servant_Source_Context_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  PICML::Event ev = PICML::Event::Cast (et);
  std::string name = port.name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  this->out_ << CUTS_BE_CPP::function_header ("push_" + name)
             << "void " << this->context_ << "::push_"
             << name << " (" << fq_type << " * ev)" << std::endl
             << "{"
             << "this->" << port.name () << "_.send_event (ev);"
             << "}";

  if (port.single_destination ())
  {
    this->out_ << CUTS_BE_CPP::function_header ("endpoint_" + name)
               << "CUTS_TCPIP_CCM_Publisher & "
               << this->context_ << "::endpoint_" << name << " (void)"
               << "{"
               << "return this->" << name << "_;"
               << "}";
  }
  else
  {
    this->out_ << CUTS_BE_CPP::function_header ("endpoints_" + name)
               << "CUTS_TCPIP_CCM_Publisher_Table & "
               << this->context_ << "::endpoints_" << name << " (void)"
               << "{"
               << "return this->" << name << "_;"
               << "}";
  }
}

//
// Visit_OutEventPort
//
void Servant_Source_Context_Generator::
Visit_RequiredRequestPort (const PICML::RequiredRequestPort & port)
{
  PICML::Object obj = PICML::Object::Cast (port.ref ());

  if (obj == Udm::null || obj.type () != PICML::Object::meta)
    return;

  std::string name = port.name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (obj);
  std::string function = "get_connection_" + name;

  this->out_ << CUTS_BE_CPP::function_header (function)
             << fq_type << "_ptr " << this->context_
             << "::" << function << " (void)" << std::endl
             << "{"
             << "return " << fq_type << "::_nil ();"
             << "}";
}

}
