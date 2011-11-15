#!/bin/sh

TEST=$1
SQLFILE=$1.sql

if [ -f ${SQLFILE} ]; then
  rm ${SQLFILE}
fi

echo CREATE TABLE IF NOT EXISTS config (id INTEGER, name STRING); >> ${SQLFILE}
echo CREATE TABLE IF NOT EXISTS measured (config INTEGER, inst STRING, service REAL);
echo CREATE TABLE IF NOT EXISTS antispam (config INTEGER, inst STRING, service REAL, baseline REAL, myutl REAL, hostutil REAL, count INTEGER); >> ${SQLFILE}

COUNTER=1;

for i in `ls results/${TEST}/*.cdp`; do
  echo "processing $i..."

  BASENAME=`echo "$i" | sed "s/.cdp//"`
  DATAFILE=`echo "${BASENAME}" | sed "s/\./\//g"`

  ANTISPAM_FILE=${DATAFILE}.antispam
  ANTISPAM_FILE=`echo ${ANTISPAM_FILE} | sed "s/results/descriptors/"`
  UNITE_FILE=descriptors/${TEST}/antispam.unite

  # create the insert
  echo INSERT TO config (id, name) VALUES (${COUNTER}, ${BASENAME});

  if [ -f ${ANTISPAM_FILE} ]; then
      # process the results
      ${CUTS_ROOT}/bin/cuts-antispam -f ${ANTISPAM_FILE} > antispam.result
      
      if [ $? -eq 0 ]; then
          ${CUTS_ROOT}/bin/cuts-unite -c ${UNITE_FILE} -f $i --sandbox=sandbox > unite.result

      # locate all the instances in the antispam result
          INSTANCES=`grep inst[0-9] antispam.result | awk -F ' ' '{ printf "%s\n", $2 }'`
          
          for j in ${INSTANCES}; do
      # get the predicted response time for this component
              PREDICTED=`grep "$j" antispam.result | awk -F ' ' '{ printf "%s %s %s %s %s", $4, $5, $6, $7, $8}'`
              
          # make sure the host is not over utilized
              if [ `echo ${PREDICTED} | grep "\-[0-9]*" | wc -l` -eq 0 ]; then
          # get the expected response time for this component
                  MEASURED=`grep "$j" unite.result | awk -F ' ' '{ printf "%s", $4}'`
                  
                  echo $j ${MEASURED} ${PREDICTED} >> $2
              fi
          done
      else
          echo "  excluding $i"
      fi
  fi
done
