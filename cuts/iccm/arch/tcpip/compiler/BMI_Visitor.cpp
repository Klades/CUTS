// $Id$

#include "BMI_Visitor.h"

#if !defined (__CUTS_INLINE__)
#include "BMI_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#include "be_extern.h"
#include "be_global.h"

#include "ast_consumes.h"
#include "utl_identifier.h"

namespace iCCM
{
namespace TCPIP
{

int BMI_Visitor::visit_consumes (AST_Consumes * node)
{
  const char * local_name = node->local_name ()->get_string ();

  this->sfile_
    << "," << std::endl
    << "  " << local_name << "_consumer_ (this, " << this->port_counter_ << "l)";

  this->port_counter_++;
  return 0;
}

} // namespace iCCM
} // namespace TCPIP
