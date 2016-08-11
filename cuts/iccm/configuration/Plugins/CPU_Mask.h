#ifndef _CPU_MASK_H_
#define _CPU_MASK_H_

#include "ace/config-all.h"
#include <string>

class CPU_Mask
{
public:
  /// Default constructor
  CPU_Mask (void);

  /// Initializing constructor
  CPU_Mask (const char * affinity);
  ~CPU_Mask (void);

  CPU_Mask (const CPU_Mask & mask);

  CPU_Mask& operator= (const CPU_Mask & rhs);

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

  void parse_set (const char * affinity);
};

#endif
