// $Id$

#include "Servant_Header_Impl_Generator.h"
#include "TCPIP_Ctx.h"
#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Servant_Header_Impl_Generator
//
Servant_Header_Impl_Generator::
Servant_Header_Impl_Generator (std::ostream & out,
                               const std::string & monoimpl)
: out_ (out),
  monoimpl_ (monoimpl)
{

}

//
// Servant_Header_Impl_Generator
//
Servant_Header_Impl_Generator::~Servant_Header_Impl_Generator (void)
{

}

//
// Visit_Component
//
void Servant_Header_Impl_Generator::
Visit_Component (const PICML::Component & component)
{
  std::string name = component.name ();

  this->servant_ = name + "_Servant";

  std::string context (this->servant_);
  context += "_Context";

  // Write the first part of the this->servant_'s context.
  this->out_ << CUTS_BE_TCPIP_Ctx::single_line_comment ("Type definition of the this->servant_'s base class")
             << "typedef CUTS_TCPIP_CCM_Servant_T < " << std::endl
             << this->servant_ << "," << std::endl
             << context << "," << std::endl
             << "CIDL_" << this->monoimpl_ << "::" << name << "_Exec," << std::endl
             << "::POA_" << CUTS_BE_TCPIP_Ctx::scope (component, "::", false) << name
             << " > " << this->servant_ << "_Base;"
             << std::endl
             << "/**" << std::endl
             << " * @class " << this->servant_ << std::endl
             << " */" << std::endl
             << "class " << this->servant_ << " : public " << this->servant_ << "_Base"
             << "{"
             << "public:" << std::endl
             << CUTS_BE_TCPIP_Ctx::single_line_comment ("default constructor")
             << this->servant_ << " (const char * name, " << std::endl
             << "CUTS_TCPIP_Servant_Manager & svnt_mgr, " << std::endl
             << "CIDL_" << this->monoimpl_ << "::" << name << "_Exec_ptr executor);"
             << std::endl
             << CUTS_BE_TCPIP_Ctx::single_line_comment ("destructor")
             << "virtual ~" << this->servant_ << " (void);"
             << std::endl;

  // Visit all the output event ports.
  std::set <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit all the input event ports.
  std::set <PICML::InEventPort> inputs = component.InEventPort_kind_children ();

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  this->out_ << "};"
             << std::endl;
}

//
// Visit_OutEventPort
//
void Servant_Header_Impl_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::Event event = port.ref ();

  std::string name     = port.name ();
  std::string fq_type  = CUTS_BE_TCPIP_Ctx::fq_type (event);
  std::string consumer = fq_type + "Consumer_ptr";

  if (port.single_destination ())
  {
    this->out_ << "void connect_" << name << " (" << consumer << ");"
               << std::endl
               << consumer << " disconnect_" << name << " (void);"
               << std::endl;
  }
  else
  {
    this->out_ << "::Components::Cookie * subscribe_" << name << " (" << consumer << ");"
               << std::endl
               << consumer << " unsubscribe_" << name << " (::Components::Cookie *);"
               << std::endl;
  }
}

//
// Visit_OutEventPort
//
void Servant_Header_Impl_Generator::
Visit_InEventPort (const PICML::InEventPort & port)
{
  PICML::Event event = port.ref ();

  std::string name     = port.name ();
  std::string fq_type  = CUTS_BE_TCPIP_Ctx::fq_type (event);
  std::string consumer = fq_type + "Consumer_ptr";

  this->out_ << "public:" << std::endl
             << consumer << " get_consumer_" << name << " (void);"
             << std::endl
             << "static int tcpip_" << name << " (" << this->servant_ << " * svnt," << std::endl
             << "CUTS_TCPIP_InputCDR & input);"
             << std::endl
             << "private:" << std::endl
             << "CUTS_TCPIP_CCM_EventConsumer " << name << "_consumer_;"
             << std::endl;
}
}
