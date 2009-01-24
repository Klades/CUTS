#!/bin/bash

CONFIG_LIST=$1
OUTPUT_PATH=$2

for i in `cat ${CONFIG_LIST}`; do
  # run the test
  ./run-test.sh $i ${OUTPUT_PATH}

  # reset the testing environment
done
