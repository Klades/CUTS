// $Id$

#ifndef _TRON_TESTADAPTER_I_H_
#define _TRON_TESTADAPTER_I_H_

#include "cuts/iccm/deployment/Component_Instance_Handler_T.h"

#include "Tron_Container.h"
#include "Tron_Deployment_HandlerS.h"

#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"

/**
 * TestAdapter which works with Tron.  Resides
 * on the Tron side.
 */
class TestAdapter_i :
  public iCCM::Component_Instance_Handler_T < TestAdapter_i, POA_Tron::TestAdapter, iCCM::Tron_Container >
{
public:
  // Default ctor
  TestAdapter_i (void);

  // Destrutor
  virtual ~TestAdapter_i (void);

  // Notify the test adapter that initialization is complete
  virtual void initialization_complete (void);

  // Wait for the initalization to be complete
  void wait_for_initialization_complete (void);

  // Notify the test adapter that activation is complete
  virtual void activate_complete (void);

  // Wait for the activation to be completed
  void wait_for_activate_complete (void);

private:
  // Mutex and Condition for initialization_complete
  ACE_Thread_Mutex init_complete_mutex_;
  ACE_Condition < ACE_Thread_Mutex > init_complete_cond_;

  // Mutex and Condition for configuration_complete
  ACE_Thread_Mutex activate_complete_mutex_;
  ACE_Condition < ACE_Thread_Mutex > activate_complete_cond_;

  bool is_init_;
  bool is_activated_;
};

#endif  // !defined _TRON_TESTADAPTER_I_H_
