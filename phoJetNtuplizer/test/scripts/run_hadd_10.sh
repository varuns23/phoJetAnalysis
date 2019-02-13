#!/bin/bash

inputPath="/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017B"
outputPath="/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/met2017B"
name="Data_MET2017B_"

checkNsubDir=`ls $inputPath | wc -l`

outFileIndex=0;

for (( iDir = 0; iDir < $checkNsubDir; iDir++)); do

  filesInFolder=(`ls $inputPath/000$iDir/*.root`)
  nfilesInFolder=${#filesInFolder[*]}

  fileToHadd=10;
  nOutFiles=$(($nfilesInFolder/$fileToHadd))
  remainder=$(($nfilesInFolder%$fileToHadd))

  for (( i = 0; i < $nOutFiles; i++)); do
    outFileIndex=$(( $outFileIndex+1 ))

    hadd $name$outFileIndex.root ${filesInFolder[$((($i*$fileToHadd)))]} ${filesInFolder[$((($i*$fileToHadd)+1))]} ${filesInFolder[$((($i*$fileToHadd)+2))]} ${filesInFolder[$((($i*$fileToHadd)+3))]} ${filesInFolder[$((($i*$fileToHadd)+4))]} ${filesInFolder[$((($i*$fileToHadd)+5))]} ${filesInFolder[$((($i*$fileToHadd)+6))]} ${filesInFolder[$((($i*$fileToHadd)+7))]} ${filesInFolder[$((($i*$fileToHadd)+8))]} ${filesInFolder[$((($i*$fileToHadd)+9))]}
    
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

    lastFile=$((($i*$fileToHadd)+9))
  done

  if [ $remainder -eq 1 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    cp ${filesInFolder[$(($lastFile+1))]} $outputPath/$name$outFileIndex.root 

  elif [ $remainder -eq 2 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 3 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 4 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]} ${filesInFolder[$(($lastFile+4))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 5 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]} ${filesInFolder[$(($lastFile+4))]} ${filesInFolder[$(($lastFile+5))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 6 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]} ${filesInFolder[$(($lastFile+4))]} ${filesInFolder[$(($lastFile+5))]} ${filesInFolder[$(($lastFile+6))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 7 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]} ${filesInFolder[$(($lastFile+4))]} ${filesInFolder[$(($lastFile+5))]} ${filesInFolder[$(($lastFile+6))]} ${filesInFolder[$(($lastFile+7))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 8 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]} ${filesInFolder[$(($lastFile+4))]} ${filesInFolder[$(($lastFile+5))]} ${filesInFolder[$(($lastFile+6))]} ${filesInFolder[$(($lastFile+7))]} ${filesInFolder[$(($lastFile+8))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root

  elif [ $remainder -eq 9 ]; then
    outFileIndex=$(( $outFileIndex+1 ))
    hadd "$name$outFileIndex ${filesInFolder[$(($lastFile+1))]} ${filesInFolder[$(($lastFile+2))]} ${filesInFolder[$(($lastFile+3))]} ${filesInFolder[$(($lastFile+4))]} ${filesInFolder[$(($lastFile+5))]} ${filesInFolder[$(($lastFile+6))]} ${filesInFolder[$(($lastFile+7))]} ${filesInFolder[$(($lastFile+8))]} ${filesInFolder[$(($lastFile+9))]}"
    mv $name$outFileIndex.root $outputPath/$name$outFileIndex.root
  fi

done

echo " All Hadd DONE"
