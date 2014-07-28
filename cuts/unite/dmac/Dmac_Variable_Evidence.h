#ifndef _CUTS_DMAC_VARIABLE_EVIDENCE_H
#define _CUTS_DMAC_VARIABLE_EVIDENCE_H

#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Log_Format.h"
#include "cuts/utils/evidence/DSF_Evidence.h"
#include "Dmac_export.h"

// Represent a possible variable
// relation
struct var_relation
{
  int cause_var;
  int effect_var;
  int sup_count;
};


/**
 * @class CUTS_Dmac_Variable_Evidence
 *
 * Represent Evidence for cause-effect based on similar variable values
 */
class CUTS_DMAC_Export CUTS_Dmac_Variable_Evidence : public CUTS_DSF_Evidence
{
public:

  // Default constructor
  CUTS_Dmac_Variable_Evidence (void);

  // Destructor
  ~CUTS_Dmac_Variable_Evidence (void);

  /// Calculate evidences
  double calculate (CUTS_Dmac_Log_Format * cause_lf,
                    CUTS_Dmac_Log_Format * effect_lf,
                    std::vector <var_relation> & cause_effect_vars);

};

#endif