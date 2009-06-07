// This file was generated by:
// $Id$

#include "SimpleComponent_Impl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace SimpleComponent_Basic_Impl
{
  //
  // SimpleComponent
  //
  SimpleComponent::SimpleComponent (void)
  : eventCount_ (0),
    isActive_ (true)
  {
    this->periodic_sendData_.init (this, &SimpleComponent::periodic_sendData);
    this->periodic_sendData_.configure (CUTS_Periodic_Event::PE_CONSTANT, 10);
    this->register_object (&this->periodic_sendData_);
  }

  //
  // ~SimpleComponent
  //
  SimpleComponent::~SimpleComponent (void)
  {
  }

  //
  // sink: read_test_data
  //
  void SimpleComponent::push_read_test_data (::Outer::TestData_DDS * ev)
  {
    ACE_DEBUG ((LM_DEBUG,
		"%T (%t) - %M - received event %d from %s\n",
		ev->packet ().id,
		ev->packet ().name.in ()));
  }

  //
  // PeriodicEvent: sendData
  //
  void SimpleComponent::periodic_sendData (void)
  {
    ACE_DEBUG ((LM_INFO,
		"%T (%t) - %M - sending a new event\n"));
    
    ::CUTS_CCM_Event_T < ::OBV_Outer::TestData_DDS > event;
    event->key (7);
    event->packet ().name = ::CORBA::string_dup ("James H. Hill");
    event->packet ().id = this->eventCount_ ++;
    event->packet ().urgent = false;

    this->ctx_->push_app_op_emit (event.in ());
  }

  void SimpleComponent::ccm_activate (void)
  {
    // pass control to the base class
    this->base_type::ccm_activate ();
  }
}

//
// create_SimpleComponent_Basic_Impl
//
::Components::EnterpriseComponent_ptr 
create_SimpleComponent_Basic_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval, 
                  ::SimpleComponent_Basic_Impl::SimpleComponent (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}


// end of auto-generated file
