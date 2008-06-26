#!/bin/bash

################################################################################
##
## @file            SingleProcess.sh
##
## $Id$
##
## @author          James H. Hill
##
## Helper script for manually deploying multiple JBI client objects into 
## a single application process.
##
################################################################################

# common variables
JAVA_CMD=java

JBI_CLASSPATH=${JBI_ROOT}/lib/capi1.5.jar:${JBI_ROOT}/lib/dom4j-1.6.1.jar:${JBI_ROOT}/lib/jaxen-1.1.1.jar:${JBI_ROOT}/lib/jbossall-client.jar
CUTS_CLASSPATH=${CUTS_ROOT}/lib/cuts.java.jar:${CUTS_ROOT}/lib/cuts.java.jbi.jar:${CUTS_ROOT}/contrib/java/spring.jar:${CUTS_ROOT}/contrib/java/log4j-1.2.15.jar:${CUTS_ROOT}/contrib/java/commons-logging-1.1.1.jar

# execute to CORBA application
exec ${JAVA_CMD}                                                    \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB                     \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton   \
    -classpath ${CUTS_CLASSPATH}:${JBI_CLASSPATH}:${CLASSPATH}      \
    cuts.java.jbi.client.JbiClientApp "$@"
