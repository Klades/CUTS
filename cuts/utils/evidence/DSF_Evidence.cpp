#include "DSF_Evidence.h"

CUTS_DSF_Evidence::CUTS_DSF_Evidence (void)
{

}

CUTS_DSF_Evidence::~CUTS_DSF_Evidence (void)
{

}

void CUTS_DSF_Evidence::set_bba (double positive_val,
                                 double negative_val)
{
  // Sets the Basic Belief Assignments
  // provide the value for relation being true and false.

  this->mass_table_.insert (
    std::pair <CUTS_DSF::powerset_member, double> (CUTS_DSF::CUTS_DSF_YES, positive_val));

  this->mass_table_.insert (
    std::pair <CUTS_DSF::powerset_member, double> (CUTS_DSF::CUTS_DSF_NO, negative_val));

  this->mass_table_.insert (
    std::pair <CUTS_DSF::powerset_member, double> (CUTS_DSF::CUTS_DSF_NULL_SET, 0.0));

  this->mass_table_.insert (
    std::pair <CUTS_DSF::powerset_member, double> (CUTS_DSF::CUTS_DSF_THETA, 1-positive_val-negative_val));
}