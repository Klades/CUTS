// $Id:
#ifndef _CUTS_SETAF_COMMAND_H_
#define _CUTS_SETAF_COMMAND_H_


#include <string>
#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Setaf_export.h"
#include "Setaf_Variable.h"
#include "cuts/unite/Variable_Table.h"

/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Command
 *
 * Base class for adaptation commnads.
 */


class CUTS_SETAF_Export CUTS_Setaf_Command
{
public:

  /// Constructor
  CUTS_Setaf_Command (void);

  /// Destructor
  virtual ~CUTS_Setaf_Command (void);

  /**
   * Execute the command and update the variable values.
   * @param[in]     vars   The set of variables of a log format.
   */
  virtual void execute (CUTS_Log_Format_Variable_Table & vars) = 0;

};



/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Assignment_Command
 *
 * Represent an assignment command in SETAF.
 */

class CUTS_SETAF_Export CUTS_Setaf_Assignment_Command :
  public CUTS_Setaf_Command
{
public:

  /**
   * Initializing Constructor.
   * @param[in]     lhs   The left hand side of the command.
   * @param[in]     rhs   The right hand side of the command.
   */
  CUTS_Setaf_Assignment_Command (CUTS_Setaf_Variable * lhs,
                                 CUTS_Setaf_Variable * rhs);

  /// Destructor
  ~CUTS_Setaf_Assignment_Command (void);

  /**
   * Execute the command and update the variable values.
   * @param[in]     vars   The set of variables of a log format.
   */
  virtual void execute (CUTS_Log_Format_Variable_Table & vars);

private:

  /// left hand side of an assignment command.
  CUTS_Setaf_Variable * lhs_;

  /// right hand side of an assignment command.
  CUTS_Setaf_Variable * rhs_;

};



/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Increment_Command
 *
 * Represent an Increment command in SETAF.
 */

class CUTS_SETAF_Export CUTS_Setaf_Increment_Command :
  public CUTS_Setaf_Command
{
public:

  /**
   * Initializing Constructor.
   * @param[in]     incr_var   The variable to incremented.
   */
  CUTS_Setaf_Increment_Command (CUTS_Setaf_Variable * incr_var);

  /// Destructor
  ~CUTS_Setaf_Increment_Command (void);

  /**
   * Execute the command and update the variable values.
   * @param[in]     vars   The set of variables of a log format.
   */
  virtual void execute (CUTS_Log_Format_Variable_Table & vars);

private:

  /// The variable to be incremented.
  CUTS_Setaf_Variable * incr_var_;

};




/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Add_Command
 *
 * Represent an Addition command in SETAF.
 */

class CUTS_SETAF_Export CUTS_Setaf_Add_Command :
  public CUTS_Setaf_Command
{
public:

  /**
   * Initializing Constructor.
   * @param[in]     lhs   The left hand side of the command.
   * @param[in]     rhs   The right hand paramter.
   * @param[in]     value The value which need to be added to the variable.
   */
  CUTS_Setaf_Add_Command (CUTS_Setaf_Variable * lhs,
                          CUTS_Setaf_Variable * rhs,
                          int value);

  /// Destructor
  ~CUTS_Setaf_Add_Command (void);

  /**
   * Execute the command and update the variable values.
   * @param[in]     vars   The set of variables of a log format.
   */
  virtual void execute (CUTS_Log_Format_Variable_Table & vars);

private:

  /// The left hand side of the add command.
  CUTS_Setaf_Variable * lhs_;

  /// The right hand side of the add command.
  CUTS_Setaf_Variable * rhs_;

  /// The value need to be added.
  int value_;

};


#endif  // !defined _CUTS_SETAF_COMMAND_H_