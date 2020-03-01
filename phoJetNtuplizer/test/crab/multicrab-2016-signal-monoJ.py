import os

dataset = {
'Axial_MonoJ_NLO_Mphi-100_Mchi-1':    '/Axial_MonoJ_NLO_Mphi-100_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-100_Mchi-200':  '/Axial_MonoJ_NLO_Mphi-100_Mchi-200_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-100_Mchi-40':   '/Axial_MonoJ_NLO_Mphi-100_Mchi-40_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-300_Mchi-100': '/Axial_MonoJ_NLO_Mphi-300_Mchi-100_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-300_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-300_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-300_Mchi-300': '/Axial_MonoJ_NLO_Mphi-300_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-300_Mchi-400': '/Axial_MonoJ_NLO_Mphi-300_Mchi-400_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-500_Mchi-150': '/Axial_MonoJ_NLO_Mphi-500_Mchi-150_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-500_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-500_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-500_Mchi-200': '/Axial_MonoJ_NLO_Mphi-500_Mchi-200_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-500_Mchi-300': '/Axial_MonoJ_NLO_Mphi-500_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-500_Mchi-500': '/Axial_MonoJ_NLO_Mphi-500_Mchi-500_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-750_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-750_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-750_Mchi-300': '/Axial_MonoJ_NLO_Mphi-750_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-750_Mchi-600': '/Axial_MonoJ_NLO_Mphi-750_Mchi-600_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'
'Axial_MonoJ_NLO_Mphi-1000_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-1000_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1000_Mchi-300': '/Axial_MonoJ_NLO_Mphi-1000_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1000_Mchi-600': '/Axial_MonoJ_NLO_Mphi-1000_Mchi-600_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1500_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-1500_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1500_Mchi-300': '/Axial_MonoJ_NLO_Mphi-1500_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1500_Mchi-600': '/Axial_MonoJ_NLO_Mphi-1500_Mchi-600_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-100': '/Axial_MonoJ_NLO_Mphi-1750_Mchi-100_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-10':  '/Axial_MonoJ_NLO_Mphi-1750_Mchi-10_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-150': '/Axial_MonoJ_NLO_Mphi-1750_Mchi-150_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-1750_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-200': '/Axial_MonoJ_NLO_Mphi-1750_Mchi-200_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-300': '/Axial_MonoJ_NLO_Mphi-1750_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-1750_Mchi-500': '/Axial_MonoJ_NLO_Mphi-1750_Mchi-500_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-100': '/Axial_MonoJ_NLO_Mphi-2000_Mchi-100_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-10':  '/Axial_MonoJ_NLO_Mphi-2000_Mchi-10_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-150': '/Axial_MonoJ_NLO_Mphi-2000_Mchi-150_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-2000_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-200': '/Axial_MonoJ_NLO_Mphi-2000_Mchi-200_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-300': '/Axial_MonoJ_NLO_Mphi-2000_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2000_Mchi-400': '/Axial_MonoJ_NLO_Mphi-2000_Mchi-400_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2250_Mchi-150': '/Axial_MonoJ_NLO_Mphi-2250_Mchi-150_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2250_Mchi-1':   '/Axial_MonoJ_NLO_Mphi-2250_Mchi-1_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2250_Mchi-300': '/Axial_MonoJ_NLO_Mphi-2250_Mchi-300_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'Axial_MonoJ_NLO_Mphi-2250_Mchi-400': '/Axial_MonoJ_NLO_Mphi-2250_Mchi-400_gSM-0p25_gDM-1p0_13TeV-madgraph/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
}

if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
name = 'monoJet2016_Axial'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data') 
config.Data.publication = False
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased' #'FileBased'

config.Site.storageSite = 'T2_US_Wisconsin'
#config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

#listOfSamples = []

for sample in listOfSamples:  
  os.popen('cp run_102X_mc2016.py run_102X_mc2016_'+sample+'.py')
  with open('run_102X_mc2016_'+sample+'.py') as oldFile:
    newText = oldFile.read().replace('Ntuple_mc.root','MC_'+sample+'.root')
  with open('run_102X_mc2016_'+sample+'.py', 'w') as newFile:
    newFile.write(newText)

  config.General.requestName = 'job_'+sample
  
  config.JobType.psetName = 'run_102X_mc2016_'+sample+'.py'
  config.JobType.outputFiles = ['MC_'+sample+'.root']
  
  config.Data.inputDataset   = dataset[sample]
  config.Data.unitsPerJob = 10000
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/varuns/'+name
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
