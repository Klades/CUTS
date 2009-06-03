// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_

#include "cuts/arch/ccm/CCM_EventConsumer.h"
#include "cuts/arch/opensplice/OpenSplice_ListenerBase.h"
#include "EventsS.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_EventConsumer
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_EventConsumer :
  public virtual CUTS_CCM_EventConsumer,
  public virtual ::POA_Components::OpenSplice::EventConsumer,
  public CUTS_OpenSplice_ListenerBase
{
 public:
  /**
   * Initializing contructor.
   */
  CUTS_OpenSplice_CCM_EventConsumer (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_EventConsumer (void);

  /**
   * Get the topic of the event consumer. This is used to 
   * by publishers who want to send events to this consumer.
   */
  virtual char * topic (void);

  int configure (const char * inst, const char * topic);

 private:
  /// The topic of the event consumer.
  ACE_CString topic_;
};

#endif  // !defined _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
