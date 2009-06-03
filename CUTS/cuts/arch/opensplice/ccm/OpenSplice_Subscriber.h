// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_SUBSCRIBER_H_
#define _CUTS_OPENSPLICE_SUBSCRIBER_H_

#include "cuts/arch/ccm/CCM_Single_Subscriber.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Subscriber
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Subscriber :
  public CUTS_CCM_Single_Subscriber
{
public:
  CUTS_OpenSplice_CCM_Subscriber (void);

  virtual ~CUTS_OpenSplice_CCM_Subscriber (void);
};

#endif
