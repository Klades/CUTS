// $Id$

#ifndef _TRON_TESTADAPTER_I_H_
#define _TRON_TESTADAPTER_I_H_

#include "cuts/iccm/deployment/Component_Instance_Handler_T.h"

#include "Tron_Container.h"
#include "Tron_Deployment_HandlerS.h"
#include "Tron_Consumer_Map_Type.h"

#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"

#include "tron/adapter.h"

/**
 * TestAdapter which works with Tron.  Resides
 * on the Tron side.
 */
class TestAdapter_i :
  public iCCM::Component_Instance_Handler_T < TestAdapter_i, POA_Tron::TestAdapter, iCCM::Tron_Container >
{
public:
  // Initalizing ctor
  TestAdapter_i (Reporter * r, tron_consumer_map_type & map);

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

  // Get the tron reporter
  Reporter * get_reporter (void);

  // Get the deployment handler's consumer map
  tron_consumer_map_type & get_consumer_map (void);

private:
  // Mutex and Condition for initialization_complete
  ACE_Thread_Mutex init_complete_mutex_;
  ACE_Condition < ACE_Thread_Mutex > init_complete_cond_;

  // Mutex and Condition for configuration_complete
  ACE_Thread_Mutex activate_complete_mutex_;
  ACE_Condition < ACE_Thread_Mutex > activate_complete_cond_;

  bool is_init_;
  bool is_activated_;

  // The tron reporter
  Reporter * reporter_;

  // The consumer map
  tron_consumer_map_type & consumer_map_;
};

#endif  // !defined _TRON_TESTADAPTER_I_H_
