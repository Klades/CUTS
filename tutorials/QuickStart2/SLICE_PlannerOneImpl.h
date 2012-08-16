// -*- C++ -*-

#ifndef _SLICE_PLANNERONEIMPL_H_
#define _SLICE_PLANNERONEIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "ComponentTypesEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"


namespace SLICE_PlannerOneImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_SLICE_PlannerOne_Impl::PlannerOne_Exec, ::SLICE::CCM_PlannerOne_Context > PlannerOne_Base;

  /**
   * @class PlannerOne
   *
   * Implementation of the CIAO_SLICE_PlannerOne_Impl::PlannerOne_Exec component executor
   */
  class PlannerOne :
    public PlannerOne_Base
  {
    public:
    // Type definition of the base component type
    typedef PlannerOne_Base base_type;

    // Default constructor
    PlannerOne (void);

    // Destructor
    virtual ~PlannerOne (void);

    // sink: recvEvent
    virtual void push_recvEvent (::SLICE::SimpleEvent * ev);

    private:
  };
}

#include "SLICE_PlannerOne_impl_export.h"

//
// create_SLICE_PlannerOne_Impl
//
extern "C" SLICE_PLANNERONE_IMPL_Export
::Components::EnterpriseComponent_ptr create_SLICE_PlannerOne_Impl (void);

#include "ace/post.h"

#endif  // !defined _SLICE_PLANNERONEIMPL_H_

// end of auto-generated file

