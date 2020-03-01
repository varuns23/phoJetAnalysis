import FWCore.ParameterSet.Config as cms

process = cms.Process("Analyzer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )
process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v12')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v10')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    'file:/hdfs/store/user/varuns/TEST-INPUTFILES/test-data2016C_MET_17Jul2018.root'
    )
)

process.TFileService = cms.Service("TFileService", 
    fileName = cms.string('Ntuple_data2016.root')
    )

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

## MET Corrections: Type-1
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )

## https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD (
    process,
    isData          = True, # false for MC
    )

## L1 Prefirring
## https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe
from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
    DataEra                      = cms.string("2016BtoH"), #2017BtoF
    UseJetEMPt                   = cms.bool(False),
    PrefiringRateSystematicUncty = cms.double(0.2),
    SkipWarnings                 = False
    )

## https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPostRecoRecipes#Running_on_2017_MiniAOD_V2
from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
    runVID = True, #saves CPU time by not needlessly re-running VID, if you want the Fall17V2 IDs, set this to True or remove (default is True)
    runEnergyCorrections=False, #no point in re-running them, they are already fine
    era    = '2016-Legacy'
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
    postfix='UpdatedJECAK4'
    )
## AK4Jet Tag: selectedUpdatedPatJetsUpdatedJECAK4

##--| ## Apply JEC in AK8
##--| from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
##--| updateJetCollection(
##--|     process,
##--|     jetSource = cms.InputTag('slimmedJetsAK8'),
##--|     pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
##--|     svSource = cms.InputTag('slimmedSecondaryVertices'),
##--|     rParam = 0.8,
##--|     jetCorrections = ('AK8PFPuppi', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
##--|     postfix='UpdatedJECAK8',
##--|     printWarning = True
##--|     )
##--| ## AK8Jet Tag: selectedUpdatedPatJetsUpdatedJECAK8
##--| 
##--| ## https://twiki.cern.ch/twiki/bin/viewauth/CMS/DeepAKXTagging#Option_1_Add_DeepAK8_to_slimmed
##--| from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
##--| from RecoBTag.MXNet.pfDeepBoostedJet_cff import _pfDeepBoostedJetTagsAll, _pfDeepBoostedJetTagsProbs, _pfDeepBoostedJetTagsMetaDiscrs, _pfMassDecorrelatedDeepBoostedJetTagsProbs, _pfMassDecorrelatedDeepBoostedJetTagsMetaDiscrs
##--| 
##--| from RecoBTag.MXNet.pfDeepBoostedJet_cff import pfDeepBoostedJetTags, pfMassDecorrelatedDeepBoostedJetTags
##--| from RecoBTag.MXNet.Parameters.V02.pfDeepBoostedJetPreprocessParams_cfi import pfDeepBoostedJetPreprocessParams as pfDeepBoostedJetPreprocessParamsV02
##--| from RecoBTag.MXNet.Parameters.V02.pfMassDecorrelatedDeepBoostedJetPreprocessParams_cfi import pfMassDecorrelatedDeepBoostedJetPreprocessParams as pfMassDecorrelatedDeepBoostedJetPreprocessParamsV02
##--| pfDeepBoostedJetTags.preprocessParams = pfDeepBoostedJetPreprocessParamsV02
##--| pfDeepBoostedJetTags.model_path = 'RecoBTag/Combined/data/DeepBoostedJet/V02/full/resnet-symbol.json'
##--| pfDeepBoostedJetTags.param_path = 'RecoBTag/Combined/data/DeepBoostedJet/V02/full/resnet-0000.params'
##--| pfMassDecorrelatedDeepBoostedJetTags.preprocessParams = pfMassDecorrelatedDeepBoostedJetPreprocessParamsV02
##--| pfMassDecorrelatedDeepBoostedJetTags.model_path = 'RecoBTag/Combined/data/DeepBoostedJet/V02/decorrelated/resnet-symbol.json'
##--| pfMassDecorrelatedDeepBoostedJetTags.param_path = 'RecoBTag/Combined/data/DeepBoostedJet/V02/decorrelated/resnet-0000.params'
##--| 
##--| updateJetCollection(
##--|     process,
##--|     jetSource = cms.InputTag('slimmedJetsAK8'),
##--|     pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
##--|     svSource = cms.InputTag('slimmedSecondaryVertices'),
##--|     rParam = 0.8,
##--|     jetCorrections = ('AK8PFPuppi', cms.vstring(['L2Relative', 'L3Absolute', 'L2L3Residual']), 'None'),
##--|     btagDiscriminators = _pfDeepBoostedJetTagsAll,
##--|     postfix='AK8WithDeepTags',
##--|     printWarning = True
##--|     )
##--| ## AK8Jet Tag: selectedUpdatedPatJetsAK8WithDeepTags

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
#process.phoJetNtuplizer.jetsAK8Token = cms.InputTag("selectedUpdatedPatJetsUpdatedJECAK8")
#process.phoJetNtuplizer.jetsAK8TagToken = cms.InputTag("selectedUpdatedPatJetsAK8WithDeepTags")

process.p = cms.Path(
    process.fullPatMetSequence *
    process.egammaPostRecoSeq *
    process.prefiringweight *
    process.rerunMvaIsolationSequence *
    process.NewTauIDsEmbedded *
    process.phoJetNtuplizer
    )

#print process.dumpPython()
