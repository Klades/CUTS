#include "Dmac_Relation.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Dmac_Log_Format.h"


//
// CUTS_Dmac_Relation
//
CUTS_Dmac_Relation::CUTS_Dmac_Relation (CUTS_Dmac_Log_Format * effect_lf,
                                        CUTS_Dmac_Execution * execution)
: effect_lf_ (effect_lf),
  execution_ (execution)
{

}

//
// ~CUTS_Dmac_Relation
//
CUTS_Dmac_Relation::~CUTS_Dmac_Relation (void)
{

}

//
// add_cause_effect
//
void CUTS_Dmac_Relation::add_cause_effect (CUTS_DMAC_UTILS::int_pair cause_effect)
{
  this->cause_effects_.push_back (cause_effect);
}

//
// print_relation
//
void CUTS_Dmac_Relation::print_relation (CUTS_Dmac_Log_Format * cause_lf,
                                         CUTS_Dmac_Execution * execution)
{

  if (this->execution_ == execution)
  {
    std::stringstream cause_lf_string;
    cause_lf_string << "LF" << cause_lf->id ();

    std::stringstream effect_lf_string;
    effect_lf_string << "LF" << this->effect_lf_->id ();

    std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it;

    for (it = this->cause_effects_.begin (); it != this->cause_effects_.end (); it++)
    {
      std::cout << cause_lf_string.str () << "." << (*it).first <<" = ";
      std::cout << effect_lf_string.str () << "." << (*it).second << std::endl;
    }
  }
}

//
// = operator
//
const CUTS_Dmac_Relation &
CUTS_Dmac_Relation::operator = (const CUTS_Dmac_Relation & copy)
{
  // Assign one relation to the other

  if (this == &copy)
    return *this;

  this->effect_lf_ = copy.effect_lf_;
  this->cause_effects_ = copy.cause_effects_;

  return *this;
}

//
// == operator
//
bool
CUTS_Dmac_Relation::operator == (CUTS_Dmac_Relation & relation)
{
  // Check the similarity between two log formats

  if (this->effect_lf_->id ()==
      relation.effect_lf_->id ())
  {
    // cause-effect relations should be the same.

    if (this->cause_effects_.size () !=
          relation.cause_effects_.size ())
      return false;

    std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it1;
    std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it2;

    for (it1 = relation.cause_effects_.begin ();
          it1 != relation.cause_effects_.end (); it1++)
    {
      for (it2 = this->cause_effects_.begin ();
            it2 != this->cause_effects_.end (); it2++)
      {
        if ((it1->first != it2->first) ||
            (it1->second != it2->second))
          return false;
      }
    }
    return true;

  }
  else
    return false;
}

//
// != operator
//
bool
CUTS_Dmac_Relation::operator != (CUTS_Dmac_Relation & relation)
{
  return !((*this) == relation);
}

//
// cause_effects
//
std::vector <CUTS_DMAC_UTILS::int_pair> & CUTS_Dmac_Relation::cause_effects ()
{
  return this->cause_effects_;
}

//
// serialize
//
void CUTS_Dmac_Relation::serialize (std::ofstream & xml_content)
{
  // Convert the relations and all its cause-effects to
  // xml

  xml_content
    << "<relation effectref=\"LF" << this->effect_lf_->id ()
    << "\">" << std::endl;

  std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it1;

  for (it1 = this->cause_effects_.begin ();
       it1 != this->cause_effects_.end (); it1++)
  {
    xml_content
      << "<causality cause=\"X" << (*it1).first << "\" "
      << "effect=\"X" << (*it1).second << "\" />"
      << std::endl;
  }

  xml_content
    << "</relation>"
    << std::endl;

}

//
// execution
//
CUTS_Dmac_Execution * CUTS_Dmac_Relation::execution ()
{
  return this->execution_;
}