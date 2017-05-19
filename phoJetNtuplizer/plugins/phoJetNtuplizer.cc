// -*- C++ -*-
//
// Package:    phoJetAnalysis/phoJetNtuplizer
// Class:      phoJetNtuplizer
// 
/**\class phoJetNtuplizer phoJetNtuplizer.cc phoJetAnalysis/phoJetNtuplizer/plugins/phoJetNtuplizer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Varun Sharma
//         Created:  Fri, 10 Mar 2017 16:18:28 GMT
//
//
//
// class declaration
//
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit){
  UShort_t a = 1;
  x |= (a << bit);
}

phoJetNtuplizer::phoJetNtuplizer(const edm::ParameterSet& iConfig){
  //now do what ever initialization is needed

  debug_                = iConfig.getParameter<bool>("debug");
  isData_               = iConfig.getParameter<bool>("isData");

  runEventInfo_              = iConfig.getParameter<bool>("runEventInfo");
  rhoToken_                  = consumes<double>                       (iConfig.getParameter<InputTag>("rhoToken"));
  rhoCentralToken_           = consumes<double>                       (iConfig.getParameter<InputTag>("rhoCentralToken"));
  vtxToken_                  = consumes<reco::VertexCollection>       (iConfig.getParameter<InputTag>("vtxToken"));
  vtxBSToken_                = consumes<reco::VertexCollection>       (iConfig.getParameter<InputTag>("vtxBSToken"));

  //Trigger Info
  trgEventToken_             = consumes<trigger::TriggerEvent>                  (iConfig.getParameter<InputTag>("triggerEvent"));
  trgObjectsToken_           = consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerEvent"));
  trgResultsToken_           = consumes<edm::TriggerResults>                    (iConfig.getParameter<InputTag>("triggerResults"));
  trgResultsProcess_         =                                                   iConfig.getParameter<InputTag>("triggerResults").process();
  patTrgResultsToken_        = consumes<edm::TriggerResults>                    (iConfig.getParameter<InputTag>("patTriggerResults"));

  //Photon Info
  runPhotons_          = iConfig.getParameter<bool>("runPhotons");
  photonToken_         = consumes<edm::View<pat::Photon> > (iConfig.getParameter<edm::InputTag>("photonToken"));
  calibPhotonToken_    = consumes<edm::View<pat::Photon> > (iConfig.getParameter<edm::InputTag>("calibPhotonToken"));
  egmScaler_           = new EnergyScaleCorrection_class("EgammaAnalysis/ElectronTools/data/ScalesSmearings/Moriond17_23Jan_ele");
  //  recoPhotonToken_     = consumes<reco::PhotonCollection > (iConfig.getParameter<edm::InputTag>("recoPhotonToken"));

  //photon ID decision objects and isolations
  full5x5SigmaIEtaIEtaMapToken_        = consumes<edm::ValueMap<float> > (iConfig.getParameter<edm::InputTag>("full5x5SigmaIEtaIEtaMapToken"));

  phoChargedIsolationToken_        = consumes<edm::ValueMap<float> > (iConfig.getParameter<edm::InputTag>("phoChargedIsolationToken"));
  phoChargedWorstIsolationToken_   = consumes<edm::ValueMap<float> > (iConfig.getParameter<edm::InputTag>("phoChargedWorstIsolationToken"));
  phoNeutralHadronIsolationToken_  = consumes<edm::ValueMap<float> > (iConfig.getParameter<edm::InputTag>("phoNeutralHadronIsolationToken"));
  phoPhotonIsolationToken_         = consumes<edm::ValueMap<float> > (iConfig.getParameter<edm::InputTag>("phoPhotonIsolationToken"));

  phoLooseIdMapToken_   =  consumes<edm::ValueMap<bool> > (iConfig.getParameter<edm::InputTag>("phoLooseIdMapToken"));
  phoMediumIdMapToken_  =  consumes<edm::ValueMap<bool> > (iConfig.getParameter<edm::InputTag>("phoMediumIdMapToken"));
  phoTightIdMapToken_   =  consumes<edm::ValueMap<bool> > (iConfig.getParameter<edm::InputTag>("phoTightIdMapToken"));
  phoMVAValuesMapToken_ =  consumes<edm::ValueMap<float> > (iConfig.getParameter<edm::InputTag>("phoMVAValuesMapToken"));

  ebReducedRecHitCollection_   = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("ebReducedRecHitCollection"));
  eeReducedRecHitCollection_   = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("eeReducedRecHitCollection"));
  esReducedRecHitCollection_   = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("esReducedRecHitCollection"));

  //Jet Info
  runJets_                  =  iConfig.getParameter<bool>("runJets");
  jetsAK4Token_             =  consumes<View<pat::Jet> >              (iConfig.getParameter<InputTag>("jetsAK4Token"));

  //Electron Info
  runEle_                  =  iConfig.getParameter<bool>("runEle");
  electronToken_           =  consumes<View<pat::Electron> >          (iConfig.getParameter<InputTag>("electronToken"));
  calibelectronToken_      =  consumes<View<pat::Electron> >          (iConfig.getParameter<InputTag>("calibelectronToken"));
  packedPFCandsToken_      =  consumes<pat::PackedCandidateCollection>(iConfig.getParameter<InputTag>("packedPFCands"));
  //Electron ID and isolations
  eleVetoIdMapToken_       = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleVetoIdMap"));
  eleLooseIdMapToken_      = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"));
  eleMediumIdMapToken_     = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"));
  eleTightIdMapToken_      = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleTightIdMap"));
  eleHLTIdMapToken_        = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleHLTIdMap"));
  eleHEEPIdMapToken_       = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleHEEPIdMap"));
  eleMVAValuesMapToken_    = consumes<edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("eleMVAValuesMap"));
  elePFClusEcalIsoToken_   = mayConsume<edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("elePFClusEcalIsoProducer"));
  elePFClusHcalIsoToken_   = mayConsume<edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("elePFClusHcalIsoProducer"));

  pfAllCandidateToken_     =  consumes<reco::PFCandidateCollection>   (iConfig.getParameter<InputTag>("pfAllCandidate")); 

  //Muon Info
  runMuon_                 = iConfig.getParameter<bool>("runMuon");
  muonToken_               = consumes<View<pat::Muon> >(iConfig.getParameter<InputTag>("muonToken"));

  //MET Info
  runMet_               = iConfig.getParameter<bool>("runMet");
  pfmetToken_           = consumes<edm::View<pat::MET> > (iConfig.getParameter<edm::InputTag>("pfmetToken"));
  BadChCandFilterToken_ = consumes<bool>(iConfig.getParameter<edm::InputTag>("BadChargedCandidateFilter"));
  BadPFMuonFilterToken_ = consumes<bool>(iConfig.getParameter<edm::InputTag>("BadPFMuonFilter"));

  //Gen Particles
  runGenInfo_                = iConfig.getParameter<bool>("runGenInfo");
  generatorToken_            = consumes<GenEventInfoProduct>        (iConfig.getParameter<InputTag>("generatorToken"));
  lheEventToken_             = consumes<LHEEventProduct>            (iConfig.getParameter<InputTag>("lheEventToken"));
  puCollection_              = consumes<vector<PileupSummaryInfo> > (iConfig.getParameter<InputTag>("pileupCollection"));
  genParticlesToken_         = consumes<vector<reco::GenParticle> > (iConfig.getParameter<InputTag>("genParticleToken"));

  usesResource("TFileService");
  edm::Service<TFileService> fs;
  tree_    = fs->make<TTree>("eventTree", "event tree for analysis");
  //hEvents_ = fs->make<TH1F>("hEvents",    "total processed and skimmed events",   2,  0,   2);

  if(runEventInfo_) branchEventInfo (tree_);
  if(runPhotons_)   branchPhotons(tree_);
  if(runJets_)      branchJets(tree_);
  if(runEle_)       branchElectrons(tree_);
  if(runMuon_)      branchMuons(tree_);
  if(runMet_)       branchMet(tree_);
  if(runGenInfo_)   branchGenInfo(tree_);

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer constructor "<<std::endl;
}

phoJetNtuplizer::~phoJetNtuplizer(){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer destructor "<<std::endl;
}

//
// member functions
//

// ------------ method called for each event  ------------
void
phoJetNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  using namespace edm;

  if (runGenInfo_) {
    jetResolution_   = JME::JetResolution::get(iSetup, "AK4PFchs_pt");
    jetResolutionSF_ = JME::JetResolutionScaleFactor::get(iSetup, "AK4PFchs");
  }
  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);

  reco::Vertex vtx;                                                                                     

  // best-known primary vertex coordinates
  math::XYZPoint pv(0, 0, 0);
  for(reco::VertexCollection::const_iterator iv = vtxHandle->begin(); iv != vtxHandle->end(); ++iv){
    // replace isFake() for miniAOD since it requires tracks while miniAOD vertices don't have tracks:
    // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
    bool isFake = (iv->chi2() == 0 && iv->ndof() == 0);

    if (!isFake) {
      pv.SetXYZ(iv->x(), iv->y(), iv->z());
      vtx = *iv;   
      break;      
    }             
  }

  if(debug_) std::cout<< "<<DEBUG>>:: Inside analyze method "<<std::endl;

  if(runEventInfo_) fillEventInfo(iEvent, iSetup);
  if(runMet_)       fillMet(iEvent, iSetup);
  if(runPhotons_)   fillPhotons(iEvent, iSetup);
  if(runEle_)       fillElectrons(iEvent, iSetup, pv);
  if(runMuon_)      fillMuons(iEvent, pv, vtx);
  if(runGenInfo_)   fillGenInfo(iEvent);
  if(runJets_)      fillJets(iEvent, iSetup);

  tree_->Fill();
}

//define this as a plug-in
DEFINE_FWK_MODULE(phoJetNtuplizer);
