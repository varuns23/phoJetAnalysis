#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t            nEle_;//

vector<float>    eleE_;
vector<float>    elePt_;
vector<float>    eleEta_;
vector<float>    elePhi_;

vector<float>    eleR9Full5x5_;
vector<int>      eleCharge_;
vector<int>      eleChargeConsistent_;
vector<float>    eleD0_;
vector<float>    eleDz_;
vector<float>    eleSIP_;

vector<float>    eleUnCalibE_;
vector<float>    eleUnCalibESigma_;
vector<float>    eleCalibEecalonly_;
vector<float>    eleCalibE_;
vector<float>    eleCalibESigma_;
vector<float>    eleCalibEt_;
vector<float>    eleCalibEtSigma_;

vector<float>    eleEnergyScale_;
vector<float>    eleEnergySigma_;

vector<float>    eleSCRawE_;
vector<float>    eleSCE_;
vector<float>    eleSCEta_;
vector<float>    eleSCPhi_;
vector<float>    eleSCEtaWidth_;
vector<float>    eleSCPhiWidth_;

vector<float>    eleHoverE_;  //H/E
vector<float>    eleEoverP_;
vector<float>    eleEoverPout_;
vector<float>    eleEoverPInv_;  //(1/E-1/P)
vector<float>    eleBrem_;
vector<float>    eledEtaAtVtx_;   //dEtaIn
vector<float>    eledPhiAtVtx_;  //dPhiIn
vector<float>    eledEtaAtCalo_;
vector<float>    eledEtaseedAtVtx_; //dEtaSeed

vector<ULong64_t> eleFiredSingleTrgs_;
vector<ULong64_t> eleFiredDoubleTrgs_;
vector<ULong64_t> eleFiredL1Trgs_;

vector<float>    eleSigmaIEtaIEtaFull5x5_;
vector<float>    eleSigmaIPhiIPhiFull5x5_;
vector<int>      eleConvVeto_;
vector<int>      eleMissHits_;

vector<float>    elePFChIso_; //relIso
vector<float>    elePFPhoIso_; //relIso
vector<float>    elePFNeuIso_; //relIso
vector<float>    elePFPUIso_;
vector<float>    elePFClusEcalIso_;
vector<float>    elePFClusHcalIso_;

vector<float>    eleHEEPID_;
vector<float>    eleMVAIsoID_;
vector<float>    eleMVAnoIsoID_;
vector<UShort_t> eleIDbit_; 

vector<float>    eleTrkdxy_;
vector<float>    eleKFHits_;
vector<float>    eleKFChi2_;
vector<float>    eleGSFChi2_;

vector<float>    eleScale_up_;
vector<float>    eleScale_dn_;
vector<float>    eleScale_stat_up_;
vector<float>    eleScale_stat_dn_;
vector<float>    eleScale_syst_up_;
vector<float>    eleScale_syst_dn_;
vector<float>    eleScale_gain_up_;
vector<float>    eleScale_gain_dn_;

vector<float>    eleResol_up_;
vector<float>    eleResol_dn_;
vector<float>    eleResol_rho_up_;
vector<float>    eleResol_rho_dn_;
vector<float>    eleResol_phi_up_;
vector<float>    eleResol_phi_dn_;

