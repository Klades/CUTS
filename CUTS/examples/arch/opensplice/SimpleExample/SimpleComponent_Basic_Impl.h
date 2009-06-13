// -*- C++ -*-

#ifndef _SIMPLECOMPONENT_BASIC_IMPL_H_
#define _SIMPLECOMPONENT_BASIC_IMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "SimpleComponentEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "cuts/Periodic_Event_T.h"

namespace SimpleComponent_Basic_Impl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec, ::Example::CCM_SimpleComponent_Context > SimpleComponent_Base;

  /**
   * @class SimpleComponent
   *
   * Implementation of the CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec component executor
   */
  class SimpleComponent :
    public SimpleComponent_Base 
  {
    public:
    // Type definition of the base component type
    typedef SimpleComponent_Base base_type;

    // Default constructor
    SimpleComponent (void);

    // Destructor
    virtual ~SimpleComponent (void);

    // sink: tcpip_read_test_data
    virtual void push_tcpip_read_test_data (::Outer::TestData_DDS * ev);

    // sink: dds_read_test_data
    virtual void push_dds_read_test_data (::Outer::TestData_DDS * ev);

    // sink: corba_read_test_data
    virtual void push_corba_read_test_data (::Outer::TestData_DDS * ev);

    // PeriodicEvent: sendData
    void periodic_sendData (void);

    virtual void ccm_activate (void);

    private:
    // variable: isActive
    ::CORBA::Long isActive_;

    // variable: eventCount
    ::CORBA::Long eventCount_;

    // worker variable: cpu1
    CUTS_LD_CPU_Worker cpu1_;

    // periodic: sendData
    CUTS_Periodic_Event_T < SimpleComponent > periodic_sendData_;
  };
}

#include "SimpleComponent_Basic_Impl_export.h"

//
// create_SimpleComponent_Basic_Impl
//
extern "C" SIMPLECOMPONENT_BASIC_IMPL_Export
::Components::EnterpriseComponent_ptr create_SimpleComponent_Basic_Impl (void);

#include "ace/post.h"

#endif  // !defined _SIMPLECOMPONENT_H_

// end of auto-generated file

