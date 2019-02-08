import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v8')
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v6')

#jec from sqlite
process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
    connect = cms.string('sqlite:Fall17_17Nov2017_V32_102X_DATA.db'),
    toGet = cms.VPSet(
      cms.PSet(
	record = cms.string('JetCorrectionsRecord'),
	tag = cms.string('JetCorrectorParametersCollection_Fall17_17Nov2017_V32_102X_DATA_AK4PFchs'),
	label = cms.untracked.string('AK4PFchs')
	)))
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1 #1000

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/hdfs/store/user/varuns/monoZprime/TEST-INPUTFILES/test_data_MET-2017B-31March18.root'
    )
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('Ntuple_data2018.root')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

##MET Corrections: Type-1
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )


## Tau ID
from phoJetAnalysis.phoJetNtuplizer.runTauIdMVA import *
na = TauIDEmbedder(process, cms, # pass tour process object
     debug=True,
     toKeep = ["2017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
    )
na.runTauID()


##L1 Prefirring
##https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe
from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
    DataEra = cms.string("2017BtoF"),
    UseJetEMPt = cms.bool(False),
    PrefiringRateSystematicUncty = cms.double(0.2),
    SkipWarnings = False)


#https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox
# For AK8 jets 


### Analyzer Related
process.load("phoJetAnalysis.phoJetNtuplizer.phoJetNtuplizer_cfi")
process.phoJetNtuplizer.debug        = cms.bool(False);
process.phoJetNtuplizer.is_Data      = cms.bool(True);  # False for MC
process.phoJetNtuplizer.runEventInfo = cms.bool(True);
process.phoJetNtuplizer.runPhotons   = cms.bool(True);
process.phoJetNtuplizer.runJets      = cms.bool(True);
process.phoJetNtuplizer.runJetWidthCalculator = cms.bool(True); # needed for monoZprime Analysis [Valid only if runJets is True]
process.phoJetNtuplizer.runEle       = cms.bool(True);
process.phoJetNtuplizer.runMuon      = cms.bool(True);
process.phoJetNtuplizer.runTaus      = cms.bool(True);
process.phoJetNtuplizer.runMet       = cms.bool(True);
process.phoJetNtuplizer.runGenInfo   = cms.bool(False); # True for MC
#process.phoJetNtuplizer.pfmetToken  = cms.InputTag("slimmedMETsModifiedMET")

process.p = cms.Path(
#    process.fullPatMetSequenceModifiedMET *
#    process.egammaPostRecoSeq *
#    process.ecalBadCalibReducedMINIAODFilter *
    process.prefiringweight *
    process.rerunMvaIsolationSequence *
    process.NewTauIDsEmbedded *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
