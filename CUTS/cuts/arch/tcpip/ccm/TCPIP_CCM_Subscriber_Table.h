// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Subscriber_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_TCPIP_CCM_SUBSCRIBER_TABLE_H_

#include "cuts/arch/ccm/CCM_Subscriber_Table.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Subscriber_Table
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Subscriber_Table :
  public CUTS_CCM_Subscriber_Table
{
public:
  CUTS_TCPIP_CCM_Subscriber_Table (void);

  virtual ~CUTS_TCPIP_CCM_Subscriber_Table (void) = 0;

private:
  CUTS_TCPIP_CCM_Subscriber_Table (const CUTS_TCPIP_CCM_Subscriber_Table &);
  const CUTS_TCPIP_CCM_Subscriber_Table & operator = (const CUTS_TCPIP_CCM_Subscriber_Table &);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Subscriber_Table.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_SUBSCRIBER_TABLE_H_
