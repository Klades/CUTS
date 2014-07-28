#include "Dmac_Variable_Evidence.h"
#include <iostream>

#define WEIGHT 0.95


bool compare_sup_count (var_relation & rel1,
                        var_relation & rel2)
{
  return rel1.sup_count < rel2.sup_count;
}



CUTS_Dmac_Variable_Evidence::
CUTS_Dmac_Variable_Evidence ()
{
}

CUTS_Dmac_Variable_Evidence::
~CUTS_Dmac_Variable_Evidence ()
{
}

double CUTS_Dmac_Variable_Evidence::
calculate (CUTS_Dmac_Log_Format * cause_lf,
           CUTS_Dmac_Log_Format * effect_lf,
           std::vector <var_relation> & cause_effect_vars)
{
  int combination_count = 0;

  // Algorithm for calculating the variable evidence

  std::vector <CUTS_Dmac_Log_Msg_Details *>::iterator it1, it2, current;

  for (it1 = cause_lf->msg_instances ().begin ();
       it1 != cause_lf->msg_instances ().end ();
       it1++)
  {
    for (it2 = effect_lf->msg_instances ().begin ();
         it2 != effect_lf->msg_instances ().end ();
         it2++)
    {
      combination_count++;
      current = it2;
      std::vector <var_relation>::iterator rel_it;
      for (rel_it = cause_effect_vars.begin ();
           rel_it != cause_effect_vars.end ();
           rel_it++)
      {
        // Now check for variable realtions. We have
        // to iterate through all the possible cause-effect
        // relations
        it2 = current;
        while (it2 != effect_lf->msg_instances ().end ())
        {
          if ((*it1)->var_table ()[rel_it->cause_var] ==
              (*it2)->var_table ()[rel_it->effect_var])
          {
            rel_it->sup_count++;
            break;
          }
          else
            it2++;
        }
      }
      break;
    }
  }

  // We return the relation with maximim support and makes it as the
  // variable evidence
  var_relation temp = *std::max_element (cause_effect_vars.begin (),
                                         cause_effect_vars.end (),
                                         compare_sup_count);

  size_t effect_msg_count = effect_lf->msg_instances ().size ();
  double positive_var_evidence;

  if (effect_msg_count > 0)
  {
    //positive_var_evidence = (double)temp.sup_count / (double)effect_msg_count;
    positive_var_evidence = (double)temp.sup_count / (double)combination_count;

    /*if (positive_var_evidence > 0)
    {
      std::cout << "Cause-var : " << temp.cause_var
                << "  Effect-var : " << temp.effect_var
                << std::endl;
    }*/
  }
  else
  {
    positive_var_evidence = 0.0;
  }

  this->set_bba (positive_var_evidence * WEIGHT, 0.0);

  return positive_var_evidence * WEIGHT;
}