// -*- C++ -*-

#ifndef _SLICE_PLANNERTWOIMPL_H_
#define _SLICE_PLANNERTWOIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "ComponentTypesEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"


namespace SLICE_PlannerTwoImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_SLICE_PlannerTwo_Impl::PlannerTwo_Exec, ::SLICE::CCM_PlannerTwo_Context > PlannerTwo_Base;

  /**
   * @class PlannerTwo
   *
   * Implementation of the CIAO_SLICE_PlannerTwo_Impl::PlannerTwo_Exec component executor
   */
  class PlannerTwo :
    public PlannerTwo_Base
  {
    public:
    // Type definition of the base component type
    typedef PlannerTwo_Base base_type;

    // Default constructor
    PlannerTwo (void);

    // Destructor
    virtual ~PlannerTwo (void);

    // sink: recvEvent
    virtual void push_recvEvent (::SLICE::SimpleEvent * ev);

    private:
  };
}

#include "SLICE_PlannerTwo_impl_export.h"

//
// create_SLICE_PlannerTwo_Impl
//
extern "C" SLICE_PLANNERTWO_IMPL_Export
::Components::EnterpriseComponent_ptr create_SLICE_PlannerTwo_Impl (void);

#include "ace/post.h"

#endif  // !defined _SLICE_PLANNERTWOIMPL_H_

// end of auto-generated file

