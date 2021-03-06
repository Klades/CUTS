// $Id: Dmac_Log_Format.h

#ifndef _CUTS_DMAC_LOG_FORMAT_H_
#define _CUTS_DMAC_LOG_FORMAT_H_

#include <string>
#include <sstream>
#include <fstream>
#include "Dmac_Relation.h"
#include "Dmac_Utils.h"
#include "Dmac_Log_Msg_Details.h"
#include "cuts/utils/testing/Test_Database.h"
#include "adbc/SQLite/Connection.h"
#include "Dmac_export.h"


/**
 * @class CUTS_Dmac_Log_Format
 *
 * Represent a Log Format in DMAC
 */

class CUTS_Dmac_Candidate_Relation;
class CUTS_Dmac_Execution;

class CUTS_DMAC_Export CUTS_Dmac_Log_Format
{
public:

  // Type definition of variable table
  typedef std::map <int, std::vector <std::string> > variable_table;

  // Type definition of variable table iterator
  typedef variable_table::iterator var_iterator;

  /**
   * Initializing constructor
   *
   * @param[in]     id                       Id of the lof format
   * @param[in]     log_format_items         Set of words representing the log format
   */
  CUTS_Dmac_Log_Format (int id,
                        CUTS_DMAC_UTILS::string_vector & log_format_items);

  // Destrructor
  ~CUTS_Dmac_Log_Format (void);

  /**
   * add_varaible_values
   *
   * @param[in]     trace         set of words in the log message
   */
  void add_varaible_values (CUTS_DMAC_UTILS::string_vector & trace);

  /**
   * add_relation
   *
   * @param[in]     relation      The log format relation
   *
   */

  void add_relation (CUTS_Dmac_Relation & relation);

  /**
   * extract_variable_relations
   *
   * @param[in]     log_format    The effect log format
   * @param[in]     execution     The execution context
   */
  void extract_variable_relations (CUTS_Dmac_Log_Format * log_format);

  /**
   * match_item_set
   *
   * @param[in]     values1     operand1 for matching
   * @param[in]     values2     operand2 for matching
   * @return        Flag to tell whether the two sets are matching
   */
  bool match_item_set (CUTS_DMAC_UTILS::string_vector & values1,
                       CUTS_DMAC_UTILS::string_vector & values2);

  /**
   * Get log_format_items
   *
   * @return        vector of log format items
   */
  CUTS_DMAC_UTILS::string_vector & log_format_items (void);

  /**
   * Get the log format id
   *
   * @return        id
   */
  int id (void);

   /**
   * Print the relations for a particular execution related to
   * this log format
   *
   * @param[in]     execution     Execution related to this log format
   */
  void print_relations ();

  /**
   * Convert the log format into xml
   *
   * @param[in]     xml_content     The output stream
   * @param[in]     ex              The execution
   */
  void serialize (std::ofstream & xml_content);

   /**
   * Convert the log format variable into xml
   *
   * @param[in]     xml_content     The output stream
   * @param[in]     count           The id of the variable
   */
  void serialize_variable (std::ofstream & xml_content, int & count);

  /**
   * Get the coverage of this log format
   *
   * @return the coverage
   */
  long coverage (void);

  // Increment the coverage by one
  void increment_coverage (void);

  bool is_reachable (CUTS_Dmac_Log_Format * lf);

  void insert_msg_instance (ADBC::SQLite::Record * record,
                            CUTS_DMAC_UTILS::string_vector & trace);

  void sort_msg_instances (void);

  std::vector <CUTS_Dmac_Log_Msg_Details *> & msg_instances (void);

  void insert_execution (CUTS_Dmac_Execution * ex);

  bool has_similar_execution (CUTS_Dmac_Log_Format * lf);

  friend class CUTS_Dmac_Candidate_Relation;

  friend class CUTS_Dmac_Execution;


private:

  // Id of the log format
  int id_;

  // The set of words representing the log format
  CUTS_DMAC_UTILS::string_vector log_format_items_;

  // The relations for this log format
  std::vector <CUTS_Dmac_Relation> relations_;

  // Set of variables with instance values
  variable_table vars_;

  // details of the log message instances
  std::vector <CUTS_Dmac_Log_Msg_Details *> msg_instances_;

  // Executions where the log format is occurring
  std::vector <CUTS_Dmac_Execution *> execution_list_;

 // Number of messages covered by this log format
  long coverage_;

  // A flag which tells whether the instances are
  // sorted or not.
  bool sorted_;

};

#endif  // !defined _CUTS_DMAC_LOG_FORMAT_H_