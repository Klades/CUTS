#!/bin/bash

CONFIG_LIST="$(ls *.cdp)"
CONFIG_LIST_FILE=$1

if [ -f ${CONFIG_LIST_FILE} ]; then
  rm ${CONFIG_LIST_FILE}
fi

# iterate thru each configuration
for i in `ls ${CONFIG_LIST}`; do
  # initialize the configration variables
  CONFIG_NUMBER=`echo $i | sed "s/hypothesis1-template-assembly//" | sed "s/.cdp//"`
  CONFIG_TEMPLATE=hypothesis1-template-assembly${CONFIG_NUMBER}.cdp
  CONFIG_OUTPUT_DIR=configuration${CONFIG_NUMBER}

  # delete any of the existing configurations
  if [ -d "${CONFIG_OUTPUT_DIR}" ]; then
    rm -fr ${CONFIG_OUTPUT_DIR}
  fi

  # make the output directory
  mkdir ${CONFIG_OUTPUT_DIR}

  # generate the current configuration(s)
  echo "*** info: generating $i into ${CONFIG_OUTPUT_DIR}"
  $CUTS_ROOT/bin/cuts-template --template=${CONFIG_TEMPLATE} --config-list=hypothesis1-template-assembly.config -o ${CONFIG_OUTPUT_DIR} --use-env

  # iterate thur each generated configuration
  DEPLOYMENT_LIST=${CONFIG_OUTPUT_DIR}/*.cdp

  for j in `ls ${DEPLOYMENT_LIST}`; do
    # intialize the deployment variables
    DEPLOYMENT_NUMBER=`echo "$j" | sed "s/configuration[0-9]*\/H1-DeploymentTemplate-//" | sed "s/.cdp//"`
    DEPLOYMENT_OUTPUT_DIR=${CONFIG_OUTPUT_DIR}/deployment${DEPLOYMENT_NUMBER}

    # delete any of the existing deployments
    if [ -d "${DEPLOYMENT_OUTPUT_DIR}" ]; then
      rm -fr ${DEPLOYMENT_OUTPUT_DIR}
    fi

    mkdir ${DEPLOYMENT_OUTPUT_DIR}

    # generate the deployment(s)
    echo "*** info: generating $j into ${DEPLOYMENT_OUTPUT_DIR}"
    $CUTS_ROOT/bin/cuts-template --template=$j --config-list=unique-deployments.config -o ${DEPLOYMENT_OUTPUT_DIR} --use-env

    ls ${DEPLOYMENT_OUTPUT_DIR}/*.cdp >> ${CONFIG_LIST_FILE}
  done
done
