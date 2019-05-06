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
vector<float> ak8JetRawPt_;
vector<float> ak8JetRawE_;

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

vector<float> ak8JetCEF_;
vector<float> ak8JetNEF_;
vector<float> ak8JetCHF_;
vector<float> ak8JetNHF_;
vector<int>   ak8JetNCH_;
vector<int>   ak8JetNNP_;
vector<int>   ak8JetMUF_;
vector<int>   ak8Jetnconstituents_;
vector<bool>  ak8JetPFLooseId_;
vector<bool>  ak8JetPFTightLepVetoId_;

//vector<float> ak8CHSSoftDropJetMassCorr_;
//vector<float> ak8CHSPrunedJetMassCorr_;
//vector<float> ak8JetpfBoostedDSVBTag_;

vector<float> ak8Jet_CSVv2Tags_;
vector<float> ak8JetJECUnc_;
vector<float> ak8JetL2L3corr_;

//gen-info for ak8
//vector<int>   ak8JetPartonID_;
//vector<int>   ak8JetHadFlvr_;
//vector<int>   ak8JetGenJetIndex_;
//vector<float> ak8JetGenJetE_;
//vector<float> ak8JetGenJetPt_;
//vector<float> ak8JetGenJetEta_;
//vector<float> ak8JetGenJetPhi_;
//vector<int>   ak8JetGenPartonID_;
//vector<float> ak8JetGenE_;
//vector<float> ak8JetGenPt_;
//vector<float> ak8JetGenEta_;
//vector<float> ak8JetGenPhi_;
//vector<int>   ak8JetGenPartonMomID_;
////soft drop subjets
//vector<int>             nak8softdropSubjet_ ;
//vector< vector<float> > ak8softdropSubjetPt_ ;
//vector< vector<float> > ak8softdropSubjetEta_ ;
//vector< vector<float> > ak8softdropSubjetMass_ ;
//vector< vector<float> > ak8softdropSubjetPhi_ ;
//vector< vector<float> > ak8softdropSubjetE_ ;
//vector< vector<int > >  ak8softdropSubjetCharge_ ;
//vector< vector<int > >  ak8softdropSubjetFlavour_;
//vector< vector<float> > ak8softdropSubjetCSV_ ;

