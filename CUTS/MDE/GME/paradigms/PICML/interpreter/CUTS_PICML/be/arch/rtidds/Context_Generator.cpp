// $Id$

#include "Context_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_RTIDDS
{
//
// Context_Generator
//
Context_Generator::
Context_Generator (std::ostream & header, std::ostream & source)
: header_ (header),
  source_ (source)
{

}

//
// ~Context_Generator
//
Context_Generator::~Context_Generator (void)
{

}

//
// ~Context_Generator
//
const std::string & Context_Generator::context (void) const
{
  return this->context_;
}

//
// Visit_Component
//
void Context_Generator::
Visit_Component (const PICML::Component & component)
{
  std::string name = component.name ();
  std::string scope = CUTS_BE_CPP::scope (component);
  std::string servant = name + "_Servant";
  this->context_ = name + "_Servant_Context";

  this->header_
    << CUTS_BE_CPP::single_line_comment ("Forward decl.")
    << "class " << servant << ";"
    << std::endl
    << "typedef CUTS_CCM_Context_T < " << std::endl
    << scope << "CCM_" << name << "_Context, " << std::endl
    << servant << " > " << this->context_ << "_Base;"
    << std::endl
    << "class " << this->context_ << " : "
    << "public " << this->context_ << "_Base"
    << "{"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("Initializing constructor")
    << this->context_ << " (" << servant << " & parent);"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("Destructor")
    << "virtual ~" << this->context_ << " (void);"
    << std::endl;

  this->source_
    << CUTS_BE_CPP::function_header (this->context_)
    << this->context_ << "::" << this->context_ << " (" << servant << " & parent)" << std::endl
    << " : " << this->context_ << "_Base (parent)"
    << "{"
    << "}"
    << CUTS_BE_CPP::function_header ("~" + this->context_)
    << this->context_ << "::~" << this->context_ << " (void)"
    << "{"
    << "}";

  std::vector <PICML::OutEventPort> ports = component.OutEventPort_kind_children ();
  std::for_each (ports.begin (),
                 ports.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  this->header_
    << "};";
}

//
// Visit_OutEventPort
//
void Context_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  std::string name = port.name ();
  PICML::Event event = port.ref ();
  std::string fq_type = CUTS_BE_CPP::fq_type (event);

  this->header_
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("push method for output event port: " + name)
    << "virtual void push_" << name << " (" << fq_type << " * ev);"
    << std::endl;

  this->source_
    << CUTS_BE_CPP::function_header ("push_" + name)
    << "void " << this->context_ << "::" << std::endl
    << "push_" << name << " (" << fq_type << " * ev)"
    << "{"
    << "this->" << name << "_.send_event (ev);"
    << "}";

  if (port.single_destination ())
  {
    this->header_
      << "CUTS_RTIDDS_CCM_Subscriber & writer_" << name << " (void);"
      << std::endl
      << "private:" << std::endl
      << "CUTS_RTIDDS_CCM_Subscriber_T < ::CUTS_NDDS"
      << fq_type << " > " << name << "_;" << std::endl;

    this->source_
      << CUTS_BE_CPP::function_header ("writer_" + name)
      << "CUTS_RTIDDS_CCM_Subscriber & "
      << this->context_ << "::" << std::endl
      << "writer_" << name << " (void)"
      << "{"
      << "return this->" << name << "_;"
      << "}";
  }
  else
  {
    this->header_
      << "CUTS_CCM_Subscriber_Table & writers_" << name << " (void);"
      << std::endl
      << "private:" << std::endl
      << "CUTS_RTIDDS_CCM_Subscriber_Table_T < ::CUTS_NDDS"
      << fq_type << " > " << name << "_;" << std::endl;

    this->source_
      << CUTS_BE_CPP::function_header ("writers_" + name)
      << "CUTS_CCM_Subscriber_Table & "
      << this->context_ << "::" << std::endl
      << "writers_" << name << " (void)"
      << "{"
      << "return this->" << name << "_;"
      << "}";
  }
}

}
