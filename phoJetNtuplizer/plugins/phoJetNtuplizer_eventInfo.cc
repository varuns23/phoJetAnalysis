#include "map"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t         run_;
Long64_t      event_;
Int_t         lumis_;
Int_t         nVtx_;
vector<float> vtxX_;
vector<float> vtxY_;
vector<float> vtxZ_;
vector<int>   vtxNtrks_;
vector<bool>  vtx_isFake_;
vector<int>   vtx_ndof_;
vector<float> vtx_rho_;
vector<bool>  isGoodVtx_;
float         rho_;
float         rhoCentral_;
ULong64_t     HLTPho_;
ULong64_t     HLTPhoIsPrescaled_;
vector<int>   HLTPhoPrescale_;

void phoJetNtuplizer::branchEventInfo(TTree* tree) {

  tree->Branch("run",                &run_);
  tree->Branch("event",              &event_);
  tree->Branch("lumis",              &lumis_);
  tree->Branch("nVtx",               &nVtx_);
  tree->Branch("vtxX",               &vtxX_);
  tree->Branch("vtxY",               &vtxY_);
  tree->Branch("vtxZ",               &vtxZ_);
  tree->Branch("vtxNtrks",           &vtxNtrks_);
  tree->Branch("vtx_isFake",         &vtx_isFake_);
  tree->Branch("vtx_ndof",           &vtx_ndof_);
  tree->Branch("vtx_rho",            &vtx_rho_);
  tree->Branch("isGoodVtx",          &isGoodVtx_);
  tree->Branch("rho",                &rho_);
  tree->Branch("rhoCentral",         &rhoCentral_);
  tree->Branch("HLTPho",             &HLTPho_);
  tree->Branch("HLTPhoIsPrescaled",  &HLTPhoIsPrescaled_);
  tree->Branch("HLTPhoPrescale",     &HLTPhoPrescale_); 

}

void phoJetNtuplizer::fillEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  initEventInfo();

  edm::Handle<double> rhoHandle;                                                                                      
  iEvent.getByToken(rhoToken_, rhoHandle);

  edm::Handle<double> rhoCentralHandle;
  iEvent.getByToken(rhoCentralToken_, rhoCentralHandle);

  // Run Event Lumi
  run_    = iEvent.id().run();
  event_  = iEvent.id().event();
  lumis_  = iEvent.luminosityBlock();
  rho_    = *(rhoHandle.product());
  if (rhoCentralHandle.isValid()) 
    rhoCentral_ = *(rhoCentralHandle.product());
  else 
    rhoCentral_ = -99.;


  // Vertex Information---
  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);

  if (!vtxHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no vertex info in event";
    return;
  }

  for(reco::VertexCollection::const_iterator iv = vtxHandle->begin(); iv != vtxHandle->end(); ++iv){
    vtxX_       .push_back(iv->x());
    vtxY_       .push_back(iv->y());
    vtxZ_       .push_back(iv->z());
    vtxNtrks_   .push_back(iv->nTracks());

    vtx_isFake_ .push_back(iv->isFake());
    vtx_ndof_   .push_back(iv->ndof());
    vtx_rho_    .push_back(iv->position().rho());


    bool isVtxGood_ = false;
    if (!iv->isFake() && iv->ndof() > 4. && fabs(iv->z()) <= 24. && fabs(iv->position().rho()) <= 2.) isVtxGood_ = true;
    isGoodVtx_  .push_back(isVtxGood_);
    nVtx_++;
  }

  edm::Handle<edm::TriggerResults> trgResultsHandle;
  iEvent.getByToken(trgResultsToken_, trgResultsHandle);
  
  bool cfg_changed = true;
  HLTConfigProvider hltCfg;
  hltCfg.init(iEvent.getRun(), iSetup, trgResultsProcess_, cfg_changed);

  const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);

  for (size_t i = 0; i < trgNames.size(); ++i) {
    const string &name = trgNames.triggerName(i);

    // HLT name => bit correspondence
    // Photon triggers
    int bitPho    = -1;
    if      (name.find("HLT_Photon22_v")                    != string::npos) bitPho =  0; //bit0(lowest)
    else if (name.find("HLT_Photon30_v")                    != string::npos) bitPho =  1; 
    else if (name.find("HLT_Photon36_v")                    != string::npos) bitPho =  2; 
    else if (name.find("HLT_Photon50_v")                    != string::npos) bitPho =  3; 
    else if (name.find("HLT_Photon75_v")                    != string::npos) bitPho =  4; 
    else if (name.find("HLT_Photon90_v")                    != string::npos) bitPho =  5; 
    else if (name.find("HLT_Photon120_v")                   != string::npos) bitPho =  6; 
    else if (name.find("HLT_Photon165_HE10_v")              != string::npos) bitPho =  7; 
    else if (name.find("HLT_Photon175_v")                   != string::npos) bitPho =  8; 
    else if (name.find("HLT_Photon250_NoHE_v")              != string::npos) bitPho =  9; 
    else if (name.find("HLT_Photon300_NoHE_v")              != string::npos) bitPho = 10; 
    else if (name.find("HLT_Photon500_v")                   != string::npos) bitPho = 11; 
    else if (name.find("HLT_Photon600_v")                   != string::npos) bitPho = 12;
    else if (name.find("HLT_Photon135_PFMET100_v")          != string::npos) bitPho = 13;

    // indicates prescaling and whether trigger was fired or not
    ULong64_t isPrescaled = (hltCfg.prescaleValue(0, name)!=1) ? 1 : 0;
    ULong64_t isFired     = (trgResultsHandle->accept(i)) ? 1 : 0;

    if (bitPho >= 0) {                                                                                                
      HLTPho_            |= (isFired << bitPho);
      HLTPhoIsPrescaled_ |= (isPrescaled << bitPho);
    }

    if      (name.find("HLT_Photon22_v")       != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon30_v")       != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon36_v")       != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon50_v")       != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon75_v")       != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon90_v")       != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon120_v")      != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon165_HE10_v") != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon175_v")      != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon250_NoHE_v") != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name)); 
    else if (name.find("HLT_Photon135_PFMET100_v") != string::npos) HLTPhoPrescale_.push_back(hltCfg.prescaleValue(0, name)); 
  }
  
}

void phoJetNtuplizer::initEventInfo(){
  nVtx_      = 0;
  run_       = -1;
  event_     = -1;
  lumis_     = -1;
  vtxX_      .clear();
  vtxY_      .clear();
  vtxZ_      .clear();
  vtxNtrks_  .clear();
  vtx_isFake_.clear();
  vtx_ndof_  .clear();
  vtx_rho_   .clear();
  isGoodVtx_ .clear();
  rho_       = -99;
  rhoCentral_= -99;

  HLTPho_             = 0;                    
  HLTPhoIsPrescaled_  = 0;                    
  HLTPhoPrescale_     .clear();

}
