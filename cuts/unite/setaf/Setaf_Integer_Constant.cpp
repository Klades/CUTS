// $Id:

#include "Setaf_Variable.h"
#include "cuts/unite/Log_Format_Adapter.h"

//
// CUTS_Setaf_Integer_Constant
//
CUTS_Setaf_Integer_Constant::CUTS_Setaf_Integer_Constant (int value)
: value_ (value)
{
  this->type_ = CUTS_SETAF_UTILS::ST_INTEGER_CONSTANT;
}

//
// ~CUTS_Setaf_Integer_Variable
//
CUTS_Setaf_Integer_Constant::~CUTS_Setaf_Integer_Constant (void)
{

}

//
// init_value
//
void CUTS_Setaf_Integer_Constant::init_value (std::string & val)
{
}

//
// reset_value
//
void CUTS_Setaf_Integer_Constant::reset_value (std::string & val)
{
}

//
// assign_value
//
void CUTS_Setaf_Integer_Constant::
assign_value (CUTS_Setaf_Variable * var,
              CUTS_Log_Format_Variable_Table & vars)
{
}

//
// value
//
int CUTS_Setaf_Integer_Constant::value (void)
{
  return this->value_;
}

//
// init
//
void CUTS_Setaf_Integer_Constant::init (void)
{
}

//
// reset
//
void CUTS_Setaf_Integer_Constant::reset (void)
{
}

//
// increment
//
void CUTS_Setaf_Integer_Constant::increment (void)
{
}