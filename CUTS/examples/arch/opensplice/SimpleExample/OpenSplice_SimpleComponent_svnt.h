// -*- C++ -*-

#ifndef _OPENSPLICE_SIMPLECOMPONENT_SVNT_H_
#define _OPENSPLICE_SIMPLECOMPONENT_SVNT_H_

#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_EventConsumer_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_Subscriber_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_Subscriber_Table_T.h"

#include "OpenSplice_ModelDDSDataC.h"

#include "SimpleComponentEC.h"
#include "SimpleComponentS.h"
#include "OpenSplice_SimpleComponent_svnt_export.h"

namespace SimpleComponent_Basic_Impl
{
  // Forward decl.
  class SimpleComponent_Servant;

  typedef CUTS_CCM_Context_T < ::Example::CCM_SimpleComponent_Context,
             SimpleComponent_Servant > SimpleComponent_Servant_Context_Base;

  /**
   * @class SimpleComponent_Servant_Context
   */
  class SimpleComponent_Servant_Context : public SimpleComponent_Servant_Context_Base
  {
  public:
    // default constructor
    SimpleComponent_Servant_Context (SimpleComponent_Servant & parent);

    // destructor
    virtual ~SimpleComponent_Servant_Context (void);

  public:
    // push method for output event port: handle_message
    virtual void push_app_op_emit (::Outer::TestData_DDS * ev);

    CUTS_OpenSplice_CCM_Subscriber & writer_app_op_emit (void);

  private:
    CUTS_OpenSplice_CCM_Subscriber_T < ::CUTS_DDS::Outer::TestData_DDS > app_op_emit_;

  public:
    // push method for output event port: app_op_send
    virtual void push_app_op_send (::Outer::TestData_DDS * ev);

    CUTS_CCM_Subscriber_Table & writers_app_op_send (void);

  private:
    CUTS_OpenSplice_CCM_Subscriber_Table_T < ::CUTS_DDS::Outer::TestData_DDS > app_op_send_;
  };


  // Type definition of the this->servant_'s base class
  typedef CUTS_OpenSplice_CCM_Servant_T < SimpleComponent_Servant,
            SimpleComponent_Servant_Context,
            CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec,
            ::POA_Example::SimpleComponent > SimpleComponent_Servant_Base;

  /**
   * @class SimpleComponent_Servant
   */
  class SimpleComponent_Servant : public SimpleComponent_Servant_Base
  {
  public:
    // default constructor
    SimpleComponent_Servant (const char * name,
           ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor);

    // destructor
    virtual ~SimpleComponent_Servant (void);

    // output (single_destination)
    void connect_app_op_emit (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_emit (void);

    // output (!single_destination)
    ::Components::Cookie * subscribe_app_op_send (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr unsubscribe_app_op_send (::Components::Cookie *);

    // input
  public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_read_test_data (void);

    static void deserialize_read_test_data (SimpleComponent_Servant * servant,
              const ::CUTS_DDS::Outer::TestData_DDS & dds_event);

  private:
    CUTS_OpenSplice_CCM_EventConsumer_T < SimpleComponent_Servant,
            ::CUTS_DDS::Outer::TestData_DDS > read_test_data_consumer_;
  };
}

extern "C" OPENSPLICE_SIMPLECOMPONENT_SVNT_Export
::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
        ::Components::EnterpriseComponent_ptr p);

#endif  // !defined _TCPIP_HELLOWORLD_SVNT_H_
