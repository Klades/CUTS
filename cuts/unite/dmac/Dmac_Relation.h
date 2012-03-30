// $Id: Dmac_Relation.h

#ifndef _CUTS_DMAC_RELATION_H_
#define _CUTS_DMAC_RELATION_H_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Dmac_Utils.h"


// Forward declerations
class CUTS_Dmac_Log_Format;

/**
 * @class CUTS_Dmac_Relation
 *
 * Represent a relation between two log formats in DMAC
 */

class CUTS_Dmac_Relation
{
public:

  /**
   * Initializing constructor
   *
   * @param[in]     effect_lf       The effect log format
   */
  CUTS_Dmac_Relation (CUTS_Dmac_Log_Format * effect_lf);

  // Destructor
  ~CUTS_Dmac_Relation (void);

  /**
   * Add a cause effect variable pair
   *
   * @param[in]     cause_effect    the variable cause and effect pair
   */
  void add_cause_effect (CUTS_DMAC_UTILS::int_pair cause_effect);

  /**
   * Get the set of cause_effect pairs
   *
   * @return    cause_effect    Set of cause_effectt pairs
   */
  std::vector <CUTS_DMAC_UTILS::int_pair> & cause_effects ();

  /// overloaded = operator
  const CUTS_Dmac_Relation & operator = (const CUTS_Dmac_Relation & copy);

  /// overloaded == operator
  bool operator == (CUTS_Dmac_Relation & relation);

  /// overloadee != operator
  bool operator != (CUTS_Dmac_Relation & relation);

  /**
   * Convert the relation into xml
   *
   * @param[in]     cause_lf_    The output stream
   * @param[in]     execution    The execution this relation belongs to
   */
  void print_relation (CUTS_Dmac_Log_Format * cause_lf_);

 /**
   * Convert the relation into xml
   *
   * @param[in]    xml_content    The output stream
   */
  void serialize (std::ofstream & xml_content);

  friend class CUTS_Dmac_Log_Format;

private:

  // The effect log format of this relation
  CUTS_Dmac_Log_Format * effect_lf_;

  // The set of cause_effect relationships
  std::vector <CUTS_DMAC_UTILS::int_pair> cause_effects_;

};

#endif  // !defined _CUTS_DMAC_RELATION_H_