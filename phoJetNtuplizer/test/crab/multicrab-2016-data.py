import os

dataset = {
'MET2016Bv1': '/MET/Run2016B-17Jul2018_ver1-v1/MINIAOD',
'MET2016Bv2': '/MET/Run2016B-17Jul2018_ver2-v1/MINIAOD',
'MET2016C': '/MET/Run2016C-17Jul2018-v1/MINIAOD', 
'MET2016D': '/MET/Run2016D-17Jul2018-v1/MINIAOD',
'MET2016E': '/MET/Run2016E-17Jul2018-v1/MINIAOD',
'MET2016F': '/MET/Run2016F-17Jul2018-v1/MINIAOD',
'MET2016G': '/MET/Run2016G-17Jul2018-v1/MINIAOD',
'MET2016H': '/MET/Run2016H-17Jul2018-v2/MINIAOD',

'SingleEle2016Bv1': '/SingleElectron/Run2016B-17Jul2018_ver1-v1/MINIAOD',
'SingleEle2016Bv2': '/SingleElectron/Run2016B-17Jul2018_ver2-v1/MINIAOD',
'SingleEle2016C': '/SingleElectron/Run2016C-17Jul2018-v1/MINIAOD', 
'SingleEle2016D': '/SingleElectron/Run2016D-17Jul2018-v1/MINIAOD',
'SingleEle2016E': '/SingleElectron/Run2016E-17Jul2018-v1/MINIAOD',
'SingleEle2016F': '/SingleElectron/Run2016F-17Jul2018-v1/MINIAOD',
'SingleEle2016G': '/SingleElectron/Run2016G-17Jul2018-v1/MINIAOD',
'SingleEle2016H': '/SingleElectron/Run2016H-17Jul2018-v1/MINIAOD'

}

if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
name = 'Run2016_17Jul2018'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data') 
config.Data.publication = False
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.txt'

config.Site.storageSite = 'T2_US_Wisconsin'
#config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

#listOfSamples = ['MET2016Bv1', 'MET2016Bv2', 'MET2016C', 'MET2016D', 'MET2016E', 'MET2016F', 'MET2016G', 'MET2016H']
#listOfSamples = ['SingleEle2016Bv1', 'SingleEle2016Bv2', 'SingleEle2016C', 'SingleEle2016D', 'SingleEle2016E', 'SingleEle2016F', 'SingleEle2016G', 'SingleEle2016H']

for sample in listOfSamples:  
  os.popen('cp run_102X_data2016.py run_102X_data2016_'+sample+'.py')
  with open('run_102X_data2016_'+sample+'.py') as oldFile:
    newText = oldFile.read().replace('Ntuple_data2016.root','Data_'+sample+'.root')
  with open('run_102X_data2016_'+sample+'.py', 'w') as newFile:
    newFile.write(newText)

  config.General.requestName = 'job_'+sample
  
  config.JobType.psetName = 'run_102X_data2016_'+sample+'.py'
  config.JobType.outputFiles = ['Data_'+sample+'.root']
  
  config.Data.inputDataset   = dataset[sample]
  config.Data.unitsPerJob = 10
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/varuns/'+name
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
