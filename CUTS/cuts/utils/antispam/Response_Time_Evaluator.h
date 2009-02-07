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

#include "Propogate_Arrival_Rates.h"
#include "Antispam_export.h"

/**
 * @class CUTS_Response_Time_Evaluator
 */
class CUTS_ANTISPAM_Export CUTS_Response_Time_Evaluator
{
public:
  CUTS_Response_Time_Evaluator (void);

  ~CUTS_Response_Time_Evaluator (void);

  void evaluate (CUTS_Component_Assembly & assembly);

private:
  CUTS_Propogate_Arrival_Rates arrivals_;
};

#if defined (__CUTS_INLINE__)
#include "Response_Time_Evaluator.inl"
#endif

#endif  // !defined _CUTS_RESPONSE_TIME_EVALUATOR_H_