void phoJetNtuplizer::branchElectrons (TTree* tree){

  tree->Branch("nEle",                    &nEle_);
  tree->Branch("elePt",                   &elePt_);
  tree->Branch("eleEta",                  &eleEta_);
  tree->Branch("elePhi",                  &elePhi_);
  tree->Branch("eleR9Full5x5",            &eleR9Full5x5_);
  tree->Branch("eleE",                    &eleE_);
  tree->Branch("eleCharge",               &eleCharge_);
  tree->Branch("eleChargeConsistent",     &eleChargeConsistent_);
  tree->Branch("eleD0",                   &eleD0_);
  tree->Branch("eleDz",                   &eleDz_);
  tree->Branch("eleSIP",                  &eleSIP_);

  tree->Branch("eleUnCalibE",             &eleUnCalibE_);
  tree->Branch("eleUnCalibESigma",        &eleUnCalibESigma_);
  tree->Branch("eleCalibEecalonly",       &eleCalibEecalonly_);
  tree->Branch("eleCalibE",               &eleCalibE_);
  tree->Branch("eleCalibESigma",          &eleCalibESigma_);
  tree->Branch("eleCalibEt",              &eleCalibEt_);
  tree->Branch("eleCalibEtSigma",         &eleCalibEtSigma_);

  tree->Branch("eleEnergyScale",          &eleEnergyScale_);
  tree->Branch("eleEnergySigma",          &eleEnergySigma_);

  tree->Branch("eleSCRawE",               &eleSCRawE_);
  tree->Branch("eleSCE",                  &eleSCE_);
  tree->Branch("eleSCEta",                &eleSCEta_);
  tree->Branch("eleSCPhi",                &eleSCPhi_);
  tree->Branch("eleSCEtaWidth",           &eleSCEtaWidth_);
  tree->Branch("eleSCPhiWidth",           &eleSCPhiWidth_);

  tree->Branch("eleHoverE",               &eleHoverE_);
  tree->Branch("eleEoverP",               &eleEoverP_);
  if(saveAll_){
    tree->Branch("eleEoverPout",            &eleEoverPout_);
  }
  tree->Branch("eleEoverPInv",            &eleEoverPInv_);
  tree->Branch("eleBrem",                 &eleBrem_);
  tree->Branch("eledEtaAtVtx",            &eledEtaAtVtx_);
  tree->Branch("eledPhiAtVtx",            &eledPhiAtVtx_);
  if(saveAll_){
    tree->Branch("eledEtaAtCalo",           &eledEtaAtCalo_);
  }
  tree->Branch("eledEtaseedAtVtx",        &eledEtaseedAtVtx_);

  tree->Branch("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);
  tree->Branch("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5_);
  tree->Branch("eleConvVeto",             &eleConvVeto_);
  tree->Branch("eleMissHits",             &eleMissHits_);

  tree->Branch("elePFChIso",              &elePFChIso_);
  tree->Branch("elePFPhoIso",             &elePFPhoIso_);
  tree->Branch("elePFNeuIso",             &elePFNeuIso_);
  if(saveAll_){
    tree->Branch("elePFPUIso",              &elePFPUIso_);
    tree->Branch("elePFClusEcalIso",        &elePFClusEcalIso_);
    tree->Branch("elePFClusHcalIso",        &elePFClusHcalIso_);
  }


  tree->Branch("eleFiredSingleTrgs",          &eleFiredSingleTrgs_);
  tree->Branch("eleFiredDoubleTrgs",          &eleFiredDoubleTrgs_);
  tree->Branch("eleFiredL1Trgs",              &eleFiredL1Trgs_);


  tree->Branch("eleHEEPID",               &eleHEEPID_);
  tree->Branch("eleMVAIsoID",             &eleMVAIsoID_);
  tree->Branch("eleMVAnoIsoID",           &eleMVAnoIsoID_); 
  tree->Branch("eleIDbit",                &eleIDbit_); 

  if(saveAll_){
    tree->Branch("eleTrkdxy",               &eleTrkdxy_);
    tree->Branch("eleKFHits",               &eleKFHits_);
    tree->Branch("eleKFChi2",               &eleKFChi2_);
    tree->Branch("eleGSFChi2",              &eleGSFChi2_);
  }

  tree->Branch("eleScale_up",             &eleScale_up_);
  tree->Branch("eleScale_dn",             &eleScale_dn_);
  tree->Branch("eleScale_stat_up",        &eleScale_stat_up_);
  tree->Branch("eleScale_stat_dn",        &eleScale_stat_dn_);
  tree->Branch("eleScale_syst_up",        &eleScale_syst_up_);
  tree->Branch("eleScale_syst_dn",        &eleScale_syst_dn_);
  tree->Branch("eleScale_gain_up",        &eleScale_gain_up_);
  tree->Branch("eleScale_gain_dn",        &eleScale_gain_dn_);

  tree->Branch("eleResol_up",             &eleResol_up_);
  tree->Branch("eleResol_dn",             &eleResol_dn_);
  tree->Branch("eleResol_rho_up",         &eleResol_rho_up_);
  tree->Branch("eleResol_rho_dn",         &eleResol_rho_dn_);
  tree->Branch("eleResol_phi_up",         &eleResol_phi_up_);
  tree->Branch("eleResol_phi_dn",         &eleResol_phi_dn_);
}

void phoJetNtuplizer::fillElectrons (const edm::Event& iEvent, const edm::EventSetup& iSetup, math::XYZPoint &ipv){

  initElectrons();

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  iEvent.getByToken(electronToken_, electronHandle);

  edm::Handle<pat::PackedCandidateCollection> pfcands;
  iEvent.getByToken(packedPFCandsToken_, pfcands);

  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);

  if (!electronHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Electrons in event";
    return;
  }

  for(edm::View<pat::Electron>::const_iterator iele = electronHandle->begin(); iele != electronHandle->end(); ++iele){

    eleUnCalibE_         .push_back(iele->userFloat("ecalTrkEnergyPreCorr"));
    eleUnCalibESigma_    .push_back(iele->userFloat("ecalTrkEnergyErrPreCorr"));
    eleCalibEecalonly_   .push_back(iele->userFloat("ecalEnergyPostCorr"));
    eleCalibE_           .push_back(iele->userFloat("ecalTrkEnergyPostCorr"));
    eleCalibESigma_      .push_back(iele->userFloat("ecalTrkEnergyErrPostCorr"));
    eleCalibEt_          .push_back(iele->pt()*iele->userFloat("ecalTrkEnergyPostCorr")/iele->p());
    eleCalibEtSigma_     .push_back(iele->pt()*iele->userFloat("ecalTrkEnergyErrPostCorr")/iele->p());

    eleEnergyScale_      .push_back(iele->userFloat("energyScaleValue"));
    eleEnergySigma_      .push_back(iele->userFloat("energySigmaValue"));

    elePt_               .push_back(iele->pt());
    eleEta_              .push_back(iele->eta());
    elePhi_              .push_back(iele->phi());
    eleR9Full5x5_        .push_back(iele->full5x5_r9());
    eleE_                .push_back(iele->energy());
    eleCharge_           .push_back(iele->charge()); 
    eleChargeConsistent_ .push_back((Int_t)iele->isGsfCtfScPixChargeConsistent());
    eleD0_               .push_back(iele->gsfTrack()->dxy(ipv));
    eleDz_               .push_back(iele->gsfTrack()->dz(ipv));
    eleSIP_              .push_back(fabs(iele->dB(pat::Electron::PV3D))/iele->edB(pat::Electron::PV3D));

    eleSCRawE_           .push_back(iele->superCluster()->rawEnergy());
    eleSCE_              .push_back(iele->superCluster()->energy());
    eleSCEta_            .push_back(iele->superCluster()->eta());
    eleSCPhi_            .push_back(iele->superCluster()->phi());
    eleSCEtaWidth_       .push_back(iele->superCluster()->etaWidth());
    eleSCPhiWidth_       .push_back(iele->superCluster()->phiWidth());

    eleHoverE_           .push_back(iele->hadronicOverEm());
    eleEoverP_           .push_back(iele->eSuperClusterOverP());
    if(saveAll_){
      eleEoverPout_        .push_back(iele->eEleClusterOverPout());
    }
    eleBrem_             .push_back(iele->fbrem());
    eledEtaAtVtx_        .push_back(iele->deltaEtaSuperClusterTrackAtVtx());
    eledPhiAtVtx_        .push_back(iele->deltaPhiSuperClusterTrackAtVtx());
    if(saveAll_){
      eledEtaAtCalo_       .push_back(iele->deltaEtaSeedClusterTrackAtCalo());
    }

    eleFiredSingleTrgs_ .push_back(matchSingleElectronTriggerFilters(iele->pt(), iele->eta(), iele->phi()));
    eleFiredDoubleTrgs_ .push_back(matchDoubleElectronTriggerFilters(iele->pt(), iele->eta(), iele->phi()));
    eleFiredL1Trgs_     .push_back(matchL1TriggerFilters(iele->pt(), iele->eta(), iele->phi()));


    // (1/E - 1/p)
    if (iele->ecalEnergy() == 0)   eleEoverPInv_.push_back(1e30);
    else if (!std::isfinite(iele->ecalEnergy()))  eleEoverPInv_.push_back(1e30);
    else  eleEoverPInv_.push_back((1.0 - iele->eSuperClusterOverP())/iele->ecalEnergy());

    double eledEtaseedAtVtx = iele->superCluster().isNonnull() && iele->superCluster()->seed().isNonnull() ? iele->deltaEtaSuperClusterTrackAtVtx() - iele->superCluster()->eta() + iele->superCluster()->seed()->eta() : std::numeric_limits<float>::max();

    eledEtaseedAtVtx_   .push_back(eledEtaseedAtVtx);

    eleSigmaIEtaIEtaFull5x5_    .push_back(iele->full5x5_sigmaIetaIeta());
    eleSigmaIPhiIPhiFull5x5_    .push_back(iele->full5x5_sigmaIphiIphi());
    eleConvVeto_                .push_back((Int_t)iele->passConversionVeto()); // ConvVtxFit || missHit == 0
    eleMissHits_                .push_back(iele->gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS));

    reco::GsfElectron::PflowIsolationVariables pfIso = iele->pfIsolationVariables();
    elePFChIso_         .push_back(pfIso.sumChargedHadronPt);
    elePFPhoIso_        .push_back(pfIso.sumPhotonEt);
    elePFNeuIso_        .push_back(pfIso.sumNeutralHadronEt);
    if(saveAll_){
      elePFPUIso_         .push_back(pfIso.sumPUPt);
      elePFClusEcalIso_   .push_back(iele->ecalPFClusterIso());
      elePFClusHcalIso_   .push_back(iele->hcalPFClusterIso());
    }

    eleHEEPID_          .push_back(iele->userFloat("heepTrkPtIso"));
    eleMVAIsoID_        .push_back(iele->userFloat("ElectronMVAEstimatorRun2Fall17IsoV2Values"));
    eleMVAnoIsoID_      .push_back(iele->userFloat("ElectronMVAEstimatorRun2Fall17NoIsoV2Values"));

    //VID decisions
    UShort_t tmpeleIDbit = 0;
    bool isPassLoose  = iele->electronID("cutBasedElectronID-Fall17-94X-V2-loose");
    if(isPassLoose) setbit(tmpeleIDbit, 0);
    bool isPassMedium  = iele->electronID("cutBasedElectronID-Fall17-94X-V2-medium");
    if(isPassMedium) setbit(tmpeleIDbit, 1);
    bool isPassTight  = iele->electronID("cutBasedElectronID-Fall17-94X-V2-tight");
    if(isPassTight) setbit(tmpeleIDbit, 2);
    bool isPassVeto  = iele->electronID("cutBasedElectronID-Fall17-94X-V2-veto");
    if(isPassVeto) setbit(tmpeleIDbit, 3);

    bool isPassIsoWP80  = iele->electronID("mvaEleID-Fall17-iso-V2-wp80");
    if(isPassIsoWP80) setbit(tmpeleIDbit, 4);
    bool isPassIsoWP90  = iele->electronID("mvaEleID-Fall17-iso-V2-wp90");
    if(isPassIsoWP90) setbit(tmpeleIDbit, 5);
    bool isPassIsoLoose  = iele->electronID("mvaEleID-Fall17-iso-V2-wpLoose");
    if(isPassIsoLoose) setbit(tmpeleIDbit, 6);

    bool isPassWP80  = iele->electronID("mvaEleID-Fall17-noIso-V2-wp80");
    if(isPassWP80) setbit(tmpeleIDbit, 7);
    bool isPassWP90  = iele->electronID("mvaEleID-Fall17-noIso-V2-wp90");
    if(isPassWP90) setbit(tmpeleIDbit, 8);
    bool isPassWPloose  = iele->electronID("mvaEleID-Fall17-noIso-V2-wpLoose");
    if(isPassWPloose) setbit(tmpeleIDbit, 9);

    bool isPassHEEP  = iele->electronID("heepElectronID-HEEPV70");
    if(isPassHEEP) setbit(tmpeleIDbit, 10);

    eleIDbit_           .push_back(tmpeleIDbit);


if(saveAll_){
    reco::GsfTrackRef gsfTrackRef = iele->gsfTrack();
    if (iele->gsfTrack().isNonnull()) {
      eleGSFChi2_.push_back(gsfTrackRef->normalizedChi2());
      if (vtxHandle->size() > 0)
	eleTrkdxy_.push_back(gsfTrackRef->dxy(vtxHandle->front().position()));
      else
	eleTrkdxy_.push_back(-999);
    } else {
      eleGSFChi2_.push_back(999.);
      eleTrkdxy_.push_back(-999);
    }     

    reco::TrackRef kfTrackRef = iele->closestCtfTrackRef();
    if (kfTrackRef.isAvailable() && kfTrackRef.isNonnull()) {
      eleKFHits_.push_back(kfTrackRef->hitPattern().trackerLayersWithMeasurement());
      eleKFChi2_.push_back(kfTrackRef->normalizedChi2());
    } else {
      eleKFHits_.push_back(-1.);
      eleKFChi2_.push_back(999.);
    }     
}

    // ECAL scale and smearing corrections
    eleScale_up_          .push_back(iele->userFloat("energyScaleUp"));
    eleScale_dn_          .push_back(iele->userFloat("energyScaleDown"));
    eleScale_stat_up_     .push_back(iele->userFloat("energyScaleStatUp"));
    eleScale_stat_dn_     .push_back(iele->userFloat("energyScaleStatDown"));
    eleScale_syst_up_     .push_back(iele->userFloat("energyScaleSystUp"));
    eleScale_syst_dn_     .push_back(iele->userFloat("energyScaleSystDown"));
    eleScale_gain_up_     .push_back(iele->userFloat("energyScaleGainUp"));
    eleScale_gain_dn_     .push_back(iele->userFloat("energyScaleGainDown"));

    eleResol_up_          .push_back(iele->userFloat("energySigmaUp"));
    eleResol_dn_          .push_back(iele->userFloat("energySigmaDown"));
    eleResol_rho_up_      .push_back(iele->userFloat("energySigmaRhoUp"));
    eleResol_rho_dn_      .push_back(iele->userFloat("energySigmaRhoDown"));
    eleResol_phi_up_      .push_back(iele->userFloat("energySigmaPhiUp"));
    eleResol_phi_dn_      .push_back(iele->userFloat("energySigmaPhiDown"));
    //xxxxx------- END of energy and scale systematics

    nEle_++;

  }
} //fillElectrons

void phoJetNtuplizer::initElectrons(){

  nEle_                    = 0;
  elePt_                   .clear();
  eleEta_                  .clear();
  elePhi_                  .clear();
  eleR9Full5x5_            .clear();
  eleE_                    .clear();
  eleCharge_               .clear();
  eleChargeConsistent_     .clear();
  eleD0_                   .clear();
  eleDz_                   .clear();
  eleSIP_                  .clear();

  eleUnCalibE_             .clear();
  eleUnCalibESigma_        .clear();
  eleCalibEecalonly_       .clear();
  eleCalibE_               .clear();
  eleCalibESigma_          .clear();
  eleCalibEt_              .clear();
  eleCalibEtSigma_         .clear();

  eleEnergyScale_          .clear();
  eleEnergySigma_          .clear();

  eleSCRawE_              .clear();
  eleSCE_                 .clear();
  eleSCEta_                .clear();
  eleSCPhi_                .clear();
  eleSCEtaWidth_           .clear();
  eleSCPhiWidth_           .clear();

  eleHoverE_               .clear();
  eleEoverP_               .clear();
  eleEoverPout_            .clear();
  eleEoverPInv_            .clear();
  eleBrem_                 .clear();
  eledEtaAtVtx_            .clear();
  eledPhiAtVtx_            .clear();
  eledEtaAtCalo_           .clear();
  eledEtaseedAtVtx_        .clear();

  eleSigmaIEtaIEtaFull5x5_ .clear();
  eleSigmaIPhiIPhiFull5x5_ .clear();
  eleConvVeto_             .clear();
  eleMissHits_             .clear();

  elePFChIso_              .clear();
  elePFPhoIso_             .clear();
  elePFNeuIso_             .clear();

  elePFPUIso_              .clear();
  elePFClusEcalIso_        .clear();
  elePFClusHcalIso_        .clear();

  eleHEEPID_               .clear();
  eleMVAIsoID_             .clear();
  eleMVAnoIsoID_           .clear();
  eleIDbit_                .clear(); 

  eleTrkdxy_               .clear();
  eleKFHits_               .clear();
  eleKFChi2_               .clear();
  eleGSFChi2_              .clear();

  eleScale_up_             .clear();
  eleScale_dn_             .clear();
  eleScale_stat_up_        .clear();
  eleScale_stat_dn_        .clear();
  eleScale_syst_up_        .clear();
  eleScale_syst_dn_        .clear();
  eleScale_gain_up_        .clear();
  eleScale_gain_dn_        .clear();

  eleResol_up_             .clear();
  eleResol_dn_             .clear();
  eleResol_rho_up_         .clear();
  eleResol_rho_dn_         .clear();
  eleResol_phi_up_         .clear();
  eleResol_phi_dn_         .clear(); 
  eleFiredSingleTrgs_         .clear();
  eleFiredDoubleTrgs_         .clear();
  eleFiredL1Trgs_             .clear();
}
