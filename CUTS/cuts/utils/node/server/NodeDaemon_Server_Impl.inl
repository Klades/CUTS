// -*- C++ -*-
// $Id$

//
// CUTS_NodeDaemon_Server_Impl
//
CUTS_INLINE
CUTS_NodeDaemon_Server_Impl::
CUTS_NodeDaemon_Server_Impl (CUTS_Virtual_Env_Manager & virtual_envs)
: daemon_ (virtual_envs),
  deamon_mgr_ (&daemon_, false)
{

}

//
// ~CUTS_NodeDaemon_Server_Impl
//
CUTS_INLINE
CUTS_NodeDaemon_Server_Impl::~CUTS_NodeDaemon_Server_Impl (void)
{

}
