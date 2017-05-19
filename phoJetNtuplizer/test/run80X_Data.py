import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016SeptRepro_v7')
 
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 100 #1000

#jec from sqlite
process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
 connect = cms.string('sqlite:Summer16_23Sep2016AllV4_DATA.db'),
 toGet = cms.VPSet(
 cms.PSet(
  record = cms.string('JetCorrectionsRecord'),
  tag = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK4PFchs'),
  label = cms.untracked.string('AK4PFchs')
 )))
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:Data_MINIAOD.root'
    )
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('testOutput_data.root')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

## EGamma 80X regression
## https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMRegression
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
              calibratedPatElectrons  = cms.PSet(
                        initialSeed = cms.untracked.uint32(9876543),
			engineName = cms.untracked.string('TRandom3'),
		),
	      calibratedPatPhotons    = cms.PSet( 
		        initialSeed = cms.untracked.uint32(9876543),
			engineName = cms.untracked.string('TRandom3'),
		)
)
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')
# Set the lines below to True or False depending if you are correcting the scale (data) or smearing the resolution (MC) 
process.calibratedPatElectrons.isMC = cms.bool(False)
process.calibratedPatPhotons.isMC   = cms.bool(False)

##MET Corrections: Type-1
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )

## Update Jet Collection
from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,        
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'UpdatedJEC',
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'None')
)    

## MET correction and uncertainties
##https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes#MET_Recipes
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=True                           
                           )
 
# Now you are creating the e/g corrected MET on top of the bad muon corrected MET (on re-miniaod)
from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG
corMETFromMuonAndEG(process,
                    pfCandCollection="", #not needed                        
                    electronCollection="slimmedElectronsBeforeGSFix",
                    photonCollection="slimmedPhotonsBeforeGSFix",
                    corElectronCollection="slimmedElectrons",
                    corPhotonCollection="slimmedPhotons",
                    allMETEGCorrected=True,
                    muCorrection=False,
                    eGCorrection=True,
                    runOnMiniAOD=True,
                    postfix="MuEGClean"
)
process.slimmedMETsMuEGClean = process.slimmedMETs.clone()
process.slimmedMETsMuEGClean.src = cms.InputTag("patPFMetT1MuEGClean")
process.slimmedMETsMuEGClean.rawVariation =  cms.InputTag("patPFMetRawMuEGClean")
process.slimmedMETsMuEGClean.t1Uncertainties = cms.InputTag("patPFMetT1%sMuEGClean")
del process.slimmedMETsMuEGClean.caloMET
 
process.egcorrMET = cms.Sequence(
        process.cleanedPhotonsMuEGClean+process.cleanedCorPhotonsMuEGClean+
        process.matchedPhotonsMuEGClean + process.matchedElectronsMuEGClean +
        process.corMETPhotonMuEGClean+process.corMETElectronMuEGClean+
        process.patPFMetT1MuEGClean+process.patPFMetRawMuEGClean+
        process.patPFMetT1SmearMuEGClean+process.patPFMetT1TxyMuEGClean+
        process.patPFMetTxyMuEGClean+process.patPFMetT1JetEnUpMuEGClean+
        process.patPFMetT1JetResUpMuEGClean+process.patPFMetT1SmearJetResUpMuEGClean+
        process.patPFMetT1ElectronEnUpMuEGClean+process.patPFMetT1PhotonEnUpMuEGClean+
        process.patPFMetT1MuonEnUpMuEGClean+process.patPFMetT1TauEnUpMuEGClean+
        process.patPFMetT1UnclusteredEnUpMuEGClean+process.patPFMetT1JetEnDownMuEGClean+
        process.patPFMetT1JetResDownMuEGClean+process.patPFMetT1SmearJetResDownMuEGClean+
        process.patPFMetT1ElectronEnDownMuEGClean+process.patPFMetT1PhotonEnDownMuEGClean+
        process.patPFMetT1MuonEnDownMuEGClean+process.patPFMetT1TauEnDownMuEGClean+
        process.patPFMetT1UnclusteredEnDownMuEGClean+process.slimmedMETsMuEGClean
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
process.phoJetNtuplizer.pfmetToken  = cms.InputTag("slimmedMETsMuEGClean", "", "Analyzer")
## the following line is only needed when you run on Feb 2017 re-miniAOD
process.phoJetNtuplizer.patTriggerResults=cms.InputTag("TriggerResults", "", "PAT")

process.p = cms.Path(
    process.fullPatMetSequence * # If you are re-correctign the default MET
    process.egcorrMET  *
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
