// -*- C++ -*-

#ifndef _HELLOWORLD_H_
#define _HELLOWORLD_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "HelloWorldEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "cuts/Periodic_Event_T.h"

namespace HelloWorld_Basic_Impl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec, ::CCM_HelloWorld_Context > HelloWorld_Base;

  /**
   * @class HelloWorld
   *
   * Implementation of the CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec component executor
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

    // sink: handle_message
    virtual void push_handle_message (::Message * ev);

    // PeriodicEvent: sendData
    void periodic_sendData (void);

    // attribute setter: message
    virtual void message (const char * message);

    // attribute getter: message
    virtual char * message (void);

    // attribute getter: readonly_message
    virtual char * readonly_message (void);

    virtual void ccm_activate (void);

    private:
    // variable: eventCount
    ::CORBA::Long eventCount_;

    // variable: isActive
    ::CORBA::Long isActive_;

    // attribute: readonly_message
    ACE_CString readonly_message_;

    // attribute: message
    ACE_CString message_;

    // periodic: sendData
    CUTS_Periodic_Event_T < HelloWorld > periodic_sendData_;
  };
}

#include "HelloWorld_Basic_Impl_export.h"

//
// create_HelloWorld_Basic_Impl
//
extern "C" HELLOWORLD_BASIC_IMPL_Export
::Components::EnterpriseComponent_ptr create_HelloWorld_Basic_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLOWORLD_H_

// end of auto-generated file

