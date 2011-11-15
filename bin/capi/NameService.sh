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

JACORB_CLASSPATH=${CUTS_ROOT}/contrib/java/jacorb.jar:${CUTS_ROOT}/contrib/java/avalon-framework-4.1.5.jar:${CUTS_ROOT}/contrib/java/logkit-1.2.jar

# execute the application
exec ${JAVA_CMD} ${JAVA_OPTS}                                     \
  -Djava.endorsed.dirs=${CUTS_ROOT}\contrib\java                  \
  -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                     \
  -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton   \
  -classpath ${JACORB_CLASSPATH}                                  \
  org.jacorb.naming.NameServer "$@"
