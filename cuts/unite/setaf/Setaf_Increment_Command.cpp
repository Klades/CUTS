// $Id:

#include "Setaf_Command.h"

//
// CUTS_Setaf_Increment_Command
//
CUTS_Setaf_Increment_Command::
CUTS_Setaf_Increment_Command (CUTS_Setaf_Variable * incr_var)
: incr_var_ (incr_var)
{

}

//
// ~CUTS_Setaf_Increment_Command
//
CUTS_Setaf_Increment_Command::
~CUTS_Setaf_Increment_Command (void)
{

}

//
// execute
//
void CUTS_Setaf_Increment_Command::
execute (CUTS_Log_Format_Variable_Table & vars)
{
  this->incr_var_->increment ();
}