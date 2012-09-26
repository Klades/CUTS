// $Id$

#include "Servant_VTable_Visitor.h"

#if !defined (__CUTS_INLINE__)
#include "Servant_VTable_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#include "be_extern.h"
#include "be_global.h"

#include "ast_consumes.h"
#include "utl_identifier.h"

namespace iCCM
{
namespace TCPIP
{

//
// visit_consumes
//
int Servant_VTable_Visitor::visit_consumes (AST_Consumes * node)
{
  const char * local_name = node->local_name ()->get_string ();

  this->sfile_
    << "self_type::table_[" << this->port_counter_ << "] = "
    << "&self_type::push_" << local_name << ";" << std::endl;
  this->port_counter_++;

  return 0;
}

} // namespace iCCM
} // namespace TCPIP
