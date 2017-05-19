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

vector<float>    eleCalibPt_;
vector<float>    eleCalibEn_;

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
vector<float>    eleIDMVA_;
vector<UShort_t> eleIDbit_; 

vector<float>  eleScale_stat_up_;
vector<float>  eleScale_stat_dn_;
vector<float>  eleScale_syst_up_;
vector<float>  eleScale_syst_dn_;
vector<float>  eleScale_gain_up_;
vector<float>  eleScale_gain_dn_;
vector<float>  eleResol_rho_up_;
vector<float>  eleResol_rho_dn_;
vector<float>  eleResol_phi_up_;
vector<float>  eleResol_phi_dn_;


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

  tree->Branch("eleCalibPt",              &eleCalibPt_);
  tree->Branch("eleCalibEn",              &eleCalibEn_);

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
  tree->Branch("eleIDMVA",                &eleIDMVA_);
  tree->Branch("eleIDbit",                &eleIDbit_); 

  tree->Branch("eleScale_stat_up",        &eleScale_stat_up_);
  tree->Branch("eleScale_stat_dn",        &eleScale_stat_dn_);
  tree->Branch("eleScale_syst_up",        &eleScale_syst_up_);
  tree->Branch("eleScale_syst_dn",        &eleScale_syst_dn_);
  tree->Branch("eleScale_gain_up",        &eleScale_gain_up_);
  tree->Branch("eleScale_gain_dn",        &eleScale_gain_dn_);
  tree->Branch("eleResol_rho_up",         &eleResol_rho_up_);
  tree->Branch("eleResol_rho_dn",         &eleResol_rho_dn_);
  tree->Branch("eleResol_phi_up",         &eleResol_phi_up_);
  tree->Branch("eleResol_phi_dn",         &eleResol_phi_dn_);

}

