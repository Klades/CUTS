// $Id$

#include "OpenSplice_SimpleComponent_svnt.h"
#include "cuts/arch/ccm/CCM_T.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace SimpleComponent_Basic_Impl
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
  // push_app_op_tcpip
  //
  void SimpleComponent_Servant_Context::
  push_app_op_tcpip (::Outer::TestData_DDS * ev)
  {
    this->app_op_tcpip_.send_event (ev);
  }

  //
  // writers_app_op_tcpip
  //
  CUTS_CCM_Subscriber_Table & SimpleComponent_Servant_Context::
  writers_app_op_tcpip (void)
  {
    return this->app_op_tcpip_;
  }

  //
  // push_app_op_dds
  //
  void SimpleComponent_Servant_Context::
  push_app_op_dds (::Outer::TestData_DDS * ev)
  {
    this->app_op_dds_.send_event (ev);
  }

  //
  // writer_app_op_dds
  //
  CUTS_OpenSplice_CCM_Subscriber & SimpleComponent_Servant_Context::
  writer_app_op_dds (void)
  {
    return this->app_op_dds_;
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
  // writer_app_op_corba
  //
  CUTS_OpenSplice_CCM_Subscriber & SimpleComponent_Servant_Context::
  writer_app_op_corba (void)
  {
    return this->app_op_corba_;
  }

  //
  // SimpleComponent_Servant
  //
  SimpleComponent_Servant::
  SimpleComponent_Servant (const char * name,
                           ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor)
   : SimpleComponent_Servant_Base (name, executor),
     tcpip_read_test_data_consumer_ (this, &SimpleComponent_Servant::deserialize_tcpip_read_test_data),
     dds_read_test_data_consumer_ (this, &SimpleComponent_Servant::deserialize_dds_read_test_data),
     corba_read_test_data_consumer_ (this, &SimpleComponent_Servant::deserialize_corba_read_test_data)
  {
    this->publishes_.bind ("app_op_tcpip", &this->ctx_->writers_app_op_tcpip ());
    this->emits_.bind ("app_op_dds", &this->ctx_->writer_app_op_dds ());
    this->emits_.bind ("app_op_corba", &this->ctx_->writer_app_op_corba ());

    this->consumers_.bind ("tcpip_read_test_data", &this->tcpip_read_test_data_consumer_);
    this->consumers_.bind ("dds_read_test_data", &this->dds_read_test_data_consumer_);
    this->consumers_.bind ("corba_read_test_data", &this->corba_read_test_data_consumer_);
  }

  //
  // ~SimpleComponent_Servant
  //
  SimpleComponent_Servant::~SimpleComponent_Servant (void)
  {
  }

  //
  // subscribe_app_op_tcpip
  //
  ::Components::Cookie * SimpleComponent_Servant::
  subscribe_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // unsubscribe_app_op_tcpip
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  unsubscribe_app_op_tcpip(::Components::Cookie *)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // connect_app_op_dds
  //
  void SimpleComponent_Servant::
  connect_app_op_dds (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_app_op_dds
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_app_op_dds (void)
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
  // get_consumer_tcpip_read_test_data
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_tcpip_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // deserialize_tcpip_read_test_data
  //
  void SimpleComponent_Servant::
  deserialize_tcpip_read_test_data (SimpleComponent_Servant * servant,
                                    const ::CUTS_DDS::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    *event.in () <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_tcpip_read_test_data (event.in ());
  }

  //
  // get_consumer_dds_read_test_data
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_dds_read_test_data (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // deserialize_dds_read_test_data
  //
  void SimpleComponent_Servant::
  deserialize_dds_read_test_data (SimpleComponent_Servant * servant,
                                  const ::CUTS_DDS::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    *event.in () <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_dds_read_test_data (event.in ());
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
  // deserialize_corba_read_test_data
  //
  void SimpleComponent_Servant::
  deserialize_corba_read_test_data (SimpleComponent_Servant * servant,
                                    const ::CUTS_DDS::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    *event.in () <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_corba_read_test_data (event.in ());
  }
}

extern "C" ::PortableServer::Servant
create_SimpleComponent_Servant (const char * name, ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS::CCM::create_servant <
    ::CIDL_SimpleComponent_Basic_Impl::_Exec, 
    ::OpenSplice_SimpleComponent_Basic_Impl::SimpleComponent_Servant > (name, p);
}

