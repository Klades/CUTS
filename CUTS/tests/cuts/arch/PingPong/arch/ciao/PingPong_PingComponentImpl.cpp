// This file was generated by:
// $Id$

#include "PingPong_PingComponentImpl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace PingPong_PingComponentImpl
{
  //
  // PingComponent
  //
  PingComponent::PingComponent (void)
  {
  }

  //
  // ~PingComponent
  //
  PingComponent::~PingComponent (void)
  {
  }

  //
  // sink: PP_min_msg_in
  //
  void PingComponent::push_PP_min_msg_in (::PingPong::PP_min_msg_ev * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // sink: PP_seq_msg_in
  //
  void PingComponent::push_PP_seq_msg_in (::PingPong::PP_seq_msg_ev * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // sink: PP_string_msg_in
  //
  void PingComponent::push_PP_string_msg_in (::PingPong::PP_string_msg_ev * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // sink: PP_fixed_msg_in
  //
  void PingComponent::push_PP_fixed_msg_in (::PingPong::PP_fixed_msg_ev * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // sink: PP_array_msg_in
  //
  void PingComponent::push_PP_array_msg_in (::PingPong::PP_array_msg_ev * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // attribute setter: result_file
  //
  void PingComponent::result_file (const char * result_file)
  {
    this->result_file_ = result_file;
  }

  //
  // attribute getter: result_file
  //
  char * PingComponent::result_file (void)
  {
    ::CORBA::String_var s =
      ::CORBA::string_dup (this->result_file_.c_str ());
    return s._retn ();
  }

  //
  // attribute setter: nof_cycles
  //
  void PingComponent::nof_cycles (::CORBA::ULong nof_cycles)
  {
    this->nof_cycles_ = nof_cycles;
  }

  //
  // attribute getter: nof_cycles
  //
  ::CORBA::ULong PingComponent::nof_cycles (void)
  {
    return this->nof_cycles_;
  }
}

//
// create_PingPong_PingComponent_Impl
//
::Components::EnterpriseComponent_ptr
create_PingPong_PingComponent_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval,
                  ::PingPong_PingComponentImpl::PingComponent (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}


// end of auto-generated file
