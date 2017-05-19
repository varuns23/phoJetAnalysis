#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t            nMu_;
vector<float>    muPt_;
vector<float>    muEn_;
vector<float>    muEta_;
vector<float>    muPhi_;
vector<int>      muCharge_;
vector<int>      muType_;
vector<UShort_t> muIDbit_;
vector<float>    muD0_;
vector<float>    muDz_;
vector<float>    muSIP_;
vector<float>    muChi2NDF_;
vector<float>    muInnerD0_;
vector<float>    muInnerDz_;
vector<int>      muTrkLayers_;
vector<int>      muPixelLayers_;
vector<int>      muPixelHits_;
vector<int>      muMuonHits_;
vector<int>      muStations_;
vector<int>      muMatches_;
vector<int>      muTrkQuality_;
vector<float>    muIsoTrk_;
vector<float>    muPFChIso_;
vector<float>    muPFPhoIso_;
vector<float>    muPFNeuIso_;
vector<float>    muPFPUIso_;
vector<float>    muInnervalidFraction_;
vector<float>    musegmentCompatibility_;
vector<float>    muchi2LocalPosition_;
vector<float>    mutrkKink_;
vector<float>    muBestTrkPtError_;
vector<float>    muBestTrkPt_;

void phoJetNtuplizer::branchMuons(TTree* tree){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::branchMuons -->BEGIN<-- "<<std::endl;

  tree->Branch("nMu",                    &nMu_);
  tree->Branch("muPt",                   &muPt_);
  tree->Branch("muEn",                   &muEn_);
  tree->Branch("muEta",                  &muEta_);
  tree->Branch("muPhi",                  &muPhi_);
  tree->Branch("muCharge",               &muCharge_);
  tree->Branch("muType",                 &muType_);
  tree->Branch("muIDbit",                &muIDbit_);
  tree->Branch("muD0",                   &muD0_);
  tree->Branch("muDz",                   &muDz_);
  tree->Branch("muSIP",                  &muSIP_);
  tree->Branch("muChi2NDF",              &muChi2NDF_);
  tree->Branch("muInnerD0",              &muInnerD0_);
  tree->Branch("muInnerDz",              &muInnerDz_);
  tree->Branch("muTrkLayers",            &muTrkLayers_);
  tree->Branch("muPixelLayers",          &muPixelLayers_);
  tree->Branch("muPixelHits",            &muPixelHits_);
  tree->Branch("muMuonHits",             &muMuonHits_);
  tree->Branch("muStations",             &muStations_);
  tree->Branch("muMatches",              &muMatches_);
  tree->Branch("muTrkQuality",           &muTrkQuality_);
  tree->Branch("muIsoTrk",               &muIsoTrk_);
  tree->Branch("muPFChIso",              &muPFChIso_);
  tree->Branch("muPFPhoIso",             &muPFPhoIso_);
  tree->Branch("muPFNeuIso",             &muPFNeuIso_);
  tree->Branch("muPFPUIso",              &muPFPUIso_);
  tree->Branch("muInnervalidFraction",   &muInnervalidFraction_);
  tree->Branch("musegmentCompatibility", &musegmentCompatibility_);
  tree->Branch("muchi2LocalPosition",    &muchi2LocalPosition_);
  tree->Branch("mutrkKink",              &mutrkKink_);
  tree->Branch("muBestTrkPtError",       &muBestTrkPtError_);
  tree->Branch("muBestTrkPt",            &muBestTrkPt_);

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::branchMuons -->END<--"<<std::endl;
}                                                                                                                                                                                    

void phoJetNtuplizer::fillMuons(const edm::Event& iEvent, math::XYZPoint& ipv, reco::Vertex ivtx){
  
  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillMuons -->BEGIN<-- "<<std::endl;
  
  initMuons();

  edm::Handle<edm::View<pat::Muon> > muonHandle;
  iEvent.getByToken(muonToken_, muonHandle);

  edm::Handle<pat::PackedCandidateCollection> pfcands;
  iEvent.getByToken(packedPFCandsToken_, pfcands);

  if (!muonHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Muons in event";
    return;
  }

for (edm::View<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu){

    if (iMu->pt() < 3) continue;
    if (! (iMu->isPFMuon() || iMu->isGlobalMuon() || iMu->isTrackerMuon())) continue;
                               
    muPt_    .push_back(iMu->pt());                                                 
    muEn_    .push_back(iMu->energy());                                             
    muEta_   .push_back(iMu->eta());                                                
    muPhi_   .push_back(iMu->phi());                                                
    muCharge_.push_back(iMu->charge());                                             
    muType_  .push_back(iMu->type());                                               
    muD0_    .push_back(iMu->muonBestTrack()->dxy(ipv));                             
    muDz_    .push_back(iMu->muonBestTrack()->dz(ipv));                              
    muSIP_   .push_back(fabs(iMu->dB(pat::Muon::PV3D))/iMu->edB(pat::Muon::PV3D));  
                               
    UShort_t tmpmuIDbit = 0;   
                               
    if (iMu->isLooseMuon())     setbit(tmpmuIDbit, 0);
    if (iMu->isMediumMuon())    setbit(tmpmuIDbit, 1);
    if (iMu->isTightMuon(ivtx))  setbit(tmpmuIDbit, 2);
    if (iMu->isSoftMuon(ivtx))   setbit(tmpmuIDbit, 3);
    if (iMu->isHighPtMuon(ivtx)) setbit(tmpmuIDbit, 4);
    muIDbit_.push_back(tmpmuIDbit);

    muBestTrkPtError_        .push_back(iMu->muonBestTrack()->ptError());
    muBestTrkPt_             .push_back(iMu->muonBestTrack()->pt());
    musegmentCompatibility_  .push_back(iMu->segmentCompatibility());
    muchi2LocalPosition_     .push_back(iMu->combinedQuality().chi2LocalPosition);
    mutrkKink_               .push_back(iMu->combinedQuality().trkKink);

    const reco::TrackRef glbmu = iMu->globalTrack();
    const reco::TrackRef innmu = iMu->innerTrack();

    if (glbmu.isNull()) {
      muChi2NDF_ .push_back(-99.);                                                  
      muMuonHits_.push_back(-99);                                                   
    } else {                   
      muChi2NDF_.push_back(glbmu->normalizedChi2());                                
      muMuonHits_.push_back(glbmu->hitPattern().numberOfValidMuonHits());           
    }                          
    if (innmu.isNull()) {                                
      muInnerD0_     .push_back(-99.);                   
      muInnerDz_     .push_back(-99.);                   
      muTrkLayers_   .push_back(-99);                    
      muPixelLayers_ .push_back(-99);                    
      muPixelHits_   .push_back(-99);                    
      muTrkQuality_  .push_back(-99);                    
  
      muInnervalidFraction_ .push_back(-99);             
    } else {                                             
      muInnerD0_     .push_back(innmu->dxy(ipv));         
      muInnerDz_     .push_back(innmu->dz(ipv));          
      muTrkLayers_   .push_back(innmu->hitPattern().trackerLayersWithMeasurement());
      muPixelLayers_ .push_back(innmu->hitPattern().pixelLayersWithMeasurement());
      muPixelHits_   .push_back(innmu->hitPattern().numberOfValidPixelHits());
      muTrkQuality_  .push_back(innmu->quality(reco::TrackBase::highPurity));
  
      muInnervalidFraction_ .push_back(innmu->validFraction());     
    }     
  
    muStations_ .push_back(iMu->numberOfMatchedStations());         
    muMatches_  .push_back(iMu->numberOfMatches());      
    muIsoTrk_   .push_back(iMu->trackIso());             
    muPFChIso_  .push_back(iMu->pfIsolationR04().sumChargedHadronPt);
    muPFPhoIso_ .push_back(iMu->pfIsolationR04().sumPhotonEt);      
    muPFNeuIso_ .push_back(iMu->pfIsolationR04().sumNeutralHadronEt);
    muPFPUIso_  .push_back(iMu->pfIsolationR04().sumPUPt);
  
    nMu_++;
  }

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillMuons -->END<--"<<std::endl;
}


void phoJetNtuplizer::initMuons(){

  nMu_                    = 0;
  muPt_                   .clear();
  muEn_                   .clear();
  muEta_                  .clear();
  muPhi_                  .clear();
  muCharge_               .clear();
  muType_                 .clear();
  muIDbit_                .clear();
  muD0_                   .clear();
  muDz_                   .clear();
  muSIP_                  .clear();
  muChi2NDF_              .clear();
  muInnerD0_              .clear();
  muInnerDz_              .clear();
  muTrkLayers_            .clear();
  muPixelLayers_          .clear();
  muPixelHits_            .clear();
  muMuonHits_             .clear();
  muStations_             .clear();
  muMatches_              .clear();
  muTrkQuality_           .clear();
  muIsoTrk_               .clear();
  muPFChIso_              .clear();
  muPFPhoIso_             .clear();
  muPFNeuIso_             .clear();
  muPFPUIso_              .clear();
  muInnervalidFraction_   .clear();
  musegmentCompatibility_ .clear();
  muchi2LocalPosition_    .clear();
  mutrkKink_              .clear();
  muBestTrkPtError_       .clear();
  muBestTrkPt_            .clear();

}



