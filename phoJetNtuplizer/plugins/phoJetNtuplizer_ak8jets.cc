#include "FWCore/MessageLogger/interface/MessageLogger.h"                                                                                                     
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGauss.h"
#include <iostream>
#include <vector>

using namespace std;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;


Int_t         nak8Jet_;
vector<float> ak8JetPt_;
vector<float> ak8JetE_;
vector<float> ak8JetEta_;
vector<float> ak8JetPhi_;
vector<float> ak8JetMass_;

vector<float> ak8Jet_tau1_;
vector<float> ak8Jet_tau2_;
vector<float> ak8Jet_tau3_;

vector<float> ak8Jet_PrunedMass_;
vector<float> ak8Jet_SoftDropMass_;
vector<float> ak8Jet_PuppiSoftDropMass_;

vector<float> ak8Jet_PuppiTau1_;
vector<float> ak8Jet_PuppiTau2_;
vector<float> ak8Jet_PuppiTau3_;

vector<float> ak8JetCHS_pt_;
vector<float> ak8JetCHS_eta_;
vector<float> ak8JetCHS_phi_;
vector<float> ak8JetCHS_mass_;

vector<float> ak8Jet_nb1AK8PuppiSoftDropN2_; 
vector<float> ak8Jet_nb1AK8PuppiSoftDropN3_;
vector<float> ak8Jet_nb2AK8PuppiSoftDropN2_;
vector<float> ak8Jet_nb2AK8PuppiSoftDropN3_;

vector<float> ak8Jet_CSVv2Tags_;
//-| vector<float> ak8Jet_DeepCSVTags_b_;
//-| vector<float> ak8Jet_DeepCSVTags_bb_;
//-| vector<float> ak8Jet_BoostedDSVTags_bb_;

vector<float> ak8Jet_TvsQCD_;
vector<float> ak8Jet_WvsQCD_;
vector<float> ak8Jet_ZvsQCD_;
vector<float> ak8Jet_MD_TvsQCD_;
vector<float> ak8Jet_MD_WvsQCD_;
vector<float> ak8Jet_MD_ZvsQCD_;

vector<float> ak8JetJECUnc_;
//vector<float> ak8JetL2L3corr_;

void phoJetNtuplizer::branchak8Jets(TTree* tree){

  tree->Branch("nak8Jet",                  &nak8Jet_);
  tree->Branch("ak8JetPt",                 &ak8JetPt_);
  tree->Branch("ak8JetE",                  &ak8JetE_);
  tree->Branch("ak8JetEta",                &ak8JetEta_);
  tree->Branch("ak8JetPhi",                &ak8JetPhi_);
  tree->Branch("ak8JetMass",               &ak8JetMass_);
 
  tree->Branch("ak8Jet_tau1",              &ak8Jet_tau1_);
  tree->Branch("ak8Jet_tau2",              &ak8Jet_tau2_);
  tree->Branch("ak8Jet_tau3",              &ak8Jet_tau3_);

  tree->Branch("ak8Jet_PrunedMass",        &ak8Jet_PrunedMass_);
  tree->Branch("ak8Jet_SoftDropMass",      &ak8Jet_SoftDropMass_);
  tree->Branch("ak8Jet_PuppiSoftDropMass", &ak8Jet_PuppiSoftDropMass_);
  
  tree->Branch("ak8Jet_PuppiTau1",         &ak8Jet_PuppiTau1_);
  tree->Branch("ak8Jet_PuppiTau2",         &ak8Jet_PuppiTau2_);
  tree->Branch("ak8Jet_PuppiTau3",         &ak8Jet_PuppiTau3_);
  tree->Branch("ak8JetCHS_pt",             &ak8JetCHS_pt_);
  tree->Branch("ak8JetCHS_eta",            &ak8JetCHS_eta_);
  tree->Branch("ak8JetCHS_phi",            &ak8JetCHS_phi_);
  tree->Branch("ak8JetCHS_mass",           &ak8JetCHS_mass_);

  tree->Branch("ak8Jet_nb1AK8PuppiSoftDropN2", &ak8Jet_nb1AK8PuppiSoftDropN2_);
  tree->Branch("ak8Jet_nb1AK8PuppiSoftDropN3", &ak8Jet_nb1AK8PuppiSoftDropN3_);
  tree->Branch("ak8Jet_nb2AK8PuppiSoftDropN2", &ak8Jet_nb2AK8PuppiSoftDropN2_);
  tree->Branch("ak8Jet_nb2AK8PuppiSoftDropN3", &ak8Jet_nb2AK8PuppiSoftDropN3_);
 
  tree->Branch("ak8Jet_CSVv2Tags",         &ak8Jet_CSVv2Tags_);
  //-| tree->Branch("ak8Jet_DeepCSVTags_b",     &ak8Jet_DeepCSVTags_b_);
  //-| tree->Branch("ak8Jet_DeepCSVTags_bb",    &ak8Jet_DeepCSVTags_bb_);
  //-| tree->Branch("ak8Jet_BoostedDSVTags_bb", &ak8Jet_BoostedDSVTags_bb_);
  tree->Branch("ak8JetJECUnc",             &ak8JetJECUnc_);

  tree->Branch("ak8Jet_TvsQCD",    &ak8Jet_TvsQCD_);
  tree->Branch("ak8Jet_WvsQCD",    &ak8Jet_WvsQCD_);
  tree->Branch("ak8Jet_ZvsQCD",    &ak8Jet_ZvsQCD_);
  tree->Branch("ak8Jet_MD_TvsQCD", &ak8Jet_MD_TvsQCD_);
  tree->Branch("ak8Jet_MD_WvsQCD", &ak8Jet_MD_WvsQCD_);
  tree->Branch("ak8Jet_MD_ZvsQCD", &ak8Jet_MD_ZvsQCD_);

  //tree->Branch("ak8JetL2L3corr",             &ak8JetL2L3corr_);

}

