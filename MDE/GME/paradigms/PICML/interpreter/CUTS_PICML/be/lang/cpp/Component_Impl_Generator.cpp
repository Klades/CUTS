// $Id$

#include "Component_Impl_Generator.h"

#include <functional>
#include "game/mga/utils/Name_Sort_T.h"

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
Visit_Component (const PICML::Component_in component)
{
  std::vector <PICML::Variable> variables;
  for (auto variable : component->get_Variables ())
    variables.push_back (variable);

  if (variables.size ())
  {
    std::sort (variables.begin (), variables.end (), GAME::Mga::Name_Sort_T ());

    // Locate the first variable with an initial value.
    auto iter =
      std::find_if (variables.begin (),
                    variables.end (),
                    [&] (PICML::Variable v) {return v->InitialValue () != "";});

    if (iter != variables.end ())
    {
      // Write the initial value of the first variable.
      this->out_ << std::endl
                 << ": " << (*iter)->name () << "_ ("
                 << (*iter)->InitialValue () << ")";

      // Write the initial values of the remaining variables.
      std::for_each (++ iter,
                     variables.end (),
                     [this] (PICML::Variable v) {v->accept (this);});
    }
  }
}

//
// Visit_Variable
//
void Base_Member_Init::
Visit_Variable (const PICML::Variable_in variable)
{
  std::string init_value (variable->InitialValue ());

  if (!init_value.empty ())
  {
    this->out_ << "," << std::endl
               << "  " << variable->name () << "_ (" << init_value << ")";
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
Visit_PeriodicEvent (const PICML::PeriodicEvent_in periodic)
{
  const std::string name = periodic->name ();
  PICML::Component parent = periodic->parent ();
  const std::string parent_name = parent->name ();

  this->out_
    << "this->periodic_" << name << "_.init (this, &"
    << parent_name << "::periodic_" << name << ");"
    << "this->periodic_" << name << "_.configure (CUTS_Periodic_Event::";

  std::string distribution = periodic->Distribution ();

  if (distribution == "Constant")
    this->out_ << "PE_CONSTANT, ";
  else if (distribution == "Exponential")
    this->out_ << "PE_EXPONENTIAL, ";
  else
    this->out_ << "PE_UNDEFINED, ";

  this->out_
    << periodic->Hertz () << ");"
    << "this->register_object (&this->periodic_" << name << "_);";
}

//
// Visit_InEventPort
//
void Initialize_Entity::Visit_InEventPort (const PICML::InEventPort_in in)
{
  if (!in->has_src_of_Input ())
    return;

  // Get the Input connection from this port.
  PICML::Input input = in->src_of_Input ();

  // Get the properties assigned to this input action.
  PICML::InputAction action = input->dst_InputAction ();
  auto properties = action->children <PICML::Property> ();

  auto iter =
    std::find_if (properties.begin (),
                  properties.end (),
                  [&] (PICML::Property p) {return p->name () == "asynchronous";});

  if (iter == properties.end ())
    return;

  // Register the event handler object.
  const std::string name = in->name ();
  const std::string varname (name + "_event_handler_");
  PICML::Component parent = in->parent ();
  const std::string parent_name = parent->name ();

  this->out_
    << "this->" << varname << ".init (this, "
    << "&" << parent_name << "::push_" << name << "_i);"
    << "this->register_object (&this->" << varname << ");";
}

}
