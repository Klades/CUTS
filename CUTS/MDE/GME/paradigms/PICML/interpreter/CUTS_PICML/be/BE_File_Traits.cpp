// $Id$

#include "BE_File_Traits.h"

#if !defined (__CUTS_INLINE__)
#include "BE_File_Traits.inl"
#endif

//
// ~CUTS_BE_File_Traits
//
CUTS_BE_File_Traits::~CUTS_BE_File_Traits (void)
{
  if (this->out_.is_open ())
    this->out_.close ();
}
