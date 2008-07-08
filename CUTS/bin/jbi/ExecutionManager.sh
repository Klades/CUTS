#!/bin/bash

###############################################################################
##
## @file            ExecutionManager.sh
##
## $Id$
##
## @author          James H. Hill
##
## Helper script for launching the execution manager for the deployment
## framework.
##
###############################################################################

# comman variables
JAVA_CMD=java
CUTS_CLASSPATH=${CUTS_ROOT}/lib/cuts.java.jar:${CUTS_ROOT}/lib/cuts.java.jbi.jar:${CUTS_ROOT%}/lib/cuts.java.jbi.deployment.jar:${CUTS_ROOT}/contrib/java/log4j-1.2.15.jar

# execute the application
exec ${JAVA_CMD} ${JAVA_OPTS}                                                                  \
  -Djava.endorsed.dirs=${CUTS_ROOT}/contrib/java                                               \
  -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                                                  \
  -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton                                \
  -classpath ${CUTS_CLASSPATH}:${CLASSPATH} cuts.java.jbi.deployment.JbiExecutionManager "$@"
