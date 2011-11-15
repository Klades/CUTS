// -*- C++ -*-

//=============================================================================
/**
 * @file        TE_Score_State.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TE_SCORE_STATE_H_
#define _CUTS_TE_SCORE_STATE_H_

#include "TE_Score_Core_export.h"
#include "ace/SString.h"

/**
 * @ingroup CUTS_TE_Score_Core
 *
 * @class CUTS_TE_Score_State
 */
class CUTS_TE_SCORE_CORE_Export CUTS_TE_Score_State
{
public:
  /// Default constuctor.
  CUTS_TE_Score_State (void);

  /**
   * Initializing constructor.
   */
  CUTS_TE_Score_State (const ACE_CString & name,
                       const ACE_CString & condition,
                       size_t priority,
                       bool is_valid,
                       size_t min_occurs,
                       size_t max_occurs);

  /**
   * Copy constructor.
   */
  CUTS_TE_Score_State (const CUTS_TE_Score_State & state);

  /// Destructor.
  ~CUTS_TE_Score_State (void);

  /**
   * Assignment operator.
   */
  const CUTS_TE_Score_State & operator = (const CUTS_TE_Score_State & rhs);

  /// The name of the state.
  ACE_CString name_;

  /// The condition of the state.
  ACE_CString condition_;

  /// Priority of the state.
  size_t priority_;

  /// The validity of the state.
  bool is_valid_;

  /// Minimun number of occurences.
  long min_occurs_;

  /// Maximum number of occurences.
  long max_occurs_;
};

#if defined (__CUTS_INLINE__)
#include "TE_Score_State.inl"
#endif

#endif  // !defined _CUTS_TE_SCORE_STATE_H_
