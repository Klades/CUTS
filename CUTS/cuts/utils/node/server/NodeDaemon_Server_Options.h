// -*- C++ -*-

//=============================================================================
/**
 * @file      NodeDaemon_Server_Options.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODEDAEMON_SERVER_OPTIONS_H_
#define _CUTS_NODEDAEMON_SERVER_OPTIONS_H_

#include "ace/SString.h"

/**
 * @class CUTS_NodeDaemon_Server_Options
 *
 * Options for the node daemon server.
 */
class CUTS_NodeDaemon_Server_Options
{
public:
  /// Name used to register server with naming service.
  ACE_CString ns_name_;
};

#endif  // !defined _CUTS_NODEDAEMON_SERVER_OPTIONS_H_
