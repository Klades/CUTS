#!/bin/bash

DEPLOYMENT=$1
DATAFILE=$2
TEST_CONFIG=cutstest.config

${CUTS_ROOT}/bin/cuts-template --template=/proj/AntiSPAM/config/cutstest.config.template --ignore-variables > ${TEST_CONFIG}
${CUTS_ROOT}/bin/cutstest --config=${TEST_CONFIG}-DDEPLOYMENT_PLAN=${DEPLOYMENT} --time=120 -f ${DATAFILE} --ignore-errors --debug --verbose --shutdown-timeout=5
