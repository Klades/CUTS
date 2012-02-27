// $Id:

#include "Setaf_Command.h"

//
// CUTS_Setaf_Assignment_Command
//
CUTS_Setaf_Assignment_Command::
CUTS_Setaf_Assignment_Command (CUTS_Setaf_Variable * lhs,
                               CUTS_Setaf_Variable * rhs)
: lhs_ (lhs),
  rhs_ (rhs)
{

}

//
// ~CUTS_Setaf_Assignment_Command
//
CUTS_Setaf_Assignment_Command::
~CUTS_Setaf_Assignment_Command (void)
{
  if (this->lhs_->type_ == CUTS_SETAF_UTILS::ST_UNITE)
    delete this->lhs_;

  if (this->lhs_->type_ == CUTS_SETAF_UTILS::ST_UNITE)
    delete this->rhs_;
}

//
// execute
//
void CUTS_Setaf_Assignment_Command::
execute (CUTS_Log_Format_Variable_Table & vars)
{
  this->lhs_->assign_value (this->rhs_, vars);
}