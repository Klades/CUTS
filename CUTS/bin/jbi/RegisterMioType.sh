#!/bin/bash

################################################################################
##
## @file            RegisterMioType.sh
##
## $Id$
##
## @author          James H. Hill
##
## Helper script for manually registering MIO types with the JBI
## server.
##
################################################################################

# common variables
JAVA_CMD=java

JBI_CLASSPATH=${JBI_ROOT}/lib/capi1.5.jar:${JBI_ROOT}/lib/dom4j-1.6.1.jar:${JBI_ROOT}/lib/jaxen-1.1.1.jar:${JBI_ROOT}/lib/jbossall-client.jar
CUTS_CLASSPATH=${CUTS_ROOT}/lib/cuts.java.jbi.jar:${CUTS_ROOT}/contrib/java/log4j-1.2.15.jar:${CUTS_ROOT}/contrib/java/commons-logging-1.1.1.jar

# execute to CORBA application
exec ${JAVA_CMD} ${JAVA_OPTS}                                       \
    -classpath ${CUTS_CLASSPATH}:${JBI_CLASSPATH}:${CLASSPATH}      \
    CUTS.jbi.utils.RegisterMioType "$@"
