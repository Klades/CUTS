// -*- C++ -*-

#ifndef _HELLO_SENDERIMPL_H_
#define _HELLO_SENDERIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"

#include "Sender_iCCMC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "cuts/Periodic_Event_T.h"

namespace Hello_SenderImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_Hello_Sender_Impl::Sender_Exec, ::Hello::iCCM_Sender_Context > Sender_Base;

  /**
   * @class Sender
   *
   * Implementation of the CIAO_Hello_Sender_Impl::Sender_Exec component executor
   */
  class Sender :
    public Sender_Base
  {
    public:
    // Type definition of the base component type
    typedef Sender_Base base_type;

    // Default constructor
    Sender (void);

    // Destructor
    virtual ~Sender (void);

    // sink: read_message
    virtual void push_read_message (::Hello::ReadMessage * ev);

    // PeriodicEvent: trigger
    void periodic_trigger (void);

    // attribute setter: local_message
    virtual void local_message (const char * local_message);

    // attribute getter: local_message
    virtual char * local_message (void);

    private:
    // attribute: local_message
    ACE_CString local_message_;

    // periodic: trigger
    CUTS_Periodic_Event_T < Sender > periodic_trigger_;
  };
}

#include "Hello_Sender_impl_export.h"

//
// create_Hello_Sender_Impl
//
extern "C" HELLO_SENDER_IMPL_Export
::Components::EnterpriseComponent_ptr create_Hello_Sender_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLO_SENDERIMPL_H_

// end of auto-generated file

