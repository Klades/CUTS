// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Remote_Endpoint_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_T_H_
#define _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_T_H_

#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint_T.h"
#include "TCPIP_CCM_Remote_Endpoint.h"
#include "TCPIP_CCM_EventConsumer.h"

/**
 * @class CUTS_TCPIP_CCM_Remote_Endpoint_T
 */
template <typename T>
class CUTS_TCPIP_CCM_Remote_Endpoint_T :
  public CUTS_TCPIP_CCM_Remote_Endpoint,
  public CUTS_TCPIP_Remote_Endpoint_T <T>
{
public:
  typedef typename CUTS_TCPIP_Remote_Endpoint_T <T>::type type;

  CUTS_TCPIP_CCM_Remote_Endpoint_T (void);

  virtual ~CUTS_TCPIP_CCM_Remote_Endpoint_T (void);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  virtual ::Components::EventConsumerBase_ptr disconnect (void);

private:
  /// The consumer for the endpoint.
  ::Components::TCPIP::EventConsumerBase_var consumer_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Remote_Endpoint_T.inl"
#endif

#include "TCPIP_CCM_Remote_Endpoint_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_T_H_
