// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_H_

#include "ndds/ndds_cpp.h"
#include "cuts/arch/ccm/CCM_Publisher_Table.h"
#include "RTIDDS_CCM_export.h"

/**
 * @class CUTS_RTIDDS_CCM_Publisher_Table
 */
class CUTS_RTIDDS_CCM_Export CUTS_RTIDDS_CCM_Publisher_Table :
  public CUTS_CCM_Publisher_Table
{
public:
  /// Default constructor.
  CUTS_RTIDDS_CCM_Publisher_Table (void);

  /// Destuctor.
  virtual ~CUTS_RTIDDS_CCM_Publisher_Table (void);

  /**
   * Configure the publisher table. This method will assign a DDS
   * publisher to this publisher table.
   */
  virtual void configure (::DDSPublisher * publisher);

protected:
  /// The publisher assigned to the table.
  ::DDSPublisher * publisher_;
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher_Table.inl"
#endif

#endif  // !defined _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_H_
