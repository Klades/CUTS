#!/bin/bash

OUTPUT_PATH=$1
CONFIG_LIST=config.lst

# generate all deployments; list specified file
generate-DnC.sh ${CONFIG_LIST}

# run all tests; store data in specified directory
run-test-all.sh ${CONFIG_LIST} ${OUTPUT_PATH}
