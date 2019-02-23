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

void setbit(ULong64_t& x, UShort_t bit){
  ULong64_t a = 1;
  x |= (a << bit);
}

phoJetNtuplizer::phoJetNtuplizer(const edm::ParameterSet& iConfig):
   hltPrescaleProvider_(iConfig, consumesCollector(), *this)
{
  //now do what ever initialization is needed

  debug_                = iConfig.getParameter<bool>("debug");
  is_Data_               = iConfig.getParameter<bool>("is_Data");

  runEventInfo_              = iConfig.getParameter<bool>("runEventInfo");
  rhoToken_                  = consumes<double>                       (iConfig.getParameter<InputTag>("rhoToken"));
  rhoCentralToken_           = consumes<double>                       (iConfig.getParameter<InputTag>("rhoCentralToken"));
  vtxToken_                  = consumes<reco::VertexCollection>       (iConfig.getParameter<InputTag>("vtxToken"));

  //Trigger Info
  trgResultsToken_           = consumes<edm::TriggerResults>          (iConfig.getParameter<InputTag>("triggerResults"));
  trgResultsProcess_         =                                         iConfig.getParameter<InputTag>("triggerResults").process();
  patTrgResultsToken_        = consumes<edm::TriggerResults>          (iConfig.getParameter<InputTag>("patTriggerResults"));
  recoTrgResultsToken_       = consumes<edm::TriggerResults>          (iConfig.getParameter<InputTag>("recoTriggerResults"));
  triggerObjectsLabel_       = consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerEvent"));
  //trigger filter realted 
  trgFilterDeltaPtCut_       = iConfig.getParameter<double>("trgFilterDeltaPtCut");
  trgFilterDeltaRCut_        = iConfig.getParameter<double>("trgFilterDeltaRCut");

  if(is_Data_){
    prefweight_token           = consumes< double >                     (edm::InputTag("prefiringweight:nonPrefiringProb"));
    prefweightup_token         = consumes< double >                     (edm::InputTag("prefiringweight:nonPrefiringProbUp"));
    prefweightdown_token       = consumes< double >                     (edm::InputTag("prefiringweight:nonPrefiringProbDown"));
  }

  //Photon Info
  runPhotons_          = iConfig.getParameter<bool>("runPhotons");
  photonToken_         = consumes<edm::View<pat::Photon> > (iConfig.getParameter<edm::InputTag>("photonToken"));

  ebReducedRecHitCollection_   = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("ebReducedRecHitCollection"));
  eeReducedRecHitCollection_   = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("eeReducedRecHitCollection"));
  esReducedRecHitCollection_   = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("esReducedRecHitCollection"));


 //Jet Info
  runJets_                  =  iConfig.getParameter<bool>("runJets");
  runJetWidthCalculator_    =  iConfig.getParameter<bool>("runJetWidthCalculator");
  jetsAK4Token_             =  consumes<View<pat::Jet> >              (iConfig.getParameter<InputTag>("jetsAK4Token"));

  //Electron Info
  runEle_                  =  iConfig.getParameter<bool>("runEle");
  electronToken_           =  consumes<View<pat::Electron> >          (iConfig.getParameter<InputTag>("electronToken"));
  packedPFCandsToken_      =  consumes<pat::PackedCandidateCollection>(iConfig.getParameter<InputTag>("packedPFCands"));
///--  pfAllCandidateToken_     =  consumes<reco::PFCandidateCollection>   (iConfig.getParameter<InputTag>("pfAllCandidate")); 

  //Muon Info
  runMuon_                 = iConfig.getParameter<bool>("runMuon");
  muonToken_               = consumes<View<pat::Muon> >(iConfig.getParameter<InputTag>("muonToken"));

  //Tau Info
  runTaus_                 = iConfig.getParameter<bool>("runTaus");
  //tausToken_               = consumes<View<pat::Tau> >(iConfig.getParameter<InputTag>("tausToken"));
  tausToken_               = consumes<vector<pat::Tau> >(iConfig.getParameter<InputTag>("tausToken"));

  //MET Info
  runMet_               = iConfig.getParameter<bool>("runMet");
  pfmetToken_           = consumes<edm::View<pat::MET> > (iConfig.getParameter<edm::InputTag>("pfmetToken"));

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
  if(runTaus_)      branchTaus(tree_);
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
  
  if(debug_) std::cout<< "<<DEBUG>>:: Inside analyze method "<<std::endl;

///--  if (runGenInfo_) {
///--    jetResolution_   = JME::JetResolution::get(iSetup, "AK4PFchs_pt");
///--    jetResolutionSF_ = JME::JetResolutionScaleFactor::get(iSetup, "AK4PFchs");
///--  }
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

  initTriggerFilters(iEvent);

  if(runEventInfo_) fillEventInfo(iEvent, iSetup);
  if(runMet_)       fillMet(iEvent, iSetup);
  if(runPhotons_)   fillPhotons(iEvent, iSetup);
  if(runEle_)       fillElectrons(iEvent, iSetup, pv);
  if(runMuon_)      fillMuons(iEvent, pv, vtx);
  if(runTaus_)      fillTaus(iEvent);
  if(runGenInfo_)   fillGenInfo(iEvent);
  if(runJets_)      fillJets(iEvent, iSetup);

  tree_->Fill();
}

//define this as a plug-in
DEFINE_FWK_MODULE(phoJetNtuplizer);
