#include "FromCORBA.h"

namespace FromCORBA
{
  template<>
  void copy (void *to, TAO::String_Manager from)
  {
    char **result_ptr = static_cast<char **> (to);
    *result_ptr = CORBA::string_dup (from.in ());
  }
  
  template<>
  void copy (void *to, TAO::WString_Manager from)
  {
    wchar_t **result_ptr = static_cast<wchar_t **> (to);
    *result_ptr = CORBA::wstring_dup (from.in ());
  }
}
