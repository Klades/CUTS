// $Id: Setaf_Log_Format.h

#ifndef _CUTS_SETAF_FORMAT_H
#define _CUTS_SETAF_FORMAT_H



#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include <string>
#include <vector>


/**
 * @class CUTS_Setaf_Log_Format
 *
 * Represent Datapoints in the SETAF specification
 */

class CUTS_Setaf_Log_Format
{

public:

  /**
   * Initializing constructor
   *
   * @param[in]   type    Type of the new log format variable
   */
  CUTS_Setaf_Log_Format (std::string & type);

  // Destructor
  ~CUTS_Setaf_Log_Format ();

  /**
   * Get the name of the Log Format
   *
   * @param[in]   type    Type of the new log format variable
   */
  std::string & name ();

  /**
   * Get the Id of the Variable
   *
   * @return  variable id
   */
  std::string & id ();

  /**
   * Get the Type of the Variable
   *
   * @return  variable type
   */
  std::string & type ();

  /**
   * Process the log format variable string and populate the object
   *
   * @param[in]  format_string    String containing the log format variable
   */
  void process_format_string (std::string & format_string);

private:

  // Log format name
  std::string name_;

  // Variable name
  std::string id_;

  // Type of the variable
  std::string type_;

};

/**
 * @class CUTS_Setaf_Log_Format_Relation
 *
 * Represent Relations in the SETAF specification
 */

class CUTS_Setaf_Log_Format_Relation
{

public:
  // Default constructor
  CUTS_Setaf_Log_Format_Relation ();

  // Destructor
  ~CUTS_Setaf_Log_Format_Relation ();

  /**
   * Get the cause log format
   *
   * @return   Name of the cause log format
   */
  std::string & cause_lf ();

  /**
   * Get the cause log format variable
   *
   * @return   Name of the cause log format variable
   */
  std::string & cause_var ();

  /**
   * Get the effect log format
   *
   * @return   Name of the effect log format
   */
  std::string & effect_lf ();

  /**
   * Get the effect log format variable
   *
   * @return   Name of the effect log format variable
   */
  std::string & effect_var ();

  /**
   * Process the relation string and populate the object
   *
   * @param[in]   cause_string    String containing the cause
   * @param[in]   effect_string   String containing the effect
   */
  void process_relation_strings (std::string & cause_string,
                                 std::string & effect_string);

private:

  // String representing the cause log format
  std::string cause_lf_;

  // String representing the cause log format variable
  std::string cause_var_;

  // String representing the effect log format
  std::string effect_lf_;

  // String representing the effect log format variable
  std::string effect_var_;

};

/**
 * @class CUTS_Setaf_Log_Format_Code
 *
 * Represent Adaptation code in the SETAF specification
 */

class CUTS_Setaf_Log_Format_Code
{

public:

  /**
   * Initializing constructor
   *
   * @param[in]   code_id    Id of the code block
   * @param[in]   adaptation_code     String representing the code block
   */
  CUTS_Setaf_Log_Format_Code (std::string & code_id,
                              std::string & adaptation_code);

  // Destructor
  ~CUTS_Setaf_Log_Format_Code ();

  /**
   * Get the Id of the code block
   *
   * @return   String Id of the code block
   */
  std::string & code_id ();

  /**
   * Get the adaptation code
   *
   * @return   String adaptation code.
   */
  std::string & adaptation_code ();


private:
  // Id of the code block
  std::string code_id_;

  // Adaptation code
  std::string adaptation_code_;

};


#if defined (__CUTS_INLINE__)
#include "Setaf_Format.inl"
#endif

#endif /* _CUTS_SETAF_FORMAT_H */