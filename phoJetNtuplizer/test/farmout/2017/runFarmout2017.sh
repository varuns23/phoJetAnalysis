#!/bin/bash

##- /MET/Run2017B-31Mar2018-v1/MINIAOD
##- /MET/Run2017C-31Mar2018-v1/MINIAOD
##- /MET/Run2017D-31Mar2018-v1/MINIAOD
##- /MET/Run2017E-31Mar2018-v1/MINIAOD
##- /MET/Run2017F-31Mar2018-v1/MINIAOD

##- /SingleElectron/Run2017B-31Mar2018-v1/MINIAOD
##- /SingleElectron/Run2017C-31Mar2018-v1/MINIAOD
##- /SingleElectron/Run2017D-31Mar2018-v1/MINIAOD
##- /SingleElectron/Run2017E-31Mar2018-v1/MINIAOD
##- /SingleElectron/Run2017F-31Mar2018-v1/MINIAOD

##- /SinglePhoton/Run2017B-31Mar2018-v1/MINIAOD
##- /SinglePhoton/Run2017C-31Mar2018-v1/MINIAOD
##- /SinglePhoton/Run2017D-31Mar2018-v1/MINIAOD
##- /SinglePhoton/Run2017E-31Mar2018-v1/MINIAOD
##- /SinglePhoton/Run2017F-31Mar2018-v1/MINIAOD


datasets=(
    /SingleElectron/Run2017E-31Mar2018-v1/MINIAOD
    )

dirName=(
   SingleEle2017E
    )


index=-1;
for sampleName in "${datasets[0]}"; do
  index=$(( $index+1 ))

 echo submitting jobs for "$sampleName"  with out dir name "${dirName[$index]}"

farmoutAnalysisJobs \
 --input-files-per-job=1 \
 --lumi-mask=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt \
 --input-dbs-path=$sampleName \
 --extra-inputs=Fall17_17Nov2017_V32_102X_DATA.db,Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt \
 --extra-usercode-files=cfipython \
 --memory-requirements=4000 \
 --assume-input-files-exist \
 --skip-existing-output \
 --base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \
 ${dirName[$index]} \
 /cms/varuns/Ntuples/2017/CMSSW_10_2_18 \
 $PWD/run_102X_data2017-farmout.py

done


# --memory-requirements=4000 \
# --assume-input-files-exist \ ##to run for files elsewhere in US
# --skip-existing-output \ ## to resubmit for missing root files
 
# To use HEP machines only
#--base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \

