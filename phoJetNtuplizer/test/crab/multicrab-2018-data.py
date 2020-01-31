import os

dataset = {
  'MET2018A' : '/MET/Run2018A-17Sep2018-v1/MINIAOD',
  'MET2018B' : '/MET/Run2018A-17Sep2018-v1/MINIAOD',
  'MET2018C' : '/MET/Run2018C-17Sep2018-v1/MINIAOD',

  'EGamma2018A' : '/EGamma/Run2018A-17Sep2018-v2/MINIAOD',
  'EGamma2018B' : '/EGamma/Run2018B-17Sep2018-v1/MINIAOD',
  'EGamma2018C' : '/EGamma/Run2018C-17Sep2018-v1/MINIAOD',
  'EGamma2018D' : '/EGamma/Run2018D-22Jan2019-v2/MINIAOD',

  'JetHT2018A' : '/JetHT/Run2018A-17Sep2018-v1/MINIAOD',
  'JetHT2018B' : '/JetHT/Run2018B-17Sep2018-v1/MINIAOD',
  'JetHT2018C' : '/JetHT/Run2018C-17Sep2018-v1/MINIAOD',
}

if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
name = 'data2018_22Jan2019_JECv19'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.inputFiles = ['Autumn18_RunABCD_V19_DATA.db']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data') 
config.Data.publication = False
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'

config.Site.storageSite = 'T2_US_Wisconsin'
config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

#listOfSamples = ['MET2018A', 'MET2018B', 'MET2018C']
listOfSamples = ['EGamma2018D']


for sample in listOfSamples:  
  os.popen('cp run_102X_data2018.py run_102X_data2018_'+sample+'.py')
  with open('run_102X_data2018_'+sample+'.py') as oldFile:
    newText = oldFile.read().replace('Ntuple_data2018.root','Data_'+sample+'.root')
  with open('run_102X_data2018_'+sample+'.py', 'w') as newFile:
    newFile.write(newText)

  config.General.requestName = 'job_'+sample
  
  config.JobType.psetName = 'run_102X_data2018_'+sample+'.py'
  config.JobType.outputFiles = ['Data_'+sample+'.root']
  
  config.Data.inputDataset   = dataset[sample]
  config.Data.unitsPerJob = 13
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/varuns/'+name
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
