// -*- C++ -*-

#ifndef _PINGPONG_PINGCOMPONENTIMPL_H_
#define _PINGPONG_PINGCOMPONENTIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "PingComponentEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"


namespace PingPong_PingComponentImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_PingPong_PingComponent_Impl::PingComponent_Exec, ::PingPong::CCM_PingComponent_Context > PingComponent_Base;

  /**
   * @class PingComponent
   *
   * Implementation of the CIAO_PingPong_PingComponent_Impl::PingComponent_Exec component executor
   */
  class PingComponent :
    public PingComponent_Base
  {
    public:
    // Type definition of the base component type
    typedef PingComponent_Base base_type;

    // Default constructor
    PingComponent (void);

    // Destructor
    virtual ~PingComponent (void);

    // sink: PP_min_msg_in
    virtual void push_PP_min_msg_in (::PingPong::PP_min_msg_ev * ev);

    // sink: PP_seq_msg_in
    virtual void push_PP_seq_msg_in (::PingPong::PP_seq_msg_ev * ev);

    // sink: PP_string_msg_in
    virtual void push_PP_string_msg_in (::PingPong::PP_string_msg_ev * ev);

    // sink: PP_fixed_msg_in
    virtual void push_PP_fixed_msg_in (::PingPong::PP_fixed_msg_ev * ev);

    // sink: PP_array_msg_in
    virtual void push_PP_array_msg_in (::PingPong::PP_array_msg_ev * ev);

    // attribute setter: result_file
    virtual void result_file (const char * result_file);

    // attribute getter: result_file
    virtual char * result_file (void);

    // attribute setter: nof_cycles
    virtual void nof_cycles (::CORBA::ULong nof_cycles);

    // attribute getter: nof_cycles
    virtual ::CORBA::ULong nof_cycles (void);

    private:
    // attribute: result_file
    ACE_CString result_file_;

    // attribute: nof_cycles
    ::CORBA::ULong nof_cycles_;
  };
}

#include "PingPong_PingComponent_impl_export.h"

//
// create_PingPong_PingComponent_Impl
//
extern "C" PINGPONG_PINGCOMPONENT_IMPL_Export
::Components::EnterpriseComponent_ptr create_PingPong_PingComponent_Impl (void);

#include "ace/post.h"

#endif  // !defined _PINGPONG_PINGCOMPONENTIMPL_H_

// end of auto-generated file