void phoJetNtuplizer::fillElectrons (const edm::Event& iEvent, const edm::EventSetup& iSetup, math::XYZPoint &ipv){

  initElectrons();

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  iEvent.getByToken(electronToken_, electronHandle);

  edm::Handle<edm::View<pat::Electron> > calibelectronHandle;
  iEvent.getByToken(calibelectronToken_, calibelectronHandle);

  edm::Handle<pat::PackedCandidateCollection> pfcands;
  iEvent.getByToken(packedPFCandsToken_, pfcands);

  if (!electronHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Electrons in event";
    return;
  }

  if (!calibelectronHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no calibrated pat::Electrons in event";
    return;
  }

  edm::Handle<edm::ValueMap<bool> >  veto_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  tight_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  hlt_id_decisions; 
  edm::Handle<edm::ValueMap<bool> >  heep_id_decisions;
  edm::Handle<edm::ValueMap<float> > eleMVAValues;
  edm::Handle<edm::ValueMap<float> > elePFClusEcalIsoValues;
  edm::Handle<edm::ValueMap<float> > elePFClusHcalIsoValues;

  iEvent.getByToken(eleVetoIdMapToken_ ,         veto_id_decisions);
  iEvent.getByToken(eleLooseIdMapToken_ ,        loose_id_decisions);
  iEvent.getByToken(eleMediumIdMapToken_,        medium_id_decisions);
  iEvent.getByToken(eleTightIdMapToken_,         tight_id_decisions);
  iEvent.getByToken(eleHLTIdMapToken_,           hlt_id_decisions);
  iEvent.getByToken(eleHEEPIdMapToken_ ,         heep_id_decisions);
  iEvent.getByToken(eleMVAValuesMapToken_,       eleMVAValues);
  iEvent.getByToken(elePFClusEcalIsoToken_,      elePFClusEcalIsoValues);
  iEvent.getByToken(elePFClusHcalIsoToken_,      elePFClusHcalIsoValues);

  for(edm::View<pat::Electron>::const_iterator iele = electronHandle->begin(); iele != electronHandle->end(); ++iele){

    Float_t corrPt = -1;      
    Float_t corrEn = -1;      
    for (edm::View<pat::Electron>::const_iterator iCele = calibelectronHandle->begin(); iCele != calibelectronHandle->end(); ++iCele) {
      if (fabs(iele->eta() - iCele->eta()) < 0.001 && fabs(iele->phi() - iCele->phi()) < 0.001) {
	corrPt = iCele->pt(); 
	corrEn = iCele->energy();
      }                       
    }//calibElectronHandle

    eleCalibPt_          .push_back(corrPt);
    eleCalibEn_          .push_back(corrEn);

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

    ///HEEP ID                
    double eledEtaseedAtVtx = iele->superCluster().isNonnull() && iele->superCluster()->seed().isNonnull() ? iele->deltaEtaSuperClusterTrackAtVtx() - iele->superCluster()->eta() + iele->superCluster()->seed()->eta() : std::numeric_limits<float>::max();

    eledEtaseedAtVtx_   .push_back(eledEtaseedAtVtx);

    // VID calculation of (1/E - 1/p)
    if (iele->ecalEnergy() == 0)   eleEoverPInv_.push_back(1e30);
    else if (!std::isfinite(iele->ecalEnergy()))  eleEoverPInv_.push_back(1e30);
    else  eleEoverPInv_.push_back((1.0 - iele->eSuperClusterOverP())/iele->ecalEnergy());

    eleSigmaIEtaIEtaFull5x5_    .push_back(iele->full5x5_sigmaIetaIeta());
    eleSigmaIPhiIPhiFull5x5_    .push_back(iele->full5x5_sigmaIphiIphi());
    eleConvVeto_                .push_back((Int_t)iele->passConversionVeto()); // ConvVtxFit || missHit == 0
    eleMissHits_                .push_back(iele->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS));

    reco::GsfElectron::PflowIsolationVariables pfIso = iele->pfIsolationVariables();
    elePFChIso_         .push_back(pfIso.sumChargedHadronPt);
    elePFPhoIso_        .push_back(pfIso.sumPhotonEt);
    elePFNeuIso_        .push_back(pfIso.sumNeutralHadronEt);
    elePFPUIso_         .push_back(pfIso.sumPUPt);
    elePFClusEcalIso_   .push_back(iele->ecalPFClusterIso());
    elePFClusHcalIso_   .push_back(iele->hcalPFClusterIso());

    //edm::Ptr<reco::GsfElectron> recoEl(iele);      
    //const auto el = electrons->ptrAt(nEle_);
    const auto el = electronHandle->ptrAt(nEle_);

    UShort_t tmpeleIDbit = 0;

    bool isPassVeto  = (*veto_id_decisions)[el];
    if (isPassVeto) setbit(tmpeleIDbit, 0);

    bool isPassLoose  = (*loose_id_decisions)[el];
    if (isPassLoose) setbit(tmpeleIDbit, 1);

    bool isPassMedium = (*medium_id_decisions)[el];
    if (isPassMedium) setbit(tmpeleIDbit, 2);

    bool isPassTight  = (*tight_id_decisions)[el];
    if (isPassTight) setbit(tmpeleIDbit, 3);

    bool isPassHEEP = (*heep_id_decisions)[el];
    if (isPassHEEP) setbit(tmpeleIDbit, 4);

    bool isPassHLT = (*hlt_id_decisions)[el];
    if (isPassHLT) setbit(tmpeleIDbit, 5);

    eleIDMVA_    .push_back((*eleMVAValues)[el]);
    eleIDbit_    .push_back(tmpeleIDbit);


    // systematic uncertainties for energy scale and resolution
    EcalClusterLazyTools lazyTool(iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
    
    DetId seedDetId = iele->superCluster()->seed()->seed();
    bool isBarrel = seedDetId.subdetId() == EcalBarrel;
    const EcalRecHitCollection * recHits = (isBarrel?lazyTool.getEcalEBRecHitCollection():lazyTool.getEcalEERecHitCollection());

    float et = iele->correctedEcalEnergy() / cosh(fabs(iele->eta()));

    EcalRecHitCollection::const_iterator seedRecHit = recHits->find(seedDetId);
    unsigned int gainSeedSC = 12;
    if (seedRecHit != recHits->end()) { 
      if(seedRecHit->checkFlag(EcalRecHit::kHasSwitchToGain6)) gainSeedSC = 6;
      if(seedRecHit->checkFlag(EcalRecHit::kHasSwitchToGain1)) gainSeedSC = 1;
    }
    int runNumber = iEvent.id().run();
    double scale  = egmScaler_->ScaleCorrection(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC);  
    //double smear  = egmScaler_->getSmearingSigma(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 0., 0.);

    float scale_stat_up = scale + egmScaler_->ScaleCorrectionUncertainty(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 1);
    float scale_stat_dn = scale - egmScaler_->ScaleCorrectionUncertainty(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 1);
    float scale_syst_up = scale + egmScaler_->ScaleCorrectionUncertainty(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 2);
    float scale_syst_dn = scale - egmScaler_->ScaleCorrectionUncertainty(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 2);
    float scale_gain_up = scale + egmScaler_->ScaleCorrectionUncertainty(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 4);
    float scale_gain_dn = scale - egmScaler_->ScaleCorrectionUncertainty(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 4);
    float resol_rho_up  = egmScaler_->getSmearingSigma(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 1., 0.);
    float resol_rho_dn  = egmScaler_->getSmearingSigma(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, -1., 0.);
    float resol_phi_up  = egmScaler_->getSmearingSigma(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 0., 1.);
    float resol_phi_dn = egmScaler_->getSmearingSigma(runNumber, iele->isEB(), iele->full5x5_r9(), fabs(iele->eta()), et, gainSeedSC, 0., -1.);   

    eleScale_stat_up_.push_back(scale_stat_up);
    eleScale_stat_dn_.push_back(scale_stat_dn);
    eleScale_syst_up_.push_back(scale_syst_up);
    eleScale_syst_dn_.push_back(scale_syst_dn);
    eleScale_gain_up_.push_back(scale_gain_up);
    eleScale_gain_dn_.push_back(scale_gain_dn);
    eleResol_rho_up_.push_back(resol_rho_up);
    eleResol_rho_dn_.push_back(resol_rho_dn);
    eleResol_phi_up_.push_back(resol_phi_up);
    eleResol_phi_dn_.push_back(resol_phi_dn);
    ///////////////////////////////// END of energy and scale systematics


    nEle_++;

  }



} //fillElectrons

