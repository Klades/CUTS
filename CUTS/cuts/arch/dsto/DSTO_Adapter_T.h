#ifndef DSTO_ADAPTER_T_H
#define DSTO_ADAPTER_T_H

#include /**/ "ace/pre.h"

#include "DSTO_AdapterBase.h"

namespace DSTO
{
  template<typename BASE_SKEL>
  class Adapter : public virtual BASE_SKEL,
                  public virtual AdapterBase
  {
  public:
    Adapter (const char * instance_name,
             ::CIAO::Container_ptr container);
    virtual ~Adapter (void);
  };
}

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "DSTO_Adapter_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("DSTO_Adapter_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include /**/ "ace/post.h"

#endif // DSTO_ADAPTER_T_H