#!/bin/bash

CONFIG_LIST=$1
OUTPUT_PATH=$2

for i in `cat ${CONFIG_LIST}`; do
  DATAFILE=`echo "$i" | sed "s/\//./g"`
  ARCHIVE_FILE=${OUTPUT_PATH}/${DATAFILE}

  if [ ! -f "${ARCHIVE_FILE}" ]; then
    # run the test
    echo "*** info: running test for deployment $i; storing data at ${DATAFILE}"
    ./run-test.sh $i ${DATAFILE}

    # archive the datafile
    mv ${DATAFILE} ${OUTPUT_PATH}
    
    # reset the test environment
    ./reset-nodes.sh 30000
    sleep 5s
  fi
done
