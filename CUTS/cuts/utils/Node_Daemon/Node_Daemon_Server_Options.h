// -*- C++ -*-

//=============================================================================
/**
 * @file        Node_Daemon_Server_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODE_DAEMON_SERVER_OPTIONS_H_
#define _CUTS_NODE_DAEMON_SERVER_OPTIONS_H_

#include "ace/SString.h"
#include "ace/Vector_T.h"

/**
 * @class CUTS_Node_Daemon_Server_Options
 *
 * Collection of server options that can be set via command-line
 * arguments.
 */
class CUTS_Node_Daemon_Server_Options
{
public:
  /// The IOR file name for the daemon.
  ACE_CString ior_file_;

  /// The initial directory for starting the node daemon.
  ACE_CString init_dir_;

  /// Initial configuration for the node daemon.
  ACE_CString config_;

  /// Properties defined at the command line.
  ACE_Vector <ACE_CString> defines_;
};

#endif  // !defined _CUTS_NODE_DAEMON_SERVER_OPTIONS_H_
