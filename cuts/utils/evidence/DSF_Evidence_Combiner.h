#ifndef _CUTS_DSF_EVIDENCE_COMBINER_H
#define _CUTS_DSF_EVIDENCE_COMBINER_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dsf_export.h"
#include <map>
#include <vector>
#include "DSF_Evidence.h"

/**
 * @class CUTS_DSF_Evidence_Combiner
 *
 * Implements evidence combining framework
 */
class CUTS_DSF_Export CUTS_DSF_Evidence_Combiner
{
public:

  // Default constructor
  CUTS_DSF_Evidence_Combiner (
    std::vector <CUTS_DSF_Evidence> & evidences);

  // Destructor
  ~CUTS_DSF_Evidence_Combiner (void);

  // Calculate the belief
  void calculate_belief (void);

  double total_belief (void);

  double plausibility (void);

  // Get the intersection of the powersets
  CUTS_DSF::powerset_member intersected_value (CUTS_DSF::powerset_member val1,
                                               CUTS_DSF::powerset_member val2);

private:

  std::vector <CUTS_DSF_Evidence> & evidences_;

  double total_belief_;

  double plausibility_;

};

#endif