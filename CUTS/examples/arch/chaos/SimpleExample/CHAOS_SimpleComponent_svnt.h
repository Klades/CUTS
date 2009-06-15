// -*- C++ -*-

#ifndef _CHAOS_SIMPLECOMPONENT_SVNT_H_
#define _CHAOS_SIMPLECOMPONENT_SVNT_H_

#include "SimpleComponentEC.h"

#include "cuts/ccm/CCM_Context_T.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Servant_T.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Single_Subscriber.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Subscriber_Table.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_EventConsumer.h"

#include "SimpleComponentS.h"
#include "OpenSplice_SimpleComponentC.h"
#include "TCPIP_SimpleComponentC.h"

namespace CHAOS_SimpleComponent_Basic_Impl
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
    // push method for output event port: app_op_dds
    virtual void push_app_op_dds (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_dds (void);

    private:
    CUTS_OpenSplice_CCM_Subscriber_T < ::CUTS_DDS::Outer::TestData_DDS > app_op_dds_;

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
    ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec,
    ::POA_Example::SimpleComponent > SimpleComponent_Servant_Base;

  class SimpleComponent_Servant : public SimpleComponent_Servant_Base
  {
    public:
    // Initializing constructor
    SimpleComponent_Servant (const char * name,
                             ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor);

    virtual ~SimpleComponent_Servant (void);

    void connect_app_op_dds (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_dds (void);

    void connect_app_op_corba (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_corba (void);

    void connect_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_tcpip (void);

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_dds_read_test_data (void);

    private:
    static void upcall_dds_read_test_data (SimpleComponent_Servant *,
                                           const ::CUTS_DDS::Outer::TestData_DDS& dds_event);

    CUTS_OpenSplice_CCM_EventConsumer_T < 
      SimpleComponent_Servant,
      ::CUTS_DDS::Outer::TestData_DDS > dds_read_test_data_consumer_;

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_corba_read_test_data (void);

    private:
    static int upcall_corba_read_test_data (SimpleComponent_Servant *,
                                            ::Outer::TestData_DDS *);

    CUTS_CCM_EventConsumer_T < ::Outer::TestData_DDS, SimpleComponent_Servant > corba_read_test_data_consumer_;

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_tcpip_read_test_data (void);

    private:
    static int upcall_tcpip_read_test_data (SimpleComponent_Servant *,
                                            CUTS_TCPIP_InputCDR &);

    CUTS_TCPIP_CCM_EventConsumer tcpip_read_test_data_consumer_;
  };
}

#include "OpenSplice_SimpleComponent_svnt_export.h"

extern "C" OPENSPLICE_SIMPLECOMPONENT_SVNT_Export
::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
                                ::Components::EnterpriseComponent_ptr p);

#endif  // !defined _CHAOS_SIMPLECOMPONENT_SVNT_H_
