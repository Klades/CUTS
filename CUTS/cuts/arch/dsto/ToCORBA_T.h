#ifndef TO_CORBA_T_H
#define TO_CORBA_T_H

namespace ToCORBA
{
  template<typename T>
  void copy (void *to, T from)
  {
    T* result_ptr = static_cast<T*> (to);
    *result_ptr = from;
  };
}

#endif // TO_CORBA_T_H