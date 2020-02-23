#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t            nPho_;

vector<float>    phoE_;
vector<float>    phoEt_;
vector<float>    phoEta_;
vector<float>    phoPhi_;

vector<float>    phoUnCalibE_;
vector<float>    phoUnCalibESigma_;
vector<float>    phoCalibE_;
vector<float>    phoCalibESigma_;
vector<float>    phoCalibEt_;

vector<float>    phoEnergyScale_;
vector<float>    phoEnergySigma_;

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
vector<float>    phoSigmaIEtaIPhiFull5x5_;
vector<float>    phoSigmaIPhiIPhiFull5x5_;

vector<float>    phoPFChIso_;
vector<float>    phoPFChWorstIso_;
vector<float>    phoPFPhoIso_;
vector<float>    phoPFNeuIso_;

vector<float>    phoIDMVA_;
vector<UShort_t> phoIDbit_;

vector<float>    phoSeedTime_;
vector<float>    phoSeedEnergy_;

vector<ULong64_t> phoFiredSingleTrgs_;
vector<ULong64_t> phoFiredDoubleTrgs_;
vector<ULong64_t> phoFiredTripleTrgs_;
vector<ULong64_t> phoFiredL1Trgs_;

vector<float>    phoScale_up_;
vector<float>    phoScale_dn_;
vector<float>    phoScale_stat_up_;
vector<float>    phoScale_stat_dn_;
vector<float>    phoScale_syst_up_;
vector<float>    phoScale_syst_dn_;
vector<float>    phoScale_gain_up_;
vector<float>    phoScale_gain_dn_;

vector<float>    phoResol_up_;
vector<float>    phoResol_dn_;
vector<float>    phoResol_rho_up_;
vector<float>    phoResol_rho_dn_;
vector<float>    phoResol_phi_up_;
vector<float>    phoResol_phi_dn_;

