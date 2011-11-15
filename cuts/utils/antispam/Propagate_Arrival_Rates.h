// -*- C++ -*-

//=============================================================================
/**
 * @file        Propogate_Arrival_Rates.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPOGATE_ARRIVAL_RATES_H_
#define _CUTS_PROPOGATE_ARRIVAL_RATES_H_

#include "Component_Assembly.h"

/**
 * @class CUTS_Propagate_Arrival_Rates
 */
class CUTS_ANTISPAM_Export CUTS_Propagate_Arrival_Rates
{
public:
  /// Default constructor.
  CUTS_Propagate_Arrival_Rates (void);

  /// Destructor.
  ~CUTS_Propagate_Arrival_Rates (void);

  /**
   * Propogate the arrival rates for the given assembly.
   *
   * @param[in]           assembly        Target assembly to update.
   */
  void propogate (CUTS_Component_Assembly & assembly);

private:
  void propogate_input (CUTS_Behavior_Graph::vertex_descriptor port);

  void visit_input_to_output (CUTS_Behavior_Graph::edge_descriptor edge);

  void visit_output_to_input (CUTS_Behavior_Graph::edge_descriptor edge);

  CUTS_Component_Assembly * assembly_;

  double incr_lambda_;
};

#if defined (__CUTS_INLINE__)
#include "Propagate_Arrival_Rates.inl"
#endif

#endif  // !defined _CUTS_RESPONSE_TIME_EVALUATOR_I_H_
