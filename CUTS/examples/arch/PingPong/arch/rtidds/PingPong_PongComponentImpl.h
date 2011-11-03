// -*- C++ -*-

#ifndef _PINGPONG_PONGCOMPONENTIMPL_H_
#define _PINGPONG_PONGCOMPONENTIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "PongComponentEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"


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

    // sink: PP_seq_msg
    virtual void push_PP_seq_msg_in (::PingPong::PP_seq_msg_ev * ev);

    // sink: PP_array_msg
    virtual void push_PP_array_msg_in (::PingPong::PP_array_msg_ev * ev);

    // sink: PP_string_msg
    virtual void push_PP_string_msg_in (::PingPong::PP_string_msg_ev * ev);

    // sink: PP_quit_msg
    virtual void push_PP_quit_msg_in (::PingPong::PP_quit_msg_ev * ev);

    // sink: PP_fixed_msg
    virtual void push_PP_fixed_msg_in (::PingPong::PP_fixed_msg_ev * ev);

    // sink: PP_min_msg
    virtual void push_PP_min_msg_in (::PingPong::PP_min_msg_ev * ev);

    private:
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

