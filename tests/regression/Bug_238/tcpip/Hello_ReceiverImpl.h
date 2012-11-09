// -*- C++ -*-

#ifndef _HELLO_RECEIVERIMPL_H_
#define _HELLO_RECEIVERIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"

#include "Receiver_iCCMC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "Client_Logger.h"

namespace Hello_ReceiverImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_Hello_Receiver_Impl::Receiver_Exec, ::Hello::iCCM_Receiver_Context > Receiver_Base;

  /**
   * @class Receiver
   *
   * Implementation of the CIAO_Hello_Receiver_Impl::Receiver_Exec component executor
   */
  class Receiver :
    public Receiver_Base
  {
    public:
    // Type definition of the base component type
    typedef Receiver_Base base_type;

    // Default constructor
    Receiver (void);

    // Destructor
    virtual ~Receiver (void);

    // sink: click_in
    virtual void push_click_in (::Hello::TimeOut * ev);

    private:
    // async event handler variable: click_in
    CUTS_CCM_Event_Handler_T < Receiver, ::Hello::TimeOut > click_in_event_handler_;

    public:
    // sink impl: click_in
    void push_click_in_i (::Hello::TimeOut * ev);

    // sink: push_message
    virtual void push_push_message (::Hello::PushMessage * ev);

    private:
    // async event handler variable: push_message
    CUTS_CCM_Event_Handler_T < Receiver, ::Hello::PushMessage > push_message_event_handler_;

    public:
    // sink impl: push_message
    void push_push_message_i (::Hello::PushMessage * ev);

    // attribute setter: iterations
    virtual void iterations (::CORBA::Short iterations);

    // attribute getter: iterations
    virtual ::CORBA::Short iterations (void);

    virtual void ccm_activate (void);

    virtual void ccm_passivate (void);

    private:
    // worker variable: logger
    CUTS_Client_Logger logger_;

    // attribute: iterations
    ::CORBA::Short iterations_;
  };
}

#include "Hello_Receiver_impl_export.h"

//
// create_Hello_Receiver_Impl
//
extern "C" HELLO_RECEIVER_IMPL_Export
::Components::EnterpriseComponent_ptr create_Hello_Receiver_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLO_RECEIVERIMPL_H_

// end of auto-generated file

