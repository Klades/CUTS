#!/bin/bash

DEPLOYMENT=$1
DATAFILE=`echo "$1" | sed "s/\//./g"`
ARCHIVE_FILE=$2/${DATAFILE}

if [ ! -f "${ARCHIVE_FILE}" ]; then
  # run the test
  echo "*** info: running test for deployment ${DEPLOYMENT}; storing data at ${DATAFILE}"
  ${CUTS_ROOT}/bin/cutstest --config=/proj/AntiSPAM/config/cutstest.config -DDEPLOYMENT_PLAN=${DEPLOYMENT} --time=120 -f ${DATAFILE} --ignore-errors --debug --verbose

  # move the data file to the archive
  mv ${DATAFILE} $2/${DATAFILE}
else
  echo "*** info: ${DATAFILE} already archived; skipping test..."
fi
