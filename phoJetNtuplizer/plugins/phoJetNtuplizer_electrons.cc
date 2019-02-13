#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t            nEle_;//
vector<float>    elePt_;
vector<float>    eleEta_;
vector<float>    elePhi_;
vector<float>    eleR9_;
vector<float>    eleR9Full5x5_;
vector<float>    eleEn_;
vector<int>      eleCharge_;
vector<int>      eleChargeConsistent_;
vector<float>    eleD0_;
vector<float>    eleDz_;
vector<float>    eleSIP_;

//vector<float>    eleUnCalibE_;
//vector<float>    eleUnCalibESigma_;
//vector<float>    eleCalibEecalonly_;
//vector<float>    eleCalibE_;
//vector<float>    eleCalibESigma_;
//vector<float>    eleCalibEt_;
//vector<float>    eleCalibEtSigma_;

//vector<float>    eleEnergyScale_;
//vector<float>    eleEnergySigma_;

vector<float>    eleSCRawEn_;
vector<float>    eleSCEn_;
vector<float>    eleSCEta_;
vector<float>    eleSCPhi_;
vector<float>    eleSCEtaWidth_;
vector<float>    eleSCPhiWidth_;

vector<float>    eleHoverE_;
vector<float>    eleEoverP_;
vector<float>    eleEoverPout_;
vector<float>    eleEoverPInv_;
vector<float>    eleBrem_;
vector<float>    eledEtaAtVtx_;
vector<float>    eledPhiAtVtx_;
vector<float>    eledEtaAtCalo_;
vector<float>    eledEtaseedAtVtx_;

vector<float>    eleSigmaIEtaIEtaFull5x5_;
vector<float>    eleSigmaIPhiIPhiFull5x5_;
vector<int>      eleConvVeto_;
vector<int>      eleMissHits_;

vector<float>    elePFChIso_;
vector<float>    elePFPhoIso_;
vector<float>    elePFNeuIso_;
vector<float>    elePFPUIso_;
vector<float>    elePFClusEcalIso_;
vector<float>    elePFClusHcalIso_;

vector<float>    eleHEEPID_;
vector<float>    eleMVAIsoID_;
vector<float>    eleMVAnoIsoID_;
vector<UShort_t> eleIDbit_; 
vector<UShort_t> eleMVAIsoIDbit_; 
vector<UShort_t> eleMVAnoIsoIDbit_;

vector<float>    eleTrkdxy_;
vector<float>    eleKFHits_;
vector<float>    eleKFChi2_;
vector<float>    eleGSFChi2_;

//vector<float>    eleScale_up_;
//vector<float>    eleScale_dn_;
//vector<float>    eleScale_stat_up_;
//vector<float>    eleScale_stat_dn_;
//vector<float>    eleScale_syst_up_;
//vector<float>    eleScale_syst_dn_;
//vector<float>    eleScale_gain_up_;
//vector<float>    eleScale_gain_dn_;
// 
//vector<float>    eleResol_up_;
//vector<float>    eleResol_dn_;
//vector<float>    eleResol_rho_up_;
//vector<float>    eleResol_rho_dn_;
//vector<float>    eleResol_phi_up_;
//vector<float>    eleResol_phi_dn_;

