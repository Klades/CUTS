#!/usr/bin/env python

###############################################################################
#
# @file        MpcEngine.py
#
# $Id$
#
# @author      James H. Hill
#
###############################################################################

import os
import subprocess

#
# Help function that defines a MPC workspace object. This object
# can be used to generate and build the workspace.
#
# @param[in]          workspace         Target workspace
# @param[in]          type              Build type
# @param[in]          features          Features for the build
# @param[in]          use_ace           Use MPC script in ACE
#
def define_workspace (workspace, type, features = None, use_ace = False) :
  return MpcWorkspace (workspace, type, features, use_ace)

#
# @class MpcEngine
#
# Wrapper class for using MPC.
#
class MpcWorkspace:
  #
  # Initializing constructor
  #
  # @param[in]          use_ace       Use mwc.pl in $ACE_ROOT/bin
  def __init__ (self, workspace, type, features = None, use_ace = False):
    self._workspace_ = workspace
    self._type_ = type
    self._features_ = features
    self._use_ace_ = use_ace

  #
  # Generate a MPC workspace for a build tool.
  #
  def generate (self):
    env = os.environ

    # Determine the location of mwc.pl
    if self._use_ace_:
      ACE_ROOT = env['ACE_ROOT']
      mwc_pl = os.path.join (ACE_ROOT, 'bin', 'mwc.pl')

    else:
      MPC_ROOT = env['MPC_ROOT']
      mwc_pl = os.path.join (MPC_ROOT, 'mwc.pl')

    # Construct the base command line.
    cmd = ['perl', '--', mwc_pl, '-type', self._type_, self._workspace_]

    # Insert the optional features.
    if self._features_ is not None:
      cmd.append ('-features')
      cmd.append (self._features_)

    # Execute the workspace generator script
    dir = os.path.dirname (self._workspace_)
    p = subprocess.Popen (cmd, cwd = dir)

    # Wait for the build to exit.
    p.wait ()

  #
  # Build the workspace.
  #
  def build (self):
   # Construct the correct build command based on the build type
    if self._type_.find ('vc') == 0:
      # Set the executable command.
      solution = self._workspace_.replace ('.mwc', '.sln')
      cmd = ['devenv.com', solution, '/useenv', '/Build', 'Debug']

    elif self._type_ in ('gnuace', 'nmake', 'make'):
      # Set the executable command.
      if self._type_ == 'gnuace':
        cmd = ['gmake']
      else:
        cmd = [self._type_]

      # Append the macros to the command-line
      macros = self._features_.split (',')
      for macro in macros :
        cmd.append (macro)

    else:
      print ("*** error: unsupported build type")
      sys.exit (1)

    # Execute the build command
    dir = os.path.dirname (self._workspace_)
    p = subprocess.Popen (cmd, cwd = dir)

    # Wait for the build to exit.
    p.wait ()
