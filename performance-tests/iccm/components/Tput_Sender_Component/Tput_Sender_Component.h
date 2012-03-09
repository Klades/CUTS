// -*- C++ -*-

#ifndef _TPUT_RECEIVER_COMPONENT_H_
#define _TPUT_RECEIVER_COMPONENT_H_

#include "ace/pre.h"
#include "../../Performance_Test_Components_iCCMC.h"

#include "cuts/arch/ccm/CCM_Component_T.h"
#include "ace/High_Res_Timer.h"

#include "Tput_Sender_Component_export.h"

namespace SenderComponentImpl
{
  /**
   * @class SenderComponent_Task
   */
  class SenderComponent_Task : public ACE_Task_Base
  {
  public:
    SenderComponent_Task (void)
      : is_active_ (false),
        count_ (0)
    {

    }

    virtual ~SenderComponent_Task (void)
    {

    }

    virtual int svc (void)
    {
      this->is_active_ = true;
      return 0;
    }

    void deactivate (void)
    {
      this->is_active_ = false;
    }

    size_t count (void) const
    {
      return this->count_;
    }

    void reset_count (void)
    {
      this->count_ = 0;
    }

  protected:
    /// Activate state of the task.
    bool is_active_;

    size_t count_;
  };

  /**
   * @class SenderComponent_Task
   */
  template <typename T>
  class SenderComponent_Task_T : public SenderComponent_Task
  {
  public:
    typedef void (iCCM_SenderComponent_Context::*PUSH_METHOD) (T * ev);
    typedef T * (iCCM_SenderComponent_Context::*NEW_EVENT_METHOD) (void);

    SenderComponent_Task_T (::iCCM_SenderComponent_Context_ptr ctx,
                            PUSH_METHOD push_method,
                            NEW_EVENT_METHOD new_event_method)
      : ctx_ (::iCCM_SenderComponent_Context::_duplicate (ctx)),
        push_method_ (push_method),
        new_event_method_ (new_event_method)
    {

    }

    virtual ~SenderComponent_Task_T (void)
    {

    }

    virtual int svc (void)
    {
      // Pass control to the base class.
      SenderComponent_Task::svc ();

      // Create a new event.
      T::_var_type ev = (this->ctx_->*this->new_event_method_) ();

      // Send the event as much as we can.
      while (this->is_active_)
      {
        this->count_ ++;
        (this->ctx_->*this->push_method_) (ev.in ());
      }

      return 0;
    }


  private:
    ::iCCM_SenderComponent_Context_var ctx_;

    PUSH_METHOD push_method_;

    NEW_EVENT_METHOD new_event_method_;
  };

  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T <
    CIAO_SenderComponent_Impl::SenderComponent_Exec,
    ::iCCM_SenderComponent_Context >
    SenderComponent_Base;

  /**
   * @class HelloReceiver
   *
   * Implementation of the CIAO_HelloReceiver_Impl::HelloReceiver_Exec component executor
   */
  class SenderComponent :
    public SenderComponent_Base
  {
  public:
    // Default constructor
    SenderComponent (void);

    // Destructor
    virtual ~SenderComponent (void);

    /// Activate the CCM component.
    virtual void ccm_activate (void);

    /// Passivate the CCM component.
    virtual void ccm_passivate (void);

    virtual void datasize (CORBA::UShort val);
    virtual CORBA::UShort datasize (void);

  private:
    ACE_High_Res_Timer timer_;
    ACE_Auto_Ptr <SenderComponent_Task> task_;
    CORBA::UShort datasize_;
  };
}

//
// create_HelloReceiver_Impl
//
extern "C" TPUT_SENDER_COMPONENT_Export
::Components::EnterpriseComponent_ptr create_TPUT_Sender_Component_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLORECEIVERIMPL_H_

// end of auto-generated file

