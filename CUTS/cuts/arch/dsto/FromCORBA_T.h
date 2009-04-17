#ifndef FROM_CORBA_T_H
#define FROM_CORBA_T_H

namespace FromCORBA
{
  template<typename T>
  void copy (void *to, T from)
  {
    T* result_ptr = static_cast<T*> (to);
    *result_ptr = from;
  };
}

#endif // FROM_CORBA_T_H