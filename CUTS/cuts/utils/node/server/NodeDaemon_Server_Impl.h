// -*- C++ -*-

//=============================================================================
/**
 * @file      NodeDaemon_Server_Impl.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODEDAEMON_SERVER_IMPL_H_
#define _CUTS_NODEDAEMON_SERVER_IMPL_H_

#include "cuts/ORB_Server_Task.h"
#include "cuts/Servant_Manager_T.h"
#include "cuts/Servant_Traits_T.h"
#include "cuts/IOR_File_Trait.h"
#include "cuts/IOR_Table_Trait.h"

#include "NodeDaemon_Server_Options.h"
#include "NodeDaemon_i.h"

// Forward decl.
class CUTS_Virtual_Env_Manager;

/**
 * @class CUTS_NodeDaemon_Server_Impl
 *
 * Implementation of the node daemon's server.
 */
class CUTS_NodeDaemon_Server_Impl
{
public:
  /// Initializing constructor.
  CUTS_NodeDaemon_Server_Impl (CUTS_Virtual_Env_Manager & virtual_envs);

  /// Destructor.
  virtual ~CUTS_NodeDaemon_Server_Impl (void);

  /**
   * Initialize the server.
   *
   * @param[in]     argc          Number of command-line arguments
   * @param[in]     argv          The actual command-line arguments
   */
  virtual int init (int argc, char * argv []);

  /// Finalize the server.
  virtual int fini (void);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// The ORB for the server.
  ::CORBA::ORB_var orb_;

  /// The RootPOA for the ORB.
  ::PortableServer::POA_var root_poa_;

  /// The active object that runs the ORB event loop.
  CUTS_ORB_Server_Task task_;

  /// The node daemon's servant.
  CUTS_NodeDaemon_i daemon_;

  /// Type definition of the node daemon servant's traits.
  typedef
    CUTS_Servant_Trait_T <CUTS_IOR_File_Trait,
    CUTS_Servant_Trait_T <CUTS_IOR_Table_Trait> > traits_type;

  /// Servant manager for the \a CUTS_NodeDaemon_i.
  CUTS_Servant_Manager_Ex_T <CUTS_NodeDaemon_i, traits_type> deamon_mgr_;

  /// The name of the IOR file.
  CUTS_NodeDaemon_Server_Options opts_;
};

#if defined (__CUTS_INLINE__)
#include "NodeDaemon_Server_Impl.inl"
#endif

#endif  // !defined _CUTS_NODEDAEMON_SERVER_H_
