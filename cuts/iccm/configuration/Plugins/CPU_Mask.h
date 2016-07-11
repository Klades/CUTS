#ifndef _CPU_MASK_H_
#define _CPU_MASK_H_

#include "ace/config-all.h"
#include <string>

class CPU_Mask
{
public:
  CPU_Mask (void);
  ~CPU_Mask (void);

  void set (int affinity);
  void clear (int affinity);
  void zero (void);

#ifdef ACE_HAS_PTHREADS
  cpu_set_t * get (void);
#endif
#ifdef ACE_WIN32
  DWORD_PTR * get (void);
#endif

private:
#ifdef ACE_HAS_PTHREADS
  cpu_set_t * mask_;
#endif
#ifdef ACE_WIN32
  DWORD_PTR * mask_;
#endif

};

#endif
