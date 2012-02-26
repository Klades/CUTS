// $Id:
#ifndef _CUTS_SETAF_VARIABLE_H_
#define _CUTS_SETAF_VARIABLE_H_


#include <string>
#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Setaf_export.h"
#include "cuts/unite/Variable_Table.h"
#include "Setaf_Utils.h"


/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Variable
 *
 * Base class for a SETAF Variable.
 */

class CUTS_SETAF_Export CUTS_Setaf_Variable
{
public:

  /// Constructor
  CUTS_Setaf_Variable (void);

  /// Destructor
  virtual ~CUTS_Setaf_Variable (void);

  /**
   * Set the init value
   * @param[in]     val    Initializing value.
   */
  virtual void init_value (std::string & val) = 0;

  /**
   * Set the reset value
   * @param[in]    val    Reset value.
   */
  virtual void reset_value (std::string & val) = 0;

  /**
   * Assign a new value to the variable
   * @param[in]     var       The right hand side variable.
   * @param[in]     vars      The variable table from UNITE.
   */
  virtual void assign_value (CUTS_Setaf_Variable * var,
                             CUTS_Log_Format_Variable_Table & vars) = 0;

  /// Initialize the variable
  virtual void init (void) = 0;

  /// Reset the variable
  virtual void reset (void) = 0;

  /// Increment the variable
  virtual void increment (void) = 0;

  /// Additional type information, this is required during
  /// assignment.
  CUTS_SETAF_UTILS::type_t type_;

};


/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_State_Variable
 *
 * Represent interpreter state variables.
 */

class CUTS_SETAF_Export CUTS_Setaf_State_Variable :
  public CUTS_Setaf_Variable
{
public:

  /// Constructor
  CUTS_Setaf_State_Variable (void);

  /// Destructor
  ~CUTS_Setaf_State_Variable (void);

  /// Set the init value
  virtual void init_value (std::string & val) = 0;

  /// Set the reset value
  virtual void reset_value (std::string & val) = 0;

  /// Assign a new value to the variable
  virtual void assign_value (CUTS_Setaf_Variable * var,
                             CUTS_Log_Format_Variable_Table & vars) = 0;

  /// Init the variable
  virtual void init (void) = 0;

  /// Reset the variable
  virtual void reset (void) = 0;

  /// Increment the variable.
  virtual void increment (void) = 0;

};


/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Integer_Variable
 *
 * Represent Interpreter State integer variable.
 */

class CUTS_SETAF_Export CUTS_Setaf_Integer_Variable :
  public CUTS_Setaf_State_Variable
{
public:

  /// Constructor
  CUTS_Setaf_Integer_Variable (void);

  /// Destructor
  ~CUTS_Setaf_Integer_Variable (void);

  /// Set the init value.
  virtual void init_value (std::string & val);

  /// Set the reset value.
  virtual void reset_value (std::string & val);

  /// Assign a new value to the variable
  virtual void assign_value (CUTS_Setaf_Variable * var,
                             CUTS_Log_Format_Variable_Table & vars);

  /// Initialize the value of the variable
  virtual void init (void);

  /// Reset the value of the variable
  virtual void reset (void);

  /// Increment the value of the variable by one
  virtual void increment (void);

  /// Get the value
  int value (void);

  /// Increment the value by val
  void add_value (int val);


private:

  /// The current value of the variable
  int value_;

  /// The initializing value set when init is called
  int init_value_;

  /// Reset value set when reset is called
  int reset_value_;

};



/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_String_Variable
 *
 * Represent Interpreter state String variable.
 */

class CUTS_SETAF_Export CUTS_Setaf_String_Variable :
  public CUTS_Setaf_State_Variable
{
public:

  /// Constructor
  CUTS_Setaf_String_Variable (void);

  /// Destructor
  ~CUTS_Setaf_String_Variable (void);

  /// Set the initializing value
  virtual void init_value (std::string & val);

  /// Set the resetting value
  virtual void reset_value (std::string & val);

  /// Assign a new value to the variable
  virtual void assign_value (CUTS_Setaf_Variable * var,
                             CUTS_Log_Format_Variable_Table & vars);

  /// Set to the init value
  virtual void init (void);

  /// Set to the reset value
  virtual void reset (void);

  /// Increment the value
  virtual void increment (void);

  /// Get the value
  std::string & value (void);


private:

  /// Value of the variable
  std::string value_;

  /// Variable is set to this value when
  /// init is called
  std::string init_value_;

  /// Variable is set to this value when
  /// reset is called.
  std::string reset_value_;

};


/**
 * @ingroup SETAF_Common
 *
 * @class CUTS_Setaf_Unite_Variable
 *
 * Represent Variables created from UNITE.
 */

class CUTS_Setaf_Unite_Variable :
  public CUTS_Setaf_Variable
{
public:

  /// Constructor
  CUTS_Setaf_Unite_Variable (std::string & name);

  /// Destructor
  ~CUTS_Setaf_Unite_Variable (void);

  /// Set the init value
  virtual void init_value (std::string & val);

  /// Set the reset value
  virtual void reset_value (std::string & val);

  /// Assign a new value to the variable
  virtual void assign_value (CUTS_Setaf_Variable * var,
                             CUTS_Log_Format_Variable_Table & vars);

  /// Initialize the value
  virtual void init (void);

  /// Reset the value
  virtual void reset (void);

  /// Increment the value
  virtual void increment (void);

  /// Get the name of the unite variable
  std::string & name (void);


private:

  /// The name of the unite variable
  std::string name_;

};

#endif  // !defined _CUTS_SETAF_VARIABLE_H_