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
    params = { 'arch_name' : opts["name"]}

    # Evaluate the templates.
    if not os.path.exists (output):
      os.makedirs (output)

    template_dir = iCCM.TemplateFile.TemplateDirectory ()
    template_dir.evaluate ('iCCM/templates/cpp', params, output)

  except getopt.error as ex:
    print ("*** error: " + ex.args[0])
    sys.exit (1)


def parse_args (args) :
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
## main entry point

if __name__ == "__main__" :
  main ()
