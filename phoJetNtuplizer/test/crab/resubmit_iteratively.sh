#!/bin/sh

#sleep 50 #inseconds

for (( i=0; i<10; i++)); do
  for jobDir in `ls crab_ntuple_data31Mar2018`; do
  crab resubmit -d crab_ntuple_data31Mar2018/${jobDir}
  done

echo "Sleep for 1hr"
sleep 3600
done
exit 0;
