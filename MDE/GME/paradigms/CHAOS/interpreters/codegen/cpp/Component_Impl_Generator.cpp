// $Id$

#include "StdAfx.h"
#include "Component_Impl_Generator.h"
#include "UDM_Utility_T.h"
#include "boost/bind.hpp"
#include <functional>

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
Visit_Component (const CHAOS::Component & component)
{
  typedef std::vector <CHAOS::Variable> Variables;
  Variables variables = component.Variable_kind_children_sorted (Sorted_By_Name <CHAOS::Variable> ());

  if (!variables.empty ())
  {
    // Locate the first variable with an initial value.
    Variables::iterator iter =
      std::find_if (variables.begin (),
                    variables.end (),
                    boost::bind (std::not_equal_to <std::string> (),
                                 "",
                                 boost::bind (&CHAOS::Variable::InitialValue, _1)));

    if (iter != variables.end ())
    {
      // Write the initial value of the first variable.
      this->out_ << std::endl
                 << ": " << iter->name () << "_ ("
                 << iter->InitialValue () << ")";

      // Write the initial values of the remaining variables.
      std::for_each (++ iter,
                     variables.end (),
                      [&] (CHAOS::Variable item) {item.Accept (*this);});
    }
  }
}

//
// Visit_Variable
//
void Base_Member_Init::
Visit_Variable (const CHAOS::Variable & variable)
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
Visit_PeriodicEvent (const CHAOS::PeriodicEvent & periodic)
{
  std::string name (periodic.name ());

  CHAOS::Component parent (CHAOS::Component::Cast (periodic.parent ()));
  std::string parent_name (parent.name ());

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

}
