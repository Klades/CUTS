// $Id$

#include "Project_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Project_Generator.inl"
#endif

#include "../../BE_IDL_Node.h"

//
// CUTS_BE_Project_Write_T
//
void CUTS_BE_Project_Write_T <CUTS_BE_TCPIP_Ctx, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  std::string name (node.file_.name ());
  this->stub_files_.insert ("TCPIP_" + name + "C.cpp");

  base_type::generate (node);
}
