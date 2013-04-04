// $Id$

#include "Event_Traits.h"

#include "be_extern.h"
#include "Context.h"

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
  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  this->hfile_
    << std::endl
    << "namespace iCCM {";

  int retval = this->visit_scope (node);

  this->hfile_
    << "}";

  return retval;
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
  const char * local_name = node->local_name ()->get_string ();
  const char * full_name = node->full_name ();

  // We should probably store the name of the TAO event when we are actually
  // creating the event. This way, we can just lookup the event name and not
  // try to reconstruct it here!
//  std::string tao_full_name (node->full_name ());
//  size_t pos = tao_full_name.find_last_of (":");

//  tao_full_name.insert (pos + 1, "TAO_");

  this->hfile_
    << "/**" << std::endl
    << " * @struct iCCM::TAO_Event_Traits < ::" << full_name << " >" << std::endl
    << " *" << std::endl
    << " * Trait information for " << full_name << " event type." << std::endl
    << " */" << std::endl
    << "template < >" << std::endl
    << "struct TAO_Event_Traits < ::" << full_name << " >"
    << "{"
    << "typedef ::" << this->scope_ << "TAO_" << local_name << " tao_event_type;"
    << "};";

  return 0;
}

}
