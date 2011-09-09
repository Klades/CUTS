#!/usr/bin/env python

###############################################################################
#
# @file        build_sources.py
#
# $Id$
#
# @author      James H. Hill
#
###############################################################################

# system imports
import getopt
import os
import sys
import subprocess

# local imports
import mpc

#
# Print help about the script.
#
def print_help ():
  usage = """Build CUTS and third-party sources

USAGE: build_sources.py [OPTIONS]

General Options:
  -p, --property-file=FILE          Property configuration file
  --type=TYPE                       MPC build type

  --skip=PROJECT                    Skip building a project

Print Options:
  -h, --help                        Print this help message
"""

  print (usage)
  sys.exit (2)

#
# @class BuildConfig
#
# Build configuration for the program.
#
class BuildConfig:
  build_DOC_middleware = True
  build_CUTS = True
  build_XSC = True

#
# Read the contents of a property file
#
# @param[in]          filename          Name of the property file
#
def read_property_file (filename):
  file = open (filename, 'r')
  props = dict ()

  for line in file:
    line = line.strip ()

    if len (line) > 0 and line[0] != '#':
      # This not a comment line. So, we need to split the contents of
      # the line by the equal sign.
      entry = line.split ('=', 1)

      # Let's assume the value is a path, and that we need to normalize
      # its contents.
      props[entry[0]] = os.path.normpath (entry[1])

  return props

def build_Boost ():
  print ("*** info: building Boost libraries...")

#
# Build all of the DOC middleware
#
def build_DOC_middleware (type):
  # First, we are going to build ACE + TAO + CIAO + DAnCE
  CIAO_ROOT = os.environ['CIAO_ROOT']
  workspace = os.path.join (CIAO_ROOT, 'CIAO_TAO_DANCE.mwc')

  features = "xerces3=1"
  mwc = mpc.define_workspace (workspace, type, features, True)
  mwc.generate ()
  mwc.build ()

  # Now, we are goig to build ADBC
  ADBC_ROOT = os.environ['ADBC_ROOT']
  workspace = os.path.join (ADBC_ROOT, 'ADBC.mwc')
  features = 'sqlite=1'

  mwc = mpc.define_workspace (workspace, type, features, True)
  mwc.generate ()
  mwc.build ()

#
# Build the CUTS workspace
#
def build_XSC (type):
  XSC_ROOT = os.environ['XSC_ROOT']
  workspace = os.path.join (XSC_ROOT, 'XSC.mwc')

  # Generate the workspace
  features = 'xerces3=1,boost=1,exceptions=1'

  mwc = mpc.define_workspace (workspace, type, features, True)
  mwc.generate ()
  mwc.build ()

#
# Build the CUTS workspace
#
def build_CUTS (type):
  CUTS_ROOT = os.environ['CUTS_ROOT']
  workspace = os.path.join (CUTS_ROOT, 'CUTS.mwc')

  # Generate the workspace
  mpc = mpc.define_workspace (workspace, type, use_ace = True)
  mpc.generate ()
  mpc.build ()

#
# Main entry point for the application.
#
def main ():
  try:
    # Parse the command-line arguments.
    opts, args = getopt.getopt (sys.argv[1:],
                                "hp:",
                                ["help", "property-file=", 'type=', '--skip='])

    config = BuildConfig ()
    property_file = None
    type = None

    for opt, arg in opts:
      if opt == "--prefix":
        prefix = arg
      elif opt in ("-h", "--help"):
        print_help ()
      elif opt in ("-p", "--property-file"):
        property_file = arg
      elif opt == "--type":
        type = arg
      elif opt == '--skip':
        if arg == 'XSC':
          config.build_XSC = False
        elif arg == 'DOC':
          config.build_DOC_middleware = False
        elif arg == 'CUTS':
          config.build_CUTS = False
        else:
          assert False, "unknown project"
      else:
        assert False, "unknown option"

    # Make sure the property file has been specified on the command line.
    # Otherwise, we should not continue.
    if property_file is None:
      print ("*** error: property file not specified")
      sys.exit (1)

    if type is None:
      print ("*** error: build type is missing")
      sys.exit (1)

    # Read the contents of the property file.
    props = read_property_file (property_file)

    # Update the environment variables based on the contents of the
    # property file.
    env = os.environ

    for key, value in props.items ():
      env[key] = value

    # Build the different sources (these are MPC specific).
    if (config.build_XSC):
      build_XSC (type)

    if (config.build_DOC_middleware):
      build_DOC_middleware (type)

    if (config.build_CUTS):
      build_CUTS (type)

  except getopt.error as ex:
    print ("Error: " + ex.args[0])
    sys.exit (1)

#
# Invoke the main entry point, if applicable.
#
if __name__ == "__main__":
    main ()
