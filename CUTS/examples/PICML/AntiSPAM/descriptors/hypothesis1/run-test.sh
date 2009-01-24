#!/bin/bash

DEPLOYMENT=$1
DATAFILE_BASENAME=`echo "$1" | sed "s/\//./"`
DATAFILE=$2/${DATAFILE_BASENAME}

if [ ! -f "${DATAFILE}" ]; then
  echo "*** info: running test for deployment ${DATAFILE}"

  ${CUTS_ROOT}/bin/cutstest --config=/proj/AntiSPAM/config/cutstest.config -DDEPLOYMENT_PLAN=${DEPLOYMENT} --time=120 -f ${DATAFILE} --ignore-errors
else
  echo "*** info: ${DATAFILE} already exists; skipping test..."
fi
