// $Id$

#include "SimpleComponent_svnt.h"

namespace Example {
SimpleComponent_Context::SimpleComponent_Context (SimpleComponent_Servant & parent)
: SimpleComponent_Context_Base (parent)
{
}

SimpleComponent_Context::~SimpleComponent_Context (void)
{
}

void SimpleComponent_Context::push_app_op_ndds (::Outer::TestData_DDS *ev)
{
  this->app_op_ndds_.send_event (ev);
}

void SimpleComponent_Context::push_app_op_ospl (::Outer::TestData_DDS *ev)
{
  this->app_op_ospl_.send_event (ev);
}

void SimpleComponent_Context::push_app_op_tcpip (::Outer::TestData_DDS *ev)
{
  this->app_op_tcpip_.send_event (ev);
}

void SimpleComponent_Context::push_app_op_corba (::Outer::TestData_DDS *ev)
{
  this->app_op_corba_.send_event (ev);
}

::Outer::TestData_DDS * SimpleComponent_Context::new_app_op_ndds_event (void)
{
  return this->app_op_ndds_.allocate_event ();
}

::Outer::TestData_DDS * SimpleComponent_Context::new_app_op_ospl_event (void)
{
  return this->app_op_ospl_.allocate_event ();
}

::Outer::TestData_DDS * SimpleComponent_Context::new_app_op_tcpip_event (void)
{
  return this->app_op_tcpip_.allocate_event ();
}

::Outer::TestData_DDS * SimpleComponent_Context::new_app_op_corba_event (void)
{
  return this->app_op_corba_.allocate_event ();
}

iCCM::CHAOS_Publisher & SimpleComponent_Context::get_app_op_ndds_publisher (void)
{
  return this->app_op_ndds_;
}

iCCM::CHAOS_Publisher & SimpleComponent_Context::get_app_op_ospl_publisher (void)
{
  return this->app_op_ospl_;
}

iCCM::CHAOS_Publisher & SimpleComponent_Context::get_app_op_tcpip_publisher (void)
{
  return this->app_op_tcpip_;
}

iCCM::CHAOS_Publisher & SimpleComponent_Context::get_app_op_corba_publisher (void)
{
  return this->app_op_corba_;
}

SimpleComponent_Servant::
SimpleComponent_Servant (const char * name,
                         ::PortableServer::POA_ptr poa,
                         ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec_ptr executor)
: SimpleComponent_Servant_Base (this, name, poa, executor),
  ndds_read_test_data_consumer_ (this, &SimpleComponent_Servant::push_ndds_read_test_data),
  ospl_read_test_data_consumer_ (this, &SimpleComponent_Servant::push_ospl_read_test_data),
  corba_read_test_data_consumer_ (this, &SimpleComponent_Servant::push_corba_read_test_data),
  tcpip_read_test_data_consumer_ (this, &SimpleComponent_Servant::push_tcpip_read_test_data)
{
  this->emits_.bind ("app_op_ndds", &this->ctx_->get_app_op_ndds_publisher ());
  this->consumers_.bind ("ndds_read_test_data", &this->ndds_read_test_data_consumer_);
  this->consumers_.bind ("ospl_read_test_data", &this->ospl_read_test_data_consumer_);
  this->consumers_.bind ("corba_read_test_data", &this->corba_read_test_data_consumer_);
  this->consumers_.bind ("tcpip_read_test_data", &this->tcpip_read_test_data_consumer_);
  this->emits_.bind ("app_op_ospl", &this->ctx_->get_app_op_ospl_publisher ());
  this->emits_.bind ("app_op_tcpip", &this->ctx_->get_app_op_tcpip_publisher ());
  this->emits_.bind ("app_op_corba", &this->ctx_->get_app_op_corba_publisher ());
}

SimpleComponent_Servant::~SimpleComponent_Servant (void)
{
}

void SimpleComponent_Servant::set_attributes (const ::Components::ConfigValues & config)
{
  const ::CORBA::ULong length = config.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    // Get the next configuraton value
    const ::Components::ConfigValue * value = config[i];
  }
}

void SimpleComponent_Servant::connect_app_op_ndds (::Outer::TestData_DDSConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::disconnect_app_op_ndds (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

void SimpleComponent_Servant::connect_app_op_ospl (::Outer::TestData_DDSConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::disconnect_app_op_ospl (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

void SimpleComponent_Servant::connect_app_op_tcpip (::Outer::TestData_DDSConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::disconnect_app_op_tcpip (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

void SimpleComponent_Servant::connect_app_op_corba (::Outer::TestData_DDSConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::disconnect_app_op_corba (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

void SimpleComponent_Servant::push_ndds_read_test_data (::Outer::TestData_DDS *ev)
{
  if (0 != this->impl_)
    this->impl_->push_ndds_read_test_data (ev);
}

void SimpleComponent_Servant::push_ospl_read_test_data (::Outer::TestData_DDS *ev)
{
  if (0 != this->impl_)
    this->impl_->push_ospl_read_test_data (ev);
}

void SimpleComponent_Servant::push_corba_read_test_data (::Outer::TestData_DDS *ev)
{
  if (0 != this->impl_)
    this->impl_->push_corba_read_test_data (ev);
}

void SimpleComponent_Servant::push_tcpip_read_test_data (::Outer::TestData_DDS *ev)
{
  if (0 != this->impl_)
    this->impl_->push_tcpip_read_test_data (ev);
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::get_ndds_read_test_data_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::get_ospl_read_test_data_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::get_corba_read_test_data_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::get_tcpip_read_test_data_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::PortableServer::Servant
create_Example_SimpleComponent_Servant (const char * name,
                                        ::PortableServer::POA_ptr poa,
                                        ::Components::EnterpriseComponent_ptr p)
{
  return ::iCCM::create_servant < CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec, SimpleComponent_Servant > (name, poa, p);
}

}
