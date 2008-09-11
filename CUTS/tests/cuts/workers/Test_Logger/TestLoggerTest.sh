#!/bin/bash

################################################################################
##
## @file            TestLoggerTest.sh
##
## $Id$
##
## @author          James H. Hill
##
################################################################################

# common variables
JAVA_CMD=java

CUTS_CLASSPATH=${CUTS_ROOT}/lib/CUTS.TestLogger.jar:${CUTS_ROOT}/lib/cuts.java.jar:${CUTS_ROOT}/contrib/java/log4j-1.2.15.jar:${CUTS_ROOT}/contrib/java/commons-logging-1.1.1.jar:${CUTS_ROOT}/contrib/java/castor-1.2.jar:${CUTS_ROOT}/contrib/java/jacorb.jar:${CUTS_ROOT}/contrib/java/avalon-framework-4.1.5.jar:${CUTS_ROOT}/contrib/java/logkit-1.2.jar

# execute the application
exec ${JAVA_CMD} ${JAVA_OPTS}                                       \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                     \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton   \
    -classpath .:${CUTS_CLASSPATH}                                  \
    TestLoggerTest "$@"
