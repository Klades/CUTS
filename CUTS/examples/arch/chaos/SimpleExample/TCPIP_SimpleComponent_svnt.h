// -*- C++ -*-

#ifndef _TCPIP_SIMPLECOMPONENT_SVNT_H_
#define _TCPIP_SIMPLECOMPONENT_SVNT_H_

#include "SimpleComponentS.h"
#include "TCPIP_SimpleComponentC.h"

#include "SimpleComponentEC.h"

#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Servant_T.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Single_Subscriber.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_Subscriber_Table.h"
#include "cuts/arch/chaos/ccm/CHAOS_CCM_EventConsumer.h"
#include "TCPIP_SimpleComponent_svnt_export.h"

// Forward decl.
class CUTS_TCPIP_Servant_Manager;

namespace TCPIP_SimpleComponent_Basic_Impl
{
  // Forward decl.
  class SimpleComponent_Servant;

  /// Type definition of the context base type.
  typedef CUTS_CCM_Context_T <
    ::Example::CCM_SimpleComponent_Context,
    SimpleComponent_Servant >
    SimpleComponent_Servant_Context_Base;

  /**
   * @class SimpleComponent_Servant_Context
   */
  class SimpleComponent_Servant_Context :
    public SimpleComponent_Servant_Context_Base
  {
  public:
    typedef SimpleComponent_Servant_Context_Base base_type;

    // Default constructor
    SimpleComponent_Servant_Context (SimpleComponent_Servant & parent);

    // Destructor
    virtual ~SimpleComponent_Servant_Context (void);

  public:
    // push method for output event port: app_op_emit
    virtual void push_app_op_tcpip (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_tcpip (void);

  private:
    CUTS_TCPIP_CCM_Remote_Endpoint_T < ::Outer::TestData_DDS > app_op_tcpip_;

  public:
    // push method for output event port: app_op_emit
    virtual void push_app_op_corba (::Outer::TestData_DDS * ev);

    CUTS_CCM_Single_Subscriber & subscriber_app_op_corba (void);

  private:
    CUTS_CCM_Single_Subscriber_T < ::Outer::TestData_DDS > app_op_corba_;
  };


  // Type definition of the this->servant_'s base class
  typedef
    CUTS_CHAOS_CCM_Servant_T <
      SimpleComponent_Servant,
      SimpleComponent_Servant_Context,
      CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec,
      ::POA_Example::SimpleComponent > SimpleComponent_Servant_Base;

  /**
   * @class SimpleComponent_Servant
   */
  class SimpleComponent_Servant :
    public SimpleComponent_Servant_Base
  {
    public:
    // default constructor
    SimpleComponent_Servant (const char * name,
                             CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor);

    // destructor
    virtual ~SimpleComponent_Servant (void);

    void connect_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_tcpip (void);

    void connect_app_op_corba (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_corba (void);

  public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_tcpip_read_test_data (void);

  private:
    static int upcall_tcpip_read_test_data (SimpleComponent_Servant * svnt,
                                            CUTS_TCPIP_InputCDR & input);

    CUTS_TCPIP_CCM_EventConsumer tcpip_read_test_data_consumer_;

  public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_corba_read_test_data (void);

  private:
    static int upcall_corba_read_test_data (SimpleComponent_Servant * svnt,
                                            ::Outer::TestData_DDS * ev);

    CUTS_CCM_EventConsumer_T <
      ::Outer::TestData_DDS,
      SimpleComponent_Servant >
      corba_read_test_data_consumer_;
  };
}

extern "C" TCPIP_SIMPLECOMPONENT_SVNT_Export
::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
                                ::Components::EnterpriseComponent_ptr p);

#endif  // !defined _TCPIP_SIMPLECOMPONENT_SVNT_H_
