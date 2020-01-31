import os

dataset = {
  'MET2018Dv1' : '/MET/Run2018D-PromptReco-v1/MINIAOD',
  'MET2018Dv2' : '/MET/Run2018D-PromptReco-v2/MINIAOD',

  'EGamma2018Dv1' : '/EGamma/Run2018D-PromptReco-v1/MINIAOD',
  'EGamma2018Dv2' : '/EGamma/Run2018D-PromptReco-v2/MINIAOD',
}

if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
name = 'data2018_Prompt'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['inputFiles']

config.section_('Data') 
config.Data.publication = False
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'

config.Site.storageSite = 'T2_US_Wisconsin'
#config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

#listOfSamples = ['MET2018Bv1', 'MET2018Bv2', 'MET2018Dv1', 'MET2018Dv2']
listOfSamples = ['EGamma2018Dv1', 'EGamma2018Dv2']


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
  config.Data.unitsPerJob = 6
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/varuns/'+name
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
