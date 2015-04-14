// $Id$

#include "Behavior_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Behavior_Generator.inl"
#endif

#include "../../BE_Options.h"
#include "Variable_Type.h"

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variables_Begin_T

void CUTS_BE_Variables_Begin_T <CUTS_BE_CPP::Context>::
generate (const PICML::Component_in )
{
  this->ctx_.header_
    << "private:" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variable_T

void CUTS_BE_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::Variable_in variable)
{
  if (variable->PredefinedType_is_nil ())
    return;

  PICML::PredefinedType type = variable->refers_to_PredefinedType ();

  std::string name (variable->name ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("variable: " + name);

  CUTS_BE_CPP::Variable_Type var_type (this->ctx_.header_);
  var_type.generate (type);

  this->ctx_.header_
    << " " << name << "_;"
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Variable_T

void CUTS_BE_Attribute_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::ReadonlyAttribute_in attr)
{
  if (!attr->has_AttributeMember ())
    return;

  PICML::AttributeMember member = attr->get_AttributeMember ();

  if (member->MemberType_is_nil ())
    return;

  PICML::MemberType type = member->refers_to_MemberType ();

  std::string name (attr->name ());
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("attribute: " + name);

  CUTS_BE_CPP::Variable_Type var_type (this->ctx_.header_);
  var_type.generate (type);

  this->ctx_.header_
    << " " << attr->name () << "_;"
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Periodic_Variable_T

void CUTS_BE_PeriodicEvent_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::PeriodicEvent_in periodic)
{
  std::string name (periodic->name ());
  PICML::Component parent = PICML::Component::_narrow (periodic->parent ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("periodic: " + name)
    << "CUTS_Periodic_Event_T < " << parent->name ()
    << " > periodic_" << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Application_Task_Variable_T

void CUTS_BE_ApplicationTask_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::ApplicationTask_in apptask)
{
  std::string name (apptask->name ());
  PICML::Component parent = apptask->parent ();

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("apptask: " + name)
    << "CUTS_Application_Task_T < " << parent->name ()
    << " > apptask_" << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Variable_T

void CUTS_BE_Worker_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::WorkerType_in var, const PICML::Worker_in worker)
{
  std::string name (var->name ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("worker variable: " + name)
    << worker->name () << " " << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

void CUTS_BE_Action_Property_T <CUTS_BE_CPP::Context>::
generate (const PICML::Property_in prop)
{
  // TODO Add support for complex properties.

  // Write the value of the prop.
  PICML::SimpleProperty simple = PICML::SimpleProperty::_narrow (prop);
  this->ctx_.source_ << simple->Value ();

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
generate (const PICML::Action_in action)
{
  this->ctx_.skip_action_ = false;

  // Now, how are we to log this action. If logging is enabled
  // then we need to invoke the logging method. If not, then we
  // need to invoke the non-logging method.

  PICML::ActionType action_type = action->get_ActionType ();
  PICML::Operation op = action_type->refers_to_Operation ();

  this->ctx_.source_
    << "this->" << action->name () << "_."
    << op->name () << " (";

  this->ctx_.arg_count_ = action->children <PICML::Property> ().count ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Begin_T

void CUTS_BE_OutputAction_Begin_T <CUTS_BE_CPP::Context>::
generate (const PICML::OutputAction_in action)
{
  std::string scoped_name;
  const std::string name = action->name ();

  if (this->ctx_.outevent_mgr_.get_scoped_typename (name, scoped_name))
  {
    std::string id = action->id ();
    std::replace (id.begin (), id.end (), '-', '_');
    this->ctx_.source_
      << "::" << scoped_name << "_var __event_"
      << id << "__ = this->ctx_->new_" << name << "_event ();";

    this->ctx_.skip_action_ = false;
  }
  else
  {
    this->ctx_.source_
      << "// could not locate scoped name for " << name << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Property_T

void CUTS_BE_OutputAction_Property_T <CUTS_BE_CPP::Context>::
generate (const PICML::OutputAction_in action,
          const PICML::Property_in prop)
{
  std::string id = action->id ();
  std::replace (id.begin (), id.end (), '-', '_');

  std::ostringstream varname;
  varname << "__event_" << id << "__";

  if (prop->meta ()->name () == PICML::SimpleProperty::impl_type::metaname)
  {
    // Write the contents for a simple property.
    PICML::SimpleProperty simple = PICML::SimpleProperty::_narrow (prop);
    std::string value = simple->Value ();

    if (value == "$TIMEOFDAY")
      value = "ACE_OS::gettimeofday ().msec ()";

    this->ctx_.source_
      << varname.str () << "->" << prop->name ()
      << " (" << value << ");";
  }
  else
  {
    PICML::ComplexProperty complex = PICML::ComplexProperty::_narrow (prop);

    const std::string propname = prop->name ();
    for (auto datavalue : complex->get_DataValues ())
    {
      this->ctx_.source_
        << varname.str () << "->" << propname
        << " ()." << datavalue->name () << " = " << datavalue->Value () << ";";
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_End_T

void CUTS_BE_OutputAction_End_T <CUTS_BE_CPP::Context>::
generate (const PICML::OutputAction_in action)
{
  if (this->ctx_.skip_action_)
    return;

  std::string id = action->id ();
  std::replace (id.begin (), id.end (), '-', '_');

  this->ctx_.source_
    << "this->ctx_->push_"
    << action->name () << " (__event_" << id << "__.in ());"
    << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_CallAction_Begin_T

void CUTS_BE_CallAction_Begin_T <CUTS_BE_CPP::Context>::
generate (const PICML::CallAction_in action)
{
  if (!action->has_TargetRequiredRequestPort ())
    return;

  PICML::TargetRequiredRequestPort target = action->get_TargetRequiredRequestPort ();
  PICML::RequiredRequestPort port = target->refers_to_RequiredRequestPort ();

  this->ctx_.source_
    << "this->ctx_->get_connection_" << port->name () << " ()->" << action->name () << " (";

  // Get the children properties
  this->ctx_.arg_count_ = action->children <PICML::Property> ().count ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_CallAction_Property_T

void CUTS_BE_CallAction_Property_T <CUTS_BE_CPP::Context>::
generate (const PICML::CallAction_in action,
          const PICML::Property_in prop)
{
  // TODO Add support for complex properties.

  // Write the value of the prop.
  PICML::SimpleProperty simple = PICML::SimpleProperty::_narrow (prop);
  this->ctx_.source_ << simple->Value ();

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
// CUTS_BE_CallAction_End_T

void CUTS_BE_CallAction_End_T <CUTS_BE_CPP::Context>::
generate (const PICML::CallAction_in action)
{
  this->ctx_.source_
    << ");" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Precondition_T

void CUTS_BE_Precondition_T <CUTS_BE_CPP::Context>::
generate (const std::string & cond)
{
  this->ctx_.source_ << cond;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Postcondition_T

void CUTS_BE_Postcondition_T <CUTS_BE_CPP::Context>::
generate (const std::string & cond)
{
  this->ctx_.source_ << cond;
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

//
// CUTS_BE_Action_Properties_Begin_T
//
void CUTS_BE_Action_Properties_Begin_T <CUTS_BE_CPP::Context>::generate (size_t count)
{
  this->ctx_.arg_count_ = count;
}

//
// CUTS_BE_Do_While_Begin_T
//
void CUTS_BE_Do_While_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "do"
    << "{";
}

//
// CUTS_BE_Do_While_End_T
//
void CUTS_BE_Do_While_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "}"
    << "while ";
}


//
// CUTS_BE_Do_While_Condition_Begin_T
//
void CUTS_BE_Do_While_Condition_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "(";
}

//
// CUTS_BE_Do_While_Condition_End_T
//
void CUTS_BE_Do_While_Condition_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << ");";
}

//
// CUTS_BE_While_Condition_Begin_T
//
void CUTS_BE_While_Condition_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "while (";
}

//
// CUTS_BE_While_Condition_End_T
//
void CUTS_BE_While_Condition_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << ")";
}

//
// CUTS_BE_While_Begin_T
//
void CUTS_BE_While_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "{";
}

//
// CUTS_BE_While_End_T
//
void CUTS_BE_While_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "}";
}

//
// CUTS_BE_For_Condition_Begin_T
//
void CUTS_BE_For_Condition_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "for (";
}

//
// CUTS_BE_For_Condition_Delimiter_T
//
void CUTS_BE_For_Condition_Delimiter_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << ";";
}

//
// CUTS_BE_For_Condition_End_T
//
void CUTS_BE_For_Condition_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << ")";
}

//
// CUTS_BE_For_Begin_T
//
void CUTS_BE_For_Begin_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "{";
}

//
// CUTS_BE_For_End_T
//
void CUTS_BE_For_End_T <CUTS_BE_CPP::Context>::generate (void)
{
  this->ctx_.source_
    << "}";
}

