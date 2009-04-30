// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Remote_Endpoint_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_REMOTE_ENDPOINT_T_H_
#define _CUTS_TCPIP_REMOTE_ENDPOINT_T_H_

#include "TCPIP_Remote_Endpoint.h"

/**
 * @class CUTS_TCPIP_Remote_Endpoint_T
 */
template <typename T>
class CUTS_TCPIP_Remote_Endpoint_T : public CUTS_TCPIP_Remote_Endpoint
{
public:
  typedef T type;

  CUTS_TCPIP_Remote_Endpoint_T (void);

  virtual ~CUTS_TCPIP_Remote_Endpoint_T (void);

  int send_event (T * ev);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Remote_Endpoint_T.inl"
#endif

#include "TCPIP_Remote_Endpoint_T.cpp"

#endif  // !defined _CUTS_TCPIP_REMOTE_ENDPOINT_T_H_
