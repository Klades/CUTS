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
  return this->visit_scope (node);
}

//
// visit_module
//
int Event_Traits::visit_module (AST_Module * node)
{
  return this->visit_scope (node);
}

//
// visit_eventtype
//
int Event_Traits::visit_eventtype (AST_EventType * node)
{
  const char * full_name = node->full_name ();

  ACE_CString tcpip_event;
  TCPIP::Context * ctx = dynamic_cast <TCPIP::Context *> (be_global);

  be_global->get_wrapper_eventtype (node, tcpip_event);

  this->hfile_
    << "/**" << std::endl
    << " * @struct iCCM::TCPIP_Event_Traits < ::" << full_name << " >" << std::endl
    << " *" << std::endl
    << " * Trait information for " << full_name << "Event event type." << std::endl
    << " */" << std::endl
    << "namespace iCCM {"
    << "template < >" << std::endl
    << "struct TCPIP_Event_Traits < ::" << full_name << " >"
    << "{"
    << "typedef ::OBV_" << full_name << " tcpip_event_type;"
    << "};"
    << "}";

  return 0;
}

}
