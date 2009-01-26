#!/bin/bash

DEPLOYMENT=$1
DATAFILE=$2

${CUTS_ROOT}/bin/cutstest --config=/proj/AntiSPAM/config/cutstest.config -DDEPLOYMENT_PLAN=${DEPLOYMENT} --time=120 -f ${DATAFILE} --ignore-errors --debug --verbose --shutdown-timeout=5

