#!/bin/bash

inputPath="/hdfs/store/user/varuns/NTuples/Data/Run2018_PromptReco/EGamma/Temp-EGamma2018Dv2-1"
outputPath="/hdfs/store/user/varuns/NTuples/Data/Run2018_PromptReco/EGamma/EGamma2018Dv2"
name="Data_EGamma2018Dv2_"

outFileIndex=0;

filesInFolder=(`ls $inputPath/*.root`)
nfilesInFolder=${#filesInFolder[*]}

fileToHadd=3;
nOutFiles=$(($nfilesInFolder/$fileToHadd))
remainder=$(($nfilesInFolder%$fileToHadd))

for (( i = 0; i < $nOutFiles; i++)); do
  outFileIndex=$(( $outFileIndex+1 ))

  hadd $name$outFileIndex.root ${filesInFolder[$((($i*$fileToHadd)))]} ${filesInFolder[$((($i*$fileToHadd)+1))]} ${filesInFolder[$((($i*$fileToHadd)+2))]}  
  mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  lastFile=$((($i*$fileToHadd)+$fileToHadd-1))
done

if [ $remainder -eq 1 ]; then
  outFileIndex=$(( $outFileIndex+1 ))
  cp ${filesInFolder[$(($lastFile+1))]} $outputPath/$name$outFileIndex.root 

elif [ $remainder -eq 2 ]; then
  outFileIndex=$(( $outFileIndex+1 ))
  hadd $name$outFileIndex.root ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]}
  mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

fi


echo " All Hadd DONE"
