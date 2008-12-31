// -*- C++ -*-

//=============================================================================
/**
 * @file          Barrier_Client.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BARRIER_CLIENT_H_
#define _CUTS_BARRIER_CLIENT_H_

#include "BarrierCallback_i.h"

/**
 * @class CUTS_Barrier_Client
 */
class CUTS_Barrier_Client
{
public:
  /// Default constructor.
  CUTS_Barrier_Client (void);

  /// Destructor.
  ~CUTS_Barrier_Client (void);

  int run_main (int argc, char * argv []);

  void shutdown (void);

  void destroy (void);

private:
  int parse_args (int argc, char * argv []);

  void print_help (void);

  CORBA::ORB_var orb_;

  PortableServer::POA_var root_;

  CUTS_Barrier_Callback_i callback_;

  ACE_CString name_;
};

#if defined (__CUTS_INLINE__)
#include "Barrier_Client.inl"
#endif

#endif  // !defined _CUTS_BARRIER_CLIENT_H_
