// -*- C++ -*-

//=============================================================================
/**
 * @file        Update_Service_Times.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UPDATE_SERVICE_TIMES_H_
#define _CUTS_UPDATE_SERVICE_TIMES_H_

#include "Antispam_Visitor.h"

/**
 * @class CUTS_Update_Service_Times
 *
 * Update the service times for an assembly.
 */
class CUTS_Update_Service_Times : public CUTS_Antispam_Visitor
{
public:
  CUTS_Update_Service_Times (void);

  virtual ~CUTS_Update_Service_Times (void);

  virtual void visit_CUTS_Component_Assembly (
    CUTS_Component_Assembly & assembly);

  virtual void visit_CUTS_Component_Instance (
    CUTS_Component_Instance & instance);

  virtual void visit_CUTS_Input_Event_Port_Instance (
    CUTS_Input_Event_Port_Instance & port);

  virtual void visit_CUTS_Output_Event_Port_Instance (
    CUTS_Output_Event_Port_Instance & port);

private:
  /// The current availability of the utilization.
  double used_util_;

  /// The current utilization.
  double curr_util_;
};

#if defined (__CUTS_INLINE__)
#include "Update_Service_Times.inl"
#endif

#endif  // !defined _CUTS_UPDATE_SERVICE_TIMES_H_
