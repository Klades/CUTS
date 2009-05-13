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

#include "ccm/CCM_ObjectS.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Events_Impl
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Servant :
  public virtual POA_Components::CCMObject
{
public:
  /**
   * Default constructor.
   */
  CUTS_TCPIP_CCM_Servant (const char * name);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Servant (void);

  /// Method for activating a component.
  virtual void activate_component (void) = 0;

  /// Method for passivating a component.
  virtual void passivate_component (void) = 0;

  /// Method for removing a component.
  virtual void remove (void) = 0;

  const ACE_CString & name (void) const;

protected:
  /// Name of the CCM servant.
  ACE_CString name_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_SERVANT_H_
