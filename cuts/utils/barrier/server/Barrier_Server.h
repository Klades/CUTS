// -*- C++ -*-

//=============================================================================
/**
 * @file          Barrier_Server.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BARRIER_SERVER_H_
#define _CUTS_BARRIER_SERVER_H_

#include "Barrier_i.h"

/**
 * @class CUTS_Barrier_Server
 */
class CUTS_Barrier_Server
{
public:
  /// Default constructor.
  CUTS_Barrier_Server (void);

  /// Destructor.
  virtual ~CUTS_Barrier_Server (void);

  int run_main (int argc, char * argv []);

  /// Shutdown the server.
  void shutdown (void);

  /// Destroy the server resources.
  void destroy (void);

private:
  int parse_args (int argc, char * argv []);

  int register_with_iortable (const char * name, CORBA::Object_ptr obj);

  void print_help (void);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// Reference to the RootPOA.
  PortableServer::POA_var root_;

  /// Number of nodes to wait.
  size_t count_;

  /// The barrier servant for the server.
  CUTS_Barrier_i barrier_;
};

#if defined (__CUTS_INLINE__)
#include "Barrier_Server.inl"
#endif

#endif  // !defined _CUTS_BARRIER_SERVER_H_
