import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100 #1000

#jec from sqlite
process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
 connect = cms.string('sqlite:Summer16_23Sep2016V4_MC.db'),
 toGet = cms.VPSet(
 cms.PSet(
  record = cms.string('JetCorrectionsRecord'),
  tag = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016V4_MC_AK4PFchs'),
  label = cms.untracked.string('AK4PFchs')
 )))
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:QCD_Pt_600to800_fileMINIAOD.root'
    )
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('testOutput_MC.root')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

## EGamma 80X regression
## https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMRegression
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

### EGM scale and smearing correction
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
              calibratedPatElectrons = cms.PSet(
                        initialSeed  = cms.untracked.uint32(9876543),
			engineName   = cms.untracked.string('TRandom3'),
		),
	      calibratedPatPhotons   = cms.PSet( 
		        initialSeed  = cms.untracked.uint32(9876543),
			engineName   = cms.untracked.string('TRandom3'),
		),
	      phoJetNtuplizer        = cms.PSet(
		        initialSeed  = cms.untracked.uint32(567890),
			engineName   = cms.untracked.string('TRandom3')
		)
)
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')
# Set the lines below to True or False depending if you are correcting the scale (data) or smearing the resolution (MC) 
process.calibratedPatElectrons.isMC = cms.bool(True)
process.calibratedPatPhotons.isMC   = cms.bool(True)

## Update Jet Collection
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,        
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'UpdatedJEC',
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')
)    

## MET correction and uncertainties
##https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes#MET_Recipes
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=False
                           )
 
## MET Filters
process.load("RecoMET.METFilters.BadPFMuonFilter_cfi")
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
 
process.load("RecoMET.METFilters.BadChargedCandidateFilter_cfi")
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")



##VID 
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
switchOnVIDPhotonIdProducer(process, dataFormat)

# define which IDs we want to produce
eleid_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff']

#add them to the VID producer
for idmod in eleid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff',
	         'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff']

for idmod in phoid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

process.load("RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi")
process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
process.load("RecoEgamma.PhotonIdentification.PhotonIDValueMapProducer_cfi")
process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')
process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')

process.load("phoJetAnalysis.phoJetNtuplizer.phoJetNtuplizer_cfi")
process.phoJetNtuplizer.debug       = cms.bool(False);
process.phoJetNtuplizer.runPhotons  = cms.bool(True);
process.phoJetNtuplizer.runJets     = cms.bool(True);
process.phoJetNtuplizer.runEle      = cms.bool(True);
process.phoJetNtuplizer.runMuon     = cms.bool(True);
process.phoJetNtuplizer.runMet      = cms.bool(True);
process.phoJetNtuplizer.runGenInfo  = cms.bool(True);
process.phoJetNtuplizer.pfmetToken  = cms.InputTag("slimmedMETsMuEGClean", "", "Analyzer")
## the following line is only needed when you run on Feb 2017 re-miniAOD
process.phoJetNtuplizer.patTriggerResults=cms.InputTag("TriggerResults", "", "PAT")

process.p = cms.Path(
    process.BadPFMuonFilter *
    process.BadChargedCandidateFilter * 
    process.regressionApplication *
    process.calibratedPatElectrons *
    process.calibratedPatPhotons *
    process.egmGsfElectronIDSequence *
    process.egmPhotonIDSequence *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
