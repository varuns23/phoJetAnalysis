import FWCore.ParameterSet.Config as cms

phoJetNtuplizer = cms.EDAnalyzer('phoJetNtuplizer',
                                  debug                                = cms.bool(False),
                                  is_Data                              = cms.bool(True),
                                  runEventInfo                         = cms.bool(True),
                                  runPhotons                           = cms.bool(False),
                                  runJets                              = cms.bool(False),
                                  runJetWidthCalculator                = cms.bool(False),
                                  runEle                               = cms.bool(False),
                                  runMuon                              = cms.bool(False),
                                  runTaus                              = cms.bool(False),
                                  runMet                               = cms.bool(False),
				  runGenInfo                           = cms.bool(False),

				  rhoToken                             = cms.InputTag("fixedGridRhoFastjetAll"),
				  rhoCentralToken                      = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
				  vtxToken                             = cms.InputTag("offlineSlimmedPrimaryVertices"),

				  triggerResults                       = cms.InputTag("TriggerResults", "", "HLT"),
				  patTriggerResults                    = cms.InputTag("TriggerResults", "", "PAT"),
				  recoTriggerResults                   = cms.InputTag("TriggerResults", "", "RECO"),

				  photonToken                          =  cms.InputTag("slimmedPhotons"),

				  ebReducedRecHitCollection            = cms.InputTag("reducedEgamma","reducedEBRecHits"),
				  eeReducedRecHitCollection            = cms.InputTag("reducedEgamma","reducedEERecHits"),
				  esReducedRecHitCollection            = cms.InputTag("reducedEgamma","reducedESRecHits"),

                                  #jetsAK4Token                          = cms.InputTag("selectedUpdatedPatJetsUpdatedJEC"), 
				  jetsAK4Token                          = cms.InputTag("slimmedJets"), 
				  
				  electronToken                        = cms.InputTag("slimmedElectrons"),
				  packedPFCands                        = cms.InputTag("packedPFCandidates"),
				  
				  muonToken                            = cms.InputTag("slimmedMuons"),
				  
				  tausToken                            = cms.InputTag("NewTauIDsEmbedded"),
                                  
				  pfmetToken                           = cms.InputTag("slimmedMETs"),
				  
				  pfAllCandidate                       = cms.InputTag("particleFlow"),

				  elePFClusEcalIsoProducer             = cms.InputTag("electronEcalPFClusterIsolationProducer"),
				  elePFClusHcalIsoProducer             = cms.InputTag("electronHcalPFClusterIsolationProducer"),


				  generatorToken                       = cms.InputTag("generator"),
				  lheEventToken                        = cms.InputTag("externalLHEProducer"),
				  pileupCollection                     = cms.InputTag("slimmedAddPileupInfo"),
				  genParticleToken                     = cms.InputTag("prunedGenParticles"),

)
