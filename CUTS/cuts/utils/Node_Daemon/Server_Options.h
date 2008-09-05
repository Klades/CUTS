/* -*- C++ -*- */

//=============================================================================
/**
 * @file        Server_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _SERVER_OPTIONS_H_
#define _SERVER_OPTIONS_H_

#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/SString.h"

/**
 * @class CUTS_Node_Daemon_Server_Options
 *
 * Collection of server options that can be set via command-line
 * arguments.
 */

class CUTS_Node_Daemon_Server_Options
{
public:
  /// Default constructor.
  CUTS_Node_Daemon_Server_Options (void);

  /// Destructor.
  ~CUTS_Node_Daemon_Server_Options (void);

  /// The IOR file name for the daemon.
  ACE_CString ior_file_;

  /// The initial directory for starting the node daemon.
  ACE_CString init_dir_;

  /// Initial configuration for the node daemon.
  ACE_CString config_;
};

#endif  /* !defined _SERVER_OPTIONS_H_ */
