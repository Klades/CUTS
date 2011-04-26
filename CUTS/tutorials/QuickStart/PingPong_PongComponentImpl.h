// -*- C++ -*-

#ifndef _PINGPONG_PONGCOMPONENTIMPL_H_
#define _PINGPONG_PONGCOMPONENTIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "PingPongEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "Client_Logger.h"
#include "CPU_Worker.h"

namespace PingPong_PongComponentImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_PingPong_PongComponent_Impl::PongComponent_Exec, ::PingPong::CCM_PongComponent_Context > PongComponent_Base;

  /**
   * @class PongComponent
   *
   * Implementation of the CIAO_PingPong_PongComponent_Impl::PongComponent_Exec component executor
   */
  class PongComponent :
    public PongComponent_Base
  {
    public:
    // Type definition of the base component type
    typedef PongComponent_Base base_type;

    // Default constructor
    PongComponent (void);

    // Destructor
    virtual ~PongComponent (void);

    // sink: recvData
    virtual void push_recvData (::PingPong::SimpleEvent * ev);

    private:
    // async event handler variable: recvData
    CUTS_CCM_Event_Handler_T < PongComponent, ::PingPong::SimpleEvent > recvData_event_handler_;

    public:
    // sink impl: recvData
    void push_recvData_i (::PingPong::SimpleEvent * ev);

    private:
    // worker variable: logger
    CUTS_Client_Logger logger_;

    // worker variable: cpu
    CUTS_CPU_Worker cpu_;
  };
}

#include "PingPong_PongComponent_impl_export.h"

//
// create_PingPong_PongComponent_Impl
//
extern "C" PINGPONG_PONGCOMPONENT_IMPL_Export
::Components::EnterpriseComponent_ptr create_PingPong_PongComponent_Impl (void);

#include "ace/post.h"

#endif  // !defined _PINGPONG_PONGCOMPONENTIMPL_H_

// end of auto-generated file

