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
  // push_emitEvent
  //
  void SimpleComponent_Servant_Context::
  push_emitEvent (::Outer::TestData_DDS * ev)
  {
    this->emitEvent_.send_event (ev);
  }

  //
  // writer_emitEvent
  //
  CUTS_OpenSplice_CCM_Subscriber & SimpleComponent_Servant_Context::
  writer_emitEvent (void)
  {
    return this->emitEvent_;
  }

  //
  // push_publishEvent
  //
  void SimpleComponent_Servant_Context::
  push_publishEvent (::Outer::TestData_DDS * ev)
  {
    this->publishEvent_.send_event (ev);
  }

  //
  // writers_publishEvent
  //
  CUTS_CCM_Subscriber_Table & SimpleComponent_Servant_Context::
  writers_publishEvent (void)
  {
    return this->publishEvent_;
  }

  //
  // SimpleComponent_Servant
  //
  SimpleComponent_Servant::
  SimpleComponent_Servant (const char * name,
                           ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec_ptr executor)
   : SimpleComponent_Servant_Base (name, executor),
     processEvent_consumer_ (this, &SimpleComponent_Servant::deserialize_processEvent)
  {
    this->emits_.bind ("emitEvent", &this->ctx_->writer_emitEvent ());
    this->publishes_.bind ("publishEvent", &this->ctx_->writers_publishEvent ());

    this->consumers_.bind ("processEvent", &this->processEvent_consumer_);
  }

  //
  // ~SimpleComponent_Servant
  //
  SimpleComponent_Servant::~SimpleComponent_Servant (void)
  {
  }

  //
  // connect_emitEvent
  //
  void SimpleComponent_Servant::
  connect_emitEvent (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_emitEvent
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  disconnect_emitEvent (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // subscribe_publishEvent
  //
  ::Components::Cookie * SimpleComponent_Servant::
  subscribe_publishEvent (::Outer::TestData_DDSConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // unsubscribe_publishEvent
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  unsubscribe_publishEvent(::Components::Cookie *)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // get_consumer_processEvent
  //
  ::Outer::TestData_DDSConsumer_ptr SimpleComponent_Servant::
  get_consumer_processEvent (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // deserialize_processEvent
  //
  void SimpleComponent_Servant::
  deserialize_processEvent (SimpleComponent_Servant * servant,
                            const ::CUTS_DDS::Outer::TestData_DDS & dds_event)
  {
    // First, extract the event.
    CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    *event.in () <<= dds_event;

    // Now, puch the event to the implemetation.
    if (servant->impl_)
      servant->impl_->push_processEvent (event.in ());
  }

  extern "C" ::PortableServer::Servant
  create_Example_SimpleComponent_Servant (const char * name, ::Components::EnterpriseComponent_ptr p)
  {
    return ::CUTS::CCM::create_servant <
      ::CIAO_Example_SimpleComponent_Impl::SimpleComponent_Exec, 
      ::Example::SimpleComponent_Servant > (name, p);
  }
}

