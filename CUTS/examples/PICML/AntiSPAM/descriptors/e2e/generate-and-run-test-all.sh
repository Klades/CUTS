#!/bin/bash

CONFIG_LIST=config.lst
DIRNAME=`dirname $0`

# generate all deployments; list specified file
${DIRNAME}/generate-DnC.sh ${CONFIG_LIST}
ARCHIVE=$1/birthtest

# run all tests; store data in specified directory
if [ ! -d ${ARCHIVE} ]; then
  mkdir ${ARCHIVE}
fi

${DIRNAME}/run-test-all.sh ${CONFIG_LIST} ${ARCHIVE}
