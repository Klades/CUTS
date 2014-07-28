#ifndef _CUTS_DMAC_TIME_EVIDENCE_H
#define _CUTS_DMAC_TIME_EVIDENCE_H

#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Log_Format.h"
#include "cuts/utils/evidence/DSF_Evidence.h"
#include "Dmac_export.h"

/**
 * @class CUTS_Dmac_Time_Evidence
 *
 * Represent Evidence for cause-effect based on event occurring times
 */
class CUTS_DMAC_Export CUTS_Dmac_Time_Evidence : public CUTS_DSF_Evidence
{
public:

  // Default constructor
  CUTS_Dmac_Time_Evidence (void);

  // Destructor
  ~CUTS_Dmac_Time_Evidence (void);

  /// Calculate evidences
  double calculate (CUTS_Dmac_Log_Format * cause_lf,
                    CUTS_Dmac_Log_Format * effect_lf);

};


#endif