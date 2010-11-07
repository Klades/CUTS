// -*- C++ -*-

#ifndef _HELLOWORLDIMPL_H_
#define _HELLOWORLDIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "HelloWorldEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "CPU_Worker.h"
#include "cuts/Periodic_Event_T.h"

namespace HelloWorldImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_HelloWorld_Impl::HelloWorld_Exec, ::CCM_HelloWorld_Context > HelloWorld_Base;

  /**
   * @class HelloWorld
   *
   * Implementation of the CIAO_HelloWorld_Impl::HelloWorld_Exec component executor
   */
  class HelloWorld :
    public HelloWorld_Base 
  {
    public:
    // Type definition of the base component type
    typedef HelloWorld_Base base_type;

    // Default constructor
    HelloWorld (void);

    // Destructor
    virtual ~HelloWorld (void);

    // sink: input_message
    virtual void push_input_message (::Message * ev);

    // PeriodicEvent: EventCreator
    void periodic_EventCreator (void);

    // attribute setter: message
    virtual void message (const char * message);

    // attribute getter: message
    virtual char * message (void);

    // attribute getter: readonly_message
    virtual char * readonly_message (void);

    private:
    // worker variable: cpu1
    CUTS_CPU_Worker cpu1_;

    // attribute: message
    ACE_CString message_;

    // attribute: readonly_message
    ACE_CString readonly_message_;

    // periodic: EventCreator
    CUTS_Periodic_Event_T < HelloWorld > periodic_EventCreator_;
  };
}

#include "HelloWorld_impl_export.h"

//
// create_HelloWorld_Impl
//
extern "C" HELLOWORLD_IMPL_Export
::Components::EnterpriseComponent_ptr create_HelloWorld_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLOWORLDIMPL_H_

// end of auto-generated file

