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
    # Parse command-line arguments.
    opts = parse_args (sys.argv[1:])

    # Import iCCM template generator.  
    CUTS_ROOT = os.environ['CUTS_ROOT']
    iCCM_ROOT = os.path.join (CUTS_ROOT, 'bin', 'iCCM')
    sys.path.append (iCCM_ROOT)

    import iCCM.TemplateFile

    output = opts["output"]
    params = { 'arch_name' : opts['name']}

    # Evaluate the templates.
    if not os.path.exists (output):
      print ('***info: making directory', output)
      os.makedirs (output)

    template_dir = iCCM.TemplateFile.TemplateDirectory ()
    template_dir.evaluate (os.path.join (iCCM_ROOT, 'templates/cpp'),
                           params,
                           output)

  except getopt.error as ex:
    print ("*** error: " + ex.args[0])
    sys.exit (1)

#
# Display the help screen to the user. This function does not
# return control to the caller. Instead, it exits the system.
#
def print_help ():
    usage = """Generate the skeleton code for a new iCCM backend

USAGE: generate_iccm_project.py [OPTIONS]

General Options:
  -o PATH                           Output directory for project
  -n, --name=NAME                   Name of iCCM project

Print Options:
  -h, --help [COMMAND]              Print this help information
"""
    # Print the generic help information.
    print (usage)
    
    sys.exit (1)

#
# Parse the command-line options
# 
def parse_args (args) :
  short_opts = 'n:o:h'
  long_opts = ['name=', 'help']

  values = { 'output' : '.' }
  
  opts, args = getopt.gnu_getopt ( sys.argv[1:], short_opts, long_opts )

  # parse the command-line arguments
  for o, a in opts:
    if o in ("-n", "--name"):
      values["name"] = a
    elif o in ('-o') :
      values["output"] = a
    elif o in ('-h', '--help'):
      print_help ()
    else:
      assert False, "unhandled option (%s)" % o

  return values

###############################################################################
## main entry point

if __name__ == "__main__" :
  main ()
