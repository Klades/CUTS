// -*- C++ -*-

#ifndef _HELLORECEIVERIMPL_H_
#define _HELLORECEIVERIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "HelloWorld_iCCMC.h"

#include "cuts/arch/ccm/CCM_Component_T.h"


namespace HelloReceiverImpl
{
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

