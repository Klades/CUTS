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

#include "ace/Unbounded_Set.h"
#include "ace/Containers_T.h"
#include "TE_Score_State.h"

// Forward decl.
class CUTS_Dataset_Repo;

// Forward decl.
class CUTS_DB_Query;

/// Type definition for a list of states.
typedef ACE_Array <CUTS_TE_Score_State> CUTS_TE_Score_State_List;

/**
 * @ingroup CUTS_TE_Score_Core
 *
 * @class CUTS_TE_Score_Evaluator
 */
class CUTS_TE_SCORE_CORE_Export CUTS_TE_Score_Evaluator
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
                 CUTS_TE_Score_State_List & states);

  /// Number of points award.
  size_t points (void) const;

  /// Maximum number of points award.
  size_t max_points (void) const;

  /// The final grade of the evaluation.
  double final_grade (void) const;

private:
  void accumulate_maxpoints (const CUTS_TE_Score_State & state);

  void evaluate_state (const ACE_CString & dataset,
                       const CUTS_TE_Score_State & state);

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
