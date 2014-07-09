// $Id:
#ifndef _CUTS_SETAF_INTERPRETER_H_
#define _CUTS_SETAF_INTERPRETER_H_


#include "Setaf_Variable.h"
#include "Setaf_Utils.h"
#include "Setaf_export.h"
#include "cuts/unite/Log_Format_Adapter.h"
#include "Setaf_Command.h"
#include <map>



/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Interpreter
 *
 * Represent the SETAF interpreter.
 */

class CUTS_SETAF_Export CUTS_Setaf_Interpreter :
  public CUTS_Log_Format_Adapter
{
public:

  /// Type definition of a string vector
  typedef std::vector <std::string> string_vector;

  /// Type definition of the variable map
  typedef std::map <std::string, CUTS_Setaf_Variable *> variable_map;

  /// Type definition of the command list
  typedef std::vector <CUTS_Setaf_Command *> command_list;

  /// Type definition of the set of commands of log formats
  typedef std::map <std::string, command_list> command_map;

  /// constructor
  CUTS_Setaf_Interpreter (void);

  /// Destructor
  ~CUTS_Setaf_Interpreter (void);

  // init method
  void init ();

  /**
   * Add new log format variables to the log format.
   * @param[in]     lfmt   The log format variables need to be added.
   */
  void update_log_format (CUTS_Log_Format * lfmt);

  /**
   * Add new log format relations.
   * @param[in]     lfmt   The log format the relations need to be added.
   */
  void update_relations (CUTS_Log_Format * lfmt);

  /**
   * Populate values for the variables.
   * @param[in]     lhs   The set of log format variables.
   * @param[in]     rhs   The log format need to be adapted.
   */
  void update_values (CUTS_Log_Format_Variable_Table & vars,
                      CUTS_Log_Format * lfmt);

  // Reset the adapter
  void reset ();

  // Close the adapter
  void close ();

  /**
   * Add an interpreter variable to the table.
   * @param[in]     name   The name of the variable.
   * @param[in]     var    The log format need to be adapted.
   */
  void add_state_variable (std::string & name,
                           CUTS_Setaf_Variable * var);

  /**
   * Add a new log format variable.
   * @param[in]     datapoint   The log format variable need to added.
   */
  void add_setaf_datapoint (CUTS_Setaf_Log_Format * datapoint);

  /**
   * Add a new log format relation.
   * @param[in]     relation   Add a new log format relation.
   */
  void add_setaf_relation (CUTS_Setaf_Log_Format_Relation * relation);

  /**
   * Add a new adaptation command.
   * @param[in]     lf_names   The nams of the log format list.
   * @param[in]     cmd        Command need to be added..
   */
  void add_setaf_command (string_vector & lf_names,
                          CUTS_Setaf_Command * cmd);

  /**
   * Set the init value for the variable.
   * @param[in]     var_name   The name of the variable.
   * @param[in]     val        The init value.
   */
  void set_init_value (std::string & var_name,
                       std::string & val);

  /**
   * Set the reset value for the variable.
   * @param[in]     var_name   The name of the variable.
   * @param[in]     val        The reset value.
   */
  void set_reset_value (std::string & var_name,
                        std::string & val);

  /**
   * Create an assignemnt command
   * @param[in]     lhs_qual_name   The name of the left hand side variable.
   * @param[in]     rhs_qual_name   The name of the right hand side of the variable.
   * @param[in]     lf_name         The name of the log format.
   */
  void create_assignment_command (std::string & lhs_qual_name,
                                  std::string & rhs_qual_name,
                                  string_vector & lf_names);

  /**
   * Create an increment command
   * @param[in]     incr_var_qual_name    The name of the variable to be incremented.
   * @param[in]     lf_name               The name of the log format.
   */
  void create_increment_command (std::string & incr_var_qual_name,
                                 string_vector & lf_names);

  /**
   * Create an add command
   * @param[in]     lhs_var_qual_name     The name of the left hand side variable.
   * @param[in]     operand1_qual_name    The name of the right hand side of the variable.
   * @param[in]     value                 The value need to be added.
   * @param[in]     lf_name               The name of the log format.
   */
  void create_integer_add_command (std::string & lhs_var_qual_name,
                                   std::string & operand1_qual_name,
                                   int operand2,
                                   string_vector & lf_names);

  /**
   * Create an assignemnt command
   * @param[in]     lhs_var_qual_name     The name of the left hand side variable.
   * @param[in]     operand1_qual_name    The name of the right hand side of the variable.
   * @param[in]     value                 The value need to be added.
   * @param[in]     lf_name               The name of the log format.
   */
  void create_variable_add_command (std::string & lhs_var_qual_name,
                                    std::string & operand1_qual_name,
                                    std::string & operand2_qual_name,
                                    string_vector & lf_names);


private:

  /// Create or find a setaf variable using the name.
  void get_variable (std::string & var_qual_name,
                     CUTS_Setaf_Variable ** setaf_var);

  /// Table of setaf interpeter variables
  variable_map state_variables_;

  /// Set of new log format variables need to be added.
  CUTS_SETAF_UTILS::Setaf_Entries datapoints_;

  /// Set of new log format relations need to be added.
  CUTS_SETAF_UTILS::Setaf_Relations relations_;

  /// Set of commands to set the variable values for each log
  /// format.
  command_map log_format_adapts_;

};

#endif  // !defined _CUTS_SETAF_INTERPRETER_H_