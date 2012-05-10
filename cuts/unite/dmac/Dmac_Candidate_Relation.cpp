#include "Dmac_Candidate_Relation.h"

#define TIME_GAP 1


bool compare_sup_count (var_relation & rel1,
                        var_relation & rel2)
{
  return rel1.sup_count < rel2.sup_count;
}

//
// CUTS_Dmac_Candidate_Relation
//
CUTS_Dmac_Candidate_Relation::
CUTS_Dmac_Candidate_Relation (CUTS_Dmac_Log_Format * cause_lf,
                              CUTS_Dmac_Log_Format * effect_lf)
: cause_lf_ (cause_lf),
  effect_lf_ (effect_lf),
  var_evidence_ (0.0),
  time_evidence_ (0.0),
  support_ (0)
{
  this->populate_cause_effect_vars ();
}

//
// ~CUTS_Dmac_Candidate_Relation
//
CUTS_Dmac_Candidate_Relation::
~CUTS_Dmac_Candidate_Relation (void)
{
}

//
// populate_cause_effect_vars
//
void CUTS_Dmac_Candidate_Relation::
populate_cause_effect_vars (void)
{
  std::map <int, std::string>::iterator it1;
  std::map <int, std::string>::iterator it2;

  for (it1 = this->cause_lf_->msg_instances_ [0].var_table_.begin ();
       it1 != this->cause_lf_->msg_instances_ [0].var_table_.end ();
       it1++)
  {
    for (it2 = this->effect_lf_->msg_instances_ [0].var_table_.begin ();
         it2 != this->effect_lf_->msg_instances_ [0].var_table_.end ();
         it2++)
    {
      var_relation relation;
      relation.cause_var = it1->first;
      relation.effect_var = it2->first;
      relation.sup_count = 0;
      this->cause_effect_vars_.push_back (relation);
    }
  }
}

//
// calculate_var_evidence
//
void CUTS_Dmac_Candidate_Relation::
calculate_var_evidence (void)
{
  // Algorithm for calculating the variable evidence

  std::vector <CUTS_Dmac_Log_Msg_Details>::iterator it1, it2, current;

  for (it1 = this->cause_lf_->msg_instances_.begin ();
       it1 != this->cause_lf_->msg_instances_.end ();
       it1++)
  {
    for (it2 = this->effect_lf_->msg_instances_.begin ();
         it2 != this->effect_lf_->msg_instances_.end ();
         it2++)
    {

      // First calculate the precedence count of LFi and
      // LFj
      if (it1->time_val_ <= it2->time_val_)
      {
        current = it2;
        this->support_++;
        std::vector <var_relation>::iterator rel_it;
        for (rel_it = this->cause_effect_vars_.begin ();
             rel_it != this->cause_effect_vars_.end ();
             rel_it++)
        {
          // Now check for variable realtions. We have
          // to iterate through all the possible cause-effect
          // relations

          it2 = current;
          while (it2 != this->effect_lf_->msg_instances_.end ())
          {
            if (it1->var_table_ [rel_it->cause_var] ==
                it2->var_table_ [rel_it->effect_var])
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
  }
  // We return the relation with maximim support and makes it as the
  // variable evidence
  var_relation temp = *std::max_element (this->cause_effect_vars_.begin (),
                                         this->cause_effect_vars_.end (),
                                         compare_sup_count);

  this->var_evidence_ = (double)temp.sup_count / (double) this->support_;
}

//
// calculate_time_evidence
//
void CUTS_Dmac_Candidate_Relation::
calculate_time_evidence (void)
{
  // Here we assume that variable evidence is calcuted prior to
  // this, therefore no point in calculating the prcedence
  // support again.

  std::vector <CUTS_Dmac_Log_Msg_Details>::iterator it1, it2;
  int count = 0;

  for (it1 = this->cause_lf_->msg_instances_.begin ();
       it1 != this->cause_lf_->msg_instances_.end ();
       it1++)
  {
    for (it2 = this->effect_lf_->msg_instances_.begin ();
         it2 != this->effect_lf_->msg_instances_.end ();
         it2++)
    {
      if (it1->time_val_ <= it2->time_val_)
      {
        if (it2->time_val_ - it1->time_val_ <= TIME_GAP)
          count++;

        break;
      }
    }
  }
  this->time_evidence_ = (double)count / (double) this->support_;
}

//
// count support
//
long CUTS_Dmac_Candidate_Relation::
count_support (void)
{
  long support = 0;
  std::vector <CUTS_Dmac_Log_Msg_Details>::iterator it1, it2;

  for (it1 = this->cause_lf_->msg_instances_.begin ();
       it1 != this->cause_lf_->msg_instances_.end ();
       it1++)
  {
    for (it2 = this->effect_lf_->msg_instances_.begin ();
         it2 != this->effect_lf_->msg_instances_.end ();
         it2++)
    {
      if (it1->time_val_ <= it2->time_val_)
      {
        support++;
        break;
      }
    }
  }

  return support;
}