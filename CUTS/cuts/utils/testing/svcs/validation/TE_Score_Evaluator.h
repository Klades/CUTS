// -*- C++ -*-

//=============================================================================
/**
 * @file        TE_Score_Evaluator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TE_SCORE_EVALUATOR_H_
#define _CUTS_TE_SCORE_EVALUATOR_H_

#include "cuts/utils/unite/cuts-unite.h"
#include "ace/SString.h"
#include "ace/Unbounded_Set.h"

// Forward decl.
class CUTS_Dataset_Repo;

// Forward decl.
class CUTS_DB_Query;

/**
 * @class CUTS_TE_Score_Evaluator
 */
class CUTS_TE_Score_Evaluator
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_TE_Score_Evaluator (CUTS_Dataset_Repo & repo);

  /// Destructor.
  ~CUTS_TE_Score_Evaluator (void);

  /**
   * Evaluate the selected execution states.
   *
   * @param[in]       dataset     Name of the dataset
   * @param[in]       begin       First state to evaluate
   * @param[in]       end         Last state to evaluate
   */
  bool evaluate (const ACE_CString & dataset,
                 ::CUTS::XML::correctnessTestType::state_const_iterator begin,
                 ::CUTS::XML::correctnessTestType::state_const_iterator end);

  /// Number of points award.
  size_t points (void) const;

  /// Maximum number of points award.
  size_t max_points (void) const;

  /// The final grade of the evaluation.
  double final_grade (void) const;

private:
  typedef ::CUTS::XML::correctnessTestType::state_const_iterator::value_type state_value_type;

  void accumulate_maxpoints (const state_value_type & state);

  void evaluate_state (const ACE_CString & dataset,
                       const state_value_type & state);

  void reset (void);

  CUTS_DB_Query * query_;

  size_t points_;

  size_t maxpoints_;

  size_t maxprio_;

  ACE_Unbounded_Set < ACE_SString > seen_;
};

#if defined (__CUTS_INLINE__)
#include "TE_Score_Evaluator.inl"
#endif

#endif  // !defined _CUTS_TE_SCORE_EVALUATOR_H_
