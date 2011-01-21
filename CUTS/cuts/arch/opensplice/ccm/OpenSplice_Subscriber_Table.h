// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_

#include "cuts/arch/ccm/CCM_Subscriber_Table.h"
#include "ccpp_dds_dcps.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Subscriber_Table
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Subscriber_Table :
  public CUTS_CCM_Subscriber_Table
{
public:
  /// Default constructor.
  CUTS_OpenSplice_CCM_Subscriber_Table (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Subscriber_Table (void);

  /**
   * Configure the table with this publisher. This means that all
   * connections in this table use the specified publisher.
   */
  virtual void configure (::DDS::Publisher_ptr publisher);

protected:
  /// Publisher assigned to this table.
  ::DDS::Publisher_var publisher_;
};

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_
