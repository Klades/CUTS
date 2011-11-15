// $Id$

#include "stdafx.h"
#include "Model_Interpreter_Action.h"

#if !defined (__CUTS_INLINE__)
#include "Model_Interpreter_Action.inl"
#endif

#include "cuts/utils/Property_Evaluator_T.h"
#include "cuts/utils/Property_Evaluator_Stream_Actor.h"
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// CUTS_CUTE_Replace_Model_Name_Action

//
// replace
//
void CUTS_CUTE_Replace_Model_Name_Action::
replace (const CUTS_Property_Map & config)
{
  // Expand the template value(s) in the name.
  std::ostringstream ostr;
  CUTS_Property_Evaluator_Stream_Actor actor (ostr);
  CUTS_Property_Evaluator_T <CUTS_Property_Evaluator_Stream_Actor> evaluator (config, actor);

  evaluator.config ().open_tag_ = "<%";
  evaluator.config ().close_tag_ = "%>";
  evaluator.config ().use_env_ = true;

  if (evaluator.evaluate (this->object_->name ().c_str ()))
  {
    this->old_value_ = this->object_->name ().c_str ();
    this->object_->name (ostr.str ());
  }
  else
    this->old_value_.clear ();
}

//
// reset
//
void CUTS_CUTE_Replace_Model_Name_Action::reset (void)
{
  if (this->object_->name () != this->old_value_.c_str ())
    this->object_->name (this->old_value_.c_str ());
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_CUTE_Replace_Model_Attribute_Action

//
// replace
//
void CUTS_CUTE_Replace_Model_Attribute_Action::
replace (const CUTS_Property_Map & config)
{
  // Expand the template value(s) in the name.
  std::ostringstream ostr;
  CUTS_Property_Evaluator_Stream_Actor actor (ostr);
  CUTS_Property_Evaluator_T <CUTS_Property_Evaluator_Stream_Actor> evaluator (config, actor);

  evaluator.config ().open_tag_ = "<%";
  evaluator.config ().close_tag_ = "%>";
  evaluator.config ().use_env_ = true;

  if (evaluator.evaluate (this->attr_->string_value ().c_str ()))
  {
    this->old_value_ = this->attr_->string_value ().c_str ();
    this->attr_->string_value (ostr.str ());
  }
  else
    this->old_value_.clear ();
}

//
// reset
//
void CUTS_CUTE_Replace_Model_Attribute_Action::reset (void)
{
  if (this->attr_->string_value () != this->old_value_.c_str ())
    this->attr_->string_value (this->old_value_.c_str ());
}
