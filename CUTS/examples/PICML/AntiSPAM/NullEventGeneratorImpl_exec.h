// -*- C++ -*-

#ifndef _NULLEVENTGENERATORIMPL_EXEC_H_
#define _NULLEVENTGENERATORIMPL_EXEC_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "ace/pre.h"
#include "NullEventGeneratorImplEC.h"
#include "cuts/CCM_Component_T.h"
#include "cuts/Periodic_Event_T.h"

namespace CIDL_NullEventGeneratorImpl
{
  /**
   * @class NullEventGenerator
   *
   * Implementation of the NullEventGenerator_Exec component executor
   */
  class NullEventGenerator :
    public CUTS_CCM_Component_T < NullEventGenerator_Exec, antispam::CCM_NullEventGenerator_Context > 
  {
    public:
    // Type definition for this component
    typedef NullEventGenerator type;

    // Type definition of the base component type
    typedef CUTS_CCM_Component_T < NullEventGenerator_Exec, antispam::CCM_NullEventGenerator_Context > base_type;

    // Default constructor
    NullEventGenerator (void);

    // Destructor
    virtual ~NullEventGenerator (void);

    // PeriodicEvent: eventGenerator
    void periodic_eventGenerator (void);

    // get publishHertz
    virtual ::CORBA::Double publishHertz (void);

    // set publishHertz
    virtual void publishHertz (::CORBA::Double publishHertz);

    // Environment: activate
    virtual void ccm_activate (void);

    private:
    // variable: publishHertz
    ::CORBA::Double publishHertz_;

    // periodic: eventGenerator
    CUTS_Periodic_Event_T <NullEventGenerator> periodic_eventGenerator_;
  };

  class NullEventGeneratorHome_i :
    public virtual NullEventGeneratorHome_Exec 
  {
    public:
    // default constructor
    NullEventGeneratorHome_i (void);

    // destructor
    virtual ~NullEventGeneratorHome_i (void);

    // default creation method
    virtual ::Components::EnterpriseComponent_ptr create (void);
  };
}

#include "NullEventGeneratorImpl_exec_export.h"

// create_antispam_NullEventGeneratorHome_Impl
extern "C" NULLEVENTGENERATORIMPL_EXEC_Export
::Components::HomeExecutorBase_ptr 
create_antispam_NullEventGeneratorHome_Impl (void);

#include /**/ "ace/post.h"

#endif  // !defined _NULLEVENTGENERATORIMPL_EXEC_H_
