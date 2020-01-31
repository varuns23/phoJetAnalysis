#!/bin/bash

##- /MET/Run2018A-17Sep2018-v1/MINIAOD
##- /MET/Run2018B-17Sep2018-v1/MINIAOD
##- /MET/Run2018C-17Sep2018-v1/MINIAOD
##- /MET/Run2018D-PromptReco-v2/MINIAOD CHANGE GLOBAL TAG FOR THIS
##-  
##- /EGamma/Run2018A-17Sep2018-v2/MINIAOD
##- /EGamma/Run2018B-17Sep2018-v1/MINIAOD
##- /EGamma/Run2018C-17Sep2018-v1/MINIAOD
##- /EGamma/Run2018D-22Jan2019-v2/MINIAOD

datasets=(
    /MET/Run2018D-PromptReco-v2/MINIAOD
    )

dirName=(
   MET2018D-PromptReco
    )


index=-1;
for sampleName in "${datasets[0]}"; do
  index=$(( $index+1 ))

 echo submitting jobs for "$sampleName"  with out dir name "${dirName[$index]}"

farmoutAnalysisJobs \
 --input-files-per-job=1 \
 --lumi-mask=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt \
 --input-dbs-path=$sampleName \
 --extra-inputs=Autumn18_RunABCD_V19_DATA.db,Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt \
 --extra-usercode-files=cfipython \
 --memory-requirements=4000 \
 --assume-input-files-exist \
 --skip-existing-output \
 --base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \
 ${dirName[$index]} \
 /cms/varuns/Ntuples/2018/CMSSW_10_2_18 \
 $PWD/run_102X_data2018-farmout.py

done


# --memory-requirements=4000 \
# --assume-input-files-exist \ ##to run for files elsewhere in US
# --skip-existing-output \ ## to resubmit for missing root files
 
# To use HEP machines only
#--base-requirements='TARGET.PoolName == "HEP" && ((MY.RequiresSharedFS =!= true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN =?= true) && (TARGET.HasParrotCVMFS =?= true || (TARGET.UWCMS_CVMFS_Exists && TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Revision >= 444 && TARGET.CMS_CVMFS_Revision >= 81620))) && ((MY.NoAutoRequirements =?= true || (TARGET.OSglibc_major == 2 && TARGET.OSglibc_minor >= 17 && (MY.HEP_VO =!= "uscms" || TARGET.CMS_CVMFS_Exists && TARGET.UWCMS_CVMFS_Exists)))) && (TARGET.Arch == "X86_64") && (TARGET.OpSys == "LINUX") && (TARGET.Disk >= RequestDisk) && (TARGET.Memory >= RequestMemory) && (TARGET.HasFileTransfer)' \

