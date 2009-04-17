#include "tao/String_Manager_T.h"

#include "ToCORBA.h"

namespace ToCORBA
{
  template<>
  void copy (void *to, char *from)
  {
    TAO::String_Manager *result_ptr =
      static_cast<TAO::String_Manager *> (to);
    *result_ptr = CORBA::string_dup (from);
  }
  
  template<>
  void copy (void *to, wchar_t *from)
  {
    TAO::WString_Manager *result_ptr =
      static_cast<TAO::WString_Manager *> (to);
    *result_ptr = CORBA::wstring_dup (from);
  }
}
