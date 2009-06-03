// -*- C++ -*-

#ifndef _OPENSPLICE_SIMPLECOMPONENT_SVNT_H_
#define _OPENSPLICE_SIMPLECOMPONENT_SVNT_H_

#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/ccm/CCM_Servant_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_EventConsumer_T.h"

#include "ddstypes/ModelDDSDataDcpsC.h"
#include "SimpleComponentEC.h"
#include "SimpleComponentS.h"
#include "OpenSplice_SimpleComponent_svnt_export.h"

namespace SimpleComponent_Basic_Impl
{
  // Forward decl.
  class SimpleComponent_Servant;

  typedef CUTS_CCM_Context_T < ::Example::CCM_SimpleComponent_Context, 
			       SimpleComponent_Servant> SimpleComponent_Servant_Context_Base;

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

    // CUTS_DDS_CCM_Writer_T < ::Outer::TestData_DDS > app_op_emit_;
    //CUTS_TCPIP_CCM_Remote_Endpoint & endpoint_handle_message (void);

    private:
    //CUTS_TCPIP_CCM_Remote_Endpoint_T < ::Message > handle_message_;

    public:
    // push method for output event port: handle_message_ex
    virtual void push_app_op_send (::Outer::TestData_DDS * ev);

    // CUTS_DDS_CCM_Subscriber_Table < ::Outer::TestData_DDS > app_op_send_;
    //CUTS_TCPIP_CCM_Subscriber_Table & endpoints_handle_message_ex (void);

    private:
    //CUTS_TCPIP_CCM_Subscriber_Table_T < ::Message > handle_message_ex_;
  };


  // Type definition of the this->servant_'s base class
  typedef CUTS_CCM_Servant_T < SimpleComponent_Servant_Context,
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
			     CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor);

    // destructor
    virtual ~SimpleComponent_Servant (void);

    void connect_app_op_emit (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_app_op_emit (void);

    ::Components::Cookie * subscribe_app_op_send (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr unsubscribe_app_op_send (::Components::Cookie *);

  public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_read_test_data (void);

    static void deserialize_read_test_data (SimpleComponent_Servant * servant,
					    const ::DDS::Outer::TestData_DDS & dds_event);

  private:
    CUTS_OpenSplice_CCM_EventConsumer_T < SimpleComponent_Servant,
					  ::DDS::Outer::TestData_DDSDataReader,
					  ::DDS::Outer::TestData_DDSSeq > read_test_data_consumer_;
					 
  };
}

extern "C" OPENSPLICE_SIMPLECOMPONENT_SVNT_Export
::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
				::Components::EnterpriseComponent_ptr p);

#endif  // !defined _TCPIP_HELLOWORLD_SVNT_H_
