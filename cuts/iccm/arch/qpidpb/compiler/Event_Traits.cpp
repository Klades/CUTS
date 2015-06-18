// $Id$

#include "Event_Traits.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_module.h"
#include "ast_root.h"
#include "ast_eventtype.h"
#include "utl_identifier.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

namespace iCCM
{

//
// Event_Traits
//
Event_Traits::Event_Traits (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Event_Traits
//
Event_Traits::~Event_Traits (void)
{

}

//
// visit_root
//
int Event_Traits::visit_root (AST_Root * node)
{
  return this->visit_scope (node);
}

//
// visit_module
//
int Event_Traits::visit_module (AST_Module * node)
{
  ACE_CString local_name (node->local_name ()->get_string ());
  ACE_CString backup (this->scope_);
  this->scope_ += local_name + "::";

  if (0 != this->visit_scope (node))
    return -1;

  this->scope_ = backup;
  return 0;
}

//
// visit_eventtype
//
int Event_Traits::visit_eventtype (AST_EventType * node)
{
  if (!be_global->is_wrapper_eventtype (node))
    return 0;

  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  const char * full_name = node->full_name ();

  ACE_CString protobuf_event;
  be_global->get_wrapper_eventtype (node, protobuf_event);

  this->hfile_
    << "/**" << std::endl
    << " * @class iCCM::QpidPB_Traits_T < ::" << full_name << " >" << std::endl
    << " *" << std::endl
    << " * Trait information for " << full_name << "Event event type." << std::endl
    << " */" << std::endl
    << "namespace iCCM {"
    << "template < >" << std::endl
    << "class QpidPB_Traits_T < ::" << full_name << " >"
    << "{"
    << "public:" << std::endl
    << "// event mapping types" << std::endl
    << "typedef ::qpidpb::" << this->scope_ << protobuf_event << " protobuf_event_type;"
    << "typedef ::" << full_name << "Upcall upcall_event_type;"
    << "typedef ::" << full_name << "Downcall downcall_event_type;"
    << "typedef ::" << full_name << " corba_event_type;"
    << "};"
    << "}";

  return 0;
}

}
