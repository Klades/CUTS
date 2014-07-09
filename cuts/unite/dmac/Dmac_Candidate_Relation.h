// $Id

#ifndef _CUTS_DMAC_CANDIDATE_RELATION_H
#define _CUTS_DMAC_CANDIDATE_RELATION_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Utils.h"
#include "Dmac_Log_Format.h"
#include "Dmac_Variable_Evidence.h"
#include "Dmac_Time_Evidence.h"
#include "Dmac_Domain_Evidence.h"
#include "Dmac_export.h"

/**
 * @class CUTS_Dmac_Candidate_Relation
 *
 * Represent a candidate relation with beleif
 */
class CUTS_DMAC_Export CUTS_Dmac_Candidate_Relation
{
public:

  // Initializing constructor
  CUTS_Dmac_Candidate_Relation (CUTS_Dmac_Log_Format * cause_lf,
                                CUTS_Dmac_Log_Format * effect_lf);

  // Destructor
  ~CUTS_Dmac_Candidate_Relation (void);

  // Populate the cause_effect tables
  void populate_cause_effect_vars (void);

  CUTS_Dmac_Log_Format * cause_lf (void);

  CUTS_Dmac_Log_Format * effect_lf (void);

  void calculate_belief (CUTS_DMAC_UTILS::int_double_map & knowledge_data);

  double belief (void);

  void var_evidence_val (double val);

  double var_evidence_val (void);

  double time_evidence_val (void);

  double domain_evidence_val (void);

  void belief (double val);

  void var_evidence_calculated (bool val);


private:

  CUTS_Dmac_Log_Format * cause_lf_;

  CUTS_Dmac_Log_Format * effect_lf_;

  double belief_;

  double var_evidence_val_;

  double time_evidence_val_;

  double domain_evidence_val_;

  bool var_evidence_calculated_;

  std::vector <var_relation> cause_effect_vars_;

  std::vector <CUTS_DSF_Evidence> evidences_;

};

#endif