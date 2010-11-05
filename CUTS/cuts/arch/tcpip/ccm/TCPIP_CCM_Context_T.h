// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Context_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_CONTEXT_T_H_
#define _CUTS_TCPIP_CCM_CONTEXT_T_H_

#include "ccm/Session/CCM_SessionContextC.h"
#include "cuts/config.h"

/**
 * @class CUTS_TCPIP_CCM_Events_Impl
 */
template <typename T, typename SVNT>
class CUTS_TCPIP_CCM_Context_T : public T
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
  CUTS_TCPIP_CCM_Context_T (SVNT & svnt);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Context_T (void);

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
  /// The actual servent for this wrapper.
  SVNT & svnt_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Context_T.inl"
#endif

#include "TCPIP_CCM_Context_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_T_H_
