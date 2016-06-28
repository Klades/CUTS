#include "CPU_Mask.h"

CPU_Mask::CPU_Mask (void)
{
#ifdef ACE_HAS_PTHREADS
  mask_ = new cpu_set_t;
#endif
#ifdef ACE_WIN32
  mask_ = new DWORD_PTR;
#endif
  zero ();
}

CPU_Mask::~CPU_Mask (void)
{
  delete mask_;
}

void CPU_Mask::set (int affinity)
{
#ifdef ACE_HAS_PTHREADS
  CPU_SET (affinity, mask_);
#endif
#ifdef ACE_WIN32
  *mask_ |= (1 << affinity);
#endif
}

void CPU_Mask::clear (int affinity)
{
#ifdef ACE_HAS_PTHREADS
  CPU_CLEAR (affinity, mask_);
#endif
#ifdef ACE_WIN32
  *mask_ &= ~(1 << affinity);
#endif
}

void CPU_Mask::zero (void)
{
#ifdef ACE_HAS_PTHREADS
  CPU_ZERO (mask_);
#endif
#ifdef ACE_WIN32
  *mask_ = 0;
#endif
}

#ifdef ACE_HAS_PTHREADS
cpu_set_t * CPU_Mask::get (void) 
{
  return mask_;
}
#endif

#ifdef ACE_WIN32
DWORD_PTR * CPU_Mask::get (void)
{
  return mask_;
}
#endif