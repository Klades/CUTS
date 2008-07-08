#!/bin/bash

###############################################################################
##
## @file            NameService.sh
##
## $Id$
##
## @author          James H. Hill
##
## Helper script for launching the naming service
##
###############################################################################

# common variables
JAVA_CMD=java

# execute the application
exec ${JAVA_CMD} ${JAVA_OPTS}                                     \
  -Djava.endorsed.dirs=%CUTS_ROOT%\contrib\java                   \
  -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                     \
  -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton   \
  org.jacorb.naming.NameServer "$@"                               
  