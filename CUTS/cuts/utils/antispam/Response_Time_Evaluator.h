// -*- C++ -*-

//=============================================================================
/**
 * @file        Response_Time_Evaluator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RESPONSE_TIME_EVALUATOR_H_
#define _CUTS_RESPONSE_TIME_EVALUATOR_H_

#include "Antispam_export.h"

// Forward decl.
class CUTS_Component_Assembly;

/**
 * @class CUTS_Response_Time_Evaluator
 */
class CUTS_ANTISPAM_Export CUTS_Response_Time_Evaluator
{
public:
  /// Default constructor.
  CUTS_Response_Time_Evaluator (void);

  /// Destructor.
  ~CUTS_Response_Time_Evaluator (void);

  /**
   * Evaluate an assembly.
   *
   * @param[inout]        assembly        Target assembly to evaluate.
   */
  void evaluate (CUTS_Component_Assembly & assembly);
};

#if defined (__CUTS_INLINE__)
#include "Response_Time_Evaluator.inl"
#endif

#endif  // !defined _CUTS_RESPONSE_TIME_EVALUATOR_H_
