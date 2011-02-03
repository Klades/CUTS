// -*- C++ -*-

#ifndef _PINGPONG_PINGCOMPONENTIMPL_H_
#define _PINGPONG_PINGCOMPONENTIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "PingComponentEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "Stats.h"
#include "ace/streams.h"

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

    // sink: PP_seq_msg
    virtual void push_PP_seq_msg_in (::PingPong::PP_seq_msg_ev * ev);

    // sink: PP_array_msg
    virtual void push_PP_array_msg_in (::PingPong::PP_array_msg_ev * ev);

    // sink: PP_fixed_msg
    virtual void push_PP_fixed_msg_in (::PingPong::PP_fixed_msg_ev * ev);

    // sink: PP_min_msg
    virtual void push_PP_min_msg_in (::PingPong::PP_min_msg_ev * ev);

    // sink: PP_string_msg
    virtual void push_PP_string_msg_in (::PingPong::PP_string_msg_ev * ev);

    virtual void nof_cycles (::CORBA::ULong nof_cycles);
    virtual ::CORBA::ULong nof_cycles (void);

    virtual void result_file (const char *);
    virtual char * result_file (void);

    virtual void ccm_activate (void);

  private:
    void start_new_block (bool print_stats = true);

    size_t nof_cycles_;

    size_t block_;

    char topic_;

    PP_Stats roundtrip_;

    PP_Stats write_access_;

    PP_Stats read_access_;

    ACE_Time_Value roundtrip_start_time_;

    ACE_CString result_file_;

    std::ofstream outfile_;
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

