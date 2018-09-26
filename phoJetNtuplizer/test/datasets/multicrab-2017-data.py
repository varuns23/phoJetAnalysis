#multicrab

dataset = {
  'metB' : '/MET/Run2017B-31Mar2018-v1/MINIAOD',
  'metC' : '/MET/Run2017C-31Mar2018-v1/MINIAOD',
  'metD' : '/MET/Run2017D-31Mar2018-v1/MINIAOD',
  'metE' : '/MET/Run2017E-31Mar2018-v1/MINIAOD',
  'metF' : '/MET/Run2017F-31Mar2018-v1/MINIAOD',

  'SingleEleB' : '/SingleElectron/Run2017B-31Mar2018-v1/MINIAOD',
  'SingleEleC' : '/SingleElectron/Run2017C-31Mar2018-v1/MINIAOD',
  'SingleEleD' : '/SingleElectron/Run2017D-31Mar2018-v1/MINIAOD',
  'SingleEleE' : '/SingleElectron/Run2017E-31Mar2018-v1/MINIAOD',
  'SingleEleF' : '/SingleElectron/Run2017F-31Mar2018-v1/MINIAOD'
}

if __name__ == '__main__':
from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
config = config()
name = 'Ntuples-Data-31Mar2018'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.Data.publication = False
config.Site.storageSite = 'T2_US_Wisconsin'
config.JobType.psetName = 'run_94X_data.py'
#config.JobType.inputFiles = ['Summer16_23Sep2016AllV4_DATA.db','Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt']
config.section_('Data') 
#config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
#listOfSamples = ['metB', 'metC', 'metD', 'metE', 'metF']
listOfSamples = ['SingleEleB', 'SingleEleC', 'SingleEleD', 'SingleEleE', 'SingleEleF']

for sample in listOfSamples:  
  config.General.requestName = sample
  config.Data.inputDataset   = dataset[sample]
  config.JobType.outputFiles = ['ntuple_data.root']
  config.Data.unitsPerJob = 15
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/varuns/'+name
  #submit(config)
