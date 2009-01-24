// -*- C++ -*-

#ifndef _CPUBOUNDIMPL_EXEC_H_
#define _CPUBOUNDIMPL_EXEC_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "ace/pre.h"
#include "CPUBoundImplEC.h"
#include "cuts/CCM_Component_T.h"
#include "CPU_Worker.h"
#include "Test_Logger.h"

namespace CIDL_CPUBoundImpl
{
  /**
   * @class CPUBound
   *
   * Implementation of the CPUBound_Exec component executor
   */
  class CPUBound :
    public CUTS_CCM_Component_T < CPUBound_Exec, antispam::CCM_CPUBound_Context > 
  {
    public:
    // Type definition for this component
    typedef CPUBound type;

    // Type definition of the base component type
    typedef CUTS_CCM_Component_T < CPUBound_Exec, antispam::CCM_CPUBound_Context > base_type;

    // Default constructor
    CPUBound (void);

    // Destructor
    virtual ~CPUBound (void);

    // EventSink: InPortA
    virtual void push_InPortA (antispam::NullEvent * ev);

    void push_InPortA_i (antispam::NullEvent * ev);

    // EventSink: InPortB
    virtual void push_InPortB (antispam::NullEvent * ev);

    void push_InPortB_i (antispam::NullEvent * ev);

    // EventSink: InPortE
    virtual void push_InPortE (antispam::NullEvent * ev);

    void push_InPortE_i (antispam::NullEvent * ev);

    // EventSink: InPortC
    virtual void push_InPortC (antispam::NullEvent * ev);

    void push_InPortC_i (antispam::NullEvent * ev);

    // EventSink: InPortD
    virtual void push_InPortD (antispam::NullEvent * ev);

    void push_InPortD_i (antispam::NullEvent * ev);

    // get logRate
    virtual ::CORBA::Long logRate (void);

    // set logRate
    virtual void logRate (::CORBA::Long logRate);

    // get testName
    virtual char * testName (void);

    // set testName
    virtual void testName (const char * testName);

    // get instName
    virtual char * instName (void);

    // set instName
    virtual void instName (const char * instName);

    // Environment: activate
    virtual void ccm_activate (void);

    private:
    // event handler for InPortA
    CUTS_CCM_Event_Handler_T < type, antispam::NullEvent > push_InPortA_;
    // event handler for InPortB
    CUTS_CCM_Event_Handler_T < type, antispam::NullEvent > push_InPortB_;
    // event handler for InPortC
    CUTS_CCM_Event_Handler_T < type, antispam::NullEvent > push_InPortC_;
    // event handler for InPortD
    CUTS_CCM_Event_Handler_T < type, antispam::NullEvent > push_InPortD_;
    // event handler for InPortE
    CUTS_CCM_Event_Handler_T < type, antispam::NullEvent > push_InPortE_;
    // variable: eventCountA
    ::CORBA::Long eventCountA_;

    // variable: logEventE
    ::CORBA::Boolean logEventE_;

    // variable: logEventB
    ::CORBA::Boolean logEventB_;

    // variable: logEventC
    ::CORBA::Boolean logEventC_;

    // variable: logEventD
    ::CORBA::Boolean logEventD_;

    // variable: logEventA
    ::CORBA::Boolean logEventA_;

    // variable: eventCountB
    ::CORBA::Long eventCountB_;

    // variable: eventCountE
    ::CORBA::Long eventCountE_;

    // variable: eventCountD
    ::CORBA::Long eventCountD_;

    // variable: eventCountC
    ::CORBA::Long eventCountC_;

    // worker variable: mycpu
    CUTS_LD_CPU_Worker mycpu_;

    // worker variable: logger
    CUTS_Test_Logger logger_;

    // variable: logRate
    ::CORBA::Long logRate_;

    // variable: testName
    ACE_CString testName_;

    // variable: instName
    ACE_CString instName_;
  };

  class CPUBoundHome_i :
    public virtual CPUBoundHome_Exec 
  {
    public:
    // default constructor
    CPUBoundHome_i (void);

    // destructor
    virtual ~CPUBoundHome_i (void);

    // default creation method
    virtual ::Components::EnterpriseComponent_ptr create (void);
  };
}

#include "CPUBoundImpl_exec_export.h"

// create_antispam_CPUBoundHome_Impl
extern "C" CPUBOUNDIMPL_EXEC_Export
::Components::HomeExecutorBase_ptr 
create_antispam_CPUBoundHome_Impl (void);

#include /**/ "ace/post.h"

#endif  // !defined _CPUBOUNDIMPL_EXEC_H_
