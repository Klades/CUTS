// $Id$

#include "NodeDaemon_Server.h"

#if !defined (__CUTS_INLINE__)
#include "NodeDaemon_Server.inl"
#endif

#include "NodeDaemon_Server_Impl.h"
#include "ace/Service_Config.h"

//
// CUTS_NodeDaemon_Server
//
CUTS_NodeDaemon_Server::
CUTS_NodeDaemon_Server (CUTS_Virtual_Env_Manager & virtual_envs)
{
  CUTS_NodeDaemon_Server_Impl * impl = 0;

  ACE_NEW_THROW_EX (impl,
                    CUTS_NodeDaemon_Server_Impl (virtual_envs),
                    ACE_bad_alloc ());

  this->impl_.reset (impl);
}

//
// ~CUTS_NodeDaemon_Server
//
CUTS_NodeDaemon_Server::~CUTS_NodeDaemon_Server (void)
{

}

//
// init
//
int CUTS_NodeDaemon_Server::init (int argc, char * argv [])
{
  return this->impl_->init (argc, argv);
}

//
// fini
//
int CUTS_NodeDaemon_Server::fini (void)
{
  return this->impl_->fini ();
}
