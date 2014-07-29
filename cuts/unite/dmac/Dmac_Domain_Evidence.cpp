#include "Dmac_Domain_Evidence.h"


CUTS_Dmac_Domain_Evidence::
CUTS_Dmac_Domain_Evidence (CUTS_DMAC_UTILS::int_double_map & knowledge_data)
: knowledge_data_ (knowledge_data)
{
}

CUTS_Dmac_Domain_Evidence::
~CUTS_Dmac_Domain_Evidence (void)
{

}

double CUTS_Dmac_Domain_Evidence::
calculate (CUTS_Dmac_Log_Format * cause_lf,
           CUTS_Dmac_Log_Format * effect_lf)
{
  CUTS_DMAC_UTILS::int_double_map::iterator it;
  double positive_val = 0.0;
  double negative_val = 0.0;

  bool found = false;

  for (it = this->knowledge_data_.begin ();
       it != this->knowledge_data_.end (); it++)
  {
    if ((it->first.first == cause_lf->id ()) &&
       (it->first.second == effect_lf->id ()))
    {
      //positive_val = it->second;
      positive_val = 0.9;
      found = true;
      break;
    }
  }

  if (!found)
    negative_val = 0.9;

  this->set_bba (positive_val, negative_val);

  return positive_val;
}