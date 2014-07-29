#include "DSF_Evidence_Combiner.h"

CUTS_DSF_Evidence_Combiner::
CUTS_DSF_Evidence_Combiner (
std::vector <CUTS_DSF_Evidence> & evidences)
: evidences_ (evidences),
  total_belief_ (0.0),
  plausibility_ (0.0)
{

}

CUTS_DSF_Evidence_Combiner::
~CUTS_DSF_Evidence_Combiner (void)
{

}

void CUTS_DSF_Evidence_Combiner::
calculate_belief (void)
{
  std::vector <CUTS_DSF_Evidence>::iterator ev_iter
    = this->evidences_.begin ();
  std::vector <CUTS_DSF_Evidence>::iterator ev_last
    = this->evidences_.end ();

  // Initially combined mass is the mass of first
  // evidence
  CUTS_DSF::BBA_TABLE total_mass = this->evidences_.at (0).mass_table_;

  ev_iter++;

  while (ev_iter != ev_last)
  {
    // Combine masses in each iterations
    CUTS_DSF::BBA_TABLE temp;
    CUTS_DSF::BBA_TABLE::iterator it1, it2, temp_it;

    for (it2 = total_mass.begin ();
         it2 != total_mass.end (); it2++)
    {
      for (it1 = ev_iter->mass_table_.begin ();
           it1 != ev_iter->mass_table_.end (); it1++)
      {
        // Do the intersection and find the member which needs to be
        // updated.
        CUTS_DSF::powerset_member member =
          this->intersected_value (it1->first, it2->first);
        temp_it = temp.find (member);
        if (temp_it != temp.end ())
        {
          temp_it->second = temp_it->second + (it1->second * it2->second);
        }
        else
          temp.insert (std::pair <CUTS_DSF::powerset_member, double> (member, it1->second * it2->second));
      }
    }

    // Now we need to handle the conflicting evidences.

    double conflict_factor = 1 - (temp.find (CUTS_DSF::CUTS_DSF_NULL_SET)->second);

    if (conflict_factor > 0)
    {
      temp [CUTS_DSF::CUTS_DSF_YES] = temp [CUTS_DSF::CUTS_DSF_YES] / conflict_factor;
      temp [CUTS_DSF::CUTS_DSF_NO] = temp [CUTS_DSF::CUTS_DSF_NO] / conflict_factor;
      temp [CUTS_DSF::CUTS_DSF_THETA] = temp [CUTS_DSF::CUTS_DSF_THETA] / conflict_factor;
      temp [CUTS_DSF::CUTS_DSF_NULL_SET] = 0.0;
    }

    total_mass.clear ();
    total_mass = temp;
    temp.clear ();
    ev_iter++;
  }

  this->total_belief_ = total_mass [CUTS_DSF::CUTS_DSF_YES];
  this->plausibility_ = 1 - total_mass [CUTS_DSF::CUTS_DSF_NO];
}


double CUTS_DSF_Evidence_Combiner::
plausibility (void)
{
  return this->plausibility_;
}

double CUTS_DSF_Evidence_Combiner::
total_belief (void)
{
  return this->total_belief_;
}

CUTS_DSF::powerset_member CUTS_DSF_Evidence_Combiner::
intersected_value (CUTS_DSF::powerset_member val1,
                   CUTS_DSF::powerset_member val2)
{
  // Get the intersection of powerset items for a
  // frame of discernment having two members.

  if (val1 == CUTS_DSF::CUTS_DSF_NULL_SET ||
      val2 == CUTS_DSF::CUTS_DSF_NULL_SET)
    return CUTS_DSF::CUTS_DSF_NULL_SET;

  if (val1 == val2)
    return val1;

  if (val1 == CUTS_DSF::CUTS_DSF_THETA)
    return val2;

  if (val2 == CUTS_DSF::CUTS_DSF_THETA)
    return val1;

  return CUTS_DSF::CUTS_DSF_NULL_SET;
}