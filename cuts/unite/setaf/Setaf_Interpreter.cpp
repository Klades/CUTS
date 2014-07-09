// $Id:

#include "Setaf_Interpreter.h"
#include "ace/CORBA_macros.h"

//
// CUTS_Setaf_Interpreter
//
CUTS_Setaf_Interpreter::CUTS_Setaf_Interpreter (void)
{

}

//
// ~CUTS_Setaf_Interpreter
//
CUTS_Setaf_Interpreter::~CUTS_Setaf_Interpreter (void)
{
  variable_map::iterator var_iter;
  for (var_iter = this->state_variables_.begin ();
       var_iter != this->state_variables_.end ();
       var_iter++)
    delete var_iter->second;

  CUTS_SETAF_UTILS::Setaf_Entries::iterator dp_iter;
  for (dp_iter = this->datapoints_.begin ();
       dp_iter != this->datapoints_.end ();
       dp_iter++)
    delete *dp_iter;

  CUTS_SETAF_UTILS::Setaf_Relations::iterator rel_iter;
  for (rel_iter = this->relations_.begin ();
       rel_iter != this->relations_.end ();
       rel_iter++)
    delete *rel_iter;
}

//
// init
//
void CUTS_Setaf_Interpreter::init (void)
{
  // Initialize all the variables in the map
  variable_map::iterator it;

  for (it = this->state_variables_.begin ();
       it != this->state_variables_.end (); it++)
  {
    it->second->init ();
  }
}

//
// update_log_format
//
void CUTS_Setaf_Interpreter::update_log_format (CUTS_Log_Format * lfmt)
{
  // Add new log format variables for this log format.

  const ACE_CString & name = lfmt->name ();

  CUTS_SETAF_UTILS::lf_iterator it;

  for (it = this->datapoints_.begin ();
       it != this->datapoints_.end (); it++)
  {
    if ((*it)->name ().c_str () == name)
    {
      this->add_variable (lfmt,
                         (*it)->id ().c_str (),
                         (*it)->type ().c_str ());
    }
  }
}

//
// update_relations
//
void CUTS_Setaf_Interpreter::update_relations (CUTS_Log_Format * lfmt)
{

  // Add new log format relations for this log format.

  const ACE_CString & name = lfmt->name ();

  CUTS_SETAF_UTILS::rel_iterator it;

  for (it = this->relations_.begin ();
       it != this->relations_.end (); it++)
  {
    if ((*it)->cause_lf ().c_str () == name)
    {
      this->add_relation (lfmt,
                         (*it)->effect_lf ().c_str (),
                         (*it)->cause_var ().c_str (),
                         (*it)->effect_var ().c_str ());
    }
  }

}

//
// update_values
//
void CUTS_Setaf_Interpreter::
update_values (CUTS_Log_Format_Variable_Table & vars,
               CUTS_Log_Format * lfmt)
{
  // We execute the set of commands associated with
  // each log format

  const ACE_CString & name = lfmt->name ();
  std::string key (name.c_str ());

  command_list & list =
    this->log_format_adapts_.find (key)->second;

  command_list::iterator it;

  for (it = list.begin (); it != list.end (); it++)
    (*it)->execute (vars);

}

//
// reset
//
void CUTS_Setaf_Interpreter::reset ()
{
  // Reset all the interpreter variables

  variable_map::iterator it;

  for (it = this->state_variables_.begin ();
       it != this->state_variables_.end ();
       it++)
  {
    it->second->reset ();
  }
}

//
// close
//
void CUTS_Setaf_Interpreter::close ()
{
  delete this;
}

//
// add_state_variable
//
void CUTS_Setaf_Interpreter::
add_state_variable (std::string & name, CUTS_Setaf_Variable * var)
{
  this->state_variables_.insert (
    std::pair <std::string, CUTS_Setaf_Variable *> (
    name, var));
}

//
// add_setaf_datapoint
//
void CUTS_Setaf_Interpreter::
add_setaf_datapoint (CUTS_Setaf_Log_Format * datapoint)
{
  this->datapoints_.push_back (datapoint);
}

//
// add_setaf_relation
//
void CUTS_Setaf_Interpreter::
add_setaf_relation (CUTS_Setaf_Log_Format_Relation * relation)
{
  this->relations_.push_back (relation);
}

//
// add_setaf_command
//
void CUTS_Setaf_Interpreter::
add_setaf_command (string_vector & lf_names,
                   CUTS_Setaf_Command * cmd)
{
  string_vector::iterator sit;

  for (sit = lf_names.begin ();
       sit != lf_names.end ();
       sit++)
  {
    // First check whether this log format have being
    // added previously

    command_map::iterator it =
      this->log_format_adapts_.find (*sit);

    if (it != this->log_format_adapts_.end ())
      (*it).second.push_back (cmd);

    // If not create a new list and add the command
    else
    {
      command_list list;
      list.push_back (cmd);
      this->log_format_adapts_.insert (
        std::pair <std::string, command_list> (*sit, list));
    }
  }
}

//
// set_init_value
//
void CUTS_Setaf_Interpreter::set_init_value (
  std::string & var_name, std::string & val)
{
  CUTS_Setaf_Variable * var =
    this->state_variables_.find (var_name)->second;

  var->init_value (val);
}

//
// set_reset_value
//
void CUTS_Setaf_Interpreter::set_reset_value (
  std::string & var_name, std::string & val)
{
  CUTS_Setaf_Variable * var =
    this->state_variables_.find (var_name)->second;

  var->reset_value (val);
}

//
// create_assignment_command
//
void CUTS_Setaf_Interpreter::
create_assignment_command (std::string & lhs_qual_name,
                           std::string & rhs_qual_name,
                           string_vector & lf_names)
{
  // First get the variables either interpreter variables
  // or unite variables associated with the name.

  CUTS_Setaf_Variable * lhs_var = 0;
  CUTS_Setaf_Variable * rhs_var = 0;

  this->get_variable (lhs_qual_name, &lhs_var);
  this->get_variable (rhs_qual_name, &rhs_var);

  // We have the two variables, so create the command.

  CUTS_Setaf_Command * command = 0;

  ACE_NEW_THROW_EX (command,
                    CUTS_Setaf_Assignment_Command (lhs_var, rhs_var),
                    ACE_bad_alloc ());

  // Now add the command to the relevant log formats

  this->add_setaf_command (lf_names, command);
}

//
// create_increment_command
//
void CUTS_Setaf_Interpreter::
create_increment_command (std::string & incr_var_qual_name,
                          string_vector & lf_names)
{
  // First get the variables either interpreter variables
  // or unite variables associated with the name.

  CUTS_Setaf_Variable * incr_var = 0;

  this->get_variable (incr_var_qual_name, &incr_var);

  CUTS_Setaf_Command * command = 0;

  ACE_NEW_THROW_EX (command,
                    CUTS_Setaf_Increment_Command (incr_var),
                    ACE_bad_alloc ());

  // Now add the command to the relevant log formats.

  this->add_setaf_command (lf_names, command);

}

//
// create_add_command
//
void CUTS_Setaf_Interpreter::
create_integer_add_command (std::string & lhs_var_qual_name,
                    std::string & operand1_qual_name,
                    int operand2,
                    string_vector & lf_names)
{
  // First get the variables either interpreter variables
  // or unite variables associated with the name.

  CUTS_Setaf_Variable * lhs_var = 0;
  CUTS_Setaf_Variable * operand1_var = 0;
  CUTS_Setaf_Variable * operand2_var = 0;


  this->get_variable (lhs_var_qual_name, &lhs_var);
  this->get_variable (operand1_qual_name, &operand1_var);

  ACE_NEW_THROW_EX (operand2_var,
                    CUTS_Setaf_Integer_Constant (operand2),
                    ACE_bad_alloc ());

  CUTS_Setaf_Command * command = 0;

  ACE_NEW_THROW_EX (command,
                    CUTS_Setaf_Add_Command (lhs_var, operand1_var, operand2_var),
                    ACE_bad_alloc ());

  // Now add the command to the relevant log formats.

  this->add_setaf_command (lf_names, command);

}

//
// create_add_command
//
void CUTS_Setaf_Interpreter::
create_variable_add_command (std::string & lhs_var_qual_name,
                    std::string & operand1_qual_name,
                    std::string & operand2_qual_name,
                    string_vector & lf_names)
{
  // First get the variables either interpreter variables
  // or unite variables associated with the name.

  CUTS_Setaf_Variable * lhs_var = 0;
  CUTS_Setaf_Variable * operand1_var = 0;
  CUTS_Setaf_Variable * operand2_var = 0;


  this->get_variable (lhs_var_qual_name, &lhs_var);
  this->get_variable (operand1_qual_name, &operand1_var);
  this->get_variable (operand2_qual_name, &operand2_var);

  CUTS_Setaf_Command * command = 0;

  ACE_NEW_THROW_EX (command,
                    CUTS_Setaf_Add_Command (lhs_var, operand1_var, operand2_var),
                    ACE_bad_alloc ());

  // Now add the command to the relevant log formats.

  this->add_setaf_command (lf_names, command);

}


//
// get_variable
//
void CUTS_Setaf_Interpreter::
get_variable (std::string & var_qual_name,
              CUTS_Setaf_Variable ** setaf_var)
{
  // If the variable is a unite variable then it is
  // enclosed within [ and ]. Otherwise it is an
  // interpreter variables.

  size_t found;
  std::string var_name;

  found = var_qual_name.find_first_of ("[");
  if (found != std::string::npos)
  {
    // If it is a unite variable we have to
    // create it.
    size_t found_last;
    found_last = var_qual_name.find_first_of ("]");
    if (found_last != std::string::npos)
    {
      var_name = var_qual_name.substr ( found + 1,
                                        found_last - found - 1);
      ACE_NEW_THROW_EX (*setaf_var,
                        CUTS_Setaf_Unite_Variable (var_name),
                        ACE_bad_alloc ());
    }
    else
      ACE_ERROR ((LM_ERROR,
                 ACE_TEXT ("%T (%t) - %M - Missing ] in the variable %s;\n"),
                 var_qual_name.c_str ()));
  }
  // If it is an interpreter variable no need to create it,
  // just load it from the map.
  else
    *setaf_var = this->state_variables_.find (var_qual_name)->second;
  }