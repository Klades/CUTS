#include "Dmac_Candidate_Relation.h"
#include "cuts/utils/evidence/DSF_Evidence_Combiner.h"
#include <iostream>

#define TIME_GAP 1.0

//
// CUTS_Dmac_Candidate_Relation
//
CUTS_Dmac_Candidate_Relation::
CUTS_Dmac_Candidate_Relation (CUTS_Dmac_Log_Format * cause_lf,
                              CUTS_Dmac_Log_Format * effect_lf)
: cause_lf_ (cause_lf),
  effect_lf_ (effect_lf),
  belief_ (0.0),
  var_evidence_val_ (0.0),
  time_evidence_val_ (0.0),
  var_evidence_calculated_ (false)
{
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

  for (it1 = this->cause_lf_->msg_instances_ [0]->var_table_.begin ();
       it1 != this->cause_lf_->msg_instances_ [0]->var_table_.end ();
       it1++)
  {
    for (it2 = this->effect_lf_->msg_instances_ [0]->var_table_.begin ();
         it2 != this->effect_lf_->msg_instances_ [0]->var_table_.end ();
         it2++)
    {
      // This is because for DAnCE dataset, once the code is finalized we will
      // add a generic way to implment this.
      if ((it1->first != 2) && (it2->first != 2))
      {
        var_relation relation;
        relation.cause_var = it1->first;
        relation.effect_var = it2->first;
        relation.sup_count = 0;
        this->cause_effect_vars_.push_back (relation);
      }
    }
  }
}

//
// calculate_var_evidence
//
//void CUTS_Dmac_Candidate_Relation::
//calculate_var_evidence (void)
//{
//  // Algorithm for calculating the variable evidence
//
//  std::vector <CUTS_Dmac_Log_Msg_Details *>::iterator it1, it2, current;
//
//  for (it1 = this->cause_lf_->msg_instances_.begin ();
//       it1 != this->cause_lf_->msg_instances_.end ();
//       it1++)
//  {
//    for (it2 = this->effect_lf_->msg_instances_.begin ();
//         it2 != this->effect_lf_->msg_instances_.end ();
//         it2++)
//    {
//
//      // First calculate the precedence count of LFi and
//      // LFj
//      if ((*it1)->time_val_ <= (*it2)->time_val_)
//      {
//        current = it2;
//        std::vector <var_relation>::iterator rel_it;
//        for (rel_it = this->cause_effect_vars_.begin ();
//             rel_it != this->cause_effect_vars_.end ();
//             rel_it++)
//        {
//          // Now check for variable realtions. We have
//          // to iterate through all the possible cause-effect
//          // relations
//
//          it2 = current;
//          while (it2 != this->effect_lf_->msg_instances_.end ())
//          {
//            if ((*it1)->var_table_ [rel_it->cause_var] ==
//                (*it2)->var_table_ [rel_it->effect_var])
//            {
//              rel_it->sup_count++;
//              break;
//            }
//            else
//              it2++;
//          }
//        }
//        break;
//      }
//    }
//  }
//  // We return the relation with maximim support and makes it as the
//  // variable evidence
//  var_relation temp = *std::max_element (this->cause_effect_vars_.begin (),
//                                         this->cause_effect_vars_.end (),
//                                         compare_sup_count);
//
//  var_relation temp;
//
//  if (this->support_ > 0)
//  {
//    this->var_evidence_ = (double)temp.sup_count / (double)this->support_;
//
//    if (this->var_evidence_ > 0)
//    {
//      std::cout << "Cause-var : " << temp.cause_var
//                << "  Effect-var : " << temp.effect_var
//                << std::endl;
//    }
//  }
//  else
//  {
//    this->var_evidence_ = 0;
//  }
//}
//
////
//// calculate_time_evidence
////
//void CUTS_Dmac_Candidate_Relation::
//calculate_time_evidence (void)
//{
//  // Here we assume that variable evidence is calcuted prior to
//  // this, therefore no point in calculating the prcedence
//  // support again.
//
//  std::vector <CUTS_Dmac_Log_Msg_Details *>::iterator it1, it2;
//  int count = 0;
//
//  for (it1 = this->cause_lf_->msg_instances_.begin ();
//       it1 != this->cause_lf_->msg_instances_.end ();
//       it1++)
//  {
//    for (it2 = this->effect_lf_->msg_instances_.begin ();
//         it2 != this->effect_lf_->msg_instances_.end ();
//         it2++)
//    {
//      if ((*it1)->time_val_ <= (*it2)->time_val_)
//      {
//        double diff = (*it2)->time_val_ - (*it1)->time_val_;
//        if (diff <= TIME_GAP)
//        {
//          std::cout << "Time difference is " << diff << std::endl;
//          count++;
//          break;
//        }
//      }
//    }
//  }
//  if (this->support_ > 0)
//    this->time_evidence_ = (double)count / (double) this->support_;
//  else
//    this->time_evidence_ = 0;
//}


CUTS_Dmac_Log_Format * CUTS_Dmac_Candidate_Relation::
cause_lf (void)
{
  return this->cause_lf_;
}

CUTS_Dmac_Log_Format * CUTS_Dmac_Candidate_Relation::
effect_lf (void)
{
  return this->effect_lf_;
}

//void CUTS_Dmac_Candidate_Relation::
//set_log_formats (CUTS_Dmac_Log_Format * lf1,
//                 CUTS_Dmac_Log_Format * lf2)
//{
//  std::vector <CUTS_Dmac_Log_Msg_Details *>::iterator it1, it2;
//  long lf1_precedence_count = 0;
//  long lf2_precedence_count = 0;
//  double lf1_support = 0;
//  double lf2_support = 0;
//  long lf1_count = lf1->msg_instances_.size ();
//  long lf2_count = lf2->msg_instances_.size ();
//
//  for (it1 = lf1->msg_instances_.begin ();
//       it1 != lf1->msg_instances_.end ();
//       it1++)
//  {
//    for (it2 = lf2->msg_instances_.begin ();
//         it2 != lf2->msg_instances_.end ();
//         it2++)
//    {
//      if ((*it1)->time_val_ <= (*it2)->time_val_)
//      {
//        lf1_precedence_count++;
//        break;
//      }
//    }
//  }
//
//  for (it2 = lf2->msg_instances_.begin ();
//       it2 != lf2->msg_instances_.end ();
//       it2++)
//  {
//    for (it1 = lf1->msg_instances_.begin ();
//         it1 != lf1->msg_instances_.end ();
//         it1++)
//    {
//      if ((*it2)->time_val_ <= (*it1)->time_val_)
//      {
//        lf2_precedence_count++;
//        break;
//      }
//    }
//  }
//
//  lf1_support = (double)lf1_precedence_count / (double)lf1_count;
//  lf2_support = (double)lf2_precedence_count / (double)lf2_count;
//
//  if (lf1_support >= lf2_support)
//  {
//    this->cause_lf_ = lf1;
//    this->effect_lf_ = lf2;
//    this->support_ = lf1_precedence_count;
//  }
//  else
//  {
//    this->cause_lf_ = lf2;
//    this->effect_lf_ = lf1;
//    this->support_ = lf2_precedence_count;
//  }
//
//  this->populate_cause_effect_vars ();
//
//}

void CUTS_Dmac_Candidate_Relation::
calculate_belief (CUTS_DMAC_UTILS::int_double_map & knowledge_data)
{
  CUTS_Dmac_Time_Evidence time_evidence;
  CUTS_Dmac_Variable_Evidence var_evidence;
  CUTS_Dmac_Domain_Evidence dom_evidence (knowledge_data);

  this->time_evidence_val_ = time_evidence.calculate (this->cause_lf_, this->effect_lf_);

  // For the reverse relation the variable evidence is the same.
  // So if it is alrady calulated we don't need to calculate it
  // again, just set it.
  if (!this->var_evidence_calculated_)
  {
    this->var_evidence_val_ = var_evidence.calculate (this->cause_lf_,
                                                      this->effect_lf_,
                                                      this->cause_effect_vars_);
    this->var_evidence_calculated_ = true;
  }
  else
    var_evidence.set_bba (this->var_evidence_val_, 0.0);

  /// Call the domain evidence calculation methods here
  this->domain_evidence_val_ = dom_evidence.calculate (this->cause_lf_,
                                                       this->effect_lf_);

  this->evidences_.push_back (time_evidence);
  this->evidences_.push_back (var_evidence);
  this->evidences_.push_back (dom_evidence);

  CUTS_DSF_Evidence_Combiner ev_combiner (this->evidences_);
  ev_combiner.calculate_belief ();
  this->belief_ = ev_combiner.total_belief ();
}

double CUTS_Dmac_Candidate_Relation::belief ()
{
  return this->belief_;
}

void CUTS_Dmac_Candidate_Relation::belief (double val)
{
  this->belief_ = val;
}

void CUTS_Dmac_Candidate_Relation::var_evidence_val (double val)
{
  this->var_evidence_val_ = val;
}

double CUTS_Dmac_Candidate_Relation::var_evidence_val (void)
{
  return this->var_evidence_val_;
}

void CUTS_Dmac_Candidate_Relation::
var_evidence_calculated (bool val)
{
  this->var_evidence_calculated_ = val;
}

double CUTS_Dmac_Candidate_Relation::time_evidence_val ()
{
  return this->time_evidence_val_;
}

double CUTS_Dmac_Candidate_Relation::domain_evidence_val ()
{
  return this->domain_evidence_val_;
}