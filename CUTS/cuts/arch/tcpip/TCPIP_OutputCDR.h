// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_OuputCDR.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_OUTPUTCDR_H_
#define _CUTS_TCPIP_OUTPUTCDR_H_

#include "ace/CDR_Stream.h"
#include "TCPIP_export.h"

/**
 * @class CUTS_TCPIP_OutputCDR
 */
class CUTS_TCPIP_Export CUTS_TCPIP_OutputCDR : public ACE_OutputCDR
{
public:
  CUTS_TCPIP_OutputCDR (void);

  virtual ~CUTS_TCPIP_OutputCDR (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_OutputCDR.inl"
#endif

#endif  // !defined _CUTS_TCPIP_INPUTCDR_H_
