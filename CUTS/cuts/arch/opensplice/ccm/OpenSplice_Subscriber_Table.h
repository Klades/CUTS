// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_

#include "ccpp_dds_dcps.h"
#include "cuts/arch/ccm/CCM_Subscriber_Table.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Subscriber_Table
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Subscriber_Table :
  public CUTS_CCM_Subscriber_Table
{
public:
  CUTS_OpenSplice_CCM_Subscriber_Table (void);

  virtual ~CUTS_OpenSplice_CCM_Subscriber_Table (void);

  virtual void configure (::DDS::DomainParticipant_ptr participant);

protected:
  ::DDS::DomainParticipant_var participant_;
};

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_TABLE_H_
