#!/bin/bash

#
# @file           cuts-node-reset.sh
#
# $Id$
#
# @author         James H. Hill
#

${CUTS_ROOT}/bin/cutsnode --reset -ORBInitRef NodeDaemon=corbaloc:iiop:$1/CUTS/NodeDaemon
