// $Id$

#ifndef _CUTS_DSF_H
#define _CUTS_DSF_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dsf_export.h"
#include <map>
#include <vector>


/**
 * @class CUTS_Dsf
 *
 * Represent DS theory based framework
 */
class CUTS_DSF_Export CUTS_Dsf
{
public:

  /// Reprsent all the members of a frame
  /// of discernment when there are two items
  enum powerset_member
  {
    // Relation holds
    CUTS_DSF_YES,

    // Relation does not hold
    CUTS_DSF_NO,

    // Empty set
    CUTS_DSF_NULL_SET,

    // The uncertainity portion
    CUTS_DSF_THETA
  };

  // The values of a source of evidence
  typedef std::map <CUTS_Dsf::powerset_member, double> EVIDENCE;

  // Default constructor
  CUTS_Dsf (void);

  // Destructor
  ~CUTS_Dsf (void);

  // create a new evidence source and add it to the current
  // list
  void add_evidence (double positive, double negative = 0);

  // Use DEmpster's rule to combine evidences.
  double combine_evidence (void);

private:

  // Get the intersection of the powersets
  CUTS_Dsf::powerset_member intersected_value (CUTS_Dsf::powerset_member val1,
                                               CUTS_Dsf::powerset_member val2);

  // List of evidences
  std::vector <CUTS_Dsf::EVIDENCE> evidences_;

  // Total beleif
  CUTS_Dsf::EVIDENCE total_mass_;

};

#endif