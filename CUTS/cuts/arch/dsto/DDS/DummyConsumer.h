#ifndef DUMMYCONSUMER_H
#define DUMMYCONSUMER_H

#include "DSTO_EventConsumer.h"

#include "DummyEventS.h"

namespace DSTO
{
  class ExecBase;
  class ContextBase;
}

class DDS_Utilities_Export DummyConsumer_impl
  : public virtual POA_CUTS_DDS::DummyConsumer,
    public virtual DSTO::EventConsumer
{
public:
  DummyConsumer_impl ( ::DSTO::ExecBase *,
                      ::DSTO::ContextBase *);
                      
  void push_Dummy ( ::CUTS_DDS::Dummy *);
};

#endif //DUMMYCONSUMER_H

