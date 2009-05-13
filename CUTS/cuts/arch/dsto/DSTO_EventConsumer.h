#ifndef CUTS_DSTO_EVENTCONSUMER_H
#define CUTS_DSTO_EVENTCONSUMER_H

#include "ccm/CCM_EventConsumerBaseS.h"

#include "DSTO_Utilities_export.h"

namespace CUTS_DSTO
{
  class DSTO_Utilities_Export EventConsumer
    : public virtual POA_Components::EventConsumerBase
  {
  protected:
    EventConsumer (void);
    virtual ~EventConsumer (void);

  public:  
    virtual void push_event ( ::Components::EventBase *);
    virtual void ciao_push_event ( ::Components::EventBase * ev,
                                  const char * source_id,
                                  ::CORBA::TypeCode_ptr tc);
  // Seems this isn't needed to make derived classes concrete,
  // while including it gives an 'ambiguous inheritance' error.
  #if 0
    virtual ::CORBA::Boolean ciao_is_substitutable (
      const char * event_repo_id);
  #endif // false
  };
}

#endif // CUTS_DSTO_EVENTCONSUMER_H