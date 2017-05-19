////#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"
////
////std::vector<bool>    phoconvInfo_;
////std::vector<double>  phoconvDist_;
////std::vector<double>  phoconvDCot_; 
////std::vector<double>  phoconvVtxChi2_;
////std::vector<int>     phoconvVtxNdof_;
////std::vector<double>  phoconvVertX_;
////std::vector<double>  phoconvVertY_;
////std::vector<double>  phoconvVertZ_;
////std::vector<double>  phoconvDxy_;
////std::vector<double>  phoconvDz_;
////std::vector<double>  phoconvLxy_;
////std::vector<double>  phoconvLz_;
////std::vector<double>  phoconvZofPVFromTracks_;
////
////
////void phoJetNtuplizer::branchConvPhotons(TTree* tree){
////
////  tree->Branch("phoconvInfo",             &phoconvInfo_);
////  tree->Branch("phoconvDist",             &phoconvDist_);
////  tree->Branch("phoconvDCot",             &phoconvDCot_);
////  tree->Branch("phoconvVtxChi2",          &phoconvVtxChi2_);
////  tree->Branch("phoconvVtxNdof",          &phoconvVtxNdof_);
////  tree->Branch("phoconvVertX",            &phoconvVertX_);
////  tree->Branch("phoconvVertY",            &phoconvVertY_);
////  tree->Branch("phoconvVertZ",            &phoconvVertZ_);
////  tree->Branch("phoconvDxy",              &phoconvDxy_);
////  tree->Branch("phoconvDz",               &phoconvDz_);
////  tree->Branch("phoconvLxy",              &phoconvLxy_);
////  tree->Branch("phoconvLz",               &phoconvLz_);
////  tree->Branch("phoconvZofPVFromTracks",  &phoconvZofPVFromTracks_);
////
////}
////
////void phoJetNtuplizer::fillConvPhotons(TTree* tree){
////
////  initConvPhotons();
////
////  edm::Handle<reco::ConversionCollection> conversions;
////  iEvent.getByToken(conversionsToken_, conversions);
////
////  // Get the beam spot
////  edm::Handle<reco::BeamSpot> theBeamSpot;
////  iEvent.getByToken(terminal activetheBeamSpot); 
////
////  beamSpot.SetXYZ(theBeamSpot->position().x(), theBeamSpot->position().y(), theBeamSpot->position().z());
////
////  reco::ConversionRefVector conversions(pho->conversions());
////
////  if(conversions.size() !=0){
////    reco::Conversion const& conversion(*conversions[0]);
////
////    if(conversion.nTracks()==2 && conversion.conversionVertex().isValid() && !conversion.conversionVertex().isFake()){
////
////      phoconvInfo_              .push_back(kTRUE);
////      phoconvDist_              .push_back(conversion.distOfMinimumApproach());
////      phoconvDCot_              .push_back(conversion.pairCotThetaSeparation());
////      phoconvVtxChi2_           .push_back(conversion.conversionVertex().chi2());
////      phoconvVtxNdof_           .push_back(conversion.conversionVertex().ndof());
////      phoconvVertX_             .push_back(conversion.conversionVertex().x());
////      phoconvVertY_             .push_back(conversion.conversionVertex().y());
////      phoconvVertZ_             .push_back(conversion.conversionVertex().z());
////      phoconvDxy_               .push_back(conversion.dxy(beamSpot));
////      phoconvDz_                .push_back(conversion.dz(beamSpot));
////      phoconvLxy_               .push_back(conversion.lxy(beamSpot));
////      phoconvLz_                .push_back(conversion.lz(beamSpot));
////      phoconvZofPVFromTracks_   .push_back(conversion.zOfPrimaryVertexFromTracks(beamSpot));
////
////    }
////  }
////}
////
////void phoJetNtuplizer::initConvPhotons(){
////
////  phoconvInfo_            .clear();
////  phoconvDist_            .clear();
////  phoconvDCot_            .clear(); 
////  phoconvVtxChi2_         .clear();
////  phoconvVtxNdof_         .clear();
////  phoconvVertX_           .clear();
////  phoconvVertY_           .clear();
////  phoconvVertZ_           .clear();
////  phoconvDxy_             .clear();
////  phoconvDz_              .clear();
////  phoconvLxy_             .clear();
////  phoconvLz_              .clear();
////  phoconvZofPVFromTracks_ .clear();
////
////}
////
