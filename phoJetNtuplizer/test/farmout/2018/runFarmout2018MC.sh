#!/bin/bash

##- /QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM
##- /QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM


datasets=(
   /QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM 
    )

dirName=(
    QCD_HT100to200
    )


index=-1;
for sampleName in "${datasets[0]}"; do
  index=$(( $index+1 ))

 echo submitting jobs for "$sampleName"  with out dir name "${dirName[$index]}"

farmoutAnalysisJobs \
 --input-files-per-job=1 \
 --input-dbs-path=$sampleName \
 --extra-inputs=Autumn18_V19_MC.db \
 --extra-usercode-files=cfipython \
 --memory-requirements=4000 \
 --assume-input-files-exist \
 --base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \
 ${dirName[$index]} \
 /cms/varuns/Ntuples/2018/CMSSW_10_2_18 \
 $PWD/run_102X_mc2018-farmout.py

done


# --memory-requirements=4000 \
# --assume-input-files-exist \ ##to run for files elsewhere in US
# --skip-existing-output \ ## to resubmit for missing root files
 
# To use HEP machines only
#--base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \

