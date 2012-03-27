// -*- C++ -*-

#ifndef _TPUT_RECEIVER_COMPONENT_H_
#define _TPUT_RECEIVER_COMPONENT_H_

#include "ace/pre.h"
#include "Tput_Sender_Conn_ComponentEC.h"

#include "cuts/arch/ccm/CCM_Component_T.h"
#include "ace/High_Res_Timer.h"

#include "Tput_Sender_Conn_Component_impl_export.h"

namespace CIAO_Sender_Conn_Component_Impl
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
  template <typename WRITER, typename T>
  class SenderComponent_Task_T : public SenderComponent_Task
  {
  public:
    SenderComponent_Task_T (typename WRITER::_ptr_type writer)
      : writer_ (WRITER::_duplicate (writer))
    {

    }

    virtual ~SenderComponent_Task_T (void)
    {

    }

    virtual int svc (void)
    {
      // Pass control to the base class.
      SenderComponent_Task::svc ();

      T data;

      // Send the event as much as we can.
      while (this->is_active_)
      {
        this->count_ ++;
        this->writer_->write_one (data, ::DDS::HANDLE_NIL);
      }

      return 0;
    }


  private:
    typename WRITER::_var_type writer_;
  };

  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < Sender_Conn_Component_Exec,
                                 CCM_Sender_Conn_Component_Context >
                                 Sender_Conn_Component_Base;

  class Sender_Conn_Component :
    public Sender_Conn_Component_Base
  {
  public:
    // Default constructor
    Sender_Conn_Component (void);

    // Destructor
    virtual ~Sender_Conn_Component (void);

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
extern "C" TPUT_SENDER_CONN_COMPONENT_IMPL_Export
::Components::EnterpriseComponent_ptr create_Tput_Sender_Conn_Component_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLORECEIVERIMPL_H_

// end of auto-generated file