void phoJetNtuplizer::branchPhotons(TTree* tree){

  tree->Branch("nPho",                     &nPho_);
  tree->Branch("phoE",                     &phoE_);
  tree->Branch("phoEt",                    &phoEt_);
  tree->Branch("phoEta",                   &phoEta_);
  tree->Branch("phoPhi",                   &phoPhi_);

  tree->Branch("phoUnCalibE",              &phoUnCalibE_);
  tree->Branch("phoUnCalibESigma",         &phoUnCalibESigma_);
  tree->Branch("phoCalibE",                &phoCalibE_);
  tree->Branch("phoCalibESigma",           &phoCalibESigma_);
  tree->Branch("phoCalibEt",               &phoCalibEt_);

  tree->Branch("phoEnergyScale",           &phoEnergyScale_);
  tree->Branch("phoEnergySigma",           &phoEnergySigma_);

  tree->Branch("phoSCE",                   &phoSCE_);
  tree->Branch("phoSCRawE",                &phoSCRawE_);
  tree->Branch("phoSCEta",                 &phoSCEta_);
  tree->Branch("phoSCPhi",                 &phoSCPhi_);
  tree->Branch("phoSCEtaWidth",            &phoSCEtaWidth_);
  tree->Branch("phoSCPhiWidth",            &phoSCPhiWidth_);

  tree->Branch("phohasPixelSeed",          &phohasPixelSeed_);
  tree->Branch("phoEleVeto",               &phoEleVeto_);
  if(saveAll_){
    tree->Branch("phoR9",                    &phoR9_);
  }
  tree->Branch("phoR9Full5x5",             &phoR9Full5x5_);
  tree->Branch("phoHoverE",                &phoHoverE_);
  tree->Branch("phoSigmaIEtaIEtaFull5x5",  &phoSigmaIEtaIEtaFull5x5_);
  tree->Branch("phoSigmaIEtaIPhiFull5x5",  &phoSigmaIEtaIPhiFull5x5_);
  tree->Branch("phoSigmaIPhiIPhiFull5x5",  &phoSigmaIPhiIPhiFull5x5_);

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
  tree->Branch("phoFiredTripleTrgs",       &phoFiredTripleTrgs_);
  tree->Branch("phoFiredL1Trgs",           &phoFiredL1Trgs_);

  tree->Branch("phoScale_up",              &phoScale_up_);
  tree->Branch("phoScale_dn",              &phoScale_dn_);
  tree->Branch("phoScale_stat_up",         &phoScale_stat_up_);
  tree->Branch("phoScale_stat_dn",         &phoScale_stat_dn_);
  tree->Branch("phoScale_syst_up",         &phoScale_syst_up_);
  tree->Branch("phoScale_syst_dn",         &phoScale_syst_dn_);
  tree->Branch("phoScale_gain_up",         &phoScale_gain_up_);
  tree->Branch("phoScale_gain_dn",         &phoScale_gain_dn_);

  tree->Branch("phoResol_up",              &phoResol_up_);
  tree->Branch("phoResol_dn",              &phoResol_dn_);
  tree->Branch("phoResol_rho_up",          &phoResol_rho_up_);
  tree->Branch("phoResol_rho_dn",          &phoResol_rho_dn_);
  tree->Branch("phoResol_phi_up",          &phoResol_phi_up_);
  tree->Branch("phoResol_phi_dn",          &phoResol_phi_dn_);

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

  EcalClusterLazyTools       lazyTool    (iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  noZS::EcalClusterLazyTools lazyToolnoZS(iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  for(edm::View<pat::Photon>::const_iterator ipho = photonHandle->begin(); ipho != photonHandle->end(); ++ipho){

    phoUnCalibE_              .push_back(ipho->userFloat("ecalEnergyPreCorr"));
    phoUnCalibESigma_         .push_back(ipho->userFloat("ecalEnergyErrPreCorr"));
    phoCalibE_                .push_back(ipho->userFloat("ecalEnergyPostCorr"));
    phoCalibESigma_           .push_back(ipho->userFloat("ecalEnergyErrPostCorr"));
    phoCalibEt_               .push_back(ipho->et()*ipho->userFloat("ecalEnergyPostCorr")/ipho->energy());

    phoEnergyScale_           .push_back(ipho->userFloat("energyScaleValue"));
    phoEnergySigma_           .push_back(ipho->userFloat("energySigmaValue"));

    phoE_                     .push_back(ipho->energy());
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
    if(saveAll_) phoR9_                    .push_back(ipho->r9());
    phoR9Full5x5_             .push_back(ipho->full5x5_r9());
    phoHoverE_                .push_back(ipho->hadTowOverEm());

    std::vector<float> vCov = lazyToolnoZS.localCovariances( *(ipho->superCluster()->seed()) );
    //const float see = (isnan(vCov[0]) ? 0. : sqrt(vCov[0]));
    const float spp = (isnan(vCov[2]) ? 0. : sqrt(vCov[2]));                            
    const float sep = vCov[1];

    phoSigmaIEtaIEtaFull5x5_  .push_back(ipho->full5x5_sigmaIetaIeta());
    phoSigmaIEtaIPhiFull5x5_  .push_back(sep);
    phoSigmaIPhiIPhiFull5x5_  .push_back(spp);

    phoPFChIso_               .push_back(ipho->userFloat("phoChargedIsolation"));
    phoPFChWorstIso_          .push_back(ipho->userFloat("phoWorstChargedIsolation"));
    phoPFPhoIso_              .push_back(ipho->userFloat("phoPhotonIsolation"));
    phoPFNeuIso_              .push_back(ipho->userFloat("phoNeutralHadronIsolation"));

    phoIDMVA_               .push_back(ipho->userFloat("PhotonMVAEstimatorRunIIFall17v2Values"));

    //VID decisions
    UShort_t tmpphoIDbit = 0;
    bool isPassLoose  = ipho->photonID("cutBasedPhotonID-Fall17-94X-V2-loose");
    if (isPassLoose)  setbit(tmpphoIDbit, 0);
    bool isPassMedium = ipho->photonID("cutBasedPhotonID-Fall17-94X-V2-medium");
    if (isPassMedium) setbit(tmpphoIDbit, 1);
    bool isPassTight  = ipho->photonID("cutBasedPhotonID-Fall17-94X-V2-tight");
    if (isPassTight)  setbit(tmpphoIDbit, 2);

    bool isPassWP80   = ipho->photonID("mvaPhoID-RunIIFall17-v2-wp80");
    if(isPassWP80) setbit(tmpphoIDbit, 3);
    bool isPassWP90   = ipho->photonID("mvaPhoID-RunIIFall17-v2-wp90");
    if(isPassWP90) setbit(tmpphoIDbit, 4);

    phoIDbit_                 .push_back(tmpphoIDbit);


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

    phoFiredSingleTrgs_       .push_back(matchSinglePhotonTriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));
    phoFiredDoubleTrgs_       .push_back(matchDoublePhotonTriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));
    phoFiredTripleTrgs_       .push_back(matchTriplePhotonTriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));
    phoFiredL1Trgs_           .push_back(matchL1TriggerFilters(ipho->et(), ipho->eta(), ipho->phi()));


    // ECAL scale and smearing corrections
    phoScale_up_.push_back(ipho->userFloat("energyScaleUp"));
    phoScale_dn_.push_back(ipho->userFloat("energyScaleDown"));
    phoScale_stat_up_.push_back(ipho->userFloat("energyScaleStatUp"));
    phoScale_stat_dn_.push_back(ipho->userFloat("energyScaleStatDown"));
    phoScale_syst_up_.push_back(ipho->userFloat("energyScaleSystUp"));
    phoScale_syst_dn_.push_back(ipho->userFloat("energyScaleSystDown"));
    phoScale_gain_up_.push_back(ipho->userFloat("energyScaleGainUp"));
    phoScale_gain_dn_.push_back(ipho->userFloat("energyScaleGainDown"));

    phoResol_up_.push_back(ipho->userFloat("energySigmaUp"));
    phoResol_dn_.push_back(ipho->userFloat("energySigmaDown"));
    phoResol_rho_up_.push_back(ipho->userFloat("energySigmaRhoUp"));
    phoResol_rho_dn_.push_back(ipho->userFloat("energySigmaRhoDown"));
    phoResol_phi_up_.push_back(ipho->userFloat("energySigmaPhiUp"));
    phoResol_phi_dn_.push_back(ipho->userFloat("energySigmaPhiDown"));
    //xxxxx------- END of energy and scale systematics


    nPho_++;

  }// for(edm::View<pat::Photon>::const_iterator ipho = photonHandle->begin(); ipho != photonHandle->end(); ++ipho)

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillPhotons -->END<--"<<std::endl;
}

