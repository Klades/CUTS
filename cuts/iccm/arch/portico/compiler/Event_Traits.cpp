// $Id:

#include "Event_Traits.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_root.h"
#include "ast_module.h"
#include "ast_eventtype.h"
#include "ast_field.h"

#include "utl_identifier.h"
#include <iostream>

namespace iCCM
{

//
// Event_Traits
//
Event_Traits::Event_Traits (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile),
  scope_ (),
  attribute_count_ (0)
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
  const char * full_name = node->full_name ();
  const char * local_name = node->local_name ()->get_string ();

  // Define the class with constructor and destructor
  this->hfile_
    << "/**" << std::endl
    << " * @struct Portico_ObjectClass_Trait_T < ::" << full_name << " >" << std::endl
    << " * " << std::endl
    << "Trait class specalized for the ::" << full_name << " event type." << std::endl
    << " */" << std::endl
    << "namespace iCCM {" << std::endl
    << "template < >" << std::endl
    << "struct Portico_ObjectClass_Trait_T < ::" << full_name << " >" << std::endl
    << "{" << std::endl
    << "  typedef ::" << this->scope_ << local_name << "_ObjectClass objectclass_event_type;" << std::endl
    << "  typedef ::" << this->scope_ << local_name << "_ObjectClass_Factory objectclass_factory_type;" << std::endl;

  // Get the attribute count
  this->visit_scope (node);

  this->hfile_
    << "  static const size_t attr_count = " << this->attribute_count_ << ";" << std::endl
    << "};" << std::endl
    << "}" << std::endl;

  this->attribute_count_ = 0;

  return 0;
}

//
// visit_field
//
int Event_Traits::visit_field (AST_Field * node)
{
  ++this->attribute_count_;
  return 0;
}

}
