// $Id:

#include "Setaf_Variable.h"
#include "cuts/unite/Variable.h"
#include "cuts/unite/Log_Format_Adapter.h"

//
// CUTS_Setaf_Unite_Variable
//
CUTS_Setaf_Unite_Variable::
CUTS_Setaf_Unite_Variable (std::string & name)
{
  this->type_ = CUTS_SETAF_UTILS::ST_UNITE;
  this->name_ = name;
}

//
// ~CUTS_Setaf_Unite_Variable
//
CUTS_Setaf_Unite_Variable::
~CUTS_Setaf_Unite_Variable (void)
{

}

//
// init_value
//
void CUTS_Setaf_Unite_Variable::
init_value (std::string & val)
{

}

//
// reset_value
//
void CUTS_Setaf_Unite_Variable::
reset_value (std::string & val)
{

}

//
// assign_value
//
void CUTS_Setaf_Unite_Variable::
assign_value (CUTS_Setaf_Variable * var,
              CUTS_Log_Format_Variable_Table & vars)
{
  // A unite variable can only be assigned from an
  // interpreter variable.

  if (var->type_ == CUTS_SETAF_UTILS::ST_INTEGER)
  {
    CUTS_Log_Format_Adapter::int32_var * ivar =
      dynamic_cast <CUTS_Log_Format_Adapter::int32_var *> (vars [this->name_.c_str ()]);

    ivar->value (dynamic_cast <CUTS_Setaf_Integer_Variable *> (var)->value ());

  }
  else if (var->type_ == CUTS_SETAF_UTILS::ST_STRING)
  {
    char * val = (char *) (dynamic_cast <CUTS_Setaf_String_Variable *>
      (var)->value ().c_str ());

    vars [this->name_.c_str ()]->value (val);
  }
  else
    return;

}

//
// init
//
void CUTS_Setaf_Unite_Variable::init (void)
{

}

//
// reset
//
void CUTS_Setaf_Unite_Variable::reset (void)
{

}

//
// increment
//
void CUTS_Setaf_Unite_Variable::increment (void)
{

}

//
// name
//
std::string & CUTS_Setaf_Unite_Variable::name (void)
{
  return this->name_;
}
