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
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "Behavior_Graph.h"

// Forward decl.
class CUTS_Component_Assembly;

// Forward decl.
class CUTS_Deployment;

/**
 * @class CUTS_Response_Time_Evaluator
 */
class CUTS_ANTISPAM_Export CUTS_Response_Time_Evaluator
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                double,
                                ACE_Null_Mutex> result_type;

  /// Default constructor.
  CUTS_Response_Time_Evaluator (void);

  /// Destructor.
  ~CUTS_Response_Time_Evaluator (void);

  /**
   * Evaluate an assembly.
   *
   * @param[inout]        assembly        Target assembly to evaluate.
   */
  void evaluate (const CUTS_Component_Assembly & assembly,
                 const CUTS_Deployment & deployment,
                 result_type & results);

private:
  void evaluate_i (CUTS_Behavior_Graph::vertex_descriptor port);

  result_type * results_;

  const CUTS_Component_Assembly * assembly_;

  double host_util_;
};

#if defined (__CUTS_INLINE__)
#include "Response_Time_Evaluator.inl"
#endif

#endif  // !defined _CUTS_RESPONSE_TIME_EVALUATOR_H_
