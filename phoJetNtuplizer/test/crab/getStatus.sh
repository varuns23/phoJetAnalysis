#!/bin/bash
 
for jobDir in `ls ${1}`; do
   
#echo "${jobDir}"
crab status -d ${1}/${jobDir}
   
done
