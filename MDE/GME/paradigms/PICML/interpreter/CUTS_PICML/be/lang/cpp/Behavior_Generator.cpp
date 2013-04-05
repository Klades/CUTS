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
generate (const PICML::Component & )
{
  this->ctx_.header_
    << "private:" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variable_T

void CUTS_BE_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::Variable & variable)
{
  PICML::PredefinedType type = variable.ref ();

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
generate (const PICML::ReadonlyAttribute & attr)
{
  PICML::AttributeMember member = attr.AttributeMember_child ();
  if (member == Udm::null)
    return;

  PICML::MemberType type = member.ref ();
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
generate (const PICML::PeriodicEvent & periodic)
{
  std::string name (periodic.name ());
  PICML::Component parent = PICML::Component::Cast (periodic.parent ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("periodic: " + name)
    << "CUTS_Periodic_Event_T < " << parent.name ()
    << " > periodic_" << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Variable_T

void CUTS_BE_Worker_Variable_T <CUTS_BE_CPP::Context>::
generate (const PICML::WorkerType & var, const PICML::Worker & worker)
{
  std::string name (var.name ());

  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("worker variable: " + name)
    << worker.name () << " " << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

void CUTS_BE_Action_Property_T <CUTS_BE_CPP::Context>::
generate (const PICML::Property & prop)
{
  // TODO Add support for complex properties.

  // Write the value of the prop.
  PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);
  this->ctx_.source_ << simple.Value ();

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
generate (const PICML::Action & action)
{
  this->ctx_.skip_action_ = false;

  // Now, how are we to log this action. If logging is enabled
  // then we need to invoke the logging method. If not, then we
  // need to invoke the non-logging method.

  PICML::ActionType action_type = action.ActionType_child ();
  PICML::Operation op = action_type.ref ();

  this->ctx_.source_
    << "this->" << action.name () << "_."
    << op.name () << " (";

  typedef std::vector <PICML::Property> Property_Set;
  Property_Set args = action.Property_kind_children ();

  this->ctx_.arg_count_ = args.size ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Begin_T

void CUTS_BE_OutputAction_Begin_T <CUTS_BE_CPP::Context>::
generate (const PICML::OutputAction & action)
{
  std::string scoped_name;
  const std::string name = action.name ();

  if (this->ctx_.outevent_mgr_.get_scoped_typename (name, scoped_name))
  {
    this->ctx_.source_
      << "::" << scoped_name << "_var __event_"
      << action.uniqueId () << "__ = this->ctx_->new_" << name << "_event ();";

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
generate (const PICML::OutputAction & action,
          const PICML::Property & prop)
{
  std::ostringstream varname;
  varname << "__event_" << action.uniqueId () << "__";

  if (prop.type () == PICML::SimpleProperty::meta)
  {
    // Write the contents for a simple property.
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);
    std::string value = simple.Value ();

    if (value == "$TIMEOFDAY")
      value = "ACE_OS::gettimeofday ().msec ()";

    this->ctx_.source_
      << varname.str () << "->" << prop.name ()
      << " (" << value << ");";
  }
  else
  {
    PICML::ComplexProperty complex = PICML::ComplexProperty::Cast (prop);
    std::vector <PICML::DataValue> values = complex.DataValue_kind_children ();

    std::vector <PICML::DataValue>::const_iterator
      iter = values.begin (), iter_end = values.end ();

    const std::string propname = prop.name ();

    for ( ; iter != iter_end; ++ iter)
    {
      this->ctx_.source_
        << varname.str () << "->" << propname
        << " ()." << iter->name () << " = " << iter->Value () << ";";
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_End_T

void CUTS_BE_OutputAction_End_T <CUTS_BE_CPP::Context>::
generate (const PICML::OutputAction & action)
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

