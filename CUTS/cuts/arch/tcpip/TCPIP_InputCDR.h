// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_InputCDR.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_INPUTCDR_H_
#define _CUTS_TCPIP_INPUTCDR_H_

#include "ace/CDR_Stream.h"
#include "TCPIP_export.h"

class CUTS_TCPIP_Export CUTS_TCPIP_InputCDR :
  public ACE_InputCDR
{
public:
  CUTS_TCPIP_InputCDR (const ACE_Message_Block * data, int byte_order);

  CUTS_TCPIP_InputCDR (const char * buf, size_t bufsiz);

  virtual ~CUTS_TCPIP_InputCDR (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_InputCDR.inl"
#endif

#endif  // !defined _CUTS_TCPIP_INPUTCDR_H_
