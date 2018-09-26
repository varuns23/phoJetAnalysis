#multicrab

dataset = {
  'MET2017B' : '/MET/Run2017B-31Mar2018-v1/MINIAOD',
  'MET2017C' : '/MET/Run2017C-31Mar2018-v1/MINIAOD',
  'MET2017D' : '/MET/Run2017D-31Mar2018-v1/MINIAOD',
  'MET2017E' : '/MET/Run2017E-31Mar2018-v1/MINIAOD',
  'MET2017F' : '/MET/Run2017F-31Mar2018-v1/MINIAOD',

  'SingleEle2017B' : '/SingleElectron/Run2017B-31Mar2018-v1/MINIAOD',
  'SingleEle2017C' : '/SingleElectron/Run2017C-31Mar2018-v1/MINIAOD',
  'SingleEle2017D' : '/SingleElectron/Run2017D-31Mar2018-v1/MINIAOD',
  'SingleEle2017E' : '/SingleElectron/Run2017E-31Mar2018-v1/MINIAOD',
  'SingleEle2017F' : '/SingleElectron/Run2017F-31Mar2018-v1/MINIAOD'
}

if __name__ == '__main__':
from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
config = config()
name = 'NtuplesData31Mar2018'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_94X_data.py'
#config.JobType.inputFiles = ['Summer16_23Sep2016AllV4_DATA.db','Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt']

config.section_('Data') 
config.Data.publication = False
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 50
config.Data.totalUnits = -1
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'

config.Site.storageSite = 'T2_US_Wisconsin'

listOfSamples = ['MET2017B', 'MET2017C', 'MET2017D', 'MET2017E', 'MET2017F']
#listOfSamples = ['SingleEle2017B', 'SingleEle2017C', 'SingleEle2017D', 'SingleEle2017E', 'SingleEle2017F']

for sample in listOfSamples:  
  config.General.requestName = 'job_'+sample
  config.JobType.outputFiles = ['Data'+sample+'.root']
  config.Data.inputDataset   = dataset[sample]
  config.Data.outLFNDirBase = '/store/user/varuns/'+name
  submit(config)
