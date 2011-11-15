// -*- C++ -*-

#ifndef _SLICE_EFFECTORIMPL_H_
#define _SLICE_EFFECTORIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "ComponentTypesEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "Client_Logger.h"

namespace SLICE_EffectorImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_SLICE_Effector_Impl::Effector_Exec, ::SLICE::CCM_Effector_Context > Effector_Base;

  /**
   * @class Effector
   *
   * Implementation of the CIAO_SLICE_Effector_Impl::Effector_Exec component executor
   */
  class Effector :
    public Effector_Base
  {
    public:
    // Type definition of the base component type
    typedef Effector_Base base_type;

    // Default constructor
    Effector (void);

    // Destructor
    virtual ~Effector (void);

    // sink: effectorSettings
    virtual void push_effectorSettings (::SLICE::SimpleEvent * ev);

    virtual void ccm_activate (void);

    virtual void ccm_passivate (void);

    private:
    // worker variable: logger
    CUTS_Client_Logger logger_;
  };
}

#include "SLICE_Effector_impl_export.h"

//
// create_SLICE_Effector_Impl
//
extern "C" SLICE_EFFECTOR_IMPL_Export
::Components::EnterpriseComponent_ptr create_SLICE_Effector_Impl (void);

#include "ace/post.h"

#endif  // !defined _SLICE_EFFECTORIMPL_H_

// end of auto-generated file

