# -*- Python -*-

###############################################################################
#
# @file             generate-arch-skeleton.py
#
# $Id$
#
# @author           James H. Hill
#
###############################################################################

import sys
import getopt
import os

#
# main
#
def main () :
  try:
    opts = parseArgs (sys.argv[1:])

  except getopt.GetoptError, err:
    # print help information and exit
    print str (err)
    sys.exit (2)

  # construct the dictionay for the templates.
  dict = { "archName" : opts["name"],
           "archNameUpper" : opts["name"].upper (),
           "archNameLower" : opts["name"].lower () }

  # make all the required output directories
  output = opts["output"]
  output += "/" + opts["name"]

  if (os.path.exists (output) == False) :
    os.mkdir (output)

  if (os.path.exists (output + "/ccm") == False) :
    os.mkdir (output + "/ccm")

  if (os.path.exists (output + "/server") == False) :
    os.mkdir (output + "/server")

  # write the skeleton files
  writeCCMFiles (output, dict)
  writeServerFiles (output, dict)

def parseArgs (args) :
  shortOpt = "n:o:"
  longOpt = ["name="]

  values = {}
  opts, args = getopt.gnu_getopt ( sys.argv[1:], shortOpt, longOpt )

  # parse the command-line arguments
  for o, a in opts:
    if o in ("-n", "--name"):
      values["name"] = a
    elif o in ("-o") :
      values["output"] = a
    else:
      assert False, "unhandled option (%s)" % o

  return values

###############################################################################
## CCM files

#
#
#
def writeCCMFiles (output, dict) :
  writeServantBase (output, dict)
  writeServantBaseT (output, dict)
  writeCCMMPC (output, dict)

#
# writeServantBase
#
#   Function that writes the servant base class for the architecture.
#
def writeServantBase (output, dict) :
  writeServantBaseHeader (output, dict)
  writeServantBaseSource (output, dict)
  writeServantBaseInline (output, dict)

#
# writeServantBaseHeader
#
#   Function that writes the servant base header class
#
def writeServantBaseHeader (output, dict) :
  servantBaseHeader = """// -*- C++ -*-

#ifndef _CUTS_%(archNameUpper)s_CCM_SERVANT_H_
#define _CUTS_%(archNameUpper)s_CCM_SERVANT_H_

#include "cuts/arch/ccm/CCM_Servant.h"
#include "%(archName)s_CCM_export.h"

/**
 * @class CUTS_%(archName)s_CCM_Servant
 *
 * Base class for all %(archName)s servant objects. This class enables
 * the container to send commands to the servant, such as
 * domain-specific configuration information.
 */
class CUTS_%(archNameUpper)s_CCM_Export CUTS_%(archName)s_CCM_Servant :
  public CUTS_CCM_Servant
{
public:
  /// Destructor.
  virtual ~CUTS_%(archName)s_CCM_Servant (void);

protected:
  /// Default constructor.
  CUTS_%(archName)s_CCM_Servant (const char * name);
};

#if defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_%(archNameUpper)s_CCM_SERVANT_H_
  """ % dict

  # write the servant's header to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM_Servant.h"
  outfile = open (filename, "w")
  outfile.write (servantBaseHeader)
  outfile.close ();

#
# writeServantBaseSource
#
#   Function that writes the servant base source file.
#
def writeServantBaseSource (output, dict) :
  servantBaseSource = """// $Id$

#include "%(archName)s_CCM_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Servant.inl"
#endif
  """ % dict

  # write the servant's header to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM_Servant.cpp"
  outfile = open (filename, "w")
  outfile.write (servantBaseSource)
  outfile.close ();

#
# writeServantBaseInline
#
#   Function that writes the servant base source file.
#
def writeServantBaseInline (output, dict) :
  servantBaseSource = """// -*- C++ -*-
// $Id$

//
// CUTS_%(archName)s_CCM_Servant
//
CUTS_INLINE
CUTS_%(archName)s_CCM_Servant::
CUTS_%(archName)s_CCM_Servant (const char * name)
  : CUTS_CCM_Servant (name)
{

}

//
// ~CUTS_%(archName)s_CCM_Servant
//
CUTS_INLINE
CUTS_%(archName)s_CCM_Servant::~CUTS_%(archName)s_CCM_Servant (void)
{

}
  """ % dict

  # write the servant's header to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM_Servant.inl"
  outfile = open (filename, "w")
  outfile.write (servantBaseSource)
  outfile.close ();

#
# writeServantBaseT
#
#   Function that writes the servant base class for the architecture.
#
def writeServantBaseT (output, dict) :
  writeServantBaseHeaderT (output, dict)
  writeServantBaseSourceT (output, dict)
  writeServantBaseInlineT (output, dict)

#
# writeServantBaseHeaderT
#
#   Function that writes the servant base source file.
#
def writeServantBaseHeaderT (output, dict) :
  servantBaseHeaderT = """// -*- C++ -*-

#ifndef _CUTS_%(archNameUpper)s_CCM_SERVANT_T_H_
#define _CUTS_%(archNameUpper)s_CCM_SERVANT_T_H_

#include "cuts/arch/ccm/CCM_Servant_T.h"
#include "%(archName)s_CCM_Servant.h"

/**
 * @class CUTS_%(archName)s_CCM_Servant_T
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class CUTS_%(archName)s_CCM_Servant_T :
  public CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, CUTS_%(archName)s_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Servant_T <T,
			      CONTEXT,
			      EXECUTOR,
			      POA_EXEC,
			      CUTS_%(archName)s_CCM_Servant> base_type;

  CUTS_%(archName)s_CCM_Servant_T (
    const char * name,
		typename EXECUTOR::_ptr_type executor);

  /// Destructor.
  virtual ~CUTS_%(archName)s_CCM_Servant_T (void);

protected:
  typedef typename base_type::consumer_map_type consumer_map_type;

  typedef typename base_type::emits_map_type emits_map_type;

  typedef typename base_type::publishes_map_type publishes_map_type;
};

#if defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Servant_T.inl"
#endif

#include "%(archName)s_CCM_Servant_T.cpp"

#endif  // !defined _CUTS_%(archNameUpper)s_CCM_SERVANT_T_H_
""" % dict

  # write the servant's header to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM_Servant_T.h"
  outfile = open (filename, "w")
  outfile.write (servantBaseHeaderT)
  outfile.close ();

#
# writeServantBaseInlineT
#
#   Function that writes the servant base source file.
#
def writeServantBaseInlineT (output, dict) :
  servantBaseInlineT = """// -*- C++ -*-
// $Id$

//
// CUTS_%(archName)s_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_%(archName)s_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
CUTS_%(archName)s_CCM_Servant_T (
  const char * name,
	typename EXECUTOR::_ptr_type executor)
 : base_type (name, executor)
{

}

//
// ~CUTS_%(archName)s_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_%(archName)s_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
~CUTS_%(archName)s_CCM_Servant_T (void)
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM_Servant_T.inl"
  outfile = open (filename, "w")
  outfile.write (servantBaseInlineT)
  outfile.close ();

#
# writeServantBaseSourceT
#
#   Function that writes the servant base source file.
#
def writeServantBaseSourceT (output, dict) :
  servantBaseSourceT = """// $Id$

#if !defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Servant_T.inl"
#endif
""" % dict

  # write the servant's header to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM_Servant_T.cpp"
  outfile = open (filename, "w")
  outfile.write (servantBaseSourceT)
  outfile.close ();

#
# writeCCMMPC
#
#   MPC file for building the CCM library
#
def writeCCMMPC (output, dict) :
  sourceFile = """// $Id$

project (CUTS_%(archName)s_CCM) : cuts_ccm, cuts_lib, cutslib {
  sharedname    = CUTS_%(archName)s_CCM
  dynamicflags += CUTS_%(archNameUpper)s_CCM_BUILD_DLL

  prebuild += $(ACE_ROOT)/bin/generate_export_file.pl CUTS_%(archNameUpper)s_CCM > %(archName)s_CCM_export.h

  Source_Files {
    %(archName)s_CCM_Servant.cpp
  }

  Template_Files {
    %(archName)s_CCM_Servant_T.cpp
  }
}
""" % dict

  # write source to file
  filename = output + "/ccm/" + dict["archName"] + "_CCM.mpc"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

###############################################################################
## server files

#
# writeServerFiles
#
#   Function for writing all the server files
#
def writeServerFiles (output, dict) :
  writeContainerStrategy (output, dict)
  writeContainer (output, dict)
  writeComponentServer (output, dict)
  writeComponentServerApp (output, dict)
  writeServerDriver (output, dict)
  writeServerMPC (output, dict)

#
# writeContainerStrategy
#
#   Function for writing all the container strategy files
#
def writeContainerStrategy (output, dict) :
  writeContainerStrategyHeader (output, dict)
  writeContainerStrategySource (output, dict)
  writeContainerStrategyInline (output, dict)

#
# writeContainerStrategyHeader
#
#   Function for writing the header file for the container strategy
#
def writeContainerStrategyHeader (output, dict) :
  sourceFile = """// -*- C++ -*-

#ifndef _CUTS_%(archNameUpper)s_CCM_CONTAINER_STRATEGY_H_
#define _CUTS_%(archNameUpper)s_CCM_CONTAINER_STRATEGY_H_

#include "cuts/arch/ccm/CCM_Container_Strategy_T.h"

// Forward decl.
class CUTS_%(archName)s_CCM_Container;

/// Type defintion of CUTS_%(archName)s_CCM_Container_Strategy base type.
typedef
  CUTS_CCM_Container_Strategy_T <
    CUTS_%(archName)s_CCM_Container>
    CUTS_%(archName)s_CCM_Container_Strategy_Base;

/**
 * @class CUTS_%(archName)s_CCM_Container_Strategy
 *
 * Implementation of the CCM container startegy for %(archName)s.
 */
class CUTS_%(archName)s_CCM_Container_Strategy :
  public CUTS_%(archName)s_CCM_Container_Strategy_Base
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]     container       Container hosting the strategy
   */
  CUTS_%(archName)s_CCM_Container_Strategy (CUTS_%(archName)s_CCM_Container & container);

  /// Destructor.
  virtual ~CUTS_%(archName)s_CCM_Container_Strategy (void);

  /**
   * Callback for configuring the servant. Implementing this method
   * is optional. It primarily is used to configure the servant using
   * domain-specific information specific to the target architecture.
   *
   * @param[in]     servant         Servant to configure
   * @param[in]     config          Configuration for the servant.
   */
  virtual void
    configure_servant (::PortableServer::Servant servant,
                       const ::Components::ConfigValues & config);
};

#if defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_%(archNameUpper)s_CCM_CONTAINER_STRATEGY_H_
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_Container_Strategy.h"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeContainerStrategyInline
#
#   Function for writing the inline file for the container strategy
#
def writeContainerStrategyInline (output, dict) :
  sourceFile = """// -*- C++ -*-
// $Id$

//
// CUTS_%(archName)s_CCM_Container_Strategy
//
CUTS_INLINE
CUTS_%(archName)s_CCM_Container_Strategy::
CUTS_%(archName)s_CCM_Container_Strategy (CUTS_%(archName)s_CCM_Container & container)
: CUTS_%(archName)s_CCM_Container_Strategy_Base (container)
{

}

//
// ~CUTS_%(archName)s_CCM_Container_Strategy
//
CUTS_INLINE
CUTS_%(archName)s_CCM_Container_Strategy::~CUTS_%(archName)s_CCM_Container_Strategy (void)
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_Container_Strategy.inl"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeContainerStrategySource
#
#   Function for writing the source file for the container strategy
#
def writeContainerStrategySource (output, dict) :
  sourceFile = """// -*- C++ -*-
// $Id$

#include "%(archName)s_CCM_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Container_Strategy.inl"
#endif

#include "%(archName)s_CCM_Container.h"
#include "%(archName)s_CCM_ComponentServer.h"
#include "../ccm/%(archName)s_CCM_Servant.h"

//
// configure_servant
//
void
CUTS_%(archName)s_CCM_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
		               const ::Components::ConfigValues & )
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_Container_Strategy.cpp"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeContainer
#
#   Function for writing all the container files
#
def writeContainer (output, dict) :
  writeContainerHeader (output, dict)
  writeContainerSource (output, dict)
  writeContainerInline (output, dict)

#
# writeContainerSource
#
#   Function for writing the container source file
#
def writeContainerSource (output, dict) :
  sourceFile = """// $Id$

#include "%(archName)s_CCM_Container.h"

#if !defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Container.inl"
#endif
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_Container.cpp"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeContainerInline
#
#   Function for writing the container inline file
#
def writeContainerInline (output, dict) :
  sourceFile = """// -*- C++ -*-
// $Id$

//
// CUTS_%(archName)s_CCM_Container
//
CUTS_INLINE
CUTS_%(archName)s_CCM_Container::
CUTS_%(archName)s_CCM_Container (
  CUTS_%(archName)s_CCM_ComponentServer * server,
	const Components::ConfigValues & config,
	::PortableServer::POA_ptr poa,
	::Components::Deployment::ComponentInstallation_ptr installer)
  : CUTS_%(archName)s_CCM_Container_Base (server, config, poa, installer)
{

}

//
// ~CUTS_%(archName)s_CCM_Container
//
CUTS_INLINE
CUTS_%(archName)s_CCM_Container::~CUTS_%(archName)s_CCM_Container (void)
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_Container.inl"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeContainerHeader
#
#   Function for writing the container header file
#
def writeContainerHeader (output, dict) :
  sourceFile = """// -*- C++ -*-

#ifndef _CUTS_%(archNameUpper)s_CCM_CONTAINER_H_
#define _CUTS_%(archNameUpper)s_CCM_CONTAINER_H_

#include "cuts/arch/ccm/CCM_Container_T.h"
#include "../ccm/%(archName)s_CCM_Servant.h"
#include "%(archName)s_CCM_Container_Strategy.h"

// Forward decl.
class CUTS_%(archName)s_CCM_ComponentServer;

/// Type definition of the base type.
typedef
  CUTS_CCM_Container_T <
    CUTS_%(archName)s_CCM_Container,
    CUTS_%(archName)s_CCM_ComponentServer,
    CUTS_%(archName)s_CCM_Container_Strategy,
    CUTS_%(archName)s_CCM_Servant > CUTS_%(archName)s_CCM_Container_Base;

/**
 * @class CUTS_%(archName)s_CCM_Container
 */
class CUTS_%(archName)s_CCM_Container :
  public CUTS_%(archName)s_CCM_Container_Base
{
public:
  /// Initializing constructor.
  CUTS_%(archName)s_CCM_Container (
    CUTS_%(archName)s_CCM_ComponentServer * server,
		const Components::ConfigValues & config,
		::PortableServer::POA_ptr poa,
		::Components::Deployment::ComponentInstallation_ptr installer);

  /// Destructor.
  virtual ~CUTS_%(archName)s_CCM_Container (void);
};

#if defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_Container.inl"
#endif

#endif  // !defined _CUTS_%(archNameUpper)s_CCM_CONTAINER_H_

""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_Container.h"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeComponentServer
#
#   Function for writing all the component server files
#
def writeComponentServer (output, dict) :
  writeComponentServerHeader (output, dict)
  writeComponentServerSource (output, dict)
  writeComponentServerInline (output, dict)

#
# writeComponentServerSource
#
#   Function for writing the component server source file
#
def writeComponentServerSource (output, dict) :
  sourceFile = """// $Id$

#include "%(archName)s_CCM_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_ComponentServer.inl"
#endif

#include "%(archName)s_CCM_ComponentServer_App.h"

//
// CUTS_%(archName)s_CCM_ComponentServer
//
CUTS_%(archName)s_CCM_ComponentServer::
CUTS_%(archName)s_CCM_ComponentServer (CUTS_%(archName)s_CCM_ComponentServer_App * app)
: CUTS_%(archName)s_CCM_ComponentServer_Base (app)
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_ComponentServer.cpp"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeComponentServerInline
#
#   Function for writing the compenent server inline file
#
def writeComponentServerInline (output, dict) :
  sourceFile = """// -*- C++ -*-
// $Id$

//
// ~CUTS_%(archName)s_CCM_EventConsumer
//
CUTS_INLINE
CUTS_%(archName)s_CCM_ComponentServer::~CUTS_%(archName)s_CCM_ComponentServer (void)
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_ComponentServer.inl"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeComponentServerHeader
#
#   Function for writing the compenent server header file
#
def writeComponentServerHeader (output, dict) :
  sourceFile = """// -*- C++ -*-

#ifndef _CUTS_%(archNameUpper)s_CCM_COMPONENTSERVER_H_
#define _CUTS_%(archNameUpper)s_CCM_COMPONENTSERVER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "cuts/arch/ccm/CCM_ComponentServer_T.h"
#include "%(archName)s_CCM_ComponentServer.h"
#include "%(archName)s_CCM_Container.h"

// Forward decl.
class CUTS_%(archName)s_CCM_ComponentServer_App;

/// Type definition of the base type.
typedef
  CUTS_CCM_ComponentServer_T <
    CUTS_%(archName)s_CCM_ComponentServer,
    CUTS_%(archName)s_CCM_Container> CUTS_%(archName)s_CCM_ComponentServer_Base;

/**
 * @class CUTS_%(archName)s_CCM_ComponentServer
 *
 * Implementation of the CCM component server for %(archName)s.
 */
class CUTS_%(archName)s_CCM_ComponentServer :
  public CUTS_%(archName)s_CCM_ComponentServer_Base
{
public:
  /**
   * Initializing constructor.
   *
   * Application that containers the component server implementation.
   */
  CUTS_%(archName)s_CCM_ComponentServer (
    CUTS_%(archName)s_CCM_ComponentServer_App * app);

  /// Destructor.
  virtual ~CUTS_%(archName)s_CCM_ComponentServer (void);
};

#if defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_%(archNameUpper)s_CCM_COMPONENTSERVER_H_
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_ComponentServer.h"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeComponentServer
#
#   Function for writing all the component server files
#
def writeComponentServerApp (output, dict) :
  writeComponentServerAppHeader (output, dict)
  writeComponentServerAppSource (output, dict)
  writeComponentServerAppInline (output, dict)

#
# writeComponentServerAppSource
#
#   Function for writing the component server app source file
#
def writeComponentServerAppSource (output, dict) :
  sourceFile = """// $Id$

#include "%(archName)s_CCM_ComponentServer_App.h"

#if !defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_ComponentServer_App.inl"
#endif

#include "%(archName)s_CCM_ComponentServer.h"
#include "ace/ARGV.h"
#include "ace/Get_Opt.h"

//
// run_main
//
int CUTS_%(archName)s_CCM_ComponentServer_App::
run_main (int argc, char * argv[])
{
  ACE_ARGV_T <char> argv_list (argc, argv);
  this->parse_args (argv_list.argc (), argv_list.argv ());

  return base_type::run_main (argc, argv);
}

//
// parse_args
//
int CUTS_%(archName)s_CCM_ComponentServer_App::
parse_args (int argc, char * argv [])
{
  const char * optargs = ACE_TEXT ("h");
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option (ACE_TEXT("help"), 'h');

  char opt;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp (ACE_TEXT ("help"), get_opt.long_option ()))
      {
        this->print_help ();
      }
      break;

    case 'h':
      this->print_help ();
      break;
    };
  }

  return 0;
}

//
// print_help
//
void CUTS_%(archName)s_CCM_ComponentServer_App::print_help (void)
{
  ACE_OS::exit (1);
}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_ComponentServer_App.cpp"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeComponentServerAppInline
#
#   Function for writing the component server app inline file
#
def writeComponentServerAppInline (output, dict) :
  sourceFile = """// -*- C++ -*-
// $Id$

//
// CUTS_%(archName)s_CCM_ComponentServer_App
//
CUTS_INLINE
CUTS_%(archName)s_CCM_ComponentServer_App::
CUTS_%(archName)s_CCM_ComponentServer_App (void)
{

}