void phoJetNtuplizer::fillak8Jets(const edm::Event& iEvent, const edm::EventSetup& iSetup){        
  initak8Jets();

  edm::Handle<edm::View<pat::Jet> > ak8jetHandle;
  iEvent.getByToken(jetsAK8Token_, ak8jetHandle);

  edm::Handle<edm::View<pat::Jet> > ak8jetTagHandle;
  iEvent.getByToken(jetsAK8TagToken_, ak8jetTagHandle);

  if (!ak8jetHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Jets (AK8:ak8jetHandle) in event";
    return;
  }

  if (!ak8jetTagHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Jets (AK8:ak8jetTagHandle) in event";
    return;
  }

  // Accessing the JEC uncertainties AK8 
  edm::ESHandle<JetCorrectorParametersCollection> AK8JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get("AK8PFPuppi",AK8JetCorParColl); 
  JetCorrectorParameters const & AK8JetCorPar = (*AK8JetCorParColl)["Uncertainty"];
  JetCorrectionUncertainty *ak8jecUnc=0;
  ak8jecUnc = new JetCorrectionUncertainty(AK8JetCorPar);

  for (edm::View<pat::Jet>::const_iterator iak8Jet = ak8jetHandle->begin(); iak8Jet != ak8jetHandle->end(); ++iak8Jet) {
    if(iak8Jet->pt() < 200.) continue;
    ak8JetPt_                        .push_back(iak8Jet->pt());
    ak8JetE_                         .push_back(iak8Jet->energy());
    ak8JetEta_                       .push_back(iak8Jet->eta());
    ak8JetPhi_                       .push_back(iak8Jet->phi());
    ak8JetMass_                      .push_back(iak8Jet->mass());

    ak8Jet_tau1_      .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau1"));
    ak8Jet_tau2_      .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau2"));
    ak8Jet_tau3_      .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:NjettinessAK8CHSTau3"));

    ak8Jet_PrunedMass_        .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass"));
    ak8Jet_SoftDropMass_      .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:ak8PFJetsCHSSoftDropMass"));
    ak8Jet_PuppiSoftDropMass_ .push_back(iak8Jet->userFloat("ak8PFJetsPuppiSoftDropMass"));

    ak8Jet_PuppiTau1_  .push_back(iak8Jet->userFloat("NjettinessAK8Puppi:tau1"));
    ak8Jet_PuppiTau2_  .push_back(iak8Jet->userFloat("NjettinessAK8Puppi:tau2"));
    ak8Jet_PuppiTau3_  .push_back(iak8Jet->userFloat("NjettinessAK8Puppi:tau3"));

    ak8JetCHS_pt_     .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:pt"));
    ak8JetCHS_eta_    .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:eta"));
    ak8JetCHS_phi_    .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:phi"));
    ak8JetCHS_mass_   .push_back(iak8Jet->userFloat("ak8PFJetsCHSValueMap:mass"));

    ak8Jet_nb1AK8PuppiSoftDropN2_ .push_back(iak8Jet->userFloat("ak8PFJetsPuppiSoftDropValueMap:nb1AK8PuppiSoftDropN2"));
    ak8Jet_nb1AK8PuppiSoftDropN3_ .push_back(iak8Jet->userFloat("ak8PFJetsPuppiSoftDropValueMap:nb1AK8PuppiSoftDropN3"));
    ak8Jet_nb2AK8PuppiSoftDropN2_ .push_back(iak8Jet->userFloat("ak8PFJetsPuppiSoftDropValueMap:nb2AK8PuppiSoftDropN2"));
    ak8Jet_nb2AK8PuppiSoftDropN3_ .push_back(iak8Jet->userFloat("ak8PFJetsPuppiSoftDropValueMap:nb2AK8PuppiSoftDropN3"));

    ak8Jet_CSVv2Tags_         .push_back(iak8Jet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    //-| ak8Jet_DeepCSVTags_b_     .push_back(iak8Jet->bDiscriminator("pfDeepCSVJetTags:probb"));
    //-| ak8Jet_DeepCSVTags_bb_    .push_back(iak8Jet->bDiscriminator("pfDeepCSVJetTags:probbb"));
    //-| ak8Jet_BoostedDSVTags_bb_ .push_back(iak8Jet->bDiscriminator("pfBoostedDoubleSecondaryVertexAK8BJetTags"));

    const pat::Jet &jet = (*ak8jetTagHandle)[nak8Jet_];
    ak8Jet_TvsQCD_            .push_back(jet.bDiscriminator("pfDeepBoostedDiscriminatorsJetTags:TvsQCD")); 
    ak8Jet_WvsQCD_            .push_back(jet.bDiscriminator("pfDeepBoostedDiscriminatorsJetTags:WvsQCD")); 
    ak8Jet_ZvsQCD_            .push_back(jet.bDiscriminator("pfDeepBoostedDiscriminatorsJetTags:ZvsQCD")); 
    ak8Jet_MD_TvsQCD_         .push_back(jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:TvsQCD")); 
    ak8Jet_MD_WvsQCD_         .push_back(jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:WvsQCD")); 
    ak8Jet_MD_ZvsQCD_         .push_back(jet.bDiscriminator("pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags:ZvsQCD")); 
    
    if (fabs(iak8Jet->eta()) < 5.2) {
      ak8jecUnc->setJetEta(iak8Jet->eta());
      ak8jecUnc->setJetPt(iak8Jet->pt()); // here you must use the CORRECTED jet pt
      ak8JetJECUnc_.push_back(ak8jecUnc->getUncertainty(true));
    } else {
      ak8JetJECUnc_.push_back(-1.);
    }

    nak8Jet_++;
  }

delete ak8jecUnc;
}

void phoJetNtuplizer::initak8Jets(){

  nak8Jet_ = 0;
  ak8JetPt_           .clear();
  ak8JetE_            .clear();
  ak8JetEta_          .clear();
  ak8JetPhi_          .clear();
  ak8JetMass_         .clear();

  ak8Jet_tau1_        .clear();
  ak8Jet_tau2_        .clear();
  ak8Jet_tau3_        .clear();

  ak8Jet_PrunedMass_         .clear();
  ak8Jet_SoftDropMass_       .clear();
  ak8Jet_PuppiSoftDropMass_  .clear();
  
  ak8Jet_PuppiTau1_          .clear();
  ak8Jet_PuppiTau2_          .clear();
  ak8Jet_PuppiTau3_          .clear();
  ak8JetCHS_pt_              .clear();
  ak8JetCHS_eta_             .clear();
  ak8JetCHS_phi_             .clear();
  ak8JetCHS_mass_            .clear();

  ak8Jet_nb1AK8PuppiSoftDropN2_  .clear();
  ak8Jet_nb1AK8PuppiSoftDropN3_  .clear();
  ak8Jet_nb2AK8PuppiSoftDropN2_  .clear();
  ak8Jet_nb2AK8PuppiSoftDropN3_  .clear();

  ak8Jet_CSVv2Tags_        .clear();
  //-| ak8Jet_DeepCSVTags_b_    .clear();
  //-| ak8Jet_DeepCSVTags_bb_   .clear();
  //-| ak8Jet_BoostedDSVTags_bb_.clear();
  ak8JetJECUnc_            .clear();

  ak8Jet_TvsQCD_            .clear(); 
  ak8Jet_WvsQCD_            .clear();
  ak8Jet_ZvsQCD_            .clear();  
  ak8Jet_MD_TvsQCD_         .clear();
  ak8Jet_MD_WvsQCD_         .clear();
  ak8Jet_MD_ZvsQCD_         .clear();

  //  ak8JetL2L3corr_            .clear();
}
