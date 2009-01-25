#!/bin/bash

CONFIG_LIST=$1
OUTPUT_PATH=$2

for i in `cat ${CONFIG_LIST}`; do
  # run the test
  ./run-test.sh $i ${OUTPUT_PATH}

  # reset each of the nodes
  ./reset-nodes.sh 30000  
done
