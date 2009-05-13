#ifndef CUTS_DSTO_ADAPTER_T_CPP
#define CUTS_DSTO_ADAPTER_T_CPP

#include "DSTO_Adapter_T.h"

namespace CUTS_DSTO
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

#endif // CUTS_DSTO_ADAPTER_T_CPP