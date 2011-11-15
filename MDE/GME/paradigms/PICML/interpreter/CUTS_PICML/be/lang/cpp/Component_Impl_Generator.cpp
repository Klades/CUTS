// $Id$

#include "Component_Impl_Generator.h"
#include "../../UDM_Utility_T.h"
#include "boost/bind.hpp"

namespace CUTS_BE_CPP
{
//
// Base_Member_Init
//
Base_Member_Init::Base_Member_Init (std::ostream & out)
: out_ (out)
{

}

//
// Base_Member_Init
//
Base_Member_Init::~Base_Member_Init (void)
{

}

//
// Visit_Component
//
void Base_Member_Init::
Visit_Component (const PICML::Component & component)
{
  typedef std::vector <PICML::Variable> Variables;
  Variables variables = component.Variable_kind_children_sorted (Sorted_By_Name <PICML::Variable> ());

  if (!variables.empty ())
  {
    // Locate the first variable with an initial value.
    Variables::iterator iter =
      std::find_if (variables.begin (),
                    variables.end (),
                    boost::bind (std::not_equal_to <std::string> (),
                                 "",
                                 boost::bind (&PICML::Variable::InitialValue, _1)));

    if (iter != variables.end ())
    {
      // Write the initial value of the first variable.
      this->out_ << std::endl
                 << ": " << iter->name () << "_ ("
                 << iter->InitialValue () << ")";

      // Write the initial values of the remaining variables.
      std::for_each (++ iter,
                     variables.end (),
                     boost::bind (&PICML::Variable::Accept,
                                  _1,
                                  boost::ref (*this)));
    }
  }
}

//
// Visit_Variable
//
void Base_Member_Init::
Visit_Variable (const PICML::Variable & variable)
{
  std::string init_value (variable.InitialValue ());

  if (!init_value.empty ())
  {
    this->out_ << "," << std::endl
               << "  " << variable.name () << "_ (" << init_value << ")";
  }
}

//
// Initialize_Entity
//
Initialize_Entity::Initialize_Entity (std::ostream & out)
: out_ (out)
{

}

//
// ~Initialize_Entity
//
Initialize_Entity::~Initialize_Entity (void)
{

}

//
// ~Initialize_Entity
//
void Initialize_Entity::
Visit_PeriodicEvent (const PICML::PeriodicEvent & periodic)
{
  const std::string name (periodic.name ());
  PICML::Component parent (PICML::Component::Cast (periodic.parent ()));
  const std::string parent_name (parent.name ());

  this->out_
    << "this->periodic_" << name << "_.init (this, &"
    << parent_name << "::periodic_" << name << ");"
    << "this->periodic_" << name << "_.configure (CUTS_Periodic_Event::";

  std::string distribution (periodic.Distribution ());

  if (distribution == "Constant")
    this->out_ << "PE_CONSTANT, ";
  else if (distribution == "Exponential")
    this->out_ << "PE_EXPONENTIAL, ";
  else
    this->out_ << "PE_UNDEFINED, ";

  this->out_
    << periodic.Hertz () << ");"
    << "this->register_object (&this->periodic_" << name << "_);";
}

//
// Visit_InEventPort
//
void Initialize_Entity::Visit_InEventPort (const PICML::InEventPort & in)
{
  // Get the Input connection from this port.
  PICML::Input input = in.dstInput ();

  if (input == Udm::null)
    return;

  // Get the properties assigned to this input action.
  PICML::InputAction action = input.dstInput_end ();
  std::vector <PICML::Property> properties = action.Property_children ();

  std::vector <PICML::Property>::const_iterator iter =
    std::find_if (properties.begin (),
                  properties.end (),
                  boost::bind (std::equal_to <std::string> (),
                               "asynchronous",
                               boost::bind (&PICML::Property::name, _1)));

  if (iter == properties.end ())
    return;

  // Register the event handler object.
  const std::string name (in.name ());
  const std::string varname (name + "_event_handler_");
  PICML::Component parent (PICML::Component::Cast (in.parent ()));
  const std::string parent_name (parent.name ());

  this->out_
    << "this->" << varname << ".init (this, "
    << "&" << parent_name << "::push_" << name << "_i);"
    << "this->register_object (&this->" << varname << ");";
}

}
