#ifndef _CUTS_DSF_EVIDENCE_H
#define _CUTS_DSF_EVIDENCE_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dsf_export.h"
#include <map>
#include <vector>


namespace CUTS_DSF
{
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

  // The values of Basic Beleif Assignments (BBA)
  typedef std::map <CUTS_DSF::powerset_member, double> BBA_TABLE;
}

/**
 * @class CUTS_DSF_Evidence
 *
 * Represent an evidence source
 */
class CUTS_DSF_Export CUTS_DSF_Evidence
{
public:

  // Default constructor
  CUTS_DSF_Evidence (void);

  // Destructor
  ~CUTS_DSF_Evidence (void);

  // Set the bba.
  void set_bba (double positive, double negative);

  CUTS_DSF::BBA_TABLE mass_table_;

};

#endif