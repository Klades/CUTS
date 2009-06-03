// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_SERVANT_T_H_
#define _CUTS_TCPIP_CCM_SERVANT_T_H_

#include "ccm/CCM_EventsS.h"
#include "ccm/CCM_HomeS.h"
#include "ccm/CCM_EnumerationS.h"
#include "cuts/arch/tcpip/TCPIP_Servant_T.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"
#include "TCPIP_CCM_Servant.h"
#include "cuts/arch/ccm/CCM_Servant_T.h"

/**
 * @class CUTS_TCPIP_CCM_Events_Impl
 */
template <typename T, typename CONTEXT, typename EXEC, typename POA_EXEC>
class CUTS_TCPIP_CCM_Servant_T :
  public CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC>,
  public CUTS_TCPIP_Servant_T <T>
{
public:
  /// Type definition of the context type.
  typedef CONTEXT context_type;

  /// Type definition of the executor type.
  typedef EXEC executor_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         The parent servant
   * @param[in]       svnt_mgr        Manager of the servant.
   * @param[in]       executor        Executor component for servant.
   */
  CUTS_TCPIP_CCM_Servant_T (const char * name,
                            T * servant,
                            CUTS_TCPIP_Servant_Manager & svnt_mgr,
                            typename EXEC::_ptr_type executor);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Servant_T (void);

  virtual void activate_component (void);

  virtual void passivate_component (void);

  virtual void configuration_complete (void);

  virtual void remove (void);

protected:
  CUTS_TCPIP_Servant_Manager & svnt_mgr_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant_T.inl"
#endif

#include "TCPIP_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_T_H_
