// $Id$

#include "Push_Event_Visitor.h"

#if !defined (__CUTS_INLINE__)
#include "Push_Event_Visitor.inl"
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
int Push_Event_Visitor::visit_consumes (AST_Consumes * node)
{
  const char * local_name = node->local_name ()->get_string ();
  const char * field_type = node->field_type ()->full_name ();

  this->hfile_
    << "static void push_" << local_name << " (" << this->servant_ << " * svnt, ACE_InputCDR & stream);"
    << std::endl;

  this->sfile_
    << "void " << this->servant_ << "::"
    << "push_" << local_name << " (" << this->servant_ << " * svnt, ACE_InputCDR & stream)"
    << "{"
    << "// Extract the event from the stream." << std::endl
    << "::OBV_" << field_type << " ev;" << std::endl
    << "if (!(stream >> ev))"
    << "{"
    << "ACE_ERROR ((LM_ERROR," << std::endl
    << "ACE_TEXT (\"%T (%t) - %M - failed to extract %s from stream\\n\")," << std::endl
    << "ACE_TEXT (\"::OBV_" << field_type << "\")));"
    << "}"
    << "// Push the message to the implementation." << std::endl
    << "if (svnt->impl_)" << std::endl
    << "  svnt->impl_->push_" << local_name << " (&ev);"
    << "}";

  return 0;
}

} // namespace iCCM
} // namespace TCPIP
