#include "Dmac_Time_Evidence.h"
#include <iostream>

#define TIME_GAP 0.01


CUTS_Dmac_Time_Evidence::
CUTS_Dmac_Time_Evidence (void)
{

}

CUTS_Dmac_Time_Evidence::
~CUTS_Dmac_Time_Evidence (void)
{

}

double CUTS_Dmac_Time_Evidence::
calculate (CUTS_Dmac_Log_Format * cause_lf,
           CUTS_Dmac_Log_Format * effect_lf)
{
  std::vector <CUTS_Dmac_Log_Msg_Details *>::iterator it1, it2;
  long precedence_count = 0;
  double support = 0;
  double total = 0;

  long cause_lf_count = cause_lf->msg_instances ().size ();
  long effect_lf_count = effect_lf->msg_instances ().size ();

  for (it1 = cause_lf->msg_instances ().begin ();
       it1 != cause_lf->msg_instances ().end ();
       it1++)
  {
    for (it2 = effect_lf->msg_instances ().begin ();
         it2 != effect_lf->msg_instances ().end ();
         it2++)
    {
      if ((*it1)->time_val () <= (*it2)->time_val ())
      {
        precedence_count++;
        double diff = (*it2)->time_val () - (*it1)->time_val ();
        if (diff <= TIME_GAP)
        {
          support++;
          total = total + ((TIME_GAP - diff)/TIME_GAP);
          break;
        }
      }
    }
  }

  double avg_time_prob = total / support;
  double positive_time_evidence;

  if ((precedence_count > 0) && (support > 0))
    positive_time_evidence = ((double)support / (double)cause_lf_count) * avg_time_prob;
  else
    positive_time_evidence = 0.0;

  this->set_bba (positive_time_evidence, 0.0);

  return positive_time_evidence;
}