// $Id:

#include "Setaf_Variable.h"
#include "cuts/unite/Variable.h"

//
// CUTS_Setaf_String_Variable
//
CUTS_Setaf_String_Variable::CUTS_Setaf_String_Variable (void)
{
  this->type_ = CUTS_SETAF_UTILS::ST_STRING;
}

//
// ~CUTS_Setaf_String_Variable
//
CUTS_Setaf_String_Variable::~CUTS_Setaf_String_Variable (void)
{

}

//
// init_value
//
void CUTS_Setaf_String_Variable::init_value (std::string & val)
{
  this->init_value_ = val;
}

//
// reset_value
//
void CUTS_Setaf_String_Variable::reset_value (std::string & val)
{
  this->reset_value_ = val;
}

//
// increment
//
void CUTS_Setaf_String_Variable::increment (void)
{

}

//
// assign_value
//
void CUTS_Setaf_String_Variable::
assign_value(CUTS_Setaf_Variable * var,
             CUTS_Log_Format_Variable_Table & vars)
{
  // Only a string variable can assign an another
  // string variable.

  if (var->type_ == CUTS_SETAF_UTILS::ST_UNITE)
  {
    std::string name = dynamic_cast <CUTS_Setaf_Unite_Variable *> (var)->name ();

    CUTS_String_Log_Format_Variable * svar =
      dynamic_cast <CUTS_String_Log_Format_Variable *> (vars [name.c_str ()]);

    this->value_ = svar->value ();
  }
  else
    this->value_ = dynamic_cast <CUTS_Setaf_String_Variable *> (var)->value ();
}

//
// value
//
std::string & CUTS_Setaf_String_Variable::value (void)
{
  return this->value_;
}

//
// init
//
void CUTS_Setaf_String_Variable::init (void)
{
  this->value_ = this->init_value_;
}

//
// reset
//
void CUTS_Setaf_String_Variable::reset (void)
{
  //this->value_ = this->reset_value_;
}