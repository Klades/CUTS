// -*- C++ -*-

#ifndef _HELLOSENDERIMPL_H_
#define _HELLOSENDERIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"

#include "HelloWorld_Components_iCCMC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "cuts/Periodic_Event_T.h"

namespace HelloSenderImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_HelloSender_Impl::HelloSender_Exec, ::iCCM_HelloSender_Context > HelloSender_Base;

  /**
   * @class HelloSender
   *
   * Implementation of the CIAO_HelloSender_Impl::HelloSender_Exec component executor
   */
  class HelloSender :
    public HelloSender_Base
  {
    public:
    // Type definition of the base component type
    typedef HelloSender_Base base_type;

    // Default constructor
    HelloSender (void);

    // Destructor
    virtual ~HelloSender (void);

    // PeriodicEvent: EventCreator
    void periodic_EventCreator (void);

    // attribute setter: message
    virtual void message (const char * message);

    // attribute getter: message
    virtual char * message (void);

    private:
    // attribute: message
    ACE_CString message_;

    // periodic: EventCreator
    CUTS_Periodic_Event_T < HelloSender > periodic_EventCreator_;
  };
}

#include "HelloSender_impl_export.h"

//
// create_HelloSender_Impl
//
extern "C" HELLOSENDER_IMPL_Export
::Components::EnterpriseComponent_ptr create_HelloSender_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLOSENDERIMPL_H_

// end of auto-generated file

