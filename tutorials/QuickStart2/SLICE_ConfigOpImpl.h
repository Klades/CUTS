// -*- C++ -*-

#ifndef _SLICE_CONFIGOPIMPL_H_
#define _SLICE_CONFIGOPIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "ComponentTypesEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"


namespace SLICE_ConfigOpImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_SLICE_ConfigOp_Impl::ConfigOp_Exec, ::SLICE::CCM_ConfigOp_Context > ConfigOp_Base;

  /**
   * @class ConfigOp
   *
   * Implementation of the CIAO_SLICE_ConfigOp_Impl::ConfigOp_Exec component executor
   */
  class ConfigOp :
    public ConfigOp_Base
  {
    public:
    // Type definition of the base component type
    typedef ConfigOp_Base base_type;

    // Default constructor
    ConfigOp (void);

    // Destructor
    virtual ~ConfigOp (void);

    // sink: recvEvent
    virtual void push_recvEvent (::SLICE::SimpleEvent * ev);

    private:
  };
}

#include "SLICE_ConfigOp_impl_export.h"

//
// create_SLICE_ConfigOp_Impl
//
extern "C" SLICE_CONFIGOP_IMPL_Export
::Components::EnterpriseComponent_ptr create_SLICE_ConfigOp_Impl (void);

#include "ace/post.h"

#endif  // !defined _SLICE_CONFIGOPIMPL_H_

// end of auto-generated file

