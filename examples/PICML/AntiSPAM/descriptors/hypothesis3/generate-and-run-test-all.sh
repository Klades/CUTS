#!/bin/bash

OUTPUT_PATH=$1
CONFIG_LIST=config.lst
DIRNAME=`dirname $0`

# generate all deployments; list specified file
${DIRNAME}/generate-DnC.sh ${CONFIG_LIST}

# run all tests; store data in specified directory
${DIRNAME}/run-test-all.sh ${CONFIG_LIST} ${OUTPUT_PATH}
