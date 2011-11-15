// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_SERVANT_H_
#define _CUTS_TCPIP_SERVANT_H_

#include "TCPIP_Object_T.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
// Forward decl.
class ACE_InputCDR;
ACE_END_VERSIONED_NAMESPACE_DECL

// Forward decl.
class CUTS_TCPIP_ORB;

/**
 * @class CUTS_TCPIP_Servant
 *
 * Base class for all servant objects.
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Servant
{
public:
  // Friend decl.
  friend class CUTS_TCPIP_Servant_Manager;

  /**
   * Get the UUID assigned to the object. If the object has not
   * be activated, then the UUID will be ACE_Utils::NIL_UUID.
   * Whenever the object is deactivated, then the UUID  will be
   * ACE_Utils::NIL_UUID.
   */
  const ACE_Utils::UUID & the_UUID (void) const;

  const CUTS_TCPIP_ORB * the_ORB (void) const;

  /**
   * Handle an event received on the TCP/IP port.
   *
   * @param[in]         id          Id of the event
   * @param[in]         ev          Message block containing event data
   * @retval            0           Success
   * @retval            -1          Failure
   */
  virtual int handle_event (ACE_UINT32 id, ACE_InputCDR & input) = 0;

protected:
  /// Default constructor.
  CUTS_TCPIP_Servant (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_Servant (void);

private:
  /// UUID assigned to the objeect.
  ACE_Utils::UUID uuid_;

  /// ORB the servant was activated under.
  CUTS_TCPIP_ORB * orb_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Servant.inl"
#endif

#endif  // !defined _CUTS_TCPIP_SERVANT_H_
