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
vector<float> ak8JetRawPt_;
vector<float> ak8JetRawE_;
vector<float> ak8JetMass_;
vector<float> ak8Jet_tau1_;
vector<float> ak8Jet_tau2_;
vector<float> ak8Jet_tau3_;

vector<float> ak8JetCEF_;
vector<float> ak8JetNEF_;
vector<float> ak8JetCHF_;
vector<float> ak8JetNHF_;
vector<int>   ak8JetNCH_;
vector<int>   ak8Jetnconstituents_;
vector<bool>  ak8JetPFLooseId_;
vector<bool>  ak8JetPFTightLepVetoId_;
vector<float> ak8CHSSoftDropJetMass_;
vector<float> ak8CHSSoftDropJetMassCorr_;
vector<float> ak8CHSPrunedJetMass_;
vector<float> ak8CHSPrunedJetMassCorr_;
vector<float> ak8JetpfBoostedDSVBTag_;
vector<float> ak8JetCSV_;
vector<float> ak8JetJECUnc_;
vector<float> ak8JetL2L3corr_;

//gen-info for ak8
vector<int>   ak8JetPartonID_;
vector<int>   ak8JetHadFlvr_;
vector<int>   ak8JetGenJetIndex_;
vector<float> ak8JetGenJetE_;
vector<float> ak8JetGenJetPt_;
vector<float> ak8JetGenJetEta_;
vector<float> ak8JetGenJetPhi_;
vector<int>   ak8JetGenPartonID_;
vector<float> ak8JetGenE_;
vector<float> ak8JetGenPt_;
vector<float> ak8JetGenEta_;
vector<float> ak8JetGenPhi_;
vector<int>   ak8JetGenPartonMomID_;
//soft drop subjets
vector<int>             nak8softdropSubjet_ ;
vector< vector<float> > ak8softdropSubjetPt_ ;
vector< vector<float> > ak8softdropSubjetEta_ ;
vector< vector<float> > ak8softdropSubjetMass_ ;
vector< vector<float> > ak8softdropSubjetPhi_ ;
vector< vector<float> > ak8softdropSubjetE_ ;
vector< vector<int > >  ak8softdropSubjetCharge_ ;
vector< vector<int > >  ak8softdropSubjetFlavour_;
vector< vector<float> > ak8softdropSubjetCSV_ ;

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
  tree->Branch("ak8JetCHF",                &ak8JetCHF_);
  tree->Branch("ak8JetNHF",                &ak8JetNHF_);
  tree->Branch("ak8JetCEF",                &ak8JetCEF_);
  tree->Branch("ak8JetNEF",                &ak8JetNEF_);
  tree->Branch("ak8JetNCH",                &ak8JetNCH_);
  tree->Branch("ak8Jetnconstituents",      &ak8Jetnconstituents_);
//  tree->Branch("ak8JetMUF",                &ak8JetMUF_);
  tree->Branch("ak8JetPFLooseId",          &ak8JetPFLooseId_);
  tree->Branch("ak8JetPFTightLepVetoId",   &ak8JetPFTightLepVetoId_);
  tree->Branch("ak8CHSSoftDropJetMass",    &ak8CHSSoftDropJetMass_);
  tree->Branch("ak8CHSSoftDropJetMassCorr",&ak8CHSSoftDropJetMassCorr_);
  tree->Branch("ak8CHSPrunedJetMass",      &ak8CHSPrunedJetMass_);
  tree->Branch("ak8CHSPrunedJetMassCorr",      &ak8CHSPrunedJetMassCorr_);
  tree->Branch("ak8JetpfBoostedDSVBTag",   &ak8JetpfBoostedDSVBTag_);
  tree->Branch("ak8JetCSV",        &ak8JetCSV_);
  tree->Branch("ak8JetJECUnc",             &ak8JetJECUnc_);
  tree->Branch("ak8JetL2L3corr",             &ak8JetL2L3corr_);
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
  iEvent.getByToken(jetsAK4Token_, ak8jetHandle);
//
//  if (!ak8jetHandle.isValid()) {
//    edm::LogWarning("phoJetNtuplizer") << "no pat::Jets (AK8) in event";
//    return;
//  }
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


  }


}

void phoJetNtuplizer::initak8Jets(){

  nak8Jet_ = 0;
// SubJet
  ak8JetPt_           .clear();
  ak8JetE_           .clear();
  ak8JetRawPt_        .clear();
  ak8JetRawE_        .clear();
  ak8JetEta_          .clear();
  ak8JetPhi_          .clear();
  ak8JetMass_         .clear();
  ak8Jet_tau1_        .clear();
  ak8Jet_tau2_        .clear();
  ak8Jet_tau3_        .clear();
  ak8JetCHF_          .clear();
  ak8JetNHF_          .clear();
  ak8JetCEF_          .clear();
  ak8JetNEF_          .clear();
  ak8JetNCH_          	.clear();
  ak8Jetnconstituents_     .clear();
//  ak8JetMUF_          .clear();
  ak8JetPFLooseId_         .clear();
  ak8JetPFTightLepVetoId_  .clear();
  ak8CHSSoftDropJetMass_   .clear();
  ak8CHSSoftDropJetMassCorr_   .clear();
  ak8CHSPrunedJetMass_   .clear();
  ak8CHSPrunedJetMassCorr_   .clear();
  ak8JetpfBoostedDSVBTag_  .clear();
  ak8JetCSV_   .clear();
  ak8JetJECUnc_            .clear();
  ak8JetL2L3corr_            .clear();

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


}
