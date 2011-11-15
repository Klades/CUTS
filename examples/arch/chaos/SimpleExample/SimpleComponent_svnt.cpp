// $Id$

#include "SimpleComponent_svnt.h"
#include "cuts/arch/ccm/CCM_T.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace Example
{
  //
  // SimpleComponent_Servant_Context
  //
  SimpleComponent_Servant_Context::SimpleComponent_Servant_Context (SimpleComponent_Servant & parent)
   : SimpleComponent_Servant_Context_Base (parent)
  {
  }

  //
  // ~SimpleComponent_Servant_Context
  //
  SimpleComponent_Servant_Context::~SimpleComponent_Servant_Context (void)
  {
  }

  //
  // push_app_op_ndds
  //
  void SimpleComponent_Servant_Context::
  push_app_op_ndds (::Outer::TestData_DDS * ev)
  {
    this->app_op_ndds_.send_event (ev);
  }

  //
  // subscriber_app_op_ndds
  //
  CUTS_CCM_Single_Subscriber & SimpleComponent_Servant_Context::
  subscriber_app_op_ndds (void)
  {
    return this->app_op_ndds_;
  }

  //
  // push_app_op_ospl
  //
  void SimpleComponent_Servant_Context::
  push_app_op_ospl (::Outer::TestData_DDS * ev)
  {
    this->app_op_ospl_.send_event (ev);
  }

  //
  // subscriber_app_op_ospl
  //
  CUTS_CCM_Single_Subscriber & SimpleComponent_Servant_Context::
  subscriber_app_op_ospl (void)
  {
    return this->app_op_ospl_;
  }

  //
  // push_app_op_corba
  //
  void SimpleComponent_Servant_Context::
  push_app_op_corba (::Outer::TestData_DDS * ev)
  {
    this->app_op_corba_.send_event (ev);
  }

  //
  // subscriber_app_op_corba
  //
  CUTS_CCM_Single_Subscriber & SimpleComponent_Servant_Context::
  subscriber_app_op_corba (void)
  {
    return this->app_op_corba_;
  }

  //
  // push_app_op_tcpip
  //
  void SimpleComponent_Servant_Context::
  push_app_op_tcpip (::Outer::TestData_DDS * ev)
  {
    this->app_op_tcpip_.send_event (ev);
  }

  //
  // subscriber_app_op_tcpip
  //
  CUTS_CCM_Single_Subscriber & SimpleComponent_Servant_Context::
  subscriber_app_op_tcpip (void)
  {
    return this->app_op_tcpip_;
  }

  //
  // SimpleComponent_Servant
  //
  SimpleComponent_Servant::
  SimpleComponent_Servant (const char * name,
                           ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec_ptr executor)
   : SimpleComponent_Servant_Base (name, executor),
     ospl_read_test_data_consumer_ (this, &SimpleComponent_Servant::upcall_ospl_read_test_data),
     corba_read_test_data_consumer_ (this, &SimpleComponent_Servant::upcall_corba_read_test_data),
     ndds_read_test_data_consumer_ (this, &SimpleComponent_Servant::upcall_ndds_read_test_data),
     tcpip_read_test_data_consumer_ (this, 0)
  {
    this->emits_.bind ("app_op_ndds", &this->ctx_->subscriber_app_op_ndds ());
    this->emits_.bind ("app_op_ospl", &this->ctx_->subscriber_app_op_ospl ());
    this->emits_.bind ("app_op_corba", &this->ctx_->subscriber_app_op_corba ());
    this->emits_.bind ("app_op_tcpip", &this->ctx_->subscriber_app_op_tcpip ());

    this->consumers_.bind ("ospl_read_test_data", &this->ospl_read_test_data_consumer_);
    this->consumers_.bind ("corba_read_test_data", &this->corba_read_test_data_consumer_);
    this->consumers_.bind ("ndds_read_test_data", &this->ndds_read_test_data_consumer_);
    this->consumers_.bind ("tcpip_read_test_data", &this->tcpip_read_test_data_consumer_);

    // register CORBA value types
    TAO_OBV_REGISTER_FACTORY (::Outer::TestData_DDS_init,
                              ::Outer::TestData_DDS);

    // Guard initialization of TCP/IP virtual table
    virtual_table_type::init_guard_type guard (SimpleComponent_Servant::table_, 1);

    if (SimpleComponent_Servant::table_.is_init ())
      return;

    SimpleComponent_Servant::table_[0] = &SimpleComponent_Servant::upcall_tcpip_read_test_data;
  }

  //
  // ~SimpleComponent_Servant
  //
  SimpleComponent_Servant::~SimpleComponent_Servant (void)
  {
  }

  //
  // connect_app_op_ndds
  //
  void SimpleComponent_Servant::
  connect_app_op_ndds (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_app_op_ndds
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_app_op_ndds (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // connect_app_op_ospl
  //
  void SimpleComponent_Servant::
  connect_app_op_ospl (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_app_op_ospl
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_app_op_ospl (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // connect_app_op_corba
  //
  void SimpleComponent_Servant::
  connect_app_op_corba (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_app_op_corba
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_app_op_corba (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // connect_app_op_tcpip
  //
  void SimpleComponent_Servant::
  connect_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_app_op_tcpip
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_app_op_tcpip (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // get_consumer_ospl_read_test_data
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_ospl_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // upcall_ospl_read_test_data
  //
  void SimpleComponent_Servant::
  upcall_ospl_read_test_data (SimpleComponent_Servant * servant,
                              const ::CUTS_OSPL::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    *event.in () <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_ospl_read_test_data (event.in ());
  }

  //
  // get_consumer_corba_read_test_data
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_corba_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // upcall_corba_read_test_data
  //
  int SimpleComponent_Servant::
  upcall_corba_read_test_data (SimpleComponent_Servant * servant,
                               ::Outer::TestData_DDS * event)
  {
    if (servant->impl_)
      servant->impl_->push_corba_read_test_data (event);

    return 0;
  }

  //
  // get_consumer_ndds_read_test_data
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_ndds_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // upcall_ndds_read_test_data
  //
  void SimpleComponent_Servant::
  upcall_ndds_read_test_data (SimpleComponent_Servant * servant,
                              const ::CUTS_NDDS::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    *event.in () <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_ndds_read_test_data (event.in ());
  }

  //
  // get_consumer_tcpip_read_test_data
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_tcpip_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // upcall_tcpip_read_test_data
  //
  int SimpleComponent_Servant::
  upcall_tcpip_read_test_data (SimpleComponent_Servant * servant,
                               CUTS_TCPIP_InputCDR & stream)
  {
    // Extract the event from the stream.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;

    if (!(stream >> *event.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to extract %s from stream\n"),
                         ACE_TEXT ("::Outer::TestData_DDS")),
                        -1);
    }

    // Push the message to the implementation.
    if (servant->impl_)
      servant->impl_->push_tcpip_read_test_data (event.in ());

    return 0;
  }

  //
  // create_Example_SimpleComponent_Servant
  //
  extern "C" ::PortableServer::Servant
  create_Example_SimpleComponent_Servant (const char * name, ::Components::EnterpriseComponent_ptr p)
  {
    return ::CUTS::CCM::create_servant <
      ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec,
      ::Example::SimpleComponent_Servant > (name, p);
  }
}

