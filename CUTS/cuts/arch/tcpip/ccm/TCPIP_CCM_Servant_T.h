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
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class CUTS_TCPIP_CCM_Servant_T :
  public CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, CUTS_TCPIP_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Servant_T <T,
                              CONTEXT,
                              EXECUTOR,
                              POA_EXEC,
                              CUTS_TCPIP_CCM_Servant> base_type;

  /// Type definition of the context type.
  typedef typename base_type::context_type context_type;

  /// Type definition of the executor type.
  typedef typename base_type::executor_type executor_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         The parent servant
   * @param[in]       svnt_mgr        Manager of the servant.
   * @param[in]       executor        Executor component for servant.
   */
  CUTS_TCPIP_CCM_Servant_T (const char * name,
                            ::PortableServer::POA_ptr poa,
                            typename EXECUTOR::_ptr_type executor);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Servant_T (void);

  // Method for handling the event. It will dispatch the events
  // to the correct method.
  virtual int handle_event (ACE_UINT32 id, CUTS_TCPIP_InputCDR & input);

protected:
  /// Type definition of the virtual table.
  typedef CUTS_TCPIP_Servant_VTable_T <T> vtable_type;

  /// Virtual table for the servant.
  static vtable_type table_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant_T.inl"
#endif

#include "TCPIP_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_T_H_
