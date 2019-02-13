#!/bin/bash


datasets=( 
#    /MET/Run2017B-31Mar2018-v1/MINIAOD
#    /MET/Run2017C-31Mar2018-v1/MINIAOD
    /MET/Run2017D-31Mar2018-v1/MINIAOD
#    /MET/Run2017E-31Mar2018-v1/MINIAOD
#    /MET/Run2017F-31Mar2018-v1/MINIAOD
#    /SingleElectron/Run2017B-31Mar2018-v1/MINIAOD
#    /SingleElectron/Run2017C-31Mar2018-v1/MINIAOD
#    /SingleElectron/Run2017D-31Mar2018-v1/MINIAOD
#    /SingleElectron/Run2017E-31Mar2018-v1/MINIAOD
#    /SingleElectron/Run2017F-31Mar2018-v1/MINIAOD
    )

dirName=(
#    MET2017B
#    MET2017C
    MET2017D
#    MET2017E
#    MET2017F
#    SingleElectron2017B
#    SingleElectron2017C
#    SingleElectron2017D
#    SingleElectron2017E
#    SingleElectron2017F
    )

dataset="/MET/Run2017B-31Mar2018-v1/MINIAOD"

index=-1;
for sampleName in "${datasets[@]}"; do
  index=$(( $index+1 ))

  echo submitting jobs for "$sampleName"  with out dir name "${dirName[$index]}"

farmoutAnalysisJobs \
 --input-files-per-job=1 \
 --lumi-mask=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt \
 --input-dbs-path=$sampleName \
 ${dirName[$index]} \
 /cms/varuns/CMSSW_9_4_9 \
 /cms/varuns/CMSSW_9_4_9/src/phoJetAnalysis/phoJetNtuplizer/test/run_94X_data-farmout.py \
 --memory-requirements=4000 \
 --vsize-limit=10000

done

