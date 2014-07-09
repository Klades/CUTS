// $Id:

#include "Setaf_Command.h"
#include "cuts/unite/Log_Format_Adapter.h"

//
// CUTS_Setaf_Add_Command
//
CUTS_Setaf_Add_Command::
CUTS_Setaf_Add_Command (CUTS_Setaf_Variable * lhs,
                        CUTS_Setaf_Variable * op1,
                        CUTS_Setaf_Variable * op2)
: lhs_(lhs),
  operand1_(op1),
  operand2_(op2)
{

}

//
// CUTS_Setaf_Add_Command
//
CUTS_Setaf_Add_Command::
~CUTS_Setaf_Add_Command (void)
{
  if (this->lhs_->type_ == CUTS_SETAF_UTILS::ST_UNITE)
    delete this->lhs_;

  if (this->operand1_->type_ == CUTS_SETAF_UTILS::ST_UNITE)
    delete this->operand1_;
}

//
// execute
//
void CUTS_Setaf_Add_Command::
execute (CUTS_Log_Format_Variable_Table & vars)
{
  int val1 = 0;
  int val2 = 0;
  int final_val = 0;

  val1 = this->get_operand_val (this->operand1_, vars);
  val2 = this->get_operand_val (this->operand2_, vars);

  final_val = val1 + val2;

  CUTS_Setaf_Integer_Variable temp_var;
  temp_var.add_value (final_val);

  CUTS_Setaf_Assignment_Command temp_command (this->lhs_, &temp_var);
  temp_command.execute (vars);

  // First check whether lhs and op1 denote the same
  // variable. If it is then just add the value.

  //if (this->lhs_ == this->operand1_)
  //  dynamic_cast <CUTS_Setaf_Integer_Variable *>
  //    (this->lhs_)->add_value (value);

  //// If they are different then first do the addition and
  //// then assignment.
  //else
  //{
  //  int final_value = 0;
  //  final_value = dynamic_cast <CUTS_Setaf_Integer_Variable *> (this->rhs_)->value () +
  //    this->value_;

  //  CUTS_Setaf_Integer_Variable temp_var;
  //  temp_var.add_value (final_value);

  //  CUTS_Setaf_Assignment_Command temp_command (this->lhs_, &temp_var);
  //  temp_command.execute (vars);
  //}
}


int CUTS_Setaf_Add_Command::get_operand_val (CUTS_Setaf_Variable * operand,
                                             CUTS_Log_Format_Variable_Table & vars)
{
  if (operand->type_ == CUTS_SETAF_UTILS::ST_INTEGER_CONSTANT)
      return dynamic_cast <CUTS_Setaf_Integer_Constant *> (operand)->value ();

  else if (operand->type_ == CUTS_SETAF_UTILS::ST_UNITE)
  {
    CUTS_Log_Format_Adapter::int32_var * ivar =
      dynamic_cast <CUTS_Log_Format_Adapter::int32_var *> (vars [dynamic_cast <CUTS_Setaf_Unite_Variable *>(operand)->name ().c_str ()]);

    return ivar->get_real_value ();
  }
  else if (operand->type_ == CUTS_SETAF_UTILS::ST_INTEGER)
    return dynamic_cast <CUTS_Setaf_Integer_Variable *> (operand)->value ();

  else
  {
    std::cerr << "Unexpected variable type" << std::endl;
    return -1;
  }
}