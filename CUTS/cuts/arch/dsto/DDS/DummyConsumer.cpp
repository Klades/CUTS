#include "DummyConsumer.h"

namespace CUTS_DDS
{
  DummyConsumer_impl::DummyConsumer_impl ( ::CUTS_DSTO::ExecBase *,
                                          ::CUTS_DSTO::ContextBase *)
  {
  }

  void
  DummyConsumer_impl::push_Dummy ( ::CUTS_DDS::Dummy *)
  {
  }
}


