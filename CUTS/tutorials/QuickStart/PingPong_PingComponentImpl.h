// -*- C++ -*-

#ifndef _PINGPONG_PINGCOMPONENTIMPL_H_
#define _PINGPONG_PINGCOMPONENTIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "PingPongEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "cuts/Periodic_Event_T.h"

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

    // PeriodicEvent: eventProducer
    void periodic_eventProducer (void);

    private:
    // variable: eventCount
    ::CORBA::Long eventCount_;

    // periodic: eventProducer
    CUTS_Periodic_Event_T < PingComponent > periodic_eventProducer_;
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

