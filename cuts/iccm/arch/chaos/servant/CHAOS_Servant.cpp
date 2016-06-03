// $Id$

#include "CHAOS_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Servant.inl"
#endif

namespace iCCM
{

CHAOS_Servant::~CHAOS_Servant (void)
{
  for (servant_poa_map_type::iterator it = this->servant_POAs_.begin();
       it != this->servant_POAs_.end();
       ++it)
  {
    it->int_id_->destroy (false, false);
  }
  this->servant_POAs_.unbind_all ();
}

PortableServer::POA_ptr CHAOS_Servant::
create_servant_POA (const std::string & name, ::PortableServer::POA_ptr parent)
{
  PortableServer::POA_var child;

  if (0 == this->servant_POAs_.find (name, child))
    return child._retn ();
  
  CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = parent->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::USER_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = parent->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Use the policies above to create the child POA that will be
  // used when activating servants.
  child = parent->create_POA (name.c_str (),
                              ::PortableServer::POAManager::_nil (),
                              policies);

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = child->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();

  return child._retn ();
}


}
