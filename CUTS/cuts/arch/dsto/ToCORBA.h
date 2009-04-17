#ifndef TO_CORBA_H
#define TO_CORBA_H

#include "ToCORBA_T.h"
#include "DSTO_Utilities_export.h"

namespace ToCORBA
{
  template<>
  DSTO_Utilities_Export
  void copy (void *to, char *from);
  
  template<>
  DSTO_Utilities_Export
  void copy (void *to, wchar_t *from);
}

#endif // TO_CORBA_H