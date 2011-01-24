// $Id$

#include "BE_IDL_Node.h"

//
// CUTS_BE_Dependency_Node
//
CUTS_BE_IDL_Node::CUTS_BE_IDL_Node (const std::string & name)
: name_ (name),
  basename_ (name.substr (name.find_last_of ('/') + 1)),
  has_events_ (false),
  has_components_ (false),
  has_interfaces_ (false),
  has_dds_events_ (false)
{

}
