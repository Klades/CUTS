// -*- C++ -*-

#ifndef _HELLORECEIVERIMPL_H_
#define _HELLORECEIVERIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"

#include "HelloWorld_Components_iCCMC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "cuts/iccm/servant/FacetImpl_T.h"

namespace HelloReceiverImpl
{
  // Forward decl of the component executor
  class HelloReceiver;

  // Object class implementation
  typedef ::iCCM::FacetImpl_T < HelloReceiver, CCM_Messenger> Echo_i_Base;
  class Echo_i
  : public virtual Echo_i_Base
  {
    public:
    typedef Echo_i_Base base_type;
    // Constructor
    Echo_i (HelloReceiver * parent);

    // Destructor
    ~Echo_i (void);

    // increment_count
    void increment_count (void);

    private:
    // The parent component
    HelloReceiver * parent_;
  };

  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_HelloReceiver_Impl::HelloReceiver_Exec, ::iCCM_HelloReceiver_Context > HelloReceiver_Base;

  /**
   * @class HelloReceiver
   *
   * Implementation of the CIAO_HelloReceiver_Impl::HelloReceiver_Exec component executor
   */
  class HelloReceiver :
    public HelloReceiver_Base
  {
    public:
    // Type definition of the base component type
    typedef HelloReceiver_Base base_type;

    // Default constructor
    HelloReceiver (void);

    // Destructor
    virtual ~HelloReceiver (void);

    // sink: greeting
    virtual void push_greeting (::MessageEvent * ev);

    private:
    // async event handler variable: greeting
    CUTS_CCM_Event_Handler_T < HelloReceiver, ::MessageEvent > greeting_event_handler_;

    public:
    // sink impl: greeting
    void push_greeting_i (::MessageEvent * ev);

    // facet: echo
    virtual ::CCM_Messenger_ptr
      get_echo (void);
    private:
    ::CCM_Messenger_var echo_i_;
    public:
    public:
    // variable setter: count
    virtual void count (::CORBA::ULong count);

    // variable getter: count
    virtual ::CORBA::ULong count (void);

    private:
    // variable: count
    ::CORBA::ULong count_;
  };
}

#include "HelloReceiver_impl_export.h"

//
// create_HelloReceiver_Impl
//
extern "C" HELLORECEIVER_IMPL_Export
::Components::EnterpriseComponent_ptr create_HelloReceiver_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLORECEIVERIMPL_H_

// end of auto-generated file

