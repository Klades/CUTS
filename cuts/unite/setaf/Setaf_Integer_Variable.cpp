// $Id:

#include "Setaf_Variable.h"
#include "cuts/unite/Log_Format_Adapter.h"

//
// CUTS_Setaf_Integer_Variable
//
CUTS_Setaf_Integer_Variable::CUTS_Setaf_Integer_Variable (void)
{
  this->type_ = CUTS_SETAF_UTILS::ST_INTEGER;
}

//
// ~CUTS_Setaf_Integer_Variable
//
CUTS_Setaf_Integer_Variable::~CUTS_Setaf_Integer_Variable (void)
{

}

//
// init_value
//
void CUTS_Setaf_Integer_Variable::init_value (std::string & val)
{
  this->init_value_ = ACE_OS::atoi (val.c_str ());
}

//
// reset_value
//
void CUTS_Setaf_Integer_Variable::reset_value (std::string & val)
{
  this->reset_value_ = ACE_OS::atoi (val.c_str ());
}

//
// assign_value
//
void CUTS_Setaf_Integer_Variable::
assign_value (CUTS_Setaf_Variable * var,
              CUTS_Log_Format_Variable_Table & vars)
{
  // An integer variable can be assigned from either
  // an integer variable or from a unite variable.

  if (var->type_ == CUTS_SETAF_UTILS::ST_UNITE)
  {
    // In case of a unite variable it should be
    // of integer type.

    std::string name = dynamic_cast <CUTS_Setaf_Unite_Variable *> (var)->name ();

    CUTS_Log_Format_Adapter::int32_var * ivar =
      dynamic_cast <CUTS_Log_Format_Adapter::int32_var *> (vars [name.c_str ()]);

    this->value_ = ivar->get_real_value ();
  }
  else
    this->value_ = dynamic_cast <CUTS_Setaf_Integer_Variable *> (var)->value ();
}

//
// value
//
int CUTS_Setaf_Integer_Variable::value (void)
{
  return this->value_;
}

//
// init
//
void CUTS_Setaf_Integer_Variable::init (void)
{
  this->value_ = this->init_value_;
}

//
// reset
//
void CUTS_Setaf_Integer_Variable::reset (void)
{
  this->value_ = this->reset_value_;
}

//
// increment
//
void CUTS_Setaf_Integer_Variable::increment (void)
{
  this->value_++;
}

//
// add_value
//
void CUTS_Setaf_Integer_Variable::add_value (int val)
{
  this->value_ = this->value_ + val;
}