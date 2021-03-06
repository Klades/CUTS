#!/bin/bash

###############################################################################
##
## @file            PlanLauncher.sh
##
## $Id$
##
## @author          James H. Hill
##
## Helper script to configure the deployment framework and start
## a new node manager.
##
###############################################################################

# comman variables
JAVA_CMD=java

CUTS_CLASSPATH=${CUTS_ROOT}/lib/cuts.java.jar:${CUTS_ROOT}/lib/cuts.java.capi.jar:${CUTS_ROOT}/lib/cuts.java.capi.deployment.jar:${CUTS_ROOT}/contrib/java/log4j-1.2.15.jar:${CUTS_ROOT}/contrib/java/castor-1.2.jar:${CUTS_ROOT}/contrib/java/commons-logging-1.1.1.jar
JACORB_CLASSPATH=${CUTS_ROOT}/contrib/java/jacorb.jar:${CUTS_ROOT}/contrib/java/avalon-framework-4.1.5.jar:${CUTS_ROOT}/contrib/java/logkit-1.2.jar

# execute the application
exec ${JAVA_CMD} ${JAVA_OPTS}                                       \
  -Djava.endorsed.dirs=${CUTS_ROOT}/contrib/java                    \
  -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                       \
  -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton     \
  -classpath ${JACORB_CLASSPATH}:${CUTS_CLASSPATH}:${CLASSPATH}     \
  cuts.jbi.deployment.JbiPlanLauncher "$@"
