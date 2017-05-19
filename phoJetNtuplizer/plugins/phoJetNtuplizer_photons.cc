#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t            nPho_;
vector<float>    phoE_;
vector<float>    phoPx_;
vector<float>    phoPy_;
vector<float>    phoPz_;
vector<float>    phoEt_;
vector<float>    phoEta_;
vector<float>    phoPhi_;
vector<float>    phoCalibE_;
vector<float>    phoCalibEt_;

vector<float>    phoSCE_;
vector<float>    phoSCRawE_;
vector<float>    phoSCEta_;
vector<float>    phoSCPhi_;
vector<float>    phoSCEtaWidth_;
vector<float>    phoSCPhiWidth_;

vector<int>      phohasPixelSeed_;
vector<int>      phoEleVeto_;
vector<float>    phoR9_;
vector<float>    phoR9Full5x5_;
vector<float>    phoHoverE_;
vector<float>    phoSigmaIEtaIEtaFull5x5_;
vector<float>    phoSigmaIEtaIEtaMapFull5x5_;

vector<float>    phoPFChIso_;
vector<float>    phoPFChWorstIso_;
vector<float>    phoPFPhoIso_;
vector<float>    phoPFNeuIso_;

vector<float>    phoIDMVA_;
vector<UShort_t> phoIDbit_;

vector<float>    phoSeedTime_;
vector<float>    phoSeedEnergy_;

vector<UInt_t>   phoFiredSingleTrgs_;
vector<UInt_t>   phoFiredDoubleTrgs_;
vector<UInt_t>   phoFiredL1Trgs_;

vector<float>    phoScale_stat_up_;
vector<float>    phoScale_stat_dn_;
vector<float>    phoScale_syst_up_;
vector<float>    phoScale_syst_dn_;
vector<float>    phoScale_gain_up_;
vector<float>    phoScale_gain_dn_;
vector<float>    phoResol_rho_up_;
vector<float>    phoResol_rho_dn_;
vector<float>    phoResol_phi_up_;
vector<float>    phoResol_phi_dn_;

void phoJetNtuplizer::branchPhotons(TTree* tree){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::branchPhotons -->BEGIN<-- "<<std::endl;

  tree->Branch("nPho",                     &nPho_);
  tree->Branch("phoE",                     &phoE_);
  tree->Branch("phoPx",                    &phoPx_);
  tree->Branch("phoPy",                    &phoPy_);
  tree->Branch("phoPz",                    &phoPz_);
  tree->Branch("phoEt",                    &phoEt_);
  tree->Branch("phoEta",                   &phoEta_);
  tree->Branch("phoPhi",                   &phoPhi_);
  tree->Branch("phoCalibE",                &phoCalibE_);
  tree->Branch("phoCalibEt",               &phoCalibEt_);

  tree->Branch("phoSCE",                   &phoSCE_);
  tree->Branch("phoSCRawE",                &phoSCRawE_);
  tree->Branch("phoSCEta",                 &phoSCEta_);
  tree->Branch("phoSCPhi",                 &phoSCPhi_);
  tree->Branch("phoSCEtaWidth",            &phoSCEtaWidth_);
  tree->Branch("phoSCPhiWidth",            &phoSCPhiWidth_);

  tree->Branch("phohasPixelSeed",          &phohasPixelSeed_);
  tree->Branch("phoEleVeto",               &phoEleVeto_);
  tree->Branch("phoR9",                    &phoR9_);
  tree->Branch("phoR9Full5x5",             &phoR9Full5x5_);
  tree->Branch("phoHoverE",                &phoHoverE_);
  tree->Branch("phoSigmaIEtaIEtaFull5x5",  &phoSigmaIEtaIEtaFull5x5_);
  tree->Branch("phoSigmaIEtaIEtaMapFull5x5",  &phoSigmaIEtaIEtaMapFull5x5_);

  tree->Branch("phoPFChIso",               &phoPFChIso_);
  tree->Branch("phoPFChWorstIso",          &phoPFChWorstIso_);
  tree->Branch("phoPFPhoIso",              &phoPFPhoIso_);
  tree->Branch("phoPFNeuIso",              &phoPFNeuIso_);

  tree->Branch("phoIDMVA",                 &phoIDMVA_);
  tree->Branch("phoIDbit",                 &phoIDbit_);

  tree->Branch("phoSeedTime",              &phoSeedTime_);
  tree->Branch("phoSeedEnergy",            &phoSeedEnergy_);

  tree->Branch("phoFiredSingleTrgs",       &phoFiredSingleTrgs_);
  tree->Branch("phoFiredDoubleTrgs",       &phoFiredDoubleTrgs_);
  tree->Branch("phoFiredL1Trgs",           &phoFiredL1Trgs_);

  tree->Branch("phoScale_stat_up",         &phoScale_stat_up_);
  tree->Branch("phoScale_stat_dn",         &phoScale_stat_dn_);
  tree->Branch("phoScale_syst_up",         &phoScale_syst_up_);
  tree->Branch("phoScale_syst_dn",         &phoScale_syst_dn_);
  tree->Branch("phoScale_gain_up",         &phoScale_gain_up_);
  tree->Branch("phoScale_gain_dn",         &phoScale_gain_dn_);
  tree->Branch("phoResol_rho_up",          &phoResol_rho_up_);
  tree->Branch("phoResol_rho_dn",          &phoResol_rho_dn_);
  tree->Branch("phoResol_phi_up",          &phoResol_phi_up_);
  tree->Branch("phoResol_phi_dn",          &phoResol_phi_dn_);

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::branchPhotons -->END<--"<<std::endl;
}

