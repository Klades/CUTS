#ifndef DUMMYCONSUMER_H
#define DUMMYCONSUMER_H

#include "DSTO_EventConsumer.h"

#include "DummyEventS.h"

namespace CUTS_DSTO
{
  class ExecBase;
  class ContextBase;
}

namespace CUTS_DDS
{
  class DDS_Utilities_Export DummyConsumer_impl
    : public virtual ::POA_CUTS_DDS::DummyConsumer,
      public virtual ::CUTS_DSTO::EventConsumer
  {
  public:
    DummyConsumer_impl ( ::CUTS_DSTO::ExecBase *,
                        ::CUTS_DSTO::ContextBase *);
                        
    void push_Dummy ( ::CUTS_DDS::Dummy *);
  };
}

#endif //DUMMYCONSUMER_H

