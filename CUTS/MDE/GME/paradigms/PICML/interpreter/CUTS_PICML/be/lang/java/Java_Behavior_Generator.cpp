// $Id$

#include "Java_Behavior_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Java_Behavior_Generator.inl"
#endif

#include "Java_Variable_Type.h"


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variable_T

void CUTS_BE_Variable_T <CUTS_BE_Java::Context>::
generate (const PICML::Variable & variable)
{
  PICML::PredefinedType type = variable.ref ();

  if (type != Udm::null)
  {
    std::string name (variable.name ());
    CUTS_BE_Java::Variable_Type var_type (this->ctx_.source_);

    // Generate the getter method.
    this->ctx_.source_
      << "public ";

    var_type.generate (type);

    this->ctx_.source_
      << " " << CUTS_BE_Java::getter_method (name) << " ()"
      << "{"
      << "return this." << name << "_;"
      << "}"
      << std::endl
      // Generate the setter method.
      << "public void "
      << CUTS_BE_Java::setter_method (name) << " (";

    var_type.generate (type);

    this->ctx_.source_
      << " " << name << ")"
      << "{"
      << "this." << name << "_ = " << name << ";"
      << "}"
      << std::endl
      // Generate the variable declaration.
      << CUTS_BE_Java::single_line_comment ("variable: " + name)
      << "private ";

    var_type.generate (type);

    this->ctx_.source_
      << " " << name << "_;"
      << std::endl;
  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Variable_T

void CUTS_BE_Attribute_Variable_T <CUTS_BE_Java::Context>::
generate (const PICML::ReadonlyAttribute & attr)
{
  std::string name = attr.name ();
  PICML::AttributeMember member = attr.AttributeMember_child ();

  try
  {
    PICML::PredefinedType type = PICML::PredefinedType::Cast (member.ref ());

    this->ctx_.source_
      << std::endl
      << "/**" << std::endl
      << " * attribute variable : " << name << std::endl
      << " */" << std::endl
      << "private ";

    CUTS_BE_Java::Variable_Type vtype (this->ctx_.source_);
    vtype.generate (type);

    this->ctx_.source_
      << " " << name << "_;";
  }
  catch (...)
  {

  }
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Variable_T

void CUTS_BE_Worker_Variable_T <CUTS_BE_Java::Context>::
generate (const PICML::WorkerType & var, const PICML::Worker & worker)
{
  std::string name (var.name ());

  this->ctx_.source_
    << CUTS_BE_Java::single_line_comment ("worker variable: " + name)
    << worker.name () << " " << name << "_;" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

void CUTS_BE_Action_Property_T <CUTS_BE_Java::Context>::
generate (const PICML::Property & prop)
{
  // TODO Add support for complex properties.

  PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);
  this->ctx_.source_ << simple.Value ();

  if (-- this->ctx_.arg_count_ > 0)
    this->ctx_.source_ << ", ";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_WorkerAction_Begin_T

void CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Java::Context>::
generate (const PICML::Action & action)
{
  this->ctx_.skip_action_ = false;

  // Now, how are we to log this action. If logging is enabled
  // then we need to invoke the logging method. If not, then we
  // need to invoke the non-logging method.

  PICML::Action action_type = PICML::Action (action).Archetype ();

  this->ctx_.source_
    << "this." << action.name () << "_."
    << action_type.name () << " (";
}

//
// CUTS_BE_RequestAction_Begin_T
//
void CUTS_BE_RequestAction_Begin_T <CUTS_BE_Java::Context>::
generate (const PICML::RequestAction & action)
{
  this->ctx_.source_
    << "this." << action.name () << "_."
    << action.MethodName () << " (";
}

//
// CUTS_BE_RequestAction_End_T
//
void CUTS_BE_RequestAction_End_T <CUTS_BE_Java::Context>::
generate (const PICML::RequestAction & action)
{
  this->ctx_.source_
    << ");";
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Begin_T

void CUTS_BE_OutputAction_Begin_T <CUTS_BE_Java::Context>::
generate (const PICML::OutputAction & action)
{
  // Locate the ev for the output action.
  std::string name = action.name ();
  PICML::Event ev = this->ctx_.sources_[name];

  // Construct the fully qualified name for the ev.
  std::string fq_name = CUTS_BE_Java::fq_type (ev, ".", false);

  std::ostringstream evid;
  evid << "ev_" << action.uniqueId () << "_";

  if (fq_name != this->ctx_.jbi_anyevent_.first)
  {
    // We are working with a *regular* ev.
    std::string tagname = ev.SpecifyIdTag ();

    tagname[0] = ::toupper (tagname[0]);

    this->ctx_.source_
      << "// Create a new ev for publishing" << std::endl
      << tagname << "Impl " << evid.str () << " = new " << tagname << "Impl ();";
  }
  else
  {
    this->ctx_.source_
      << "// Create a new JbiAnyEvent for publishing" << std::endl
      << "JbiAnyEvent " << evid.str () << " = new JbiAnyEvent ();";
  }
}

void CUTS_BE_OutputAction_Property_T <CUTS_BE_Java::Context>::
generate (const PICML::OutputAction & action,
          const PICML::Property & prop)
{
  std::string name = prop.name ();

  if (name == "metadata")
  {
    // We handle the metadata property specially.
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);

    this->ctx_.source_
      << "ev_" << action.uniqueId () << "_." <<
      CUTS_BE_Java::setter_method (prop.name ())
      << " (" << simple.Value () << ");";
  }
  else if (name == "payload")
  {
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);

    this->ctx_.source_ << "ev_" << action.uniqueId ()
                              << "_.setPayload (" << simple.Value ()
                              << ");";
  }
  else
  {
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);

    this->ctx_.source_
      << "ev_" << action.uniqueId () << "_.getMetadata ()." <<
      CUTS_BE_Java::setter_method (prop.name ())
      << " (" << simple.Value () << ");";
  }
}

void CUTS_BE_OutputAction_End_T <CUTS_BE_Java::Context>::
generate (const PICML::OutputAction & action)
{
  this->ctx_.source_
    << std::endl
    << "// Publishing the ev (ev_"
    << action.uniqueId () << ")." << std::endl
    << "this." << action.name () << "_.publishData (ev_"
    << action.uniqueId () << "_);";
}

void CUTS_BE_Precondition_T <CUTS_BE_Java::Context>::
generate (const std::string & precondition)
{
  this->ctx_.source_ << "if (" << precondition << ")";
}

void CUTS_BE_Postcondition_T <CUTS_BE_Java::Context>::
generate (const std::string & postcondition)
{
  this->ctx_.source_ << postcondition;
}

void CUTS_BE_Branches_Begin_T <CUTS_BE_Java::Context>::generate (size_t branches)
{
  this->ctx_.branches_.push (1);
}

void CUTS_BE_Branches_End_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.branches_.pop ();
}

void CUTS_BE_Branch_Begin_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_ << "{";
}

