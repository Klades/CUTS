#ifndef DSTO_ADAPTER_T_CPP
#define DSTO_ADAPTER_T_CPP

#include "DSTO_Adapter_T.h"

namespace DSTO
{
  template<typename BASE_SKEL>
  Adapter<BASE_SKEL>::Adapter (const char * instance_name,
                               ::CIAO::Container_ptr container)
    : AdapterBase (instance_name, container)
  {
  }

  template<typename BASE_SKEL>
  Adapter<BASE_SKEL>::~Adapter (void)
  {
  }
}

#endif // DSTO_ADAPTER_T_CPP