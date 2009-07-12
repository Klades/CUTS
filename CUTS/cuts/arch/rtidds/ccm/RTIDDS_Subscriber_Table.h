// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_H_

#include "ndds/ndds_cpp.h"
#include "cuts/arch/ccm/CCM_Subscriber_Table.h"
#include "RTIDDS_CCM_export.h"

/**
 * @class CUTS_RTIDDS_CCM_Subscriber_Table
 */
class CUTS_RTIDDS_CCM_Export CUTS_RTIDDS_CCM_Subscriber_Table :
  public CUTS_CCM_Subscriber_Table
{
public:
  CUTS_RTIDDS_CCM_Subscriber_Table (void);

  virtual ~CUTS_RTIDDS_CCM_Subscriber_Table (void);

  virtual void configure (::DDSDomainParticipant * participant);

protected:
  ::DDSDomainParticipant * participant_;
};

#endif  // !defined _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_H_
