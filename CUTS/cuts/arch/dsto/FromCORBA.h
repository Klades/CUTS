#ifndef FROM_CORBA_H
#define FROM_CORBA_H

#include "tao/String_Manager_T.h"

#include "FromCORBA_T.h"
#include "DSTO_Utilities_export.h"

namespace FromCORBA
{
  template<>
  DSTO_Utilities_Export
  void copy (void *to, TAO::String_Manager from);
  
  template<>
  DSTO_Utilities_Export
  void copy (void *to, TAO::WString_Manager from);
}

#endif // FROM_CORBA_H