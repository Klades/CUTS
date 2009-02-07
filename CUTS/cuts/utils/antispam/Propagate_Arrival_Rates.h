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

#include "Antispam_Visitor.h"

// Forward decl.
class CUTS_Component_Assembly;

/**
 * @class CUTS_Propagate_Arrival_Rates
 */
class CUTS_Propagate_Arrival_Rates :
  public CUTS_Antispam_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[inout]         assembly       Target assembly to evaluate.
   */
  CUTS_Propagate_Arrival_Rates (void);

  /// Destructor.
  virtual ~CUTS_Propagate_Arrival_Rates (void);

  virtual void visit_CUTS_Component_Assembly (
    CUTS_Component_Assembly & assembly);

  virtual void visit_CUTS_Input_Event_Port_Instance (
    CUTS_Input_Event_Port_Instance & port);

  virtual void visit_CUTS_Output_Event_Port_Instance (
    CUTS_Output_Event_Port_Instance & port);

private:
  double curr_lambda_;
};

#if defined (__CUTS_INLINE__)
#include "Propagate_Arrival_Rates.inl"
#endif

#endif  // !defined _CUTS_RESPONSE_TIME_EVALUATOR_I_H_
