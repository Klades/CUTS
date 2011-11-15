// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Publisher_Table.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_

#include "cuts/arch/ccm/CCM_Publisher_Table.h"
#include "ccpp_dds_dcps.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Publisher_Table
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Publisher_Table :
  public CUTS_CCM_Publisher_Table
{
public:
  /// Default constructor.
  CUTS_OpenSplice_CCM_Publisher_Table (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Publisher_Table (void);

  /**
   * Configure the table with this publisher. This means that all
   * connections in this table use the specified publisher.
   */
  virtual void configure (::DDS::Publisher_ptr publisher);

protected:
  /// Publisher assigned to this table.
  ::DDS::Publisher_var publisher_;
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher_Table.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_
