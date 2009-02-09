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
  filename = "hypothesis3-template-assembly%d.assembly" % id
  outfile = open (filename, "w")

  # write the header for the assembly
  outfile.write ("assembly TemplateAssembly\n{\n")

  # write the instances in the assembly
  outfile.write ("  instances\n  {\n    ")


  for i in range (1, 4) :
    writeCPUBoundComponent (outfile, i)

  for i in range (1, 4) :
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
      instName=%s
      testName=`cat /var/emulab/boot/syncserver`:10000
    }
    """ % (name, name, name)

  outfile.write (instance)

#
# writeConnections
#
def writeConnections (outfile) :
  outfile.write ("  connections\n  {\n")
  portnames = ['A', 'B', 'C', 'D', 'E']

  # write connections for each component instance
  for i in range (1, 4) :
    # select number of active ports
    active = random.randint (1, 3)
    active_ids = set ()

    # randomly select the active ports
    for n in range (0, active) :
      id = random.randint (0, 4)

      if id not in active_ids :
        active_ids.add (id)

    for id in active_ids :
      # select the generator for this port
      generator = random.randint (1, 3)
      port = portnames[id]

      # write connections for component instance
      outfile.write ("    generator%d.NullEvent >> inst%d.InPort%c\n" % (generator, i, port))

  outfile.write ("  }\n")

#
# generateConfig
#
def generateConfigs (count) :
  # open configuration file for writing
  outfile = open ("hypothesis3-template-assembly.config", "w")

  for n in range (0, count) :
    # initialize an array of publish rates
    rates = []

    for i in range (0, 3) :
      rates.append (random.randint (1, 5))

    # write the publish rates to the configuration
    config = """config (H3-DeploymentTemplate-%d.cdp) {
  generator1.publishHertz=%d
  generator2.publishHertz=%d
  generator3.publishHertz=%d
}

""" % (n, rates[0], rates[1], rates[2])

    # write the configuration
    outfile.write (config)

  # close the configuration
  outfile.close ()

def generateDeployment () :
  outfile = open ("hypothesis3-template-assembly.deployment", "w")

  str = """deployment TemplateDeployment {
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst1 : ${host.inst1}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst2 : ${host.inst2}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/inst3 : ${host.inst3}[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator1 : generator[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator2 : generator[DefaultGroup]
  ComponentImplementations/TemplateAssembly/TemplateAssembly/generator3 : generator[DefaultGroup]
 """

  outfile.write (str)
  outfile.close ()

###############################################################################
## main entry point

if __name__ == "__main__" :
  main ()