//
// ~CUTS_%(archName)s_CCM_ComponentServer_App
//
CUTS_INLINE
CUTS_%(archName)s_CCM_ComponentServer_App::
~CUTS_%(archName)s_CCM_ComponentServer_App (void)
{

}
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_ComponentServer_App.inl"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeComponentServerAppHeader
#
#   Function for writing the component server app header file
#
def writeComponentServerAppHeader (output, dict) :
  sourceFile = """// -*- C++ -*-

#ifndef _CUTS_%(archNameUpper)s_CCM_COMPONENTSERVER_APP_H_
#define _CUTS_%(archNameUpper)s_CCM_COMPONENTSERVER_APP_H_

#include "cuts/arch/ccm/CCM_ComponentServer_App_T.h"
#include "%(archName)s_CCM_ComponentServer.h"

/// Type defintion of the component server app's base type.
typedef
  CUTS_CCM_ComponentServer_App_T <
    CUTS_%(archName)s_CCM_ComponentServer_App,
    CUTS_%(archName)s_CCM_ComponentServer>
    CUTS_%(archName)s_CCM_ComponentServer_App_Base;

/**
 * @class CUTS_%(archName)s_CCM_ComponentServer_App
 *
 * Main application for the %(archName)s component server.
 */
class CUTS_%(archName)s_CCM_ComponentServer_App :
  public CUTS_%(archName)s_CCM_ComponentServer_App_Base
{
public:
  /// Type definition of the base type.
  typedef CUTS_%(archName)s_CCM_ComponentServer_App_Base base_type;

  /// Default constructor.
  CUTS_%(archName)s_CCM_ComponentServer_App (void);

  /// Destructor.
  virtual ~CUTS_%(archName)s_CCM_ComponentServer_App (void);

  /**
   * Main entry point for the application.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The actual command-line arguments
   */
  int run_main (int argc, char * argv []);

private:
  /// Help method to parse the command-line options.
  int parse_args (int argc, char * argv []);

  /// Print help for the application.
  void print_help (void);
};

#if defined (__CUTS_INLINE__)
#include "%(archName)s_CCM_ComponentServer_App.inl"
#endif

#endif  // !defined _CUTS_%(archNameUpper)s_CCM_COMPONENTSERVER_APP_H_
""" % dict

  # write the servant's header to file
  filename = output + "/server/" + dict["archName"] + "_CCM_ComponentServer_App.h"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeServerDriver
#
#   Driver program for the component server application
#
def writeServerDriver (output, dict) :
  sourceFile = """// $Id$

#include "ace/Singleton.h"
#include "ace/Signal.h"
#include "ace/Null_Mutex.h"
#include "%(archName)s_CCM_ComponentServer_App.h"

#define CUTS_%(archNameUpper)s_COMPONENT_SERVER_APP \\
  ACE_Singleton <CUTS_%(archName)s_CCM_ComponentServer_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  CUTS_%(archNameUpper)s_COMPONENT_SERVER_APP->shutdown (true);
  ACE_UNUSED_ARG (sig);
}

//
// register_sighandler
//
static void register_sighandler (void)
{
  ACE_Sig_Action sa (&server_sighandler);

  sa.register_action (SIGINT);
  sa.register_action (SIGTERM);
}

//
// main
//
int ACE_TMAIN (int argc, char * argv [])
{
  int retval = 0;

  try
  {
    try
    {
      // Register the signal handler for Ctrl+C
      register_sighandler ();

      // Run the component server's app.
      retval = CUTS_%(archNameUpper)s_COMPONENT_SERVER_APP->run_main (argc, argv);
    }
    catch (const ::CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%%T - %%M - %%s\\n"),
                  ex._info ().c_str ()));

      retval = 1;
    }
    catch (...)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%%T (%%t) - %%M - caught unknown exception\\n")));

      retval = 1;
    }

    // Destroy the component server.
    CUTS_%(archNameUpper)s_COMPONENT_SERVER_APP->destroy ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%%T (%%t) - %%M - caught unknown exception\\n")));
  }

  return retval;
}
""" % dict

  # write the servant's header to file
  filename = output + "/server/server.cpp"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

#
# writeServerMPC
#
#   MPC file for building the component server application
#
def writeServerMPC (output, dict) :
  sourceFile = """// $Id$

project (CUTS_%(archName)s_CCM_ComponentServer) : ciao_componentserver_svnt, cuts_ccm, cuts_lib, cutsexe {
  exename = cuts-%(archNameLower)s-componentserver

  after += CUTS_%(archName)s_CCM
  libs  += CUTS_%(archName)s_CCM

  Source_Files {
    %(archName)s_CCM_ComponentServer.cpp
    %(archName)s_CCM_ComponentServer_App.cpp
    %(archName)s_CCM_Container.cpp
    %(archName)s_CCM_Container_Strategy.cpp
    server.cpp
  }
}
""" % dict

  # write source to file
  filename = output + "/server/server.mpc"
  outfile = open (filename, "w")
  outfile.write (sourceFile)
  outfile.close ();

###############################################################################
## main entry point

if __name__ == "__main__" :
  main ()
