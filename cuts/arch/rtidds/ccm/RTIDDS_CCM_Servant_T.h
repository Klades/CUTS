// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_CCM_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RTIDDS_CCM_SERVANT_T_H_
#define _CUTS_RTIDDS_CCM_SERVANT_T_H_

#include "ccm/CCM_EventsS.h"
#include "ccm/CCM_HomeS.h"
#include "ccm/CCM_EnumerationS.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"
#include "cuts/arch/ccm/CCM_Servant_T.h"
#include "RTIDDS_CCM_Servant.h"

/**
 * @class CUTS_RTIDDS_CCM_Servant_T
 *
 * Template base class for all RTI-DDS servants.
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class CUTS_RTIDDS_CCM_Servant_T :
  public CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, CUTS_RTIDDS_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Servant_T <T,
                              CONTEXT,
                              EXECUTOR,
                              POA_EXEC,
                              CUTS_RTIDDS_CCM_Servant>
                              base_type;

  /**
   * Initializing constructor.
   *
   * @param[in]         name        Name of the servant
   * @param[in]         poa         POA for the ports
   * @param[in]         executor    Executor managed by servant
   */
  CUTS_RTIDDS_CCM_Servant_T (const char * name,
                             ::PortableServer::POA_ptr poa,
                             typename EXECUTOR::_ptr_type executor);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_Servant_T (void);

  /// Configure the servant.
  virtual void configure (::DDSDomainParticipant * participant);
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_CCM_Servant_T.inl"
#endif

#include "RTIDDS_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_RTIDDS_CCM_SERVANT_T_H_
