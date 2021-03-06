#include "CPU_Mask.h"
#include "ace/Tokenizer_T.h"

CPU_Mask::CPU_Mask (void)
{
  zero ();
}

CPU_Mask::CPU_Mask (const char * affinity)
{
  zero ();
  parse_set (affinity);
}

CPU_Mask::~CPU_Mask (void)
{
}

CPU_Mask::CPU_Mask (const CPU_Mask & mask)
{
  this->mask_ = mask.mask_;
}

CPU_Mask & CPU_Mask::operator= (const CPU_Mask & rhs)
{
  this->mask_ = rhs.mask_;

  return *this;
}

void CPU_Mask::set (int affinity)
{
#ifdef ACE_HAS_PTHREADS
  CPU_SET (affinity, &mask_);
#endif
#ifdef ACE_WIN32
  mask_ |= (1 << affinity);
#endif
}

void CPU_Mask::clear (int affinity)
{
#ifdef ACE_HAS_PTHREADS
  CPU_CLR (affinity, &mask_);
#endif
#ifdef ACE_WIN32
  mask_ &= ~(1 << affinity);
#endif
}

void CPU_Mask::zero (void)
{
#ifdef ACE_HAS_PTHREADS
  CPU_ZERO (&mask_);
#endif
#ifdef ACE_WIN32
  mask_ = 0;
#endif
}

bool CPU_Mask::is_set (int cpu)
{
#ifdef ACE_HAS_PTHREADS
  return CPU_ISSET (cpu, &mask_);
#endif
#ifdef ACE_WIN32
  return mask_ & (1 << cpu);
#endif
}

#ifdef ACE_HAS_PTHREADS
cpu_set_t * CPU_Mask::get (void) 
{
  return &mask_;
}
#endif

#ifdef ACE_WIN32
DWORD_PTR * CPU_Mask::get (void)
{
  return &mask_;
}
#endif

void CPU_Mask::parse_set (const char * affinity)
{
  char * local_affinity = ACE_OS::strdup (affinity);

  ACE_Tokenizer_T<char> tokenizer (local_affinity);
  tokenizer.delimiter (',');

  char * token = 0;

  while ((token = tokenizer.next()))
  {
    int i = ACE_OS::atoi (token);

    if (i >= 0)
    {
      set(i);
    }
  }

  ACE_OS::free (local_affinity); 
}


