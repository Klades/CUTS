#!/bin/bash

#
# @file           cuts-node-reset-all.sh
#
# $Id$
#
# @author         James H. Hill
#

PROJ_NAME=`${CUTS_ROOT}/etc/emulab/get-project-name.sh`
EXP_NAME=`${CUTS_ROOT}/etc/emulab/get-experiment-name.sh`
NODE_LIST=`grep h /var/emulab/boot/ltmap | sed "s/h //"`

for j in ${NODE_LIST}; do
  # get the fully qualified name of the host
  HOSTNAME=$j.${EXP_NAME}.${PROJ_NAME}.isislab.vanderbilt.edu

  # reset the host
  ${CUTS_ROOT}/etc/emulab/cuts-node-reset.sh ${HOSTNAME}:$1
done