void phoJetNtuplizer::initElectrons(){

  nEle_                     = 0;
  elePt_                    .clear();
  eleEta_                   .clear();
  elePhi_                   .clear();
  eleR9_                    .clear();
  eleR9Full5x5_             .clear();
  eleEn_                    .clear();
  eleCharge_                .clear();
  eleChargeConsistent_      .clear();
  eleD0_                    .clear();
  eleDz_                    .clear();
  eleSIP_                   .clear();

  eleCalibPt_               .clear();
  eleCalibEn_               .clear();

  eleSCRawEn_               .clear();
  eleSCEn_                  .clear();
  eleSCEta_                 .clear();
  eleSCPhi_                 .clear();
  eleSCEtaWidth_            .clear();
  eleSCPhiWidth_            .clear();

  eleHoverE_                .clear();
  eleEoverP_                .clear();
  eleEoverPout_             .clear();
  eleEoverPInv_             .clear();
  eleBrem_                  .clear();
  eledEtaAtVtx_             .clear();
  eledPhiAtVtx_             .clear();
  eledEtaAtCalo_            .clear();
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
  eleIDMVA_                .clear();
  eleIDbit_                .clear(); 

  eleScale_stat_up_        .clear();
  eleScale_stat_dn_        .clear();
  eleScale_syst_up_        .clear();
  eleScale_syst_dn_        .clear();
  eleScale_gain_up_        .clear();
  eleScale_gain_dn_        .clear();
  eleResol_rho_up_         .clear();
  eleResol_rho_dn_         .clear();
  eleResol_phi_up_         .clear();
  eleResol_phi_dn_         .clear();

}
