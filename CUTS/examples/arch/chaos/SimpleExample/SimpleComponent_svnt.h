// -*- C++ -*-

#ifndef _SIMPLECOMPONENT_SVNT_H_
#define _SIMPLECOMPONENT_SVNT_H_

#include "SimpleComponentEC.h"
#include "SimpleComponentS.h"

// include event conversion files
#include "OpenSplice_SimpleComponentC.h"
#include "RTIDDS_SimpleComponentC.h"
#include "TCPIP_SimpleComponentC.h"

// include component architecture files
#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Servant_T.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Single_Subscriber.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Subscriber_Table.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_EventConsumer.h"

// include export definitions
#include "SimpleComponent_svnt_export.h"

namespace Example
{
  // Forward decl.
  class SimpleComponent_Servant;

  typedef CUTS_CCM_Context_T < 
  ::Example::CCM_SimpleComponent_Context, 
  SimpleComponent_Servant > SimpleComponent_Servant_Context_Base;

  class SimpleComponent_Servant_Context : public SimpleComponent_Servant_Context_Base
  {
    public:
    // Initializing constructor
    SimpleComponent_Servant_Context (SimpleComponent_Servant & parent);

    // Destructor
    virtual ~SimpleComponent_Servant_Context (void);

    public:
    // push method for output event port: app_op_ndds
    virtual void push_app_op_ndds (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_ndds (void);

    private:
    CUTS_RTIDDS_CCM_Subscriber_T < ::CUTS_NDDS::Outer::TestData_DDS > app_op_ndds_;

    public:
    // push method for output event port: app_op_ospl
    virtual void push_app_op_ospl (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_ospl (void);

    private:
    CUTS_OpenSplice_CCM_Subscriber_T < ::CUTS_OSPL::Outer::TestData_DDS > app_op_ospl_;

    public:
    // push method for output event port: app_op_corba
    virtual void push_app_op_corba (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_corba (void);

    private:
    CUTS_CCM_Single_Subscriber_T < ::Outer::TestData_DDS > app_op_corba_;

    public:
    // push method for output event port: app_op_tcpip
    virtual void push_app_op_tcpip (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_tcpip (void);

    private:
    CUTS_TCPIP_CCM_Remote_Endpoint_T < ::Outer::TestData_DDS > app_op_tcpip_;
  };

  typedef CUTS_CHAOS_CCM_Servant_T < 
    SimpleComponent_Servant,
    SimpleComponent_Servant_Context,
    ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec,
    ::POA_Example::SimpleComponent > SimpleComponent_Servant_Base;

  class SimpleComponent_Servant : public SimpleComponent_Servant_Base
  {
    public:
    // Initializing constructor
    SimpleComponent_Servant (const char * name,
                             ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec_ptr executor);

    virtual ~SimpleComponent_Servant (void);

    void connect_app_op_ndds (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_ndds (void);

    void connect_app_op_ospl (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_ospl (void);

    void connect_app_op_corba (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_corba (void);

    void connect_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_tcpip (void);

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_ospl_read_test_data (void);

    private:
    static void upcall_ospl_read_test_data (SimpleComponent_Servant *,
                                            const ::CUTS_OSPL::Outer::TestData_DDS& dds_event);

    CUTS_OpenSplice_CCM_EventConsumer_T < 
      SimpleComponent_Servant,
      ::CUTS_OSPL::Outer::TestData_DDS > ospl_read_test_data_consumer_;

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_corba_read_test_data (void);

    private:
    static int upcall_corba_read_test_data (SimpleComponent_Servant *,
                                            ::Outer::TestData_DDS *);

    CUTS_CCM_EventConsumer_T < ::Outer::TestData_DDS, SimpleComponent_Servant > corba_read_test_data_consumer_;

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_ndds_read_test_data (void);

    private:
    static void upcall_ndds_read_test_data (SimpleComponent_Servant *,
                                            const ::CUTS_NDDS::Outer::TestData_DDS& dds_event);

    CUTS_RTIDDS_CCM_EventConsumer_T < 
      SimpleComponent_Servant,
      ::CUTS_NDDS::Outer::TestData_DDS > ndds_read_test_data_consumer_;

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_tcpip_read_test_data (void);

    private:
    static int upcall_tcpip_read_test_data (SimpleComponent_Servant *,
                                            CUTS_TCPIP_InputCDR &);

    CUTS_TCPIP_CCM_EventConsumer tcpip_read_test_data_consumer_;
  };


  extern "C" SIMPLECOMPONENT_SVNT_Export
  ::PortableServer::Servant
  create_Example_SimpleComponent_Servant (const char * name, ::Components::EnterpriseComponent_ptr p);
}


#endif  // !defined _SIMPLECOMPONENT_SVNT_H_
