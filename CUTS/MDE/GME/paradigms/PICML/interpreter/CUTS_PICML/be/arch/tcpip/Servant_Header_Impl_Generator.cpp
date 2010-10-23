// $Id$

#include "Servant_Header_Impl_Generator.h"
#include "TCPIP_Ctx.h"

#include "../ccm/Component_Implementation.h"
#include "../../lang/cpp/Cpp.h"
#include "../../UDM_Utility_T.h"

#include "boost/bind.hpp"
#include "boost/iterator/filter_iterator.hpp"

#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Servant_Header_Impl_Generator
//
Servant_Header_Impl_Generator::
Servant_Header_Impl_Generator (std::ostream & out,
                               const std::string & export_macro)
: out_ (out),
  export_macro_ (export_macro)
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
  std::string name (component.name ());
  this->servant_ = name + "_Servant";

  std::string context (this->servant_);
  context += "_Context";

  // Write the first part of the this->servant_'s context.
  this->out_ << CUTS_BE_CPP::single_line_comment ("Type definition of the this->servant_'s base class")
             << "typedef CUTS_TCPIP_CCM_Servant_T < " << std::endl
             << "  " << this->servant_ << "," << std::endl
             << "  " << context << "," << std::endl
             << "  CIAO_" << CUTS_BE_CPP::fq_type (component, "_", false) << "_Impl::" << name << "_Exec," << std::endl
             << "  ::POA_" << CUTS_BE_CPP::scope (component, "::", false) << name
             << " > " << this->servant_ << "_Base;"
             << std::endl
             << "/**" << std::endl
             << " * @class " << this->servant_ << std::endl
             << " */" << std::endl
             << "class " << this->servant_ << " : public " << this->servant_ << "_Base"
             << "{"
             << "public:" << std::endl
             << CUTS_BE_CPP::single_line_comment ("default constructor")
             << this->servant_ << " (const char * name, executor_type::_ptr_type executor);"
             << std::endl
             << CUTS_BE_CPP::single_line_comment ("destructor")
             << "virtual ~" << this->servant_ << " (void);"
             << std::endl;

  // Visit all the output ev ports.
  std::set <PICML::OutEventPort> outputs = component.OutEventPort_kind_children ();
  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit all the input ev ports.
  std::set <PICML::InEventPort> inputs = component.InEventPort_kind_children ();
  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  this->out_ << "public:" << std::endl;

  // Visit all the Attribute elements of the <component>.
  typedef std::vector <PICML::Attribute> Attribute_Set;
  Attribute_Set attrs = component.Attribute_kind_children ();

  std::for_each (attrs.begin (),
                 attrs.end (),
                 boost::bind (&PICML::Attribute::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit all the ReadonlyAttribute elements of the <component>.
  typedef std::vector <PICML::ReadonlyAttribute> ReadonlyAttribute_Set;
  ReadonlyAttribute_Set ro_attrs = component.ReadonlyAttribute_kind_children ();

  typedef is_type <PICML::ReadonlyAttribute> ReadonlyAttribute_Type;

  std::for_each (boost::make_filter_iterator <ReadonlyAttribute_Type> (ro_attrs.begin (), ro_attrs.end ()),
                 boost::make_filter_iterator <ReadonlyAttribute_Type> (ro_attrs.end (), ro_attrs.end ()),
                 boost::bind (&PICML::ReadonlyAttribute::Accept, _1, boost::ref (*this)));

  this->out_ << "};"
             << "extern \"C\" " << this->export_macro_ << std::endl
             << "::PortableServer::Servant " << std::endl
             << "create_" << CUTS_BE_CPP::fq_type (component, "_", false)
             << "_Servant (const char *, ::Components::EnterpriseComponent_ptr);"
             << std::endl;
}

//
// Visit_OutEventPort
//
void Servant_Header_Impl_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::EventType et = port.ref ();

  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  PICML::Event ev = PICML::Event::Cast (et);
  std::string name     = port.name ();
  std::string fq_type  = CUTS_BE_CPP::fq_type (ev);
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
  PICML::EventType et = port.ref ();

  if (et == Udm::null || et.type () != PICML::Event::meta)
    return;

  PICML::Event ev = PICML::Event::Cast (et);
  std::string name = port.name ();
  std::string fq_type = CUTS_BE_CPP::fq_type (ev);
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

//
// Visit_ReadonlyAttribute
//
void Servant_Header_Impl_Generator::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();
  std::string name (attr.name ());

  this->out_ << "virtual ";

  CUTS_BE_CCM::Cpp::Retn_Type_Generator retn_type_gen (this->out_);
  retn_type_gen.generate (type);

  this->out_ << " " << name << " (void);" << std::endl;
}

//
// Visit_Attribute
//
void Servant_Header_Impl_Generator::
Visit_Attribute (const PICML::Attribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();
  std::string name (attr.name ());

  this->out_ << "virtual void " << name << " (";

  CUTS_BE_CCM::Cpp::In_Type_Generator in_type_gen (this->out_);
  in_type_gen.generate (type);

  this->out_ << " " << name << ");" << std::endl;

  // Finally, write the readonly attribute method.
  PICML::ReadonlyAttribute readonly (attr);
  readonly.Accept (*this);
}

}
