// $Id$

#include "Servant_Header_Context_Generator.h"
#include "TCPIP_Ctx.h"

#include "../../lang/cpp/Cpp.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Servant_Header_Context_Generator
//
Servant_Header_Context_Generator::
Servant_Header_Context_Generator (std::ostream & out)
: out_ (out)
{
}

//
// Servant_Header_Context_Generator
//
Servant_Header_Context_Generator::~Servant_Header_Context_Generator (void)
{

}

//
// Visit_Component
//
void Servant_Header_Context_Generator::
Visit_Component (const PICML::Component & component)
{
  std::string name = component.name ();

  std::string servant (name);
  servant += "_Servant";

  std::string servant_base (servant);
  servant_base += "_Base";

  std::string context (servant);
  context += "_Context";

  std::string context_base (context);
  context_base += "_Base";

  // Write the first part of the servant's context.
  this->out_ << CUTS_BE_CPP::single_line_comment ("Forward decl.")
             << "class " << servant << ";"
             << std::endl
             << "typedef CUTS_TCPIP_CCM_Context_T < "
             << CUTS_BE_CPP::scope(component)
             << "CCM_" << name << "_Context, "
             << servant << " > " << context_base << ";"
             << std::endl
             << "/**" << std::endl
             << " * @class " << context << std::endl
             << " */" << std::endl
             << "class " << context << " : public "
             << context_base
             << "{"
             << "public:" << std::endl
             << CUTS_BE_CPP::single_line_comment ("default constructor")
             << context << " (" << servant << " & parent);"
             << std::endl
             << CUTS_BE_CPP::single_line_comment ("destructor")
             << "virtual ~" << context << " (void);"
             << std::endl;

  // Visit all the input port for this component.
  std::set <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();
  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  std::set <PICML::RequiredRequestPort> receptacles = component.RequiredRequestPort_kind_children ();
  std::for_each (receptacles.begin (),
                 receptacles.end (),
                 boost::bind (&PICML::RequiredRequestPort::Accept,
                              _1,
                              boost::ref (*this)));

  this->out_ << "};"
             << std::endl;
}

//
// Visit_OutEventPort
//
void Servant_Header_Context_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  PICML::Event ev = PICML::Event::Cast (et);
  std::string name = port.name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  std::string comment ("push method for output ev port: ");
  comment += name;

  this->out_ << "public:" << std::endl
             << CUTS_BE_CPP::single_line_comment (comment)
             << "virtual void push_" << name << " (" << fq_type << " * ev);"
             << std::endl;

  if (port.single_destination ())
  {
    this->out_ << "CUTS_TCPIP_CCM_Remote_Endpoint & endpoint_" << name << " (void);"
               << std::endl
               << "private:" << std::endl
               << "CUTS_TCPIP_CCM_Remote_Endpoint_T < "
               << fq_type << " > " << name << "_;"
               << std::endl;
  }
  else
  {
    this->out_ << "CUTS_TCPIP_CCM_Subscriber_Table & endpoints_" << name << " (void);"
               << std::endl
               << "private:" << std::endl
               << "CUTS_TCPIP_CCM_Subscriber_Table_T < "
               << fq_type << " > " << name << "_;"
               << std::endl;
  }
}

//
// Visit_RequiredRequestPort
//
void Servant_Header_Context_Generator::
Visit_RequiredRequestPort (const PICML::RequiredRequestPort & port)
{
  PICML::Object obj = PICML::Object::Cast (port.ref ());
  const std::string fq_type = CUTS_BE_CPP::fq_type (obj);
  const std::string name = port.name ();

  this->out_
    << "virtual " << fq_type << "_ptr get_connection_" << name << " (void);"
    << std::endl;
}


}
