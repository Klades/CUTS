// $Id$

#include "Context_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Context_Generator.inl"
#endif

#include "../../lang/cpp/Cpp.h"
#include <algorithm>

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// Visit_Component
//
void Context_Generator::
Visit_Component (const PICML::Component_in component)
{
  std::string name = component->name ();
  std::string scope = CUTS_BE_CPP::scope (component);
  std::string servant = name + "_Servant";
  this->context_ = name + "_Servant_Context";

  this->header_
    << CUTS_BE_CPP::single_line_comment ("Forward decl.")
    << "class " << servant << ";"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("Type definition of the servant type.")
    << "typedef " << this->traits_->ccm_context_template_type ()
    << " < " << std::endl
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

  for (auto port : component->get_OutEventPorts ())
    port->accept (this);

  this->header_
    << "};";
}

//
// Visit_OutEventPort
//
void Context_Generator::
Visit_OutEventPort (const PICML::OutEventPort_in port)
{
  if (port->EventType_is_nil ())
    return;

  PICML::EventType et = port->refers_to_EventType ();

  if (et->meta ()->name () != PICML::Event::impl_type::metaname)
    return;

  PICML::Event ev = et;
  std::string name = port->name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);

  // Write the push method's definition.
  this->header_
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("push method for output ev port: " + name)
    << "virtual void push_" << name << " (" << fq_type << " * ev);"
    << std::endl;

  // Write the push method's implementation.
  this->source_
    << CUTS_BE_CPP::function_header ("push_" + name)
    << "void " << this->context_ << "::" << std::endl
    << "push_" << name << " (" << fq_type << " * ev)"
    << "{"
    << "this->" << name << "_.send_event (ev);"
    << "}";

  if (port->single_destination ())
  {
    // Write the accessor method's definition.
    this->header_
      << "CUTS_CCM_Publisher & writer_" << name << " (void);"
      << std::endl
      << "private:" << std::endl
      << this->traits_->ccm_publisher_template_type ()
      << " < " << fq_type << " > " << name << "_;" << std::endl;

    // Write the accessor method's implementation.
    this->source_
      << CUTS_BE_CPP::function_header ("writer_" + name)
      << "CUTS_CCM_Publisher & "
      << this->context_ << "::" << std::endl
      << "writer_" << name << " (void)"
      << "{"
      << "return this->" << name << "_;"
      << "}";
  }
  else
  {
    // Write the accessor method's definition.
    this->header_
      << "CUTS_CCM_Publisher_Table & writers_" << name << " (void);"
      << std::endl
      << "private:" << std::endl
      << this->traits_->ccm_publisher_table_template_type ()
      << " < " << fq_type << " > " << name << "_;" << std::endl;

    // Write the accessor method's implementation.
    this->source_
      << CUTS_BE_CPP::function_header ("writers_" + name)
      << "CUTS_CCM_Publisher_Table & "
      << this->context_ << "::" << std::endl
      << "writers_" << name << " (void)"
      << "{"
      << "return this->" << name << "_;"
      << "}";
  }
}

}
}
