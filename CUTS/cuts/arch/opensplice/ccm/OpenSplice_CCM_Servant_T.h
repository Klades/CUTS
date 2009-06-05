// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_CCM_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_SERVANT_T_H_
#define _CUTS_OPENSPLICE_CCM_SERVANT_T_H_

#include "ccm/CCM_EventsS.h"
#include "ccm/CCM_HomeS.h"
#include "ccm/CCM_EnumerationS.h"
#include "cuts/arch/tcpip/TCPIP_Servant_T.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"
#include "cuts/arch/ccm/CCM_Servant_T.h"
#include "OpenSplice_CCM_Servant.h"

/**
 * @class CUTS_OpenSplice_CCM_Servant_T
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class CUTS_OpenSplice_CCM_Servant_T :
  public CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, CUTS_OpenSplice_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Servant_T <T,
			      CONTEXT,
			      EXECUTOR,
			      POA_EXEC,
			      CUTS_OpenSplice_CCM_Servant> base_type;
  
  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Servant_T (void);

protected:
  /**
   * Initializing constructor.
   *
   * @param[in]       name              Name of the servant
   * @param[in]       executor          Executor for the servant
   * @param[in]       participant       Domain participant for the servant
   */
  CUTS_OpenSplice_CCM_Servant_T (const char * name,
				 typename EXECUTOR::_ptr_type executor,
				 ::DDS::DomainParticipant_ptr participant);
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_CCM_Servant_T.inl"
#endif

#include "OpenSplice_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_T_H_
