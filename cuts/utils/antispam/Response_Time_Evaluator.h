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
 * @struct CUTS_Response_Time_Evaluator_Result
 */
struct CUTS_Response_Time_Evaluator_Result
{
  CUTS_Response_Time_Evaluator_Result (void)
    : response_time_ (0.0),
      host_util_ (0.0),
      my_service_ (0.0),
      my_util_ (0.0),
      count_ (0)
  {

  }
  CUTS_Response_Time_Evaluator_Result (const CUTS_Response_Time_Evaluator_Result & copy)
    : response_time_ (copy.response_time_),
      host_util_ (copy.host_util_),
      my_service_ (copy.my_service_),
      my_util_ (copy.my_util_),
      count_ (copy.count_)
  {

  }

  const CUTS_Response_Time_Evaluator_Result &
    operator = (const CUTS_Response_Time_Evaluator_Result & copy)
  {
    if (this == &copy)
      return *this;

    this->response_time_ = copy.response_time_;
    this->host_util_ = copy.host_util_;
    this->count_ = copy.count_;
    this->my_util_ = copy.my_util_;
    this->my_service_ = copy.my_service_;

    return *this;
  }

  /// Response time of the component.
  double response_time_;

  /// Packing utilization of the host.
  double host_util_;

  double my_service_;

  double my_util_;

  size_t count_;
};

/**
 * @class CUTS_Response_Time_Evaluator
 */
class CUTS_ANTISPAM_Export CUTS_Response_Time_Evaluator
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Response_Time_Evaluator_Result,
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
  int evaluate (const CUTS_Component_Assembly & assembly,
                const CUTS_Deployment & deployment,
                result_type & results);

private:
  void evaluate_i (CUTS_Behavior_Graph::vertex_descriptor port);

  result_type * results_;

  const CUTS_Component_Assembly * assembly_;

  double host_util_;

  size_t count_;
};

#if defined (__CUTS_INLINE__)
#include "Response_Time_Evaluator.inl"
#endif

#endif  // !defined _CUTS_RESPONSE_TIME_EVALUATOR_H_
