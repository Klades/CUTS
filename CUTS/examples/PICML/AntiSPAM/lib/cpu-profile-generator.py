# -*- Python -*-

###############################################################################
#
# @file             cpu-profile-generator.py
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
def main ():
  try:
    short_opt = "n:"
    long_opt = ["components=", "enable-post"]

    opts, args = getopt.gnu_getopt (sys.argv[1:], short_opt, long_opt)

  except getopt.GetoptError, err:
    # print help information and exit
    print str (err)
    sys.exit (2)

  count = 0
  enable_post = False

  # parse the command-line arguments
  for o, a in opts:
    if o in ("-n", "--components"):
      count = a
    elif o in ("--enable-post"):
      enable_post = True
    else:
      assert False, "unhandled option (%s)" % o

  assert count != 0, "number of instances not specified"

  # seed the random number generator
  random.seed (None)

  # generate all the profiles
  for i in range (1, int (count) + 1) :
    generateCPUProfile (i, enable_post)

#
# generateCPUProfile
#
def generateCPUProfile (id, enable_post) :
  # open the profile for writing
  profile_name = "inst%d.cpu" % id
  profile = open (profile_name, "w")

  # write the service times for each port
  for port in ['A', 'B', 'C', 'D', 'E'] :
    # get pre/post service times
    service_time = getRandomServiceTime ()

    if (enable_post) :
      pre, post = getRandomPrePostTimes (service_time)
    else :
      pre, post = service_time, 0

    # write th service times to the profile
    profile.write ("pre%c=%d\npost%c=%d\n" % (port, pre, port, post))

  # close the profile
  profile.close ()

#
# getRandomServiceTime
#
def getRandomServiceTime () :
  return random.randint (7, 16)

#
# getRandomPrePostTimes
#
def getRandomPrePostTimes (service_time) :
  # determine the preprocessing service time
  pre = random.randint (min (10, service_time), min (service_time, 70))

  # calculate the postprocessing service time
  post = service_time - pre

  # return the values to the caller
  return pre, post;

###############################################################################
## main entry point

if __name__ == "__main__" :
  main ()
