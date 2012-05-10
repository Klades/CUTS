// $Id

#ifndef _CUTS_DMAC_CANDIDATE_RELATION_H
#define _CUTS_DMAC_CANDIDATE_RELATION_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Utils.h"
#include "Dmac_Log_Format.h"

// Represent a possible variable
// relation
struct var_relation
{
  int cause_var;
  int effect_var;
  int sup_count;
};

/**
 * @class CUTS_Dmac_Candidate_Relation
 *
 * Represent a candidate relation with beleif
 */
class CUTS_Dmac_Candidate_Relation
{
public:

  // Initializing constructor
  CUTS_Dmac_Candidate_Relation (CUTS_Dmac_Log_Format * cause_lf,
                                CUTS_Dmac_Log_Format * effect_lf);

  // Destructor
  ~CUTS_Dmac_Candidate_Relation (void);


private:

  // Get the total support
  long count_support (void);

  // Populate the cause_effect tables
  void populate_cause_effect_vars (void);

  // Calculate the variable evidence
  void calculate_var_evidence (void);

  // Calculate the time evidence
  void calculate_time_evidence (void);

  CUTS_Dmac_Log_Format * cause_lf_;

  CUTS_Dmac_Log_Format * effect_lf_;

  double var_evidence_;

  double time_evidence_;

  long support_;

  std::vector <var_relation> cause_effect_vars_;

};

#endif