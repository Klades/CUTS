# -*- Python -*-

###############################################################################
#
# @file             hypothesis1-assembly-generator.py
#
# $Id$
#
# @author           James H. Hill
#
###############################################################################

import sys
import getopt
import random
import math

#
# main
#
def main () :
  try:
    short_opt = "n:"
    long_opt = ["assemblies=", "configs="]

    opts, args = getopt.gnu_getopt (sys.argv[1:], short_opt, long_opt)

  except getopt.GetoptError, err:
    # print help information and exit
    print str (err)
    sys.exit (2)

  count = 0
  configs = 1

  # parse the command-line arguments
  for o, a in opts:
    if o in ("-n", "--assemblies"):
      count = int (a)
    elif o in ("--configs") :
      configs = int (a)
    else:
      assert False, "unhandled option (%s)" % o

  assert count != 0, "number of assemblies not specified"

  # seed the random number generator
  random.seed (None)

  # generate all the assemblies
  for i in range (1, count + 1) :
    generateAssembly (i)

  # generate all the configurations
  generateConfigs (configs)
  generateDeployment ()

  return 0

#
# generateAssembly
#
def generateAssembly (id) :
  # open the profile for writing
  filename = "hypothesis1-template-assembly%d.assembly" % id
  outfile = open (filename, "w")

  # write the header for the assembly
  outfile.write ("assembly TemplateAssembly\n{\n")

  # write the instances in the assembly
  outfile.write ("  instances\n  {\n    ")

  for i in range (1, 6) :
    writeCPUBoundComponent (outfile, i)

  for i in range (1, 6) :
    writeEventGeneratorComponent (outfile, i)

  outfile.write ("}\n\n")

  # write the connections for the assembly
  writeConnections (outfile)

  # end the assembly
  outfile.write ("}\n")

  # close the output file
  outfile.close ();

#
# writeCPUBoundComponent
#
def writeCPUBoundComponent (outfile, id) :
  instid = "inst%d" % (id)

  instance = """antispam::CPUBound %s
    {
      instName=%s
      testName=`cat /var/emulab/boot/syncserver`:10000
      logRate=10
    }
    """ % (instid, instid)

  outfile.write (instance)

#
# writeEventGeneratorComponent
#
def writeEventGeneratorComponent (outfile, id) :
  name = "generator%d" % (id)

  instance = """antispam::NullEventGenerator %s
    {
      publishHertz=${%s.publishHertz}
    }
    """ % (name, name)

  outfile.write (instance)

#
# writeConnections
#
def writeConnections (outfile) :
  outfile.write ("  connections\n  {\n")

  for i in range (1, 6) :
    # select number of publishers
    pubcount = random.randint (1, 3)
    pubs = set ()

    # randomly select the publishers for component
    for n in range (0, pubcount) :
      id = random.randint (1, 5)
      name = "generator%d" % (id)

      if name not in pubs :
        pubs.add (name)

    # write connections for component
    for pubname in pubs :
      outfile.write ("    %s.NullEvent >> inst%d.InPortA\n" % (pubname, i))

  outfile.write ("  }\n")

#
# generateConfig
#
def generateConfigs (count) :
  # open configuration file for writing
  outfile = open ("hypothesis1-template-assembly.config", "w")

  for n in range (0, count) :
    # initialize an array of publish rates
    rates = []

    for i in range (0, 5) :
      rates.append (random.randint (1, 10))

    # write the publish rates to the configuration
    config = """config (H1-DeploymentTemplate-%d.cdp) {
  generator1.publishHertz=%d
  generator2.publishHertz=%d
  generator3.publishHertz=%d
  generator4.publishHertz=%d
  generator5.publishHertz=%d
}

""" % (n, rates[0], rates[1], rates[2], rates[3], rates[4])

    # write the configuration
    outfile.write (config)

  # close the configuration
  outfile.close ()

def generateDeployment () :
  outfile = open ("hypothesis1-template-assembly.deployment", "w")

  str = """deployment TemplateDeployment {
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst1 : ${host.inst1}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst2 : ${host.inst2}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst3 : ${host.inst3}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst4 : ${host.inst4}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst5 : ${host.inst5}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator1 : generator[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator2 : generator[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator3 : generator[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator4 : generator[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator5 : generator[DefaultGroup]
}"""

  outfile.write (str)
  outfile.close ()

###############################################################################
## main entry point

if __name__ == "__main__" :
  main ()
