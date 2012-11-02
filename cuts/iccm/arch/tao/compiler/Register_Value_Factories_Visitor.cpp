// $Id$

#include "Register_Value_Factories_Visitor.h"

#if !defined (__CUTS_INLINE__)
#include "Register_Value_Factories_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#include "be_extern.h"
#include "be_global.h"

#include "ast_component.h"
#include "ast_consumes.h"
#include "ast_eventtype.h"

#include "ace/Unbounded_Set.h"
#include "boost/bind.hpp"

namespace iCCM
{
namespace TAO
{

class Value_Targets : public iCCM::Scope_Visitor
{
public:
  /// Typedef of output variables
  typedef ACE_Unbounded_Set <AST_Decl *> Target_Manager;

  Value_Targets (Target_Manager & target_mgr)
   : target_mgr_ (target_mgr)
  {

  }

  virtual int visit_component (AST_Component * node)
  {
    return this->visit_scope (node);
  }

  virtual int visit_consumes (AST_Consumes * node)
  {
    return 0 != node->consumes_type () ?
      node->consumes_type ()->ast_accept (this) : -1;
  }

  virtual int visit_eventtype (AST_EventType * node)
  {
    // Skip node if it has been identified already
    if (0 == this->target_mgr_.find (node))
      return 0;

    this->target_mgr_.insert (node);

    return 0;
  }

private:
  Target_Manager & target_mgr_;
};

//
// visit_consumes
//
int Register_Value_Factories_Visitor::visit_component (AST_Component * node)
{
  Value_Targets::Target_Manager targets;
  Value_Targets vt (targets);
  node->ast_accept (&vt);

  // Don't generate anything if there are no events consumed
  if (!targets.size ())
    return 0;

  this->hfile_
    << "virtual void register_value_factories (::CORBA::ORB_ptr orb);";

  this->sfile_
    << "void " << this->servant_.c_str () << "::register_value_factories (::CORBA::ORB_ptr orb)"
    << "{";

  // Generate impl
  std::for_each (targets.begin (),
                 targets.end (),
                 boost::bind (&AST_Decl::ast_accept,
                              _1,
                              this));

  this->sfile_
    << "}";

  return 0;
}

int Register_Value_Factories_Visitor::visit_eventtype (AST_EventType * node)
{
  const char * name = node->full_name ();

  this->sfile_
    << "ICCM_TAO_REGISTER_VALUE_FACTORY (orb, ::" << name << "_init, ::" << name << ");";

  return 0;
}

} // namespace iCCM
} // namespace TAO