//
// CUTS_BE_Branch_End_T
//
void CUTS_BE_Branch_End_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_ << "}";
}

//
// CUTS_BE_Branch_Condition_Begin_T
//
void CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Java::Context>::generate (void)
{
  // We need to generate an "else if" statement if this is not
  // the first transition.
  if (!this->ctx_.branches_.empty () &&
       this->ctx_.branches_.top () ++ > 1)
  {
    this->ctx_.source_ << "else ";
  }

  // Generate the if condition for the branch.
  this->ctx_.source_
    << "if (";
}

//
// CUTS_BE_Branch_Condition_End_T
//
void CUTS_BE_Branch_Condition_End_T <CUTS_BE_Java::Context>::generate (void)
{
  // Generate the end of the if condition for the branch.
  this->ctx_.source_
    << ")";
}

//
// CUTS_BE_Branch_No_Condition_T
//
void CUTS_BE_Branch_No_Condition_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "else";
}

//
// CUTS_BE_Action_End_T
//
void CUTS_BE_Action_End_T <CUTS_BE_Java::Context>::generate (void)
{
  if (!this->ctx_.skip_action_)
    this->ctx_.source_ << ");";
}

//
// CUTS_BE_Action_Properties_Begin_T
//
void CUTS_BE_Action_Properties_Begin_T <CUTS_BE_Java::Context>::generate (size_t count)
{
  this->ctx_.arg_count_ = count;
}

//
// CUTS_BE_Do_While_Begin_T
//
void CUTS_BE_Do_While_Begin_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "do"
    << "{";
}

//
// CUTS_BE_Do_While_Begin_T
//
void CUTS_BE_Do_While_End_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "}"
    << "while ";
}


//
// CUTS_BE_Do_While_Condition_Begin_T
//
void CUTS_BE_Do_While_Condition_Begin_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "(";
}

//
// CUTS_BE_Do_While_Condition_End_T
//
void CUTS_BE_Do_While_Condition_End_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << ");";
}

//
// CUTS_BE_While_Condition_Begin_T
//
void CUTS_BE_While_Condition_Begin_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "while (";
}

//
// CUTS_BE_While_Condition_End_T
//
void CUTS_BE_While_Condition_End_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << ")";
}

//
// CUTS_BE_While_Begin_T
//
void CUTS_BE_While_Begin_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "{";
}

//
// CUTS_BE_While_End_T
//
void CUTS_BE_While_End_T <CUTS_BE_Java::Context>::generate (void)
{
  this->ctx_.source_
    << "}";
}
