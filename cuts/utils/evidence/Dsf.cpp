#include "Dsf.h"

//
// CUTS_Dsf
//
CUTS_Dsf::CUTS_Dsf (void)
{
}

//
// ~CUTS_Dsf
//
CUTS_Dsf::~CUTS_Dsf (void)
{

}

//
// add_evidence
//
void CUTS_Dsf::
add_evidence (double positive, double negative)
{
  // Adds a new evidence source. It shoould
  // provide the value for relation beong true.

  CUTS_Dsf::EVIDENCE ev;

  ev.insert (
    std::pair <CUTS_Dsf::powerset_member, double> (CUTS_DSF_YES, positive));
  ev.insert (
    std::pair <CUTS_Dsf::powerset_member, double> (CUTS_DSF_NO, negative));
  ev.insert (
    std::pair <CUTS_Dsf::powerset_member, double> (CUTS_DSF_NULL_SET, 0.0));
  ev.insert (
    std::pair <CUTS_Dsf::powerset_member, double> (CUTS_DSF_THETA, 1-positive-negative));

  this->evidences_.push_back (ev);
}

//
// combine_evidence
//

double CUTS_Dsf::combine_evidence (void)
{
  std::vector <CUTS_Dsf::EVIDENCE>::iterator ev_iter
    = this->evidences_.begin ();
  std::vector <CUTS_Dsf::EVIDENCE>::iterator ev_last
    = this->evidences_.end ();

  // Initially combined mass is the mass of first
  // evidence
  this->total_mass_ = this->evidences_.at (0);

  ev_iter++;

  while (ev_iter != ev_last)
  {
    // Add masses in each iterations
    CUTS_Dsf::EVIDENCE temp;
    CUTS_Dsf::EVIDENCE::iterator it1, it2, temp_it;

    for (it2 = this->total_mass_.begin ();
         it2 != this->total_mass_.end (); it2++)
    {
      for (it1 = ev_iter->begin (); it1 != ev_iter->end (); it1++)
      {
        // Do the intersection and find the member which needs to be
        // updated.
        CUTS_Dsf::powerset_member member =
          this->intersected_value (it1->first, it2->first);
        temp_it = temp.find (member);
        if (temp_it != temp.end ())
        {
          temp_it->second = temp_it->second + (it1->second * it2->second);
        }
        else
          temp.insert (std::pair <CUTS_Dsf::powerset_member, double> (member, it1->second * it2->second));
      }
    }

    this->total_mass_.clear ();
    this->total_mass_ = temp;
    temp.clear ();
    ev_iter++;
  }

  return this->total_mass_ [CUTS_DSF_YES];
}

CUTS_Dsf::powerset_member CUTS_Dsf::
intersected_value (CUTS_Dsf::powerset_member val1,
                   CUTS_Dsf::powerset_member val2)
{
  // Get the intersection of powerset items for a
  // frame of discernment having two members.

  if (val1 == CUTS_DSF_NULL_SET || val2 == CUTS_DSF_NULL_SET)
    return CUTS_DSF_NULL_SET;

  if (val1 == val2)
    return val1;

  if (val1 == CUTS_DSF_THETA)
    return val2;

  if (val2 == CUTS_DSF_THETA)
    return val1;

  return CUTS_DSF_NULL_SET;
}