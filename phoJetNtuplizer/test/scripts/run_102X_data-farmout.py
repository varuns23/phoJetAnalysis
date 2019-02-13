import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v6')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v6')
 
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000 #1000

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring($inputFileNames)
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('$outputFileName')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

##MET Corrections: Type-1
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )

from phoJetAnalysis.phoJetNtuplizer.runTauIdMVA import *
na = TauIDEmbedder(process, cms, # pass tour process object
     debug=True,
     toKeep = ["2017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
    )
na.runTauID()

#https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox
# For AK8 jets 


### Analyzer Related
process.load("phoJetAnalysis.phoJetNtuplizer.phoJetNtuplizer_cfi")
process.phoJetNtuplizer.debug        = cms.bool(False);
process.phoJetNtuplizer.is_Data      = cms.bool(True);  # False for MC
process.phoJetNtuplizer.runEventInfo = cms.bool(True);
process.phoJetNtuplizer.runPhotons   = cms.bool(True);
process.phoJetNtuplizer.runJets      = cms.bool(True);
process.phoJetNtuplizer.runJetWidthCalculator = cms.bool(False); # needed for monoZprime Analysis [Valid only if runJets is True]
process.phoJetNtuplizer.runEle       = cms.bool(True);
process.phoJetNtuplizer.runMuon      = cms.bool(True);
process.phoJetNtuplizer.runTaus      = cms.bool(True);
process.phoJetNtuplizer.runMet       = cms.bool(True);
process.phoJetNtuplizer.runGenInfo   = cms.bool(False); # True for MC
#process.phoJetNtuplizer.pfmetToken  = cms.InputTag("slimmedMETsModifiedMET")

process.p = cms.Path(
#    process.fullPatMetSequenceModifiedMET *
#    process.egammaPostRecoSeq *
    process.rerunMvaIsolationSequence *
    process.NewTauIDsEmbedded *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
