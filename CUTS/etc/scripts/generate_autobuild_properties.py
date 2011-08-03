#!/usr/bin/env python

###############################################################################
#
# @file        download_sources.py
#
# $Id$
#
# @author      James H. Hill
#
###############################################################################

import getopt
import os
import sys
import subprocess
from string import Template

def print_help ():
    usage = """Generate a Java properties file that is useful for CUTS autobuilds

USAGE: generate_build_properties.py [OPTIONS]

General Options:
  --prefix=PATH               Target location for properties file [default=.]

Print Options:
  -h, --help                  Print this help message

This script not only downloads the sources, but it will construct a
configuration file that details the location of CUTS and each
third-party project. This configuration file should be executed from
the command-line each time a new console is open. Otherwise, the
environment will not be configured properly."""

    print (usage)
    sys.exit (2)

#
# Generate the Java properties file for this build directory. This
# file currently assumes downloads_sources.py was used to download
# sources from their repository.
#
# @param[in]            prefix          Relative/absolute location of file
#
def generate_properties_file (prefix):
    template = Template ("""# This file was generated using the command:
# ${command_line}

# DOC Middleware
ace.dir=${abspath}${slash}Middleware${slash}ACE
tao.dir=${abspath}${slash}Middleware${slash}TAO
ciao.dir=${abspath}${slash}Middleware${slash}CIAO
dance.dir=${abspath}${slash}Middleware${slash}DAnCE
adbc.dir=${abspath}${slash}Middleware${slash}ADBC

# MPC
mpc.dir=${abspath}${slash}MPC

# CUTS
cuts.dir=${abspath}${slash}CUTS

# XSC
xsc.dir=${abspath}${slash}XSC

# Xerces-C
xercesc.dir=${abspath}${slash}xerces-c

# Boost
boost.dir=${abspath}${slash}boost
boost.version=boost-1_43

# PCRE
pcre.dir=${abspath}${slash}pcre
""")

    slash = "/"
    abspath = os.path.abspath (prefix)

    if sys.platform.startswith ('win32'):
        slash = "\\\\"
        prefix = prefix.replace ("\\", slash)
        abspath = abspath.replace ("\\", slash)

    params = {  'prefix' : prefix,
                'abspath' : abspath,
                'slash' : slash,
                'command_line' : ",".join (sys.argv).replace (",", " ")}

    # Write the configuration file.
    propfile = prefix + "/autobuild.properties"
    propfile= open (propfile, "w")
    propfile.write (template.substitute (params))
    propfile.close ()

#
# Main entry point for the application.
#
def main ():
    try:
        # Parse the command-line arguments.
        opts, args = getopt.getopt (sys.argv[1:],
                                    "h",
                                    ["help", "prefix="])

        prefix = "."

        for o, a in opts:
            if o == "--prefix":
                prefix = a
            elif o in ("-h", "--help"):
                print_help ()
            else:
                assert False, "unhandled option"

        # Finally, generate the configuration files
        generate_properties_file (prefix)

    except getopt.error as ex:
        print ("Error: " + ex.args[0])
        sys.exit (1)

#
# Invoke the main entry point, if applicable.
#
if __name__ == "__main__":
    main ()