void phoJetNtuplizer::fillPhotons(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillPhotons -->BEGIN<--"<<std::endl;

  initPhotons();

  edm::Handle<edm::View<pat::Photon> > photonHandle;
  iEvent.getByToken(photonToken_, photonHandle);

  if (!photonHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Photons in event";
    return;
  }

  edm::Handle<edm::View<pat::Photon> > calibPhotonHandle;
  iEvent.getByToken(calibPhotonToken_, calibPhotonHandle);

  if (!calibPhotonHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no calibrated pat::Photons in event";
    return;
  }

  // Get the full5x5 map
  edm::Handle<edm::ValueMap<float> > full5x5SigmaIEtaIEtaMap;
  iEvent.getByToken(full5x5SigmaIEtaIEtaMapToken_, full5x5SigmaIEtaIEtaMap);

  // photon ID isolations maps
  edm::Handle<edm::ValueMap<float> > phoChargedIsolationMap;
  edm::Handle<edm::ValueMap<float> > phoChargedWorstIsolationMap;
  edm::Handle<edm::ValueMap<float> > phoNeutralHadronIsolationMap;
  edm::Handle<edm::ValueMap<float> > phoPhotonIsolationMap;
  iEvent.getByToken(phoChargedIsolationToken_       ,phoChargedIsolationMap);
  iEvent.getByToken(phoChargedWorstIsolationToken_  ,phoChargedWorstIsolationMap);
  iEvent.getByToken(phoNeutralHadronIsolationToken_ ,phoNeutralHadronIsolationMap);
  iEvent.getByToken(phoPhotonIsolationToken_        ,phoPhotonIsolationMap);

  // Get the photon ID data from the event stream.
  // Note: this implies that the VID ID modules have been run upstream.
  // If you need more info, check with the EGM group.
  edm::Handle<edm::ValueMap<bool> >  loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  tight_id_decisions;
  edm::Handle<edm::ValueMap<float> > mvaValues;
  iEvent.getByToken(phoLooseIdMapToken_   ,loose_id_decisions);
  iEvent.getByToken(phoMediumIdMapToken_  ,medium_id_decisions);
  iEvent.getByToken(phoTightIdMapToken_   ,tight_id_decisions);
  iEvent.getByToken(phoMVAValuesMapToken_ ,mvaValues);

  EcalClusterLazyTools lazyTool(iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  for(edm::View<pat::Photon>::const_iterator ipho = photonHandle->begin(); ipho != photonHandle->end(); ++ipho){

    Float_t corrPt = -1;
    Float_t corrEn = -1;

    for(edm::View<pat::Photon>::const_iterator iCpho = calibPhotonHandle->begin(); iCpho != calibPhotonHandle->end(); ++iCpho){
      if(fabs(ipho->eta() - iCpho->eta()) < 0.001 && fabs(ipho->phi() - iCpho->phi()) < 0.001){
	corrPt = iCpho->pt();
	corrEn = iCpho->energy();
      }
    }//calibPhotonHandle

    phoCalibE_                .push_back(corrEn);
    phoCalibEt_               .push_back(corrPt);

    phoE_                     .push_back(ipho->energy());
    phoPx_                    .push_back(ipho->px());
    phoPy_                    .push_back(ipho->py());
    phoPz_                    .push_back(ipho->pz());
    phoEt_                    .push_back(ipho->et());
    phoEta_                   .push_back(ipho->eta());
    phoPhi_                   .push_back(ipho->phi());

    phoSCE_                   .push_back(ipho->superCluster()->energy());
    phoSCRawE_                .push_back(ipho->superCluster()->rawEnergy());
    phoSCEta_                 .push_back(ipho->superCluster()->eta());
    phoSCPhi_                 .push_back(ipho->superCluster()->phi());
    phoSCEtaWidth_            .push_back(ipho->superCluster()->etaWidth());
    phoSCPhiWidth_            .push_back(ipho->superCluster()->phiWidth());

    phohasPixelSeed_          .push_back((Int_t)ipho->hasPixelSeed());
    phoEleVeto_               .push_back((Int_t)ipho->passElectronVeto());
    phoR9_                    .push_back(ipho->r9());
    phoR9Full5x5_             .push_back(ipho->full5x5_r9());
    phoHoverE_                .push_back(ipho->hadTowOverEm());
    phoSigmaIEtaIEtaFull5x5_  .push_back(ipho->full5x5_sigmaIetaIeta());

    const auto pho = photonHandle->ptrAt(nPho_);

    phoSigmaIEtaIEtaMapFull5x5_  .push_back( (*full5x5SigmaIEtaIEtaMap)[pho] );
    phoPFChIso_                  .push_back( (*phoChargedIsolationMap)[pho] );
    phoPFChWorstIso_             .push_back( (*phoChargedWorstIsolationMap)[pho] );
    phoPFPhoIso_                 .push_back( (*phoPhotonIsolationMap)[pho] );
    phoPFNeuIso_                 .push_back( (*phoNeutralHadronIsolationMap)[pho] );

    phoIDMVA_                    .push_back( (*mvaValues)[pho] );

    UShort_t tmpphoIDbit = 0;

    if((*loose_id_decisions)[pho])  setbit(tmpphoIDbit, 0);
    if((*medium_id_decisions)[pho]) setbit(tmpphoIDbit, 1);
    if((*tight_id_decisions)[pho])  setbit(tmpphoIDbit, 2);

    phoIDbit_                    .push_back( tmpphoIDbit );

    ////// Seed time and energy
    DetId seed = (ipho->superCluster()->seed()->hitsAndFractions())[0].first;
    bool isBarrel = seed.subdetId() == EcalBarrel;
    const EcalRecHitCollection * rechits = (isBarrel?lazyTool.getEcalEBRecHitCollection():lazyTool.getEcalEERecHitCollection());

    EcalRecHitCollection::const_iterator theSeedHit = rechits->find(seed);
    if (theSeedHit != rechits->end()){
      phoSeedTime_  .push_back((*theSeedHit).time());
      phoSeedEnergy_.push_back((*theSeedHit).energy());
    }else{                            
      phoSeedTime_  .push_back(-99.);  
      phoSeedEnergy_.push_back(-99.);  
    }   

    //    phoFiredSingleTrgs_       .push_back(matchSinglePhotonTriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));
    //    phoFiredDoubleTrgs_       .push_back(matchDoublePhotonTriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));
    //    phoFiredL1Trgs_           .push_back(matchL1TriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));


    // ECAL scale correction and smearing
    float et = ipho->et();
    unsigned int gainSeedSC = 12;
    if (theSeedHit != rechits->end()) { 
      if(theSeedHit->checkFlag(EcalRecHit::kHasSwitchToGain6)) gainSeedSC = 6;
      if(theSeedHit->checkFlag(EcalRecHit::kHasSwitchToGain1)) gainSeedSC = 1;
    }
    int runNumber = iEvent.id().run();
    double scale = egmScaler_->ScaleCorrection(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC);  
    //double smear = egmScaler_->getSmearingSigma(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 0., 0.);

    float scale_stat_up = scale + egmScaler_->ScaleCorrectionUncertainty(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 1);
    float scale_stat_dn = scale - egmScaler_->ScaleCorrectionUncertainty(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 1);
    float scale_syst_up = scale + egmScaler_->ScaleCorrectionUncertainty(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 2);
    float scale_syst_dn = scale - egmScaler_->ScaleCorrectionUncertainty(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 2);
    float scale_gain_up = scale + egmScaler_->ScaleCorrectionUncertainty(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 4);
    float scale_gain_dn = scale - egmScaler_->ScaleCorrectionUncertainty(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 4);
    float resol_rho_up  = egmScaler_->getSmearingSigma(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 1., 0.);
    float resol_rho_dn  = egmScaler_->getSmearingSigma(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, -1., 0.);
    float resol_phi_up  = egmScaler_->getSmearingSigma(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 0., 1.);
    float resol_phi_dn = egmScaler_->getSmearingSigma(runNumber, ipho->isEB(), ipho->full5x5_r9(), fabs(ipho->eta()), et, gainSeedSC, 0., -1.);

    phoScale_stat_up_.push_back(scale_stat_up);
    phoScale_stat_dn_.push_back(scale_stat_dn);
    phoScale_syst_up_.push_back(scale_syst_up);
    phoScale_syst_dn_.push_back(scale_syst_dn);
    phoScale_gain_up_.push_back(scale_gain_up);
    phoScale_gain_dn_.push_back(scale_gain_dn);
    phoResol_rho_up_.push_back(resol_rho_up);
    phoResol_rho_dn_.push_back(resol_rho_dn);
    phoResol_phi_up_.push_back(resol_phi_up);
    phoResol_phi_dn_.push_back(resol_phi_dn);
    /////////////////////////////////END of energy and scale systematics


    nPho_++;

  }// for(edm::View<pat::Photon>::const_iterator ipho = photonHandle->begin(); ipho != photonHandle->end(); ++ipho)

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillPhotons -->END<--"<<std::endl;
}

void phoJetNtuplizer::initPhotons(){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::initPhotons -->BEGIN<--"<<std::endl;

  nPho_ = 0;

  phoE_                        .clear();
  phoPx_                       .clear();
  phoPy_                       .clear();
  phoPz_                       .clear();
  phoEt_                       .clear();
  phoEta_                      .clear();
  phoPhi_                      .clear();
  phoCalibE_                   .clear();
  phoCalibEt_                  .clear();

  phoSCE_                      .clear();
  phoSCRawE_                   .clear();
  phoSCEta_                    .clear();
  phoSCPhi_                    .clear();
  phoSCEtaWidth_               .clear();
  phoSCPhiWidth_               .clear();

  phohasPixelSeed_             .clear();
  phoEleVeto_                  .clear();
  phoR9_                       .clear();
  phoR9Full5x5_                .clear();
  phoHoverE_                   .clear();
  phoSigmaIEtaIEtaFull5x5_     .clear();
  phoSigmaIEtaIEtaMapFull5x5_  .clear();

  phoPFChIso_                  .clear();
  phoPFChWorstIso_             .clear();
  phoPFPhoIso_                 .clear();
  phoPFNeuIso_                 .clear();

  phoIDMVA_                    .clear();
  phoIDbit_                    .clear();

  phoSeedTime_                 .clear();
  phoSeedEnergy_               .clear();

  phoFiredSingleTrgs_          .clear();
  phoFiredDoubleTrgs_          .clear();
  phoFiredL1Trgs_              .clear();

  phoScale_stat_up_            .clear();
  phoScale_stat_dn_            .clear();
  phoScale_syst_up_            .clear();
  phoScale_syst_dn_            .clear();
  phoScale_gain_up_            .clear();
  phoScale_gain_dn_            .clear();
  phoResol_rho_up_             .clear();
  phoResol_rho_dn_             .clear();
  phoResol_phi_up_             .clear();
  phoResol_phi_dn_             .clear(); 

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::initPhotons -->END<--"<<std::endl;
}
