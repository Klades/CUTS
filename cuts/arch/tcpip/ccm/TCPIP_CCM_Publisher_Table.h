// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_PUBLISHER_TABLE_H_
#define _CUTS_TCPIP_CCM_PUBLISHER_TABLE_H_

#include "cuts/arch/ccm/CCM_Publisher_Table.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Publisher_Table
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Publisher_Table :
  public CUTS_CCM_Publisher_Table
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_Publisher_Table (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Publisher_Table (void);

private:
  // prevent the following operations.
  CUTS_TCPIP_CCM_Publisher_Table (const CUTS_TCPIP_CCM_Publisher_Table &);
  const CUTS_TCPIP_CCM_Publisher_Table & operator = (const CUTS_TCPIP_CCM_Publisher_Table &);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Publisher_Table.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_PUBLISHER_TABLE_H_
