import os

dataset = {
  'DY1JetsToLL_LHEZpT50-150' : '/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'DY1JetsToLL_LHEZpT150-250' : '/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
  'DY1JetsToLL_LHEZpT250-400' : '/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'DY1JetsToLL_LHEZpT400-inf' : '/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
   
  'DY2JetsToLL_M-50_LHEZpT_50-150': '/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'DY2JetsToLL_M-50_LHEZpT_150-250': '/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'DY2JetsToLL_M-50_LHEZpT_250-400': '/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'DY2JetsToLL_M-50_LHEZpT_400-inf': '/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
   
  'W1JetsToLNu_LHEWpT0-50': '/W1JetsToLNu_LHEWpT_0-50_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W1JetsToLNu_LHEWpT50-150': '/W1JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W1JetsToLNu_LHEWpT100-150': '/W1JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W1JetsToLNu_LHEWpT150-250': '/W1JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W1JetsToLNu_LHEWpT250-400': '/W1JetsToLNu_LHEWpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W1JetsToLNu_LHEWpT400-inf': '/W1JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
   
  'W2JetsToLNu_LHEWpT_0-50': '/W2JetsToLNu_LHEWpT_0-50_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W2JetsToLNu_LHEWpT_50-150': '/W2JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM',
  'W2JetsToLNu_LHEWpT_100-150': '/W2JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W2JetsToLNu_LHEWpT_150-250': '/W2JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W2JetsToLNu_LHEWpT_250-400': '/W2JetsToLNu_LHEWpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W2JetsToLNu_LHEWpT_400-inf': '/W2JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'W2JetsToLNu_LHEWpT400-inf': '/W2JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
   
   
  'Z1JetsToNuNu_LHEZpT50-150': '/Z1JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'Z1JetsToNuNu_LHEZpT150-250': '/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'Z1JetsToNuNu_LHEZpT250-400': '/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'Z1JetsToNuNu_LHEZpT400-inf': '/Z1JetsToNuNu_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
   
  'Z2JetsToNuNu_LHEZpT_50-150': '/Z2JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'Z2JetsToNuNu_LHEZpT_150-250': '/Z2JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'Z2JetsToNuNu_LHEZpT_250-400': '/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM',
  'Z2JetsToNuNu_LHEZpT_400-inf': '/Z2JetsToNuNU_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
     
}

#listOfSamples = ['ZJetsToNuNu_HT100-200', 'ZJetsToNuNu_HT200-400', 'ZJetsToNuNu_HT400-600', 'ZJetsToNuNu_HT600-800', 'ZJetsToNuNu_HT800-1200', 'ZJetsToNuNu_HT1200-2500', 'ZJetsToNuNu_HT2500-Inf']
 
#listOfSamples = ['DY1JetsToLL_LHEZpT50-150', 'DY1JetsToLL_LHEZpT150-250', 'DY1JetsToLL_LHEZpT250-400', 'DY1JetsToLL_LHEZpT400-inf']
#listOfSamples = ['DY2JetsToLL_M-50_LHEZpT_50-150', 'DY2JetsToLL_M-50_LHEZpT_150-250', 'DY2JetsToLL_M-50_LHEZpT_250-400', 'DY2JetsToLL_M-50_LHEZpT_400-inf']
#listOfSamples = ['Z1JetsToNuNu_LHEZpT50-150', 'Z1JetsToNuNu_LHEZpT150-250', 'Z1JetsToNuNu_LHEZpT250-400', Z1JetsToNuNu_LHEZpT400-inf']
#listOfSamples = ['Z2JetsToNuNu_LHEZpT_50-150', 'Z2JetsToNuNu_LHEZpT_150-250', 'Z2JetsToNuNu_LHEZpT_250-400', 'Z2JetsToNuNu_LHEZpT_400-inf']

listOfSamples = ['Z2JetsToNuNu_LHEZpT_400-inf']

DirName = 'MC2017_12Apr2018_2020Jan'
if __name__ == '__main__':
  from CRABAPI.RawCommand import crabCommand

def submit(config):
  res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
from multiprocessing import Process

config = config()
config.General.workArea = 'crab_'+DirName
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.inputFiles = ['Fall17_17Nov2017_V32_102X_MC.db']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data') 
config.Data.publication   = False
config.Data.inputDBS      = 'global'
config.Data.splitting     = 'EventAwareLumiBased' #'FileBased'
config.Data.unitsPerJob   = 10000
config.Data.totalUnits    = -1
config.Data.outLFNDirBase = '/store/user/varuns/'+DirName

config.Site.storageSite = 'T2_US_Wisconsin'
#config.Site.whitelist = ["T2_US_Wisconsin"]
#config.Site.blacklist = ['T2_CH_CERN']

for sample in listOfSamples:  
  os.popen('cp run_102X_mc2017.py run_102X_mc2017_'+sample+'.py')
  with open('run_102X_mc2017_'+sample+'.py') as oldFile:
    newText = oldFile.read().replace('Ntuple_mc.root','MC_'+sample+'.root')
  with open('run_102X_mc2017_'+sample+'.py', 'w') as newFile:
    newFile.write(newText)

  config.General.requestName = 'job_'+sample
  
  config.JobType.psetName = 'run_102X_mc2017_'+sample+'.py'
  config.JobType.outputFiles = ['MC_'+sample+'.root']
  
  config.Data.inputDataset  = dataset[sample]
 
  p = Process(target=submit, args=(config,))
  p.start()
  p.join()
