// $Id$

#include "CoreDX.h"

#if !defined (__CUTS_INLINE__)
#include "CoreDX.inl"
#endif

namespace iCCM
{
  const CoreDX::statusmask_type CoreDX::STATUS_MASK_NONE = 0;
  const CoreDX::statusmask_type CoreDX::STATUS_MASK_DATA_AVAILABLE = ::DDS::DATA_AVAILABLE_STATUS;
  const CoreDX::instancehandle_type CoreDX::HANDLE_NIL = ::DDS::HANDLE_NIL;
}
