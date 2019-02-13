import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_mc2017_realistic_v6')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v14')

#jec from sqlite
process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
    connect = cms.string('sqlite:Fall17_17Nov2017_V32_102X_MC.db'),
    toGet = cms.VPSet(
      cms.PSet(
	record = cms.string('JetCorrectionsRecord'),
	tag = cms.string('JetCorrectorParametersCollection_Fall17_17Nov2017_V32_102X_MC_AK4PFchs'),
	label = cms.untracked.string('AK4PFchs')
	)))
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1 #1000

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:/hdfs/store/user/varuns/monoZprime/TEST-INPUTFILES/test_mc_12Apr2018_94X.root'
        'file:test-mc12Apr18.root'
    )
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('Ntuple_mc.root')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

##Updating Jet collection for DeepCSV tagger
# https://twiki.cern.ch/twiki/bin/view/CMS/DeepJet#94X_installation_recipe_X_10
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
    btagDiscriminators = [
    'pfDeepFlavourJetTags:probb',
    'pfDeepFlavourJetTags:probbb',
    'pfDeepFlavourJetTags:problepb',
    'pfDeepFlavourJetTags:probc',
    'pfDeepFlavourJetTags:probuds',
    'pfDeepFlavourJetTags:probg'
    ],
    postfix='NewDFTraining'
    )

## Tau ID
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
    process.rerunMvaIsolationSequence *
    process.NewTauIDsEmbedded *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