void phoJetNtuplizer::branchElectrons (TTree* tree){

  tree->Branch("nEle",                    &nEle_);
  tree->Branch("elePt",                   &elePt_);
  tree->Branch("eleEta",                  &eleEta_);
  tree->Branch("elePhi",                  &elePhi_);
  tree->Branch("eleR9",                   &eleR9_);
  tree->Branch("eleR9Full5x5",            &eleR9Full5x5_);
  tree->Branch("eleEn",                   &eleEn_);
  tree->Branch("eleCharge",               &eleCharge_);
  tree->Branch("eleChargeConsistent",     &eleChargeConsistent_);
  tree->Branch("eleD0",                   &eleD0_);
  tree->Branch("eleDz",                   &eleDz_);
  tree->Branch("eleSIP",                  &eleSIP_);

//  tree->Branch("eleUnCalibE",             &eleUnCalibE_);
//  tree->Branch("eleUnCalibESigma",        &eleUnCalibESigma_);
//  tree->Branch("eleCalibEecalonly",       &eleCalibEecalonly_);
//  tree->Branch("eleCalibE",               &eleCalibE_);
//  tree->Branch("eleCalibESigma",          &eleCalibESigma_);
//  tree->Branch("eleCalibEt",              &eleCalibEt_);
//  tree->Branch("eleCalibEtSigma",         &eleCalibEtSigma_);

//  tree->Branch("eleEnergyScale",          &eleEnergyScale_);
//  tree->Branch("eleEnergySigma",          &eleEnergySigma_);

  tree->Branch("eleSCRawEn",              &eleSCRawEn_);
  tree->Branch("eleSCEn",                 &eleSCEn_);
  tree->Branch("eleSCEta",                &eleSCEta_);
  tree->Branch("eleSCPhi",                &eleSCPhi_);
  tree->Branch("eleSCEtaWidth",           &eleSCEtaWidth_);
  tree->Branch("eleSCPhiWidth",           &eleSCPhiWidth_);

  tree->Branch("eleHoverE",               &eleHoverE_);
  tree->Branch("eleEoverP",               &eleEoverP_);
  tree->Branch("eleEoverPout",            &eleEoverPout_);
  tree->Branch("eleEoverPInv",            &eleEoverPInv_);
  tree->Branch("eleBrem",                 &eleBrem_);
  tree->Branch("eledEtaAtVtx",            &eledEtaAtVtx_);
  tree->Branch("eledPhiAtVtx",            &eledPhiAtVtx_);
  tree->Branch("eledEtaAtCalo",           &eledEtaAtCalo_);
  tree->Branch("eledEtaseedAtVtx",        &eledEtaseedAtVtx_);

  tree->Branch("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);
  tree->Branch("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5_);
  tree->Branch("eleConvVeto",             &eleConvVeto_);
  tree->Branch("eleMissHits",             &eleMissHits_);

  tree->Branch("elePFChIso",              &elePFChIso_);
  tree->Branch("elePFPhoIso",             &elePFPhoIso_);
  tree->Branch("elePFNeuIso",             &elePFNeuIso_);
  tree->Branch("elePFPUIso",              &elePFPUIso_);
  tree->Branch("elePFClusEcalIso",        &elePFClusEcalIso_);
  tree->Branch("elePFClusHcalIso",        &elePFClusHcalIso_);

  tree->Branch("eleHEEPID",               &eleHEEPID_);
  tree->Branch("eleMVAIsoID",             &eleMVAIsoID_);
  tree->Branch("eleMVAnoIsoID",           &eleMVAnoIsoID_); 
  tree->Branch("eleIDbit",                &eleIDbit_); 
  tree->Branch("eleMVAIsoIDbit",          &eleMVAIsoIDbit_); 
  tree->Branch("eleMVAnoIsoIDbit",        &eleMVAnoIsoIDbit_);

  tree->Branch("eleTrkdxy",               &eleTrkdxy_);
  tree->Branch("eleKFHits",               &eleKFHits_);
  tree->Branch("eleKFChi2",               &eleKFChi2_);
  tree->Branch("eleGSFChi2",              &eleGSFChi2_);

//  tree->Branch("eleScale_up",             &eleScale_up_);
//  tree->Branch("eleScale_dn",             &eleScale_dn_);
//  tree->Branch("eleScale_stat_up",        &eleScale_stat_up_);
//  tree->Branch("eleScale_stat_dn",        &eleScale_stat_dn_);
//  tree->Branch("eleScale_syst_up",        &eleScale_syst_up_);
//  tree->Branch("eleScale_syst_dn",        &eleScale_syst_dn_);
//  tree->Branch("eleScale_gain_up",        &eleScale_gain_up_);
//  tree->Branch("eleScale_gain_dn",        &eleScale_gain_dn_);

//  tree->Branch("eleResol_up",             &eleResol_up_);
//  tree->Branch("eleResol_dn",             &eleResol_dn_);
//  tree->Branch("eleResol_rho_up",         &eleResol_rho_up_);
//  tree->Branch("eleResol_rho_dn",         &eleResol_rho_dn_);
//  tree->Branch("eleResol_phi_up",         &eleResol_phi_up_);
//  tree->Branch("eleResol_phi_dn",         &eleResol_phi_dn_);
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

//    eleUnCalibE_         .push_back(iele->userFloat("ecalTrkEnergyPreCorr"));
//    eleUnCalibESigma_    .push_back(iele->userFloat("ecalTrkEnergyErrPreCorr"));
//    eleCalibEecalonly_   .push_back(iele->userFloat("ecalEnergyPostCorr"));
//    eleCalibE_           .push_back(iele->userFloat("ecalTrkEnergyPostCorr"));
//    eleCalibESigma_      .push_back(iele->userFloat("ecalTrkEnergyErrPostCorr"));
//    eleCalibEt_          .push_back(iele->pt()*iele->userFloat("ecalTrkEnergyPostCorr")/iele->p());
//    eleCalibEtSigma_     .push_back(iele->pt()*iele->userFloat("ecalTrkEnergyErrPostCorr")/iele->p());

//    eleEnergyScale_      .push_back(iele->userFloat("energyScaleValue"));
//    eleEnergySigma_      .push_back(iele->userFloat("energySigmaValue"));

    elePt_               .push_back(iele->pt());
    eleEta_              .push_back(iele->eta());
    elePhi_              .push_back(iele->phi());
    eleR9_               .push_back(iele->r9());
    eleR9Full5x5_        .push_back(iele->full5x5_r9());
    eleEn_               .push_back(iele->energy());
    eleCharge_           .push_back(iele->charge()); 
    eleChargeConsistent_ .push_back((Int_t)iele->isGsfCtfScPixChargeConsistent());
    eleD0_               .push_back(iele->gsfTrack()->dxy(ipv));
    eleDz_               .push_back(iele->gsfTrack()->dz(ipv));
    eleSIP_              .push_back(fabs(iele->dB(pat::Electron::PV3D))/iele->edB(pat::Electron::PV3D));

    eleSCRawEn_          .push_back(iele->superCluster()->rawEnergy());
    eleSCEn_             .push_back(iele->superCluster()->energy());
    eleSCEta_            .push_back(iele->superCluster()->eta());
    eleSCPhi_            .push_back(iele->superCluster()->phi());
    eleSCEtaWidth_       .push_back(iele->superCluster()->etaWidth());
    eleSCPhiWidth_       .push_back(iele->superCluster()->phiWidth());

    ///https://cmssdt.ce rn.ch/SDT/doxygen/CMSSW_7_2_2/doc/html/d8/dac/GsfElectron_8h_source.html
    eleHoverE_           .push_back(iele->hcalOverEcal());
    eleEoverP_           .push_back(iele->eSuperClusterOverP());
    eleEoverPout_        .push_back(iele->eEleClusterOverPout());
    eleBrem_             .push_back(iele->fbrem());
    eledEtaAtVtx_        .push_back(iele->deltaEtaSuperClusterTrackAtVtx());
    eledPhiAtVtx_        .push_back(iele->deltaPhiSuperClusterTrackAtVtx());
    eledEtaAtCalo_       .push_back(iele->deltaEtaSeedClusterTrackAtCalo());

    // (1/E - 1/p)
    if (iele->ecalEnergy() == 0)   eleEoverPInv_.push_back(1e30);
    else if (!std::isfinite(iele->ecalEnergy()))  eleEoverPInv_.push_back(1e30);
    else  eleEoverPInv_.push_back((1.0 - iele->eSuperClusterOverP())/iele->ecalEnergy());

    ///HEEP ID                
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
    elePFPUIso_         .push_back(pfIso.sumPUPt);
    elePFClusEcalIso_   .push_back(iele->ecalPFClusterIso());
    elePFClusHcalIso_   .push_back(iele->hcalPFClusterIso());

    eleHEEPID_          .push_back(iele->userFloat("heepTrkPtIso"));
    eleMVAIsoID_        .push_back(iele->userFloat("ElectronMVAEstimatorRun2Fall17IsoV1Values"));
    eleMVAnoIsoID_      .push_back(iele->userFloat("ElectronMVAEstimatorRun2Fall17NoIsoV1Values"));

    //VID decisions
    UShort_t tmpeleIDbit = 0;
    bool isPassLoose  = iele->electronID("cutBasedElectronID-Fall17-94X-V1-loose");
    if(isPassLoose) setbit(tmpeleIDbit, 0);
    bool isPassMedium  = iele->electronID("cutBasedElectronID-Fall17-94X-V1-medium");
    if(isPassMedium) setbit(tmpeleIDbit, 1);
    bool isPassTight  = iele->electronID("cutBasedElectronID-Fall17-94X-V1-tight");
    if(isPassTight) setbit(tmpeleIDbit, 2);
    bool isPassVeto  = iele->electronID("cutBasedElectronID-Fall17-94X-V1-veto");
    if(isPassVeto) setbit(tmpeleIDbit, 3);
    bool isPassHEEP  = iele->electronID("heepElectronID-HEEPV70");
    if(isPassHEEP) setbit(tmpeleIDbit, 4);

    eleIDbit_           .push_back(tmpeleIDbit);

    UShort_t tmpeleMVAIsoIDbit = 0;
    bool isPassIsoWP80  = iele->electronID("mvaEleID-Fall17-iso-V1-wp80");
    if(isPassIsoWP80) setbit(tmpeleMVAIsoIDbit, 0);
    bool isPassIsoWP90  = iele->electronID("mvaEleID-Fall17-iso-V1-wp90");
    if(isPassIsoWP90) setbit(tmpeleMVAIsoIDbit, 1);
    bool isPassIsoLoose  = iele->electronID("mvaEleID-Fall17-iso-V1-wpLoose");
    if(isPassIsoLoose) setbit(tmpeleMVAIsoIDbit, 2);

    eleMVAIsoIDbit_           .push_back(tmpeleMVAIsoIDbit);

    UShort_t tmpeleMVAnoIsoIDbit = 0;
    bool isPassWP80  = iele->electronID("mvaEleID-Fall17-noIso-V1-wp80");
    if(isPassWP80) setbit(tmpeleMVAnoIsoIDbit, 0);
    bool isPassWP90  = iele->electronID("mvaEleID-Fall17-noIso-V1-wp90");
    if(isPassWP90) setbit(tmpeleMVAnoIsoIDbit, 1);
    bool isPassWPloose  = iele->electronID("mvaEleID-Fall17-noIso-V1-wpLoose");
    if(isPassWPloose) setbit(tmpeleMVAnoIsoIDbit, 2);

    eleMVAnoIsoIDbit_           .push_back(tmpeleMVAnoIsoIDbit);


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


    // ECAL scale and smearing corrections
//    eleScale_up_          .push_back(iele->userFloat("energyScaleUp"));
//    eleScale_dn_          .push_back(iele->userFloat("energyScaleDown"));
//    eleScale_stat_up_     .push_back(iele->userFloat("energyScaleStatUp"));
//    eleScale_stat_dn_     .push_back(iele->userFloat("energyScaleStatDown"));
//    eleScale_syst_up_     .push_back(iele->userFloat("energyScaleSystUp"));
//    eleScale_syst_dn_     .push_back(iele->userFloat("energyScaleSystDown"));
//    eleScale_gain_up_     .push_back(iele->userFloat("energyScaleGainUp"));
//    eleScale_gain_dn_     .push_back(iele->userFloat("energyScaleGainDown"));

//    eleResol_up_          .push_back(iele->userFloat("energySigmaUp"));
//    eleResol_dn_          .push_back(iele->userFloat("energySigmaDown"));
//    eleResol_rho_up_      .push_back(iele->userFloat("energySigmaRhoUp"));
//    eleResol_rho_dn_      .push_back(iele->userFloat("energySigmaRhoDown"));
//    eleResol_phi_up_      .push_back(iele->userFloat("energySigmaPhiUp"));
//    eleResol_phi_dn_      .push_back(iele->userFloat("energySigmaPhiDown"));
    //xxxxx------- END of energy and scale systematics

    nEle_++;

  }
} //fillElectrons

void phoJetNtuplizer::initElectrons(){

  nEle_                    = 0;
  elePt_                   .clear();
  eleEta_                  .clear();
  elePhi_                  .clear();
  eleR9_                   .clear();
  eleR9Full5x5_            .clear();
  eleEn_                   .clear();
  eleCharge_               .clear();
  eleChargeConsistent_     .clear();
  eleD0_                   .clear();
  eleDz_                   .clear();
  eleSIP_                  .clear();

//  eleUnCalibE_             .clear();
//  eleUnCalibESigma_        .clear();
//  eleCalibEecalonly_       .clear();
//  eleCalibE_               .clear();
//  eleCalibESigma_          .clear();
//  eleCalibEt_              .clear();
//  eleCalibEtSigma_         .clear();

//  eleEnergyScale_          .clear();
//  eleEnergySigma_          .clear();

  eleSCRawEn_              .clear();
  eleSCEn_                 .clear();
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
  eleMVAIsoIDbit_          .clear(); 
  eleMVAnoIsoIDbit_        .clear(); 

  eleTrkdxy_               .clear();
  eleKFHits_               .clear();
  eleKFChi2_               .clear();
  eleGSFChi2_              .clear();

//  eleScale_up_             .clear();
//  eleScale_dn_             .clear();
//  eleScale_stat_up_        .clear();
//  eleScale_stat_dn_        .clear();
//  eleScale_syst_up_        .clear();
//  eleScale_syst_dn_        .clear();
//  eleScale_gain_up_        .clear();
//  eleScale_gain_dn_        .clear();

//  eleResol_up_             .clear();
//  eleResol_dn_             .clear();
//  eleResol_rho_up_         .clear();
//  eleResol_rho_dn_         .clear();
//  eleResol_phi_up_         .clear();
//  eleResol_phi_dn_         .clear(); 
}
