// -*- C++ -*-

#ifndef _TPUT_RECEIVER_COMPONENT_H_
#define _TPUT_RECEIVER_COMPONENT_H_

#include "ace/pre.h"
#include "Performance_Test_Components_iCCMC.h"

#include "cuts/arch/ccm/CCM_Component_T.h"
#include "ace/High_Res_Timer.h"

#include "Receiver_Component_export.h"

namespace ReceiverComponentImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T <
    CIAO_ReceiverComponent_Impl::ReceiverComponent_Exec,
    ::iCCM_ReceiverComponent_Context >
    ReceiverComponent_Base;

  /**
   * @class HelloReceiver
   *
   * Implementation of the CIAO_HelloReceiver_Impl::HelloReceiver_Exec component executor
   */
  class ReceiverComponent :
    public ReceiverComponent_Base
  {
  public:
    // Default constructor
    ReceiverComponent (void);

    // Destructor
    virtual ~ReceiverComponent (void);

    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);

    virtual void push_size8data (Size8DataEvent * );
    virtual void push_size16data (Size16DataEvent * );
    virtual void push_size32data (Size32DataEvent * );
    virtual void push_size64data (Size64DataEvent * );

  private:
    /// Number of events received.
    size_t count_;

    /// Start time of the deployment.
    ACE_High_Res_Timer timer_;
  };
}

#include "Receiver_Component_export.h"

//
// create_HelloReceiver_Impl
//
extern "C" TPUT_RECEIVER_COMPONENT_Export
::Components::EnterpriseComponent_ptr create_TPUT_Receiver_Component_Impl (void);

#include "ace/post.h"

#endif  // !defined _HELLORECEIVERIMPL_H_

// end of auto-generated file

