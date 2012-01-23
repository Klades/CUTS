// -*- C++ -*-

//=============================================================================
/**
 *  @file         Context_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_CONTEXT_T_H_
#define _CUTS_ICCM_CONTEXT_T_H_

#include "ccm/Session/CCM_SessionContextC.h"

#include "cuts/config.h"

namespace iCCM
{

/**
 * @class Context_T
 */
template <typename T, typename SVNT>
class Context_T : public T
{
public:
  /// Type definition of the context type.
  typedef T context_type;

  /// Type definition of the servant type.
  typedef SVNT servant_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         The parent servant
   * @param[in]       svnt_mgr        Manager of the servant.
   * @param[in]       executor        Executor component for servant.
   */
  Context_T (SVNT & svnt);

  /// Destructor.
  virtual ~Context_T (void);

  virtual ::Components::CCMHome_ptr get_CCM_home (void);

#if !defined (CCM_LW)
  virtual ::Components::Principal_ptr get_caller_principal (void);

  virtual ::CORBA::Boolean get_rollback_only (void);

  virtual ::Components::Transaction::UserTransaction_ptr get_user_transaction (void);

  virtual ::CORBA::Boolean is_caller_in_role (const char *);

  virtual void set_rollback_only (void);
#endif

  virtual ::CORBA::Object_ptr resolve_service_reference (const char *);

  virtual ::CORBA::Object_ptr get_CCM_object (void);

protected:
  SVNT & svnt_;
};

}

#if defined (__CUTS_INLINE__)
#include "Context_T.inl"
#endif

#include "Context_T.cpp"

#endif  // !defined _CUTS_ICCM_CONTEXT_T_H_
