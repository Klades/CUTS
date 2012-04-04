// $Id$

#ifndef _TRON_TESTADAPTERCALLBACK_I_H_
#define _TRON_TESTADAPTERCALLBACK_I_H_

#include "Tron_Deployment_HandlerS.h"
#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"

/**
 * Callback object which receives a TestAdapter, resides
 * on the DAnCE side.
 */
class TestAdapterCallback_i : public POA_Tron::TestAdapterCallback
{
public:
  // Default ctor
  TestAdapterCallback_i (void);

  // Destructor
  virtual ~TestAdapterCallback_i (void);

  // Set the test adapter
  virtual void set_test_adapter (Tron::TestAdapter_ptr ta);

  // Wait for the test adapter to be set
  void wait_for_set_test_adapter (void);

  // Get the test adapter
  Tron::TestAdapter_ptr get_test_adapter (void);

private:
  // The TestAdapter
  Tron::TestAdapter_var ta_;

  // Mutex and Condition for setting the test adapter
  ACE_Thread_Mutex set_test_adapter_mutex_;
  ACE_Condition < ACE_Thread_Mutex > set_test_adapter_cond_;
};

#endif  // !defined _TRON_TESTADAPTERCALLBACK_I_H_
