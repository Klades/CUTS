#ifndef _CUTS_DMAC_DOMAIN_EVIDENCE_H
#define _CUTS_DMAC_DOMAIN_EVIDENCE_H

#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Log_Format.h"
#include "cuts/utils/evidence/DSF_Evidence.h"
#include "Dmac_export.h"

/**
 * @class CUTS_Dmac_Domain_Evidence
 *
 * Represent Evidence for cause-effect based on event occurring Domains
 */
class CUTS_DMAC_Export CUTS_Dmac_Domain_Evidence : public CUTS_DSF_Evidence
{
public:

  // Default constructor
  CUTS_Dmac_Domain_Evidence (CUTS_DMAC_UTILS::int_double_map & knowledge_data);

  // Destructor
  ~CUTS_Dmac_Domain_Evidence (void);

  /// Calculate evidences
  double calculate (CUTS_Dmac_Log_Format * cause_lf,
                    CUTS_Dmac_Log_Format * effect_lf);

private:

  CUTS_DMAC_UTILS::int_double_map & knowledge_data_;

};


#endif