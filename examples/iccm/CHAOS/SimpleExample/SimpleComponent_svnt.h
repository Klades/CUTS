// -*- C++ -*-

#ifndef _SIMPLECOMPONENT_SVNT_H_
#define _SIMPLECOMPONENT_SVNT_H_

#include "SimpleComponent_iCCMC.h"
#include "SimpleComponentS.h"

#include "SimpleComponentC.h"
#include "CHAOS_ModelDDSDataC.h"

#include "cuts/iccm/servant/Context_T.h"
#include "cuts/iccm/arch/chaos/servant/CHAOS_Servant_T.h"

#include "cuts/iccm/servant/Receptacle_T.h"
#include "SimpleComponent_svnt_export.h"

namespace Example {
// Forward decl.
class SimpleComponent_Servant;

// Type definition of the servant type.
typedef iCCM::Context_T < iCCM_SimpleComponent_Context, SimpleComponent_Servant > SimpleComponent_Context_Base;

/**
 * @class SimpleComponent_Context
 *
 * Implementation of the iCCM_SimpleComponent_Context interface.
 */
class SIMPLECOMPONENT_SVNT_Export SimpleComponent_Context :
  public SimpleComponent_Context_Base
{
  public:
  // Default constructor
  SimpleComponent_Context (SimpleComponent_Servant & parent);

  // Destructor
  virtual ~SimpleComponent_Context (void);

  virtual void push_app_op_ndds (::Outer::TestData_DDS *ev);

  virtual void push_app_op_ospl (::Outer::TestData_DDS *ev);

  virtual void push_app_op_tcpip (::Outer::TestData_DDS *ev);

  virtual void push_app_op_corba (::Outer::TestData_DDS *ev);

  virtual ::Outer::TestData_DDS * new_app_op_ndds_event (void);

  virtual ::Outer::TestData_DDS * new_app_op_ospl_event (void);

  virtual ::Outer::TestData_DDS * new_app_op_tcpip_event (void);

  virtual ::Outer::TestData_DDS * new_app_op_corba_event (void);

  iCCM::CHAOS_Publisher & get_app_op_ndds_publisher (void);

  iCCM::CHAOS_Publisher & get_app_op_ospl_publisher (void);

  iCCM::CHAOS_Publisher & get_app_op_tcpip_publisher (void);

  iCCM::CHAOS_Publisher & get_app_op_corba_publisher (void);

  private:
  iCCM::CHAOS_Publisher_T < Outer::TestData_DDS > app_op_ndds_;

  iCCM::CHAOS_Publisher_T < Outer::TestData_DDS > app_op_ospl_;

  iCCM::CHAOS_Publisher_T < Outer::TestData_DDS > app_op_tcpip_;

  iCCM::CHAOS_Publisher_T < Outer::TestData_DDS > app_op_corba_;
};

// Type definition of the servant base type.
typedef iCCM::CHAOS_Servant_T < 
  SimpleComponent_Servant,
  SimpleComponent_Context,
  ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec,
  ::POA_Example::SimpleComponent > SimpleComponent_Servant_Base;

class SIMPLECOMPONENT_SVNT_Export SimpleComponent_Servant
  : public SimpleComponent_Servant_Base
{
  /// typedef for generated implementation code
  typedef SimpleComponent_Servant self_type;

  /// Default constructor
  public:
  SimpleComponent_Servant (const char * name,
                           ::PortableServer::POA_ptr poa,
                           ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec_ptr executor);

  /// Destructor
  virtual ~SimpleComponent_Servant (void);

  virtual void set_attributes (const ::Components::ConfigValues &);

  virtual void connect_app_op_ndds (::Outer::TestData_DDSConsumer_ptr);
  virtual ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_ndds (void);

  virtual void connect_app_op_ospl (::Outer::TestData_DDSConsumer_ptr);
  virtual ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_ospl (void);

  virtual void connect_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr);
  virtual ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_tcpip (void);

  virtual void connect_app_op_corba (::Outer::TestData_DDSConsumer_ptr);
  virtual ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_corba (void);

  virtual void push_ndds_read_test_data (::Outer::TestData_DDS *ev);

  virtual void push_ospl_read_test_data (::Outer::TestData_DDS *ev);

  virtual void push_corba_read_test_data (::Outer::TestData_DDS *ev);

  virtual void push_tcpip_read_test_data (::Outer::TestData_DDS *ev);

  virtual ::Outer::TestData_DDSConsumer_ptr get_ndds_read_test_data_consumer (void);

  virtual ::Outer::TestData_DDSConsumer_ptr get_ospl_read_test_data_consumer (void);

  virtual ::Outer::TestData_DDSConsumer_ptr get_corba_read_test_data_consumer (void);

  virtual ::Outer::TestData_DDSConsumer_ptr get_tcpip_read_test_data_consumer (void);

  iCCM::CHAOS_EventConsumer_T < SimpleComponent_Servant, ::Outer::TestData_DDS > ndds_read_test_data_consumer_;
  iCCM::CHAOS_EventConsumer_T < SimpleComponent_Servant, ::Outer::TestData_DDS > ospl_read_test_data_consumer_;
  iCCM::CHAOS_EventConsumer_T < SimpleComponent_Servant, ::Outer::TestData_DDS > corba_read_test_data_consumer_;
  iCCM::CHAOS_EventConsumer_T < SimpleComponent_Servant, ::Outer::TestData_DDS > tcpip_read_test_data_consumer_;
};

extern "C" SIMPLECOMPONENT_SVNT_Export ::PortableServer::Servant
create_Example_SimpleComponent_Servant (const char * name,
                                        ::PortableServer::POA_ptr poa,
                                        ::Components::EnterpriseComponent_ptr p);

}
#endif  // !defined _SIMPLECOMPONENT_SVNT_H_
