// $Id$

#include "Traits.h"

#if !defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#include "../../../BE_IDL_Node.h"

//
// svnt_base_project
//
void CUTS_BE_TCPIP_Traits::
write_stub_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  proj << "    TCPIP_" << node.name_ << "C.cpp" << std::endl;
}
