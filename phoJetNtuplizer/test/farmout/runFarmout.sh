#!/bin/bash


datasets=( /EGamma/Run2018D-22Jan2019-v2/MINIAOD
    )

dirName=(
    Egamma2018D-22Jan2019-Test2
    )

#dataset="/MET/Run2017B-31Mar2018-v1/MINIAOD"

index=-1;
for sampleName in "${datasets[0]}"; do
  index=$(( $index+1 ))

  echo submitting jobs for "$sampleName"  with out dir name "${dirName[$index]}"

farmoutAnalysisJobs \
 --job-count=5  \
 --input-files-per-job=1 \
 --lumi-mask=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt \
 --input-dbs-path=$sampleName \
 --extra-inputs=Autumn18_RunABCD_V19_DATA.db \
 ${dirName[$index]} \
 /cms/varuns/2018/CMSSW_10_2_10 \
 /cms/varuns/2018/CMSSW_10_2_10/src/phoJetAnalysis/phoJetNtuplizer/test/run_102X_data2018_farmout.py

done

