import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v12')
 
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10 #1000

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/hdfs/store/user/varuns/monoZprime/TEST-INPUTFILES/test_mc_12Apr2018_94X.root'
    )
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('testOutput_mc.root')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

#https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes
#fix a bug in the ECAL-Tracker momentum combination when applying the scale and smearing
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
    runVID=False,
    era='2017-Nov17ReReco'  #era is new to select between 2016 / 2017,  it defaults to 2017
)
#a sequence egammaPostRecoSeq has now been created and should be added to your path, eg process.p=cms.Path(process.egammaPostRecoSeq)

#https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_for_2
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD (
    process,
    isData = False, # false for MC
#   fixEE2017 = True,
#   fixEE2017Params = {'userawPt': True, 'PtThreshold':50.0, 'MinEtaThreshold':2.65, 'MaxEtaThreshold': 3.139} , 
#   postfix = "ModifiedMET"
)

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
process.phoJetNtuplizer.debug       = cms.bool(False);
process.phoJetNtuplizer.isData      = cms.bool(False);  # False for MC
process.phoJetNtuplizer.runPhotons  = cms.bool(True);
process.phoJetNtuplizer.runJets     = cms.bool(True);
process.phoJetNtuplizer.runJetWidthCalculator = cms.bool(True); # needed for monoZprime Analysis [Valid only if runJets is True]
process.phoJetNtuplizer.runEle      = cms.bool(True);
process.phoJetNtuplizer.runMuon     = cms.bool(True);
process.phoJetNtuplizer.runTaus     = cms.bool(True);
process.phoJetNtuplizer.runMet      = cms.bool(True);
process.phoJetNtuplizer.runGenInfo  = cms.bool(True); # True for MC

process.p = cms.Path(
  #  process.fullPatMetSequenceModifiedMET *
    process.egammaPostRecoSeq *
    process.rerunMvaIsolationSequence *
    process.NewTauIDsEmbedded *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
