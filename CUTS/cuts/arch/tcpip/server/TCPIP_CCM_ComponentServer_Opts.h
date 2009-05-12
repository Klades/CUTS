// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_ComponentServer_Opts.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_COMPONENTSERVER_OPTS_H_
#define _CUTS_TCPIP_CCM_COMPONENTSERVER_OPTS_H_

#include "ace/SString.h"

/**
 * @class CUTS_TCPIP_CCM_ComponentServer_Opts
 */
class CUTS_TCPIP_CCM_ComponentServer_Opts
{
public:
  /// UUID for the component server.
  ACE_CString uuid_;

  /// IOR of the callback object.
  ACE_CString callback_ior_;
};

#endif  // !defined _CUTS_TCPIP_CCM_COMPONENTSERVER_OPTS_H_
