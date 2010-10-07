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

CUTS_CLASSPATH=${CUTS_ROOT}/lib/cuts.quotas.pojo.jar:${CUTS_ROOT}/contrib/java/spring.jar

# execute the application
exec ${JAVA_CMD} ${JAVA_OPTS}                                          \
  -Djava.endorsed.dirs=${CUTS_ROOT}/contrib/java                       \
  -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                          \
  -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton        \
  -classpath ${CUTS_CLASSPATH}:${CLASSPATH}        \
  cuts.quotas.pojo.PojoComponentServer "$@"
