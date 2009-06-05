// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_SERVANT_H_
#define _CUTS_TCPIP_CCM_SERVANT_H_

#include "tao/PortableServer/Servant_Base.h"
#include "cuts/arch/tcpip/TCPIP_Servant.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Servant
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Servant :
  public CUTS_TCPIP_Servant,
  public virtual ::PortableServer::ServantBase
{
public:
  /**
   * Default constructor.
   */
  CUTS_TCPIP_CCM_Servant (const char * name);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Servant (void);

  /// Method for activating a component.
  virtual void activate_component (void);

  /// Method for passivating a component.
  virtual void passivate_component (void);

  /// Method for removing a component.
  virtual void remove (void);

  /// The name assigned to the servant.
  virtual const ACE_CString & name (void) const;

protected:
  /// Name of the CCM servant.
  ACE_CString name_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_H_
