// $Id$

#include "StdAfx.h"
#include "Behavior_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Behavior_Generator.inl"
#endif

#include "Variable_Type.h"

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variables_Begin_T

void CUTS_BE_Variables_Begin_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::Component & )
{
  this->ctx_.header_
    << "private:" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variable_T

void CUTS_BE_Variable_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::Variable & variable)
{
  CHAOS::PredefinedType type = variable.ref ();

  if (type != Udm::null)
  {
    std::string name (variable.name ());

    this->ctx_.header_
      << CUTS_BE_CPP::single_line_comment ("variable: " + name);

    CUTS_BE_CPP::Variable_Type var_type (this->ctx_.header_);
    var_type.generate (type);

    this->ctx_.header_
      << " " << name << "_;"
      << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Variable_T

void CUTS_BE_Attribute_Variable_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::ReadonlyAttribute & attr)
{
  CHAOS::AttributeMember member = attr.AttributeMember_child ();
  if (member == Udm::null)
    return;

  CHAOS::MemberType type = member.ref ();
  if (type == Udm::null)
    return;

  std::string name (attr.name ());
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("attribute: " + name);

  CUTS_BE_CPP::Variable_Type var_type (this->ctx_.header_);
  var_type.generate (type);

  this->ctx_.header_
    << " " << attr.name () << "_;"
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Periodic_Variable_T

void CUTS_BE_PeriodicEvent_Variable_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::PeriodicEvent & periodic)
{
  std::string name (periodic.name ());
  CHAOS::Component parent = CHAOS::Component::Cast (periodic.parent ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("periodic: " + name)
    << "CUTS_Periodic_Event_T < " << parent.name ()
    << " > periodic_" << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Variable_T

void CUTS_BE_Worker_Variable_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::WorkerType & var, const CHAOS::Worker & worker)
{
  std::string name (var.name ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("worker variable: " + name)
    << worker.name () << " " << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

void CUTS_BE_Action_Property_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::Property & property)
{
  // Write the value of the property.
  std::string value = property.DataValue ();
  this->ctx_.source_ << value;

  if (this->ctx_.arg_count_ > 1)
  {
    // If there are anymore argurments remaining, we need to place a
    // comma separator for the next argument.
    this->ctx_.source_ << ", ";

    // Decrement the argument count.
    -- this->ctx_.arg_count_;
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_WorkerAction_Begin_T

void CUTS_BE_WorkerAction_Begin_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::Worker & worker, const CHAOS::Action & action)
{
  this->ctx_.skip_action_ = false;

  // Now, how are we to log this action. If logging is enabled
  // then we need to invoke the logging method. If not, then we
  // need to invoke the non-logging method.

  CHAOS::Action action_type = CHAOS::Action (action).Archetype ();

  this->ctx_.source_
    << "this->" << action.name () << "_."
    << action_type.name () << " (";

  typedef std::vector <CHAOS::Property> Property_Set;
  Property_Set args = action_type.Property_kind_children ();

  this->ctx_.arg_count_ = args.size ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Begin_T

void CUTS_BE_OutputAction_Begin_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::OutputAction & action)
{
  std::string scoped_name;

  if (this->ctx_.outevent_mgr_.get_scoped_typename (action.name (), scoped_name))
  {
    // We are going to use a special event for CUTS::Payload_Event. This
    // object will actually create a payload of the correct size with the
    // size () setter method is invoked.
    if (scoped_name == "CUTS::Payload_Event")
      scoped_name += "_i";

    this->ctx_.source_
      << "CUTS_CCM_Event_T <OBV_" << scoped_name
      << "> __event_" << action.uniqueId () << "__;";

    this->ctx_.skip_action_ = false;
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Property_T

void CUTS_BE_OutputAction_Property_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::OutputAction & action,
          const CHAOS::Property & property)
{
  this->ctx_.source_
    << "__event_" << action.uniqueId () << "__->"
    << property.name () << " (" << property.DataValue () << ");";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_End_T

void CUTS_BE_OutputAction_End_T <CUTS_BE_CPP::Context>::
generate (const CHAOS::OutputAction & action)
{
  if (this->ctx_.skip_action_)
    return;

  this->ctx_.source_
    << "this->ctx_->push_"
    << action.name () << " (__event_" << action.uniqueId () << "__.in ());"
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Precondition_T

void CUTS_BE_Precondition_T <CUTS_BE_CPP::Context>::
generate (const std::string & precondition)
{
  this->ctx_.source_ << "if (" << precondition << ")";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Postcondition_T

void CUTS_BE_Postcondition_T <CUTS_BE_CPP::Context>::
generate (const std::string & postcondition)
{
  this->ctx_.source_ << postcondition;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branches_Begin_T

void CUTS_BE_Branches_Begin_T <CUTS_BE_CPP::Context>::generate (size_t branches)
{
  this->ctx_.branches_.push (1);
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branches_End_T

void CUTS_BE_Branches_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.branches_.pop ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_Begin_T

void CUTS_BE_Branch_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_ << "{";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_End_T

void CUTS_BE_Branch_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_ << "}";
}

//
// CUTS_BE_Branch_Condition_Begin_T
//
void CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  if (!this->ctx_.branches_.empty () && this->ctx_.branches_.top () ++ > 1)
    this->ctx_.source_ << "else ";

  this->ctx_.source_ << "if (";
}

//
// CUTS_BE_Branch_Condition_End_T
//
void CUTS_BE_Branch_Condition_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_ << ")";
}

//
// CUTS_BE_Branch_No_Condition_T
//
void CUTS_BE_Branch_No_Condition_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_ << "else";
}

//
// CUTS_BE_Action_End_T
//
void CUTS_BE_Action_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  if (!this->ctx_.skip_action_)
    this->ctx_.source_ << ");";
}
