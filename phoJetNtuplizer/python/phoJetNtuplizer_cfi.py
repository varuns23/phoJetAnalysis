import FWCore.ParameterSet.Config as cms

phoJetNtuplizer = cms.EDAnalyzer('phoJetNtuplizer',
                                  debug                                = cms.bool(False),
                                  isData                               = cms.bool(True),
                                  runEventInfo                         = cms.bool(True),
                                  runPhotons                           = cms.bool(False),
                                  runJets                              = cms.bool(False),
                                  runEle                               = cms.bool(False),
                                  runMuon                              = cms.bool(False),
                                  runMet                               = cms.bool(False),
				  runGenInfo                           = cms.bool(False),

				  rhoToken                             = cms.InputTag("fixedGridRhoFastjetAll"),
				  rhoCentralToken                      = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
				  vtxToken                             = cms.InputTag("offlineSlimmedPrimaryVertices"),
				  vtxBSToken                           = cms.InputTag("offlinePrimaryVerticesWithBS"),

				  triggerEvent                         = cms.InputTag("selectedPatTrigger", "", ""),
				  triggerResults                       = cms.InputTag("TriggerResults", "", "HLT"),
				  #patTriggerResults                    = cms.InputTag("TriggerResults", "", "PAT"),
				  patTriggerResults                    = cms.InputTag("TriggerResults", "", "RECO"),

				  photonToken                          =  cms.InputTag("slimmedPhotons"),
				  calibPhotonToken                     =  cms.InputTag("calibratedPatPhotons"),

				  full5x5SigmaIEtaIEtaMapToken         = cms.InputTag("photonIDValueMapProducer:phoFull5x5SigmaIEtaIEta"),
				  phoChargedIsolationToken             = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"),
				  phoChargedWorstIsolationToken        = cms.InputTag("photonIDValueMapProducer:phoWorstChargedIsolation"),
				  phoNeutralHadronIsolationToken       = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"),
				  phoPhotonIsolationToken              = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation"),

				  phoLooseIdMapToken                   = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-loose"),
				  phoMediumIdMapToken                  = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium"),
				  phoTightIdMapToken                   = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-tight"),
				  phoMVAValuesMapToken                 = cms.InputTag("photonMVAValueMapProducer:PhotonMVAEstimatorRun2Spring16NonTrigV1Values"),

				  ebReducedRecHitCollection            = cms.InputTag("reducedEgamma","reducedEBRecHits"),
				  eeReducedRecHitCollection            = cms.InputTag("reducedEgamma","reducedEERecHits"),
				  esReducedRecHitCollection            = cms.InputTag("reducedEgamma","reducedESRecHits"),

				  jetsAK4Token                          = cms.InputTag("selectedUpdatedPatJetsUpdatedJEC"), 
				  
				  electronToken                        = cms.InputTag("slimmedElectrons"),
				  calibelectronToken                   = cms.InputTag("calibratedPatElectrons"),
				  packedPFCands                        = cms.InputTag("packedPFCandidates"),
				  
				  pfAllCandidate                       = cms.InputTag("particleFlow"),

				  eleVetoIdMap                         = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto"),
				  eleLooseIdMap                        = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
				  eleMediumIdMap                       = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium"),
				  eleTightIdMap                        = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight"),
				  eleHLTIdMap                          = cms.InputTag("egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1"),
				  eleHEEPIdMap                         = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV70"),
				  eleMVAValuesMap                      = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"),
				  elePFClusEcalIsoProducer             = cms.InputTag("electronEcalPFClusterIsolationProducer"),
				  elePFClusHcalIsoProducer             = cms.InputTag("electronHcalPFClusterIsolationProducer"),

				  muonToken                            = cms.InputTag("slimmedMuons"),

				  generatorToken                       = cms.InputTag("generator"),
				  lheEventToken                        = cms.InputTag("externalLHEProducer"),
				  pileupCollection                     = cms.InputTag("slimmedAddPileupInfo"),
				  genParticleToken                     = cms.InputTag("prunedGenParticles"),

                                  pfmetToken                           = cms.InputTag("slimmedMETs"),
				  BadChargedCandidateFilter            = cms.InputTag("BadChargedCandidateFilter"),
				  BadPFMuonFilter                      = cms.InputTag("BadPFMuonFilter"),
				  

)
