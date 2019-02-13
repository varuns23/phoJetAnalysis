import os
from ROOT import *

#cases = ['0000', '0001', '0002', '0003', '0004', '0005', '0006', '0007', '0008', '0009']
cases = ['0003', '0002']

#inFilePath = "/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017B/0000"
#inFilePath = "/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017B/0001"
#inFilePath = "/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017B/0002"
inFilePath = "/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017B/"
#inFilePath = "/hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/met2017B"

filesChain = TChain("phoJetNtuplizer/eventTree")

for cases_ in cases:
  for files_ in os.listdir(inFilePath+'/'+cases_): ## list the files in dir <filePath>
    if (files_.endswith(".root")):
      filesChain.Add(inFilePath+"/"+cases_+"/"+files_);
      print files_
#    print filesChain.GetEntries();

print " "    
print "Total Events:",filesChain.GetEntries();

