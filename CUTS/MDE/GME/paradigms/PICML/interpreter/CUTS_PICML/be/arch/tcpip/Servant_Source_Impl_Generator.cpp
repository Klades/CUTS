// $Id$

#include "Servant_Source_Impl_Generator.h"
#include "TCPIP_Ctx.h"

#include "../ccm/Component_Implementation.h"
#include "../../lang/cpp/Cpp.h"
#include "../../UDM_Utility_T.h"

#include "boost/bind.hpp"
#include "boost/iterator/filter_iterator.hpp"

#include <algorithm>

namespace CUTS_BE_TCPIP
{
/**
 * @class Base_Member_Init_Generator
 */
class Base_Member_Init_Generator : public PICML::Visitor
{
public:
  Base_Member_Init_Generator (std::ostream & out)
    : out_ (out),
      index_ (0)
  {

  }

  virtual ~Base_Member_Init_Generator (void)
  {

  }

  virtual void Visit_InEventPort (const PICML::InEventPort & port)
  {
    this->out_ << "," << std::endl
               << "  " << port.name ()
               << "_consumer_ (this, " << this->index_ << ")";

    ++ this->index_;
  }

private:
  std::ostream & out_;

  size_t index_;
};

/**
 * @class Virtual_Table_Init_Generator
 */
class Virtual_Table_Init_Generator : public PICML::Visitor
{
public:
  Virtual_Table_Init_Generator (std::ostream & out, const std::string & servant)
    : out_ (out),
      servant_ (servant),
      index_ (0)
  {

  }

  virtual ~Virtual_Table_Init_Generator (void)
  {

  }

  virtual void Visit_InEventPort (const PICML::InEventPort & port)
  {
    this->out_ << this->servant_ << "::table_["
               << this->index_ << "] = &" << this->servant_
               << "::tcpip_" << port.name () << ";";

    ++ this->index_;
  }

private:
  std::ostream & out_;

  const std::string & servant_;

  size_t index_;
};

/**
 * @class Consumer_Table_Init_Generator
 */
class Consumer_Table_Init_Generator : public PICML::Visitor
{
public:
  Consumer_Table_Init_Generator (std::ostream & out)
    : out_ (out)
  {

  }

  virtual ~Consumer_Table_Init_Generator (void)
  {

  }

  virtual void Visit_InEventPort (const PICML::InEventPort & port)
  {
    std::string name = port.name ();

    this->out_ << "this->consumers_.bind (\"" << name
               << "\", &this->" << name << "_consumer_);";
  }

private:
  std::ostream & out_;
};

/**
 * @class Output_Table_Init_Generator
 */
class Output_Table_Init_Generator : public PICML::Visitor
{
public:
  Output_Table_Init_Generator (std::ostream & out)
    : out_ (out)
  {

  }

  virtual ~Output_Table_Init_Generator (void)
  {

  }

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port)
  {
    std::string name = port.name ();

    if (port.single_destination ())
    {
      this->out_ << "this->emits_.bind (\"" << name
                 << "\", &this->ctx_->endpoint_" << name << " ());";
    }
    else
    {
      this->out_ << "this->publishes_.bind (\"" << name
                 << "\", &this->ctx_->endpoints_" << name << " ());";
    }
  }

private:
  std::ostream & out_;
};


//
// Servant_Source_Impl_Generator
//
Servant_Source_Impl_Generator::
Servant_Source_Impl_Generator (std::ostream & out,
                               const std::string & monoimpl)
: out_ (out),
  monoimpl_ (monoimpl)
{

}

//
// Servant_Source_Impl_Generator
//
Servant_Source_Impl_Generator::~Servant_Source_Impl_Generator (void)
{

}

//
// Visit_Component
//
void Servant_Source_Impl_Generator::
Visit_Component (const PICML::Component & component)
{
  std::set <PICML::OutEventPort> outputs =
    component.OutEventPort_kind_children ();

  std::vector <PICML::InEventPort> inputs =
    component.InEventPort_kind_children_sorted (Sorted_By_Name <PICML::InEventPort> ());

  std::string name = component.name ();
  this->servant_ = name + "_Servant";

  std::string context (this->servant_);
  context += "_Context";

  // Write the first part of the this->servant_'s context.
  this->out_ << CUTS_BE_CPP::function_header (this->servant_)
             << this->servant_ << "::" << std::endl
             << this->servant_
             << " (const char * name," << std::endl
             << "::CIDL_" << this->monoimpl_ << "::" << name << "_Exec_ptr executor)" << std::endl
             << ": " << this->servant_ << "_Base (name, executor)";

  Base_Member_Init_Generator base_member (this->out_);
  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (base_member)));

  this->out_ << "{"
             << CUTS_BE_CPP::single_line_comment ("Initializing the consumer table.");

  Consumer_Table_Init_Generator consumer_init_generator (this->out_);
  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (consumer_init_generator)));

  this->out_ << std::endl
             << CUTS_BE_CPP::single_line_comment ("Initializing the publishes/emits table.");

  Output_Table_Init_Generator output_init_generator (this->out_);

  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (output_init_generator)));


  this->out_ << std::endl
             << CUTS_BE_CPP::single_line_comment ("Guard the initialization of the virtual table.")
             << "vtable_type::init_guard_type guard (" << this->servant_ << "::table_, "
             << inputs.size () << ");"
             << std::endl
             << "if (" << this->servant_ << "::table_.is_init ())" << std::endl
             << "  return;"
             << std::endl;

  Virtual_Table_Init_Generator vtable_gen (this->out_, this->servant_);

  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (vtable_gen)));

  this->out_ << "}"
             << CUTS_BE_CPP::function_header ("~" + this->servant_)
             << this->servant_ << "::~" << this->servant_ << " (void)"
             << "{"
             << "}";

  // Visit all the output event ports.
  std::for_each (outputs.begin (),
                 outputs.end (),
                 boost::bind (&PICML::OutEventPort::Accept,
                              _1,
                              boost::ref (*this)));

  // Visit all the input event ports.
  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&PICML::InEventPort::Accept,
                              _1,
                              boost::ref (*this)));

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
}

//
// Visit_OutEventPort
//
void Servant_Source_Impl_Generator::
Visit_OutEventPort (const PICML::OutEventPort & port)
{
  PICML::Event event = port.ref ();

  std::string name     = port.name ();
  std::string fq_type  = CUTS_BE_CPP::fq_type (event);
  std::string consumer = fq_type + "Consumer_ptr";

  if (port.single_destination ())
  {
    this->out_ << CUTS_BE_CPP::function_header ("connect_" + name)
               << "void " << this->servant_ << "::" << std::endl
               << "connect_" << name << " (" << consumer << ")"
               << "{"
               << "throw ::CORBA::NO_IMPLEMENT ();"
               << "}"
               << CUTS_BE_CPP::function_header ("disconnect_" + name)
               << consumer << " " << this->servant_ << "::" << std::endl
               << "disconnect_" << name << " (void)"
               << "{"
               << "throw ::CORBA::NO_IMPLEMENT ();"
               << "}";
  }
  else
  {
    this->out_ << CUTS_BE_CPP::function_header ("subscribe_" + name)
               << "::Components::Cookie * " << this->servant_ << "::" << std::endl
               << "subscribe_" << name << " (" << consumer << ")"
               << "{"
               << "throw ::CORBA::NO_IMPLEMENT ();"
               << "}"
               << CUTS_BE_CPP::function_header ("unsubscribe_" + name)
               << consumer << " " << this->servant_ << "::" << std::endl
               << "unsubscribe_" << name << " (::Components::Cookie *)"
               << "{"
               << "throw ::CORBA::NO_IMPLEMENT ();"
               << "}";
  }
}

//
// Visit_OutEventPort
//
void Servant_Source_Impl_Generator::
Visit_InEventPort (const PICML::InEventPort & port)
{
  PICML::Event event = port.ref ();

  std::string name     = port.name ();
  std::string fq_type  = CUTS_BE_CPP::fq_type (event);
  std::string obv_type = "::OBV_" + CUTS_BE_CPP::fq_type (event, "::", false);
  std::string consumer = fq_type + "Consumer_ptr";

  this->out_ << CUTS_BE_CPP::function_header ("get_consumer_" + name)
             << consumer << " " << this->servant_ << "::" << std::endl
             << "get_consumer_" << name << " (void)"
             << "{"
             << "throw ::CORBA::NO_IMPLEMENT ();"
             << "}"
             << CUTS_BE_CPP::function_header ("tcpip_" + name)
             << "int " << this->servant_ << "::" << std::endl
             << "tcpip_" << name
             << " (" << this->servant_ << " * svnt, CUTS_TCPIP_InputCDR & stream)"
             << "{"
             << CUTS_BE_CPP::single_line_comment ("Extract the event from the stream.")
             << "CUTS_CCM_Event_T < " << obv_type << " > event;"
             << std::endl
             << "if (!(stream >> *event.in ()))"
             << "{"
             << "ACE_ERROR_RETURN ((LM_ERROR," << std::endl
             << "ACE_TEXT (\"%T (%t) - %M - failed to extract %s from stream\\n\")," << std::endl
             << "ACE_TEXT (\"" << fq_type << "\"))," << std::endl
             << "-1);"
             << "}"
             << CUTS_BE_CPP::single_line_comment ("Push the message to the implementation.")
             << "if (svnt->impl_)" << std::endl
             << "  svnt->impl_->push_" << name << " (event.in ());"
             << std::endl
             << "return 0;"
             << "}"
             << std::endl;
}

//
// Visit_ReadonlyAttribute
//
void Servant_Source_Impl_Generator::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();
  std::string name (attr.name ());

  CUTS_BE_CCM::Cpp::Retn_Type_Generator retn_type_gen (this->out_);
  retn_type_gen.generate (type);

  this->out_ << " " << this->servant_ << "::"
             << name << " (void)"
             << "{"
             << "if (this->impl_)" << std::endl
             << "  return this->impl_->" << name << " ();"
             << "else" << std::endl
             << "  throw ::CORBA::INTERNAL ();"
             << "}";
}

//
// Visit_Attribute
//
void Servant_Source_Impl_Generator::
Visit_Attribute (const PICML::Attribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  PICML::MemberType type = member.ref ();
  std::string name (attr.name ());

  this->out_ << "void " << this->servant_ << "::" << name << " (";

  CUTS_BE_CCM::Cpp::In_Type_Generator in_type_gen (this->out_);
  in_type_gen.generate (type);

  this->out_ << " " << name << ")"
             << "{"
             << "if (this->impl_)" << std::endl
             << "  this->impl_->" << name << " (" << name << ");"
             << "else" << std::endl
             << "  throw ::CORBA::INTERNAL ();"
             << "}";

  // Finally, write the readonly attribute method.
  PICML::ReadonlyAttribute readonly (attr);
  readonly.Accept (*this);
}

}
