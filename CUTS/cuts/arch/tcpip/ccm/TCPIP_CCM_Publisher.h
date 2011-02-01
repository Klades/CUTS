// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Publisher.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_PUBLISHER_H_
#define _CUTS_TCPIP_CCM_PUBLISHER_H_

#include "cuts/arch/ccm/CCM_Publisher.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Publisher
 *
 * Implementation of the CCM publisher for the TCP/IP backend.
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Publisher :
  public CUTS_CCM_Publisher
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_Publisher (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Publisher (void);

private:
  // prevent the following operations
  CUTS_TCPIP_CCM_Publisher (const CUTS_TCPIP_CCM_Publisher &);
  const CUTS_TCPIP_CCM_Publisher & operator = (const CUTS_TCPIP_CCM_Publisher &);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Publisher.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
