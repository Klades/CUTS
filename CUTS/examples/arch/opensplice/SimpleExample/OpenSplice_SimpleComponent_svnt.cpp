// $Id$

#include "OpenSplice_SimpleComponent_svnt.h"
#include "cuts/arch/ccm/CCM_Events_T.h"
//#include "cuts/arch/tcpip/ccm/TCPIP_CCM_T.h"
//#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint.h"

namespace SimpleComponent_Basic_Impl
{
  SimpleComponent_Servant_Context::SimpleComponent_Servant_Context (SimpleComponent_Servant & parent)
  : SimpleComponent_Servant_Context_Base (parent)
  {
  }

  SimpleComponent_Servant_Context::~SimpleComponent_Servant_Context (void)
  {
  }

  void SimpleComponent_Servant_Context::push_app_op_emit (::Outer::TestData_DDS * ev)
  {
    //this->app_op_emit_.send_event (ev);
    ACE_UNUSED_ARG (ev);
  }

  //CUTS_TCPIP_CCM_Remote_Endpoint & SimpleComponent_Servant_Context::endpoint_handle_message (void)
  //{
  //  //return this->handle_message_;
  //}

  void SimpleComponent_Servant_Context::push_app_op_send (::Outer::TestData_DDS * ev)
  {
    //this->app_op_send_.send_event (ev);
    ACE_UNUSED_ARG (ev);
  }

  //CUTS_TCPIP_CCM_Subscriber_Table & SimpleComponent_Servant_Context::endpoints_handle_message_ex (void)
  //{
  //  return this->handle_message_ex_;
  //}

  
  //
  // SimpleComponent_Servant
  //
  SimpleComponent_Servant::
  SimpleComponent_Servant (const char * name,
			   ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor)
    : SimpleComponent_Servant_Base (name, executor),
      read_test_data_consumer_ (this, &SimpleComponent_Servant::deserialize_read_test_data)
  {
    // Initializing the consumer table.
    //this->consumers_.bind ("handle_message", &this->handle_message_consumer_);

    // Initializing the publishes/emits table.
    //this->emits_.bind ("handle_message", &this->ctx_->endpoint_handle_message ());
    //this->publishes_.bind ("handle_message_ex", &this->ctx_->endpoints_handle_message_ex ());

    // Guard the initialization of the virtual table.
    //vtable_type::init_guard_type guard (SimpleComponent_Servant::vtable_, 1);

    //if (SimpleComponent_Servant::vtable_.is_init ())
    //  return;
  }

  //
  // ~SimpleComponent_Servant
  //
  SimpleComponent_Servant::~SimpleComponent_Servant (void)
  {
  }

  //
  // deserialize_read_test_data
  //
  void SimpleComponent_Servant:: 
  deserialize_read_test_data (SimpleComponent_Servant * servant,
			      const ::DDS::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    // event <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_read_test_data (event.in ());

    ACE_UNUSED_ARG (dds_event);
  }

  //
  // connect_handle_message
  //
  void SimpleComponent_Servant::
  connect_app_op_emit (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_app_op_emit
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_app_op_emit (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // subscribe_app_op_send
  //
  ::Components::Cookie * SimpleComponent_Servant::
  subscribe_app_op_send (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // unsubscribe_app_op_send
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  unsubscribe_app_op_send (::Components::Cookie *)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // get_consumer_handle_message
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }
}

::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
				::Components::EnterpriseComponent_ptr p)
{
  ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_var executor =
    ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec::_narrow (p);

  if (::CORBA::is_nil (executor.in ()))
    return 0;

  ::SimpleComponent_Basic_Impl::SimpleComponent_Servant * servant = 
      new ::SimpleComponent_Basic_Impl::SimpleComponent_Servant (name, executor.in ());

  return servant;
}



