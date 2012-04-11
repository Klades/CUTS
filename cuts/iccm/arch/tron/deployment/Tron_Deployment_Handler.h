// $Id:

#ifndef _TRON_DEPLOYMENT_HANDLER_H_
#define _TRON_DEPLOYMNET_HANDLER_H_

#include "tron/adapter.h"
#include "Tron_Deployment_Handlers_export.h"
#include "TestAdapter_i.h"
#include "cuts/ORB_Server_Task.h"
#include "cuts/Servant_Manager_T.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "Tron_Consumer_Map_Type.h"

/**
 * @class Tron_Deployment_Handler
 *
 * Class which interfaces with TRON and creates a iCCM compatable TestAdapter.
 */
class ICCM_TRON_DEPLOYMENT_HANDLERS_Export Tron_Deployment_Handler :
  public ::TestAdapter
{
public:
  static void create_singleton (Reporter * r);
  static void destroy_singleton (void);

  static Tron_Deployment_Handler * singleton (void);

private:
  // Default constructor
  Tron_Deployment_Handler (Reporter * r);

  // Destructor
  ~Tron_Deployment_Handler (void);

public:
  // Initialize the handler
  int init (int argc, const char * argv[]);

  // TRON hook for starting the adapter
  void adapter_start (void);

  // TRON hook for handling UPPAAL signals
  void adapter_perform (int32_t channel, uint16_t size, const int32_t data[]);

private:
  /// Helper method for activating the test adapter
  void activate_test_adapter (void);

  /// Singleton for the deployment handler.
  static Tron_Deployment_Handler * singleton_;

  /// The ORB
  ::CORBA::ORB_var orb_;

  /// The callback to send the test adapter to
  ::Tron::TestAdapterCallback_var callback_;

  /// The test adapter
  TestAdapter_i ta_;

  /// The test adapter manager
  CUTS_Servant_Manager_T < TestAdapter_i > ta_mgr_;

  /// The ORB task
  CUTS_ORB_Server_Task task_;

  /// The tron event channel to iccm consumer map
  tron_consumer_map_type consumer_map_;
};

extern "C"
{
  ICCM_TRON_DEPLOYMENT_HANDLERS_Export
  TestAdapter * adapter_new (Reporter * r, int argc, const char * args[]);

  ICCM_TRON_DEPLOYMENT_HANDLERS_Export
  void adapter_delete (TestAdapter * adapter);

  ICCM_TRON_DEPLOYMENT_HANDLERS_Export
  void adapter_start (TestAdapter * adapter);

  ICCM_TRON_DEPLOYMENT_HANDLERS_Export
  void adapter_perform (TestAdapter * adapter, int32_t chan, uint16_t n, const int32_t data[]);
}

#endif  // !defined _TRON_DEPLOYMENT_HANDLER_H_