void phoJetNtuplizer::branchak8Jets(TTree* tree){

  tree->Branch("nak8Jet",                  &nak8Jet_);
  tree->Branch("ak8JetPt",                 &ak8JetPt_);
  tree->Branch("ak8JetE",                  &ak8JetE_);
  tree->Branch("ak8JetRawPt",              &ak8JetRawPt_);
  tree->Branch("ak8JetRawE",               &ak8JetRawE_);
  tree->Branch("ak8JetEta",                &ak8JetEta_);
  tree->Branch("ak8JetPhi",                &ak8JetPhi_);
  tree->Branch("ak8JetMass",               &ak8JetMass_);

  tree->Branch("ak8Jet_tau1",              &ak8Jet_tau1_);
  tree->Branch("ak8Jet_tau2",              &ak8Jet_tau2_);
  tree->Branch("ak8Jet_tau3",              &ak8Jet_tau3_);

  tree->Branch("ak8Jet_PrunedMass", &ak8Jet_PrunedMass_);
  tree->Branch("ak8Jet_SoftDropMass", &ak8Jet_SoftDropMass_);
  tree->Branch("ak8Jet_PuppiSoftDropMass", &ak8Jet_PuppiSoftDropMass_);
  tree->Branch("ak8Jet_PuppiTau1", &ak8Jet_PuppiTau1_);
  tree->Branch("ak8Jet_PuppiTau2", &ak8Jet_PuppiTau2_);
  tree->Branch("ak8Jet_PuppiTau3", &ak8Jet_PuppiTau3_);
  tree->Branch("ak8JetCHS_pt", &ak8JetCHS_pt_);
  tree->Branch("ak8JetCHS_eta", &ak8JetCHS_eta_);
  tree->Branch("ak8JetCHS_phi", &ak8JetCHS_phi_);
  tree->Branch("ak8JetCHS_mass", &ak8JetCHS_mass_);

  tree->Branch("ak8JetCEF",                &ak8JetCEF_);
  tree->Branch("ak8JetNEF",                &ak8JetNEF_);
  tree->Branch("ak8JetCHF",                &ak8JetCHF_);
  tree->Branch("ak8JetNHF",                &ak8JetNHF_);
  tree->Branch("ak8JetNCH",                &ak8JetNCH_);
  tree->Branch("ak8JetNNP",                &ak8JetNNP_);
  tree->Branch("ak8JetMUF",                &ak8JetMUF_);
  tree->Branch("ak8Jetnconstituents",      &ak8Jetnconstituents_);
  tree->Branch("ak8JetPFLooseId",          &ak8JetPFLooseId_);
  tree->Branch("ak8JetPFTightLepVetoId",   &ak8JetPFTightLepVetoId_);
  
//  tree->Branch("ak8CHSSoftDropJetMassCorr",&ak8CHSSoftDropJetMassCorr_);
//  tree->Branch("ak8CHSPrunedJetMassCorr",  &ak8CHSPrunedJetMassCorr_);
//  tree->Branch("ak8JetpfBoostedDSVBTag",   &ak8JetpfBoostedDSVBTag_);
  
  tree->Branch("ak8Jet_CSVv2Tags",         &ak8Jet_CSVv2Tags_);
//  tree->Branch("ak8JetJECUnc",             &ak8JetJECUnc_);
//  tree->Branch("ak8JetL2L3corr",             &ak8JetL2L3corr_);
/*
  if (doGenParticles_){
    tree->Branch("ak8JetPartonID", &ak8JetPartonID_);
    tree->Branch("ak8JetHadFlvr", &ak8JetHadFlvr_);
    tree->Branch("ak8JetGenJetIndex", &ak8JetGenJetIndex_);
    tree->Branch("ak8JetGenJetE", &ak8JetGenJetE_);
    tree->Branch("ak8JetGenJetPt", &ak8JetGenJetPt_);
    tree->Branch("ak8JetGenJetEta", &ak8JetGenJetEta_);
    tree->Branch("ak8JetGenJetPhi", &ak8JetGenJetPhi_);
    tree->Branch("ak8JetGenPartonID", &ak8JetGenPartonID_);
    tree->Branch("ak8JetGenE", &ak8JetGenE_);
    tree->Branch("ak8JetGenPt", &ak8JetGenPt_);
    tree->Branch("ak8JetGenEta", &ak8JetGenEta_);
    tree->Branch("ak8JetGenPhi", &ak8JetGenPhi_);
    tree->Branch("ak8JetGenPartonMomID", &ak8JetGenPartonMomID_);
  }
  tree->Branch("nak8softdropSubjet",       &nak8softdropSubjet_);
  tree->Branch("ak8softdropSubjetPt",      &ak8softdropSubjetPt_);
  tree->Branch("ak8softdropSubjetEta",     &ak8softdropSubjetEta_);
  tree->Branch("ak8softdropSubjetPhi",     &ak8softdropSubjetPhi_);
  tree->Branch("ak8softdropSubjetMass",    &ak8softdropSubjetMass_);
  tree->Branch("ak8softdropSubjetE",       &ak8softdropSubjetE_);
  tree->Branch("ak8softdropSubjetCharge",  &ak8softdropSubjetCharge_);
  tree->Branch("ak8softdropSubjetFlavour", &ak8softdropSubjetFlavour_);
  tree->Branch("ak8softdropSubjetCSV",     &ak8softdropSubjetCSV_);
  */

}

void phoJetNtuplizer::fillak8Jets(const edm::Event& iEvent, const edm::EventSetup& iSetup){        
  initak8Jets();
//
  edm::Handle<edm::View<pat::Jet> > ak8jetHandle;
  iEvent.getByToken(jetsAK8Token_, ak8jetHandle);
//  iEvent.getByToken(jetsAK8Token_, ak8jetHandle);



  if (!ak8jetHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Jets (AK8) in event";
    return;
  }
//
//  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
//  if(runGenInfo_)iEvent.getByToken(genParticlesToken_, genParticlesHandle);
//
//  edm::Handle<reco::VertexCollection> vtxHandle;
//  iEvent.getByToken(vtxToken_, vtxHandle);
//  if (!vtxHandle.isValid()) 
//    edm::LogWarning("phoJetNtuplizer") << "Primary vertices info not unavailable";
/*
  // Accessing the JEC uncertainties AK8 
  edm::ESHandle<JetCorrectorParametersCollection> AK8JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get("AK8PFchs",AK8JetCorParColl); 
  JetCorrectorParameters const & AK8JetCorPar = (*AK8JetCorParColl)["Uncertainty"];
  //JetCorrectionUncertainty *jecUnc=0;
  //jecUnc = new JetCorrectionUncertainty(JetCorPar);
*/
 
  for (edm::View<pat::Jet>::const_iterator iak8Jet = ak8jetHandle->begin(); iak8Jet != ak8jetHandle->end(); ++iak8Jet) {

    if(iak8Jet->pt() < 200.) continue;

    ak8JetPt_                        .push_back(iak8Jet->pt());
    ak8JetE_                         .push_back(iak8Jet->energy());
    ak8JetEta_                       .push_back(iak8Jet->eta());
    ak8JetPhi_                       .push_back(iak8Jet->phi());
    ak8JetMass_                      .push_back(iak8Jet->mass());
    if(saveAll_){
      ak8JetRawPt_                     .push_back((*iak8Jet).correctedJet("Uncorrected").pt());
      ak8JetRawE_                      .push_back((*iak8Jet).correctedJet("Uncorrected").energy());
    }

    ak8JetCEF_         .push_back(iak8Jet->chargedEmEnergyFraction());
    ak8JetNEF_         .push_back(iak8Jet->neutralEmEnergyFraction());
    ak8JetCHF_         .push_back(iak8Jet->chargedHadronEnergyFraction());
    ak8JetNHF_         .push_back(iak8Jet->neutralHadronEnergyFraction());
    ak8JetNCH_         .push_back(iak8Jet->chargedMultiplicity());
    ak8JetNNP_         .push_back(iak8Jet->neutralMultiplicity());
    ak8JetMUF_         .push_back(iak8Jet->muonEnergyFraction());

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


    ak8Jet_CSVv2Tags_ .push_back(iak8Jet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));


    // ak8JetPFLooseId_;
    // ak8JetPFTightLepVetoId_;
    // ak8CHSSoftDropJetMass_;
    // ak8CHSSoftDropJetMassCorr_;
    // ak8CHSPrunedJetMass_;
    // ak8CHSPrunedJetMassCorr_;
    // ak8JetpfBoostedDSVBTag_;
    // ak8JetCSV_;
    // ak8JetJECUnc_;
    // ak8JetL2L3corr_;



    nak8Jet_++;
  }


}

void phoJetNtuplizer::initak8Jets(){

  nak8Jet_ = 0;
  // SubJet
  ak8JetPt_           .clear();
  ak8JetE_            .clear();
  ak8JetRawPt_        .clear();
  ak8JetRawE_         .clear();
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

  ak8JetCEF_          .clear();
  ak8JetNEF_          .clear();
  ak8JetCHF_          .clear();
  ak8JetNHF_          .clear();
  ak8JetNCH_          .clear();
  ak8JetNNP_          .clear();
  ak8JetMUF_          .clear();
  ak8Jetnconstituents_     .clear();
  ak8JetPFLooseId_         .clear();
  ak8JetPFTightLepVetoId_  .clear();

//  ak8CHSSoftDropJetMassCorr_   .clear();
//  ak8CHSPrunedJetMassCorr_   .clear();
//  ak8JetpfBoostedDSVBTag_  .clear();

  ak8Jet_CSVv2Tags_   .clear();
//  ak8JetJECUnc_            .clear();
//  ak8JetL2L3corr_            .clear();

  /*
  ak8JetPartonID_ .clear();
  ak8JetHadFlvr_ .clear();
  ak8JetGenJetIndex_.clear();
  ak8JetGenJetE_.clear();
  ak8JetGenJetPt_.clear();
  ak8JetGenJetEta_.clear();
  ak8JetGenJetPhi_.clear();
  ak8JetGenPartonID_.clear();
  ak8JetGenE_.clear();
  ak8JetGenPt_.clear();
  ak8JetGenEta_.clear();
  ak8JetGenPhi_.clear();
  ak8JetGenPartonMomID_.clear();

  nak8softdropSubjet_ .clear();
  ak8softdropSubjetPt_ .clear();
  ak8softdropSubjetEta_ .clear();
  ak8softdropSubjetPhi_ .clear();
  ak8softdropSubjetMass_ .clear();
  ak8softdropSubjetCharge_ .clear();
  ak8softdropSubjetE_ .clear();
  ak8softdropSubjetFlavour_ .clear();
  ak8softdropSubjetCSV_ .clear();
*/

}
