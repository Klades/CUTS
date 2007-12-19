// -*- C++ -*-

//=============================================================================
/**
 * @file        MPI_Env.h
 *
 * Defines the CUTS environment for MPI.
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_MPI_ENV_H_
#define _CUTS_MPI_ENV_H_

#include "cuts/CUTSS.h"
#include "ace/SString.h"

// Forward decl.
class Benchmark_Agent_i;

namespace CUTS
{
  // Forward decl.
  class Benchmark_Data_Collector;
}

//=============================================================================
/**
 * @class CUTS_MPI_Env
 *
 * CUTS benchmarking environment for MPI. This class contains global
 * information that should be used by all MPI functions. To prevent
 * the hosting application from having multiple environments, we use
 * the singleton pattern to limit the environment to one.
 */
//=============================================================================

class CUTS_MPI_Env
{
public:
  /**
   * Get the singleton instance of the environment. This will create
   * the singleton the first time it is called.
   */
  static CUTS_MPI_Env * instance (void);

  /// Close the singleton instance. This method must be called to
  /// ensure proper cleanup and unregistration.
  static void close_singleton (void);

  /**
   * Initialize the environment.
   *
   * @param[inout]        argc          The argument count.
   * @param[inout]        argv          The argument list.
   */
  int init (int & argc, char * argv []);

  /// Finalize the environment.
  int fini (void);

  /**
   * Get the benckmarking agent for the environment. This is
   * used by MPI functions to log performance metrics. Periodically,
   * performance metrics will be collected from the agent by the
   * Benchmark_Data_Collector.
   *
   * @return      Pointer to the agent.
   */
  Benchmark_Agent_i * agent (void);

  /**
   * Get the instance name of the environment. The instance name is
   * derived from the application's name and its rank in the world.
   *
   * @return      Instance name of the environment.
   */
  const ACE_CString & instance_name (void) const;

private:
  /// Service thread for the environment.
  static ACE_THR_FUNC_RETURN svc_thr (void *);

  /// Make the instance name from the first argument.
  void make_instance_name (const ACE_CString & arg0);

  /// Singleton instance of the environment.
  static CUTS_MPI_Env * instance_;

  /// Default constructor.
  CUTS_MPI_Env (void);

  /// Destructor.
  ~CUTS_MPI_Env (void);

  /// Helper method to get the BDC from the naming service.
  CUTS::Benchmark_Data_Collector * get_BDC (void);

  void register_with_BDC (void);

  /// CORBA ORB for the environment.
  CORBA::ORB_var orb_;

  /// The portable server for the environment.
  PortableServer::POA_var poa_;

  /// The collection agent for the MPI application.
  Benchmark_Agent_i * agent_;

  /// The servant object for the \a agent_.
  PortableServer::ServantBase_var agent_servant_;

  /// Group id of the service thread.
  int grp_id_;

  /// Registration for the application.
  CUTS::Component_Registration reg_;

  /// Instance name of this environment.
  ACE_CString instance_name_;

  /// The rank of the environment in the world.
  int rank_;
};

#if defined (__CUTS_INLINE__)
#include "MPI_Env.inl"
#endif

#endif  // !defined _CUTS_MPI_ENV_H_
