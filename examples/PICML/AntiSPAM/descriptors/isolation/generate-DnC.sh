#!/bin/bash

CONFIG_LIST="$(ls *.cdp)"
CONFIG_LIST_FILE=$1

if [ -f ${CONFIG_LIST_FILE} ]; then
  rm ${CONFIG_LIST_FILE}
fi

# iterate thru each configuration
for i in `ls ${CONFIG_LIST}`; do
  # initialize the configration variables
  CONFIG_NUMBER=`echo $i | sed "s/isolation-template-assembly//" | sed "s/.cdp//"`
  CONFIG_TEMPLATE=isolation-template-assembly${CONFIG_NUMBER}.cdp
  CONFIG_OUTPUT_DIR=assembly${CONFIG_NUMBER}

  # delete any of the existing configurations
  if [ -d "${CONFIG_OUTPUT_DIR}" ]; then
    rm -fr ${CONFIG_OUTPUT_DIR}
  fi

  # make the output directory
  mkdir ${CONFIG_OUTPUT_DIR}

  # generate the current configuration(s)
  echo "*** info: generating $i into ${CONFIG_OUTPUT_DIR}"
  $CUTS_ROOT/bin/cuts-template --template=${CONFIG_TEMPLATE} --config-list=isolation-template-assembly${CONFIG_NUMBER}.config -o ${CONFIG_OUTPUT_DIR} --use-env

  # write the configurations to the listing
  ls ${CONFIG_OUTPUT_DIR}/*.cdp >> ${CONFIG_LIST_FILE}
done
