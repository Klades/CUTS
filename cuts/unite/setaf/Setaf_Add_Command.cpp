// $Id:

#include "Setaf_Command.h"

//
// CUTS_Setaf_Add_Command
//
CUTS_Setaf_Add_Command::
CUTS_Setaf_Add_Command (CUTS_Setaf_Variable * lhs,
                        CUTS_Setaf_Variable * rhs,
                        int value)
: lhs_(lhs),
  rhs_(rhs),
  value_(value)
{

}

//
// CUTS_Setaf_Add_Command
//
CUTS_Setaf_Add_Command::
~CUTS_Setaf_Add_Command (void)
{

}

//
// execute
//
void CUTS_Setaf_Add_Command::
execute (CUTS_Log_Format_Variable_Table & vars)
{
  // First check whether lhs and rhs denote the same
  // variable. If it is then just add the value.

  if (this->lhs_ == this->rhs_)
    dynamic_cast <CUTS_Setaf_Integer_Variable *>
      (this->lhs_)->add_value (this->value_);

  // If they are different then first do the addition and
  // then assignment.
  else
  {
    int final_value = 0;
    final_value = dynamic_cast <CUTS_Setaf_Integer_Variable *> (this->rhs_)->value () +
      this->value_;

    CUTS_Setaf_Integer_Variable temp_var;
    temp_var.add_value (final_value);

    CUTS_Setaf_Assignment_Command temp_command (this->lhs_, &temp_var);
    temp_command.execute (vars);
  }
}