#include "DSTO_EventConsumer.h"

namespace DSTO
{
  EventConsumer::EventConsumer (void)
  {
  }

  EventConsumer::~EventConsumer (void)
  {
  }

  void
  EventConsumer::push_event ( ::Components::EventBase *)
  {
  }

  void
  EventConsumer::ciao_push_event ( ::Components::EventBase * /* ev */,
                                  const char * /* source_id */,
                                  ::CORBA::TypeCode_ptr /* tc */)
  {
  }
#if 0
  ::CORBA::Boolean
  EventConsumer::ciao_is_substitutable (
    const char * /* event _repo_id */)
  {
    return false;
  }
#endif // false
}