#!/bin/bash

CONFIG_LIST=$1
OUTPUT_PATH=$2

PROJ_NAME=`${CUTS_ROOT}/etc/emulab/get-project-name.sh`
EXPR_NAME=`${CUTS_ROOT}/etc/emulab/get-experiment-name.sh`
NODE_LIST=`grep h /var/emulab/boot/ltmap | sed "s/h //"`

for i in `cat ${CONFIG_LIST}`; do
  # run the test
  ./run-test.sh $i ${OUTPUT_PATH}

  for j in `${NODE_LIST}`; do
    HOSTNAME=$j.${EXPR_NAME}.${PROJ_NAME}.isislab.vanderbilt.edu
    
    echo "*** info: sending reset signal to ${HOSTNAME}"
    ${CUTS_ROOT}/bin/cutsnode --reset -ORBInitRef CUTS/NodeDaemon=${HOSTNAME}:30000/CUTS/NodeDaemon
  done
done