void phoJetNtuplizer::initPhotons(){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::initPhotons -->BEGIN<--"<<std::endl;

  nPho_ = 0;

  phoE_                        .clear();
  phoEt_                       .clear();
  phoEta_                      .clear();
  phoPhi_                      .clear();

  phoUnCalibE_                 .clear();
  phoUnCalibESigma_            .clear();
  phoCalibE_                   .clear();
  phoCalibESigma_              .clear();
  phoCalibEt_                  .clear();

  phoEnergyScale_              .clear();
  phoEnergySigma_              .clear();

  phoSCE_                      .clear();
  phoSCRawE_                   .clear();
  phoSCEta_                    .clear();
  phoSCPhi_                    .clear();
  phoSCEtaWidth_               .clear();
  phoSCPhiWidth_               .clear();

  phohasPixelSeed_             .clear();
  phoEleVeto_                  .clear();
  if(saveAll_){
    phoR9_                       .clear();
  }
  phoR9Full5x5_                .clear();
  phoHoverE_                   .clear();
  phoSigmaIEtaIEtaFull5x5_     .clear();
  phoSigmaIEtaIPhiFull5x5_     .clear();
  phoSigmaIPhiIPhiFull5x5_     .clear();

  phoPFChIso_                  .clear();
  phoPFChWorstIso_             .clear();
  phoPFPhoIso_                 .clear();
  phoPFNeuIso_                 .clear();

  phoIDMVA_                  .clear();
  phoIDbit_                    .clear();

  phoSeedTime_                 .clear();
  phoSeedEnergy_               .clear();

  phoFiredSingleTrgs_          .clear();
  phoFiredDoubleTrgs_          .clear();
  phoFiredTripleTrgs_          .clear();
  phoFiredL1Trgs_              .clear();

  phoScale_up_                 .clear();
  phoScale_dn_                 .clear();
  phoScale_stat_up_            .clear();
  phoScale_stat_dn_            .clear();
  phoScale_syst_up_            .clear();
  phoScale_syst_dn_            .clear();
  phoScale_gain_up_            .clear();
  phoScale_gain_dn_            .clear();

  phoResol_up_                 .clear();
  phoResol_dn_                 .clear();
  phoResol_rho_up_             .clear();
  phoResol_rho_dn_             .clear();
  phoResol_phi_up_             .clear();
  phoResol_phi_dn_             .clear(); 

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::initPhotons -->END<--"<<std::endl;
}
