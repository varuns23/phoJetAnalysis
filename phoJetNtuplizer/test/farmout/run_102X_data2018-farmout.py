import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )
process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v12') # for ABC
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_v15') #for D

#jec from sqlite
process.load("CondCore.CondDB.CondDB_cfi")
from CondCore.CondDB.CondDB_cfi import *
process.CondDB.connect = 'sqlite:Autumn18_RunABCD_V19_DATA.db'
process.jec = cms.ESSource("PoolDBESSource",CondDB,
    toGet = cms.VPSet(
      cms.PSet(
	record = cms.string('JetCorrectionsRecord'),
	tag = cms.string('JetCorrectorParametersCollection_Autumn18_RunABCD_V19_DATA_AK4PFchs'),
	label = cms.untracked.string('AK4PFchs')
	)
      )
    )
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        'file:/hdfs/store/user/varuns/TEST-INPUTFILES/test-data2018-17Sep2018.root'
#        'file:/hdfs/store/data/Run2018D/EGamma/MINIAOD/22Jan2019-v2/120000/0F2DA3B1-BB43-9946-AD1F-0C1B9A0E4D07.root'
         $inputFileNames
    )
)

## needed to get lumi masking using farmout script
import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt').getVLuminosityBlockRange()

process.TFileService = cms.Service("TFileService", 
    #fileName = cms.string('Ntuple_data2018.root')
    fileName = cms.string('$outputFileName')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
    isData=True #(or False for MC),
    )

##Re-run ECAL bad calibration filter 
##https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#2017_data
process.load('RecoMET.METFilters.ecalBadCalibFilter_cfi')
baddetEcallist = cms.vuint32(
    [872439604,872422825,872420274,872423218,
    872423215,872416066,872435036,872439336,
    872420273,872436907,872420147,872439731,
    872436657,872420397,872439732,872439339,
    872439603,872422436,872439861,872437051,
    872437052,872420649,872422436,872421950,
    872437185,872422564,872421566,872421695,
    872421955,872421567,872437184,872421951,
    872421694,872437056,872437057,872437313])

process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
    "EcalBadCalibFilter",
    EcalRecHitSource = cms.InputTag("reducedEgamma:reducedEERecHits"),
    ecalMinEt        = cms.double(50.),
    baddetEcal       = baddetEcallist, 
    taggingMode      = cms.bool(True),
    debug            = cms.bool(False)
    )

##MET Corrections: Type-1
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )

## https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V2
from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
    era='2018-Prompt'
    )

## Apply JEC in AK4
## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
    postfix='UpdatedJECAK4',
    )
## AK4Jet Tag: selectedUpdatedPatJetsUpdatedJECAK4

from PhysicsTools.PatAlgos.tools.helpers import getPatAlgosToolsTask
task = getPatAlgosToolsTask(process)
process.endpath = cms.EndPath(task)

## Tau ID
from phoJetAnalysis.phoJetNtuplizer.runTauIdMVA import *
na = TauIDEmbedder(process, cms, # pass tour process object
     debug=True,
     toKeep = ["2017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
    )
na.runTauID()

### Analyzer Related
process.load("phoJetAnalysis.phoJetNtuplizer.phoJetNtuplizer_cfi")
process.phoJetNtuplizer.debug        = cms.bool(False);
process.phoJetNtuplizer.runak8Jets   = cms.bool(False);
process.phoJetNtuplizer.runJetWidthCalculator = cms.bool(True); # needed for monoZprime Analysis [Valid only if runJets is True]
process.phoJetNtuplizer.jetsAK4Token = cms.InputTag("selectedUpdatedPatJetsUpdatedJECAK4")

process.p = cms.Path(
    process.fullPatMetSequence *
    process.ecalBadCalibReducedMINIAODFilter *
    process.egammaPostRecoSeq *
    process.rerunMvaIsolationSequence *
    process.NewTauIDsEmbedded *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
