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
#include "phoJetAnalysis/JetWidthCalculator/interface/JetWidthCalculator.hh"

Int_t             nJet_;

vector<float>    jetPt_;
vector<float>    jetE_;
vector<float>    jetEta_;
vector<float>    jetPhi_;
vector<float>    jetRawPt_;
vector<float>    jetRawE_;
vector<float>    jetMt_;
vector<float>    jetArea_;
vector<float>    jetMass_;
vector<float>    jetMaxDistance_;
vector<float>    jetPhiPhiMoment_;
vector<float>    jetConstituentEtaPhiSpread_;
vector<float>    jetConstituentPtDistribution_;
vector<float>    jetPileup_;
vector<UShort_t> jetID_; 
vector<float>    jetPUID_;
vector<Int_t>    jetPUFullID_;
vector<Int_t>    jetPartonID_;
vector<Int_t>    jetHadFlvr_;
vector<float>    jetJECUnc_;
vector<float>    jetP4Smear_;
vector<float>    jetP4SmearUp_;
vector<float>    jetP4SmearDo_;

vector<float>    jetCEF_;
vector<float>    jetNEF_;
vector<float>    jetCHF_;
vector<float>    jetNHF_;
vector<Int_t>    jetPhotonEnF_;
vector<Int_t>    jetElectronEnF_;
vector<float>    jetMuonEnF_;
vector<float>    jetChargedMuonEnF_;
vector<float>    jetHFHAE_;
vector<float>    jetHFEME_;
vector<Int_t>    jetNConst_;
vector<Int_t>    jetNConstituents_;
vector<Int_t>    jetNCharged_; 
vector<Int_t>    jetNNeutral_;
vector<Int_t>    jetNChargedHad_;
vector<Int_t>    jetNNeutralHad_;
vector<Int_t>    jetNPhoton_;
vector<Int_t>    jetNElectron_;
vector<Int_t>    jetNMuon_;

vector<float>    jetCSV2BJetTags_;
vector<float>    jetDeepCSVTags_b_;
vector<float>    jetDeepCSVTags_bb_;
vector<float>    jetDeepCSVTags_c_;
vector<float>    jetDeepCSVTags_udsg_;

vector<float>    jetDeepFlavour_b_;
vector<float>    jetDeepFlavour_bb_;
vector<float>    jetDeepFlavour_lepb_;
vector<float>    jetDeepFlavour_c_;
vector<float>    jetDeepFlavour_uds_;
vector<float>    jetDeepFlavour_g_;

vector<float>    jetLeadTrackPt_;
vector<float>    jetLeadTrackEta_;
vector<float>    jetLeadTrackPhi_;
vector<Int_t>    jetLepTrackPID_;
vector<float>    jetLepTrackPt_;
vector<float>    jetLepTrackEta_;
vector<float>    jetLepTrackPhi_;

vector<float>    jetetaWidth_;
vector<float>    jetphiWidth_;
//vector<int>      jetnPhotons_;
//vector<int>      jetnCHPions_;
//vector<int>      jetnMisc_;
//vector<vector<Int_t>> jetMiscPdgId_;
vector<vector<float>> jetConstPt_;
vector<vector<float>> jetConstEt_;
vector<vector<float>> jetConstEta_;
vector<vector<float>> jetConstPhi_;
vector<vector<Int_t>> jetConstPdgId_;

vector<float>    jetGenJetE_;
vector<float>    jetGenJetPt_;
vector<float>    jetGenJetEta_;
vector<float>    jetGenJetPhi_;
vector<Int_t>    jetGenPartonID_;
vector<float>    jetGenE_;
vector<float>    jetGenPt_;
vector<float>    jetGenEta_;
vector<float>    jetGenPhi_;
vector<Int_t>    jetGenPartonMomID_;

void phoJetNtuplizer::branchJets(TTree* tree){

  tree->Branch("nJet",                         &nJet_);

  tree->Branch("jetPt",                        &jetPt_);
  tree->Branch("jetE",                         &jetE_);
  tree->Branch("jetEta",                       &jetEta_);
  tree->Branch("jetPhi",                       &jetPhi_);
  tree->Branch("jetRawPt",                     &jetRawPt_);
  tree->Branch("jetRawE",                      &jetRawE_);
  tree->Branch("jetMt",                        &jetMt_);
  tree->Branch("jetArea",                      &jetArea_);
  tree->Branch("jetMass",                      &jetMass_);
  tree->Branch("jetMaxDistance",               &jetMaxDistance_);
  tree->Branch("jetPhiPhiMoment",              &jetPhiPhiMoment_);
  tree->Branch("jetConstituentEtaPhiSpread",   &jetConstituentEtaPhiSpread_);
  tree->Branch("jetConstituentPtDistribution", &jetConstituentPtDistribution_);
  tree->Branch("jetPileup",                    &jetPileup_);
  tree->Branch("jetID",                        &jetID_); 
  tree->Branch("jetPUID",                      &jetPUID_);
  tree->Branch("jetPUFullID",                  &jetPUFullID_);
  tree->Branch("jetPartonID",                  &jetPartonID_);
  tree->Branch("jetHadFlvr",                   &jetHadFlvr_);
  tree->Branch("jetJECUnc",                    &jetJECUnc_);

  tree->Branch("jetCEF",                       &jetCEF_);
  tree->Branch("jetNEF",                       &jetNEF_);
  tree->Branch("jetCHF",                       &jetCHF_);
  tree->Branch("jetNHF",                       &jetNHF_);
  tree->Branch("jetPhotonEnF",                 &jetPhotonEnF_);
  tree->Branch("jetElectronEnF",               &jetElectronEnF_);
  tree->Branch("jetMuonEnF",                   &jetMuonEnF_);
  tree->Branch("jetChargedMuonEnF",            &jetChargedMuonEnF_);
  tree->Branch("jetHFHAE",                     &jetHFHAE_);
  tree->Branch("jetHFEME",                     &jetHFEME_);
  tree->Branch("jetNConst",                    &jetNConst_);
  tree->Branch("jetNConstituents",             &jetNConstituents_);
  tree->Branch("jetNCharged",                  &jetNCharged_); 
  tree->Branch("jetNNeutral",                  &jetNNeutral_);
  tree->Branch("jetNChargedHad",               &jetNChargedHad_);
  tree->Branch("jetNNeutralHad",               &jetNNeutralHad_);
  tree->Branch("jetNPhoton",                   &jetNPhoton_);
  tree->Branch("jetNElectron",                 &jetNElectron_);
  tree->Branch("jetNMuon",                     &jetNMuon_);

  tree->Branch("jetCSV2BJetTags",              &jetCSV2BJetTags_);
  tree->Branch("jetDeepCSVTags_b",             &jetDeepCSVTags_b_);
  tree->Branch("jetDeepCSVTags_bb",            &jetDeepCSVTags_bb_);
  tree->Branch("jetDeepCSVTags_c",             &jetDeepCSVTags_c_);
  tree->Branch("jetDeepCSVTags_udsg",          &jetDeepCSVTags_udsg_);

  tree->Branch("jetDeepFlavour_b",             &jetDeepFlavour_b_);
  tree->Branch("jetDeepFlavour_bb",            &jetDeepFlavour_bb_);
  tree->Branch("jetDeepFlavour_lepb",          &jetDeepFlavour_lepb_);
  tree->Branch("jetDeepFlavour_c",             &jetDeepFlavour_c_);
  tree->Branch("jetDeepFlavour_uds",           &jetDeepFlavour_uds_);
  tree->Branch("jetDeepFlavour_g",             &jetDeepFlavour_g_);

  if(saveAll_){
    tree->Branch("jetLeadTrackPt",               &jetLeadTrackPt_);
    tree->Branch("jetLeadTrackEta",              &jetLeadTrackEta_);
    tree->Branch("jetLeadTrackPhi",              &jetLeadTrackPhi_);
    tree->Branch("jetLepTrackPID",               &jetLepTrackPID_);
    tree->Branch("jetLepTrackPt",                &jetLepTrackPt_);
    tree->Branch("jetLepTrackEta",               &jetLepTrackEta_);
    tree->Branch("jetLepTrackPhi",               &jetLepTrackPhi_);
  }

  if(runJetWidthCalculator_){
    tree->Branch("jetetaWidth",                  &jetetaWidth_);
    tree->Branch("jetphiWidth",                  &jetphiWidth_);
    //tree->Branch("jetnPhotons",                  &jetnPhotons_);
    //tree->Branch("jetnCHPions",                  &jetnCHPions_);
    //tree->Branch("jetnMisc",                     &jetnMisc_);
    //tree->Branch("jetMiscPdgId",                 &jetMiscPdgId_);
    tree->Branch("jetConstPt",                   &jetConstPt_);
    tree->Branch("jetConstEt",                   &jetConstEt_);
    tree->Branch("jetConstEta",                  &jetConstEta_);
    tree->Branch("jetConstPhi",                  &jetConstPhi_);
    tree->Branch("jetConstPdgId",                &jetConstPdgId_);
  }

  if(runGenInfo_){
    tree->Branch("jetGenJetE",                   &jetGenJetE_);
    tree->Branch("jetGenJetPt",                  &jetGenJetPt_);
    tree->Branch("jetGenJetEta",                 &jetGenJetEta_);
    tree->Branch("jetGenJetPhi",                 &jetGenJetPhi_);
    tree->Branch("jetGenPartonID",               &jetGenPartonID_);
    tree->Branch("jetGenE",                      &jetGenE_);
    tree->Branch("jetGenPt",                     &jetGenPt_);
    tree->Branch("jetGenEta",                    &jetGenEta_);
    tree->Branch("jetGenPhi",                    &jetGenPhi_);
    tree->Branch("jetGenPartonMomID",            &jetGenPartonMomID_);
    tree->Branch("jetP4Smear",                   &jetP4Smear_);
    tree->Branch("jetP4SmearUp",                 &jetP4SmearUp_);
    tree->Branch("jetP4SmearDo",                 &jetP4SmearDo_);
  }

}
void phoJetNtuplizer::fillJets(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  initJets();

  edm::Handle<edm::View<pat::Jet> > jetHandle;
  iEvent.getByToken(jetsAK4Token_, jetHandle);

  if (!jetHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no pat::Jets (AK4) in event";
    return;
  }

  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  if(runGenInfo_)iEvent.getByToken(genParticlesToken_, genParticlesHandle);

  edm::Handle<double> rhoHandle;
  iEvent.getByToken(rhoToken_, rhoHandle);
  float rho = *(rhoHandle.product());          

  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);
  if (!vtxHandle.isValid()) 
    edm::LogWarning("phoJetNtuplizer") << "Primary vertices info not unavailable";

  // Accessing the JEC uncertainties AK4 
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  JetCorrectionUncertainty *jecUnc=0;
  jecUnc = new JetCorrectionUncertainty(JetCorPar);

  for (edm::View<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {

    if (iJet->pt() < 20.) continue;
    jetPt_                        .push_back(iJet->pt());
    jetE_                         .push_back(iJet->energy());
    jetEta_                       .push_back(iJet->eta());
    jetPhi_                       .push_back(iJet->phi());
    jetRawPt_                     .push_back((*iJet).correctedJet("Uncorrected").pt());
    jetRawE_                      .push_back((*iJet).correctedJet("Uncorrected").energy());
    jetMt_                        .push_back(iJet->mt());
    jetArea_                      .push_back(iJet->jetArea());
    jetMass_                      .push_back(iJet->mass());
    jetMaxDistance_               .push_back(iJet->maxDistance());
    jetPhiPhiMoment_              .push_back(iJet->phiphiMoment());
    jetConstituentEtaPhiSpread_   .push_back(iJet->constituentEtaPhiSpread());
    jetConstituentPtDistribution_ .push_back(iJet->constituentPtDistribution());
    jetPileup_                    .push_back(iJet->pileup());


    //PF JetID
    float NHF      = iJet->neutralHadronEnergyFraction();
    float NEMF     = iJet->neutralEmEnergyFraction();
    float NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    float CHF      = iJet->chargedHadronEnergyFraction();
    float CHM      = iJet->chargedMultiplicity();
    float CEMF     = iJet->chargedEmEnergyFraction();
    float NNP      = iJet->neutralMultiplicity();
    float MUF      = iJet->muonEnergyFraction();

    bool tightJetID        = false;
    bool tightLepVetoJetID = false;
    if (fabs(iJet->eta()) <= 2.7) {
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0) || fabs(iJet->eta())>2.4);
      tightLepVetoJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.8) || fabs(iJet->eta())>2.4);
    } else if (fabs(iJet->eta()) <= 3.0) {
      tightJetID = (NEMF>0.02 && NEMF<0.99 && NNP>2);
    } else {
      tightJetID = (NEMF<0.90 && NHF>0.02 && NNP>10);
    }

    UShort_t tmpjetIDbit = 0;
    if (tightJetID)        setbit(tmpjetIDbit, 0);
    if (tightLepVetoJetID) setbit(tmpjetIDbit, 1);

    jetID_                        .push_back(tmpjetIDbit);    
    // PUJet ID from slimmedJets
    jetPUID_                      .push_back(iJet->userFloat("pileupJetId:fullDiscriminant"));
    jetPUFullID_                  .push_back(iJet->userInt("pileupJetId:fullId"));
    //parton id
    jetPartonID_                  .push_back(iJet->partonFlavour());
    jetHadFlvr_                   .push_back(iJet->hadronFlavour());

    if (fabs(iJet->eta()) < 5.2) {
      jecUnc->setJetEta(iJet->eta());
      jecUnc->setJetPt(iJet->pt()); // here you must use the CORRECTED jet pt
      jetJECUnc_.push_back(jecUnc->getUncertainty(true));
    } else {
      jetJECUnc_.push_back(-1.);
    }   

    jetCEF_                       .push_back(iJet->chargedEmEnergyFraction());
    jetNEF_                       .push_back(iJet->neutralEmEnergyFraction());
    jetCHF_                       .push_back(iJet->chargedHadronEnergyFraction());
    jetNHF_                       .push_back(iJet->neutralHadronEnergyFraction());
    jetPhotonEnF_                 .push_back(iJet->photonEnergyFraction());
    jetElectronEnF_               .push_back(iJet->electronEnergyFraction());
    jetMuonEnF_                   .push_back(iJet->muonEnergyFraction());
    jetChargedMuonEnF_            .push_back(iJet->chargedMuEnergyFraction());
    jetHFHAE_                     .push_back(iJet->HFHadronEnergy());
    jetHFEME_                     .push_back(iJet->HFEMEnergy());
    jetNConst_                    .push_back(iJet->nConstituents());
    jetNConstituents_             .push_back(iJet->numberOfDaughters());
    //jetNConst60_                  .push_back(iJet->nCarrying(0.60)); //return # of consitutents carrying 60% of energy
    jetNCharged_                  .push_back(iJet->chargedMultiplicity());
    jetNNeutral_                  .push_back(iJet->neutralMultiplicity());
    jetNChargedHad_               .push_back(iJet->chargedHadronMultiplicity());
    jetNNeutralHad_               .push_back(iJet->neutralHadronMultiplicity());
    jetNPhoton_                   .push_back(iJet->photonMultiplicity());
    jetNElectron_                 .push_back(iJet->electronMultiplicity());
    jetNMuon_                     .push_back(iJet->muonMultiplicity());

    //b/c-tagging
    jetCSV2BJetTags_             .push_back(iJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    jetDeepCSVTags_b_            .push_back(iJet->bDiscriminator("pfDeepCSVJetTags:probb"));
    jetDeepCSVTags_bb_           .push_back(iJet->bDiscriminator("pfDeepCSVJetTags:probbb"));
    jetDeepCSVTags_c_            .push_back(iJet->bDiscriminator("pfDeepCSVJetTags:probc"));
    jetDeepCSVTags_udsg_         .push_back(iJet->bDiscriminator("pfDeepCSVJetTags:probudsg"));

    jetDeepFlavour_b_            .push_back(iJet->bDiscriminator("pfDeepFlavourJetTags:probb"));
    jetDeepFlavour_bb_           .push_back(iJet->bDiscriminator("pfDeepFlavourJetTags:probbb"));
    jetDeepFlavour_lepb_         .push_back(iJet->bDiscriminator("pfDeepFlavourJetTags:problepb"));
    jetDeepFlavour_c_            .push_back(iJet->bDiscriminator("pfDeepFlavourJetTags:probc"));
    jetDeepFlavour_uds_          .push_back(iJet->bDiscriminator("pfDeepFlavourJetTags:probuds"));
    jetDeepFlavour_g_            .push_back(iJet->bDiscriminator("pfDeepFlavourJetTags:probg"));

    if(saveAll_){
      //Searching for leading track and lepton
      float leadTrkPt  = -99;
      float leadTrkEta = -99;
      float leadTrkPhi = -99;
      Int_t lepTrkPID  = -99;
      float lepTrkPt   = -99;
      float lepTrkEta  = -99;
      float lepTrkPhi  = -99;

      for (unsigned id = 0; id < iJet->getJetConstituents().size(); id++) {

	const edm::Ptr<reco::Candidate> daughter = iJet->getJetConstituents().at(id);

	if (daughter.isNonnull() && daughter.isAvailable()) {
	  if (daughter->charge() != 0 && daughter->pt() > leadTrkPt) {
	    leadTrkPt  = daughter->pt();
	    leadTrkEta = daughter->eta();
	    leadTrkPhi = daughter->phi();
	  }

	  if (fabs(daughter->pdgId()) == 11 || fabs(daughter->pdgId()) == 13) {
	    if (daughter->pt() > lepTrkPt) {
	      lepTrkPID = daughter->pdgId();
	      lepTrkPt  = daughter->pt();
	      lepTrkEta = daughter->eta();
	      lepTrkPhi = daughter->phi();
	    }
	  }
	}
      }

      jetLeadTrackPt_ .push_back(leadTrkPt);
      jetLeadTrackEta_.push_back(leadTrkEta);
      jetLeadTrackPhi_.push_back(leadTrkPhi);
      jetLepTrackPID_ .push_back(lepTrkPID);
      jetLepTrackPt_  .push_back(lepTrkPt);
      jetLepTrackEta_ .push_back(lepTrkEta);
      jetLepTrackPhi_ .push_back(lepTrkPhi);
    }

    //JetWidthCalculator
    if(runJetWidthCalculator_){
      const pat::Jet &jet = (*jetHandle)[nJet_];
      JetWidthCalculator jwc(jet);
      jetetaWidth_       .push_back(jwc.getEtaWidth());
      jetphiWidth_       .push_back(jwc.getPhiWidth());
      //jetnPhotons_       .push_back(jwc.getnPhotons());
      //jetnCHPions_       .push_back(jwc.getnCHPions());
      //jetnMisc_          .push_back(jwc.getnMiscParticles());
      //jetMiscPdgId_      .push_back(jwc.getMiscPdgId());


      jetConstPt_        .push_back(jwc.getConstPt());
      jetConstEt_        .push_back(jwc.getConstEt());
      jetConstEta_       .push_back(jwc.getConstEta());
      jetConstPhi_       .push_back(jwc.getConstPhi());
      jetConstPdgId_     .push_back(jwc.getConstPdgId());
    }


    // gen jet and parton
    if (runGenInfo_ && genParticlesHandle.isValid()) {
      Int_t  jetGenPartonID    = -99;
      Int_t  jetGenPartonMomID = -99;
      float jetGenE           = -999.;
      float jetGenPt          = -999.;
      float jetGenEta         = -999.;
      float jetGenPhi         = -999.;      
      if ((*iJet).genParton()) {
	jetGenPartonID = (*iJet).genParton()->pdgId();
	jetGenE        = (*iJet).genParton()->energy();
	jetGenPt       = (*iJet).genParton()->pt();
	jetGenEta      = (*iJet).genParton()->eta();
	jetGenPhi      = (*iJet).genParton()->phi();
	if ((*iJet).genParton()->mother()) {
	  jetGenPartonMomID = (*iJet).genParton()->mother()->pdgId();
	}
      }

      jetGenPartonID_     .push_back(jetGenPartonID);
      jetGenPartonMomID_  .push_back(jetGenPartonMomID);
      jetGenE_            .push_back(jetGenE);
      jetGenPt_           .push_back(jetGenPt);
      jetGenEta_          .push_back(jetGenEta);
      jetGenPhi_          .push_back(jetGenPhi);

      float jetGenJetE       = -999.;
      float jetGenJetPt       = -999.;
      float jetGenJetEta      = -999.;
      float jetGenJetPhi      = -999.;
      if ((*iJet).genJet()) {
	jetGenJetE     = (*iJet).genJet()->energy();
	jetGenJetPt    = (*iJet).genJet()->pt();
	jetGenJetEta   = (*iJet).genJet()->eta();
	jetGenJetPhi   = (*iJet).genJet()->phi();
      }
      jetGenJetE_         .push_back(jetGenJetE);
      jetGenJetPt_        .push_back(jetGenJetPt);
      jetGenJetEta_       .push_back(jetGenJetEta);
      jetGenJetPhi_       .push_back(jetGenJetPhi);

    
      // access jet resolution             
      JME::JetParameters parameters;
      parameters.setJetPt(iJet->pt()).setJetEta(iJet->eta()).setRho(rho);
      float jetResolution = jetResolution_.getResolution(parameters);

      edm::Service<edm::RandomNumberGenerator> rng;
      if (!rng.isAvailable()) edm::LogError("JET : random number generator is missing !");
      CLHEP::HepRandomEngine & engine = rng->getEngine( iEvent.streamID() );
      float rnd = CLHEP::RandGauss::shoot(&engine, 0., jetResolution);

      float jetResolutionSF   = jetResolutionSF_.getScaleFactor(parameters);
      float jetResolutionSFUp = jetResolutionSF_.getScaleFactor(parameters, Variation::UP);
      float jetResolutionSFDo = jetResolutionSF_.getScaleFactor(parameters, Variation::DOWN);                                                                

      float jetP4Smear   = -1.;
      float jetP4SmearUp = -1.;
      float jetP4SmearDo = -1.;
      if ( jetGenJetPt > 0 && 
           deltaR(iJet->eta(), iJet->phi(), jetGenJetEta, jetGenJetPhi) < 0.2 && 
           fabs(iJet->pt()-jetGenJetPt) < (3*jetResolution*iJet->pt())) {
	jetP4Smear   = 1. + (jetResolutionSF   - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
	jetP4SmearUp = 1. + (jetResolutionSFUp - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
	jetP4SmearDo = 1. + (jetResolutionSFDo - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
      } else {
	jetP4Smear   = 1. + rnd*sqrt(max(pow(jetResolutionSF,   2)-1, 0.));
	jetP4SmearUp = 1. + rnd*sqrt(max(pow(jetResolutionSFUp, 2)-1, 0.));
	jetP4SmearDo = 1. + rnd*sqrt(max(pow(jetResolutionSFDo, 2)-1, 0.));
      }
      jetP4Smear_  .push_back(jetP4Smear);
      jetP4SmearUp_.push_back(jetP4SmearUp);
      jetP4SmearDo_.push_back(jetP4SmearDo); 

    }// runGenInfo

    nJet_++;
  }
  delete jecUnc;
}

void phoJetNtuplizer::initJets(){

  nJet_                          = 0;

  jetPt_                        .clear();
  jetE_                         .clear();
  jetEta_                       .clear();
  jetPhi_                       .clear();
  jetRawPt_                     .clear();
  jetRawE_                      .clear();
  jetMt_                        .clear();
  jetArea_                      .clear();
  jetMass_                      .clear();
  jetMaxDistance_               .clear();
  jetPhiPhiMoment_              .clear();
  jetConstituentEtaPhiSpread_   .clear();
  jetConstituentPtDistribution_ .clear();
  jetPileup_                    .clear();
  jetID_                        .clear(); 
  jetPUID_                      .clear();
  jetPUFullID_                  .clear();
  jetPartonID_                  .clear();
  jetHadFlvr_                   .clear();
  jetJECUnc_                    .clear();
  jetP4Smear_                   .clear();
  jetP4SmearUp_                 .clear();
  jetP4SmearDo_                 .clear();

  jetCEF_                       .clear();
  jetNEF_                       .clear();
  jetCHF_                       .clear();
  jetNHF_                       .clear();
  jetPhotonEnF_                 .clear();
  jetElectronEnF_               .clear();
  jetMuonEnF_                   .clear();
  jetChargedMuonEnF_            .clear();
  jetHFHAE_                     .clear();
  jetHFEME_                     .clear();
  jetNConst_                    .clear();
  jetNConstituents_             .clear();
  jetNCharged_                  .clear(); 
  jetNNeutral_                  .clear();
  jetNChargedHad_               .clear();
  jetNNeutralHad_               .clear();
  jetNPhoton_                   .clear();
  jetNElectron_                 .clear();
  jetNMuon_                     .clear();

  jetCSV2BJetTags_              .clear();
  jetDeepCSVTags_b_             .clear();
  jetDeepCSVTags_bb_            .clear();
  jetDeepCSVTags_c_             .clear();
  jetDeepCSVTags_udsg_          .clear();

  jetDeepFlavour_b_             .clear();
  jetDeepFlavour_bb_            .clear();
  jetDeepFlavour_lepb_          .clear();
  jetDeepFlavour_c_             .clear();
  jetDeepFlavour_uds_           .clear();
  jetDeepFlavour_g_             .clear();

  jetLeadTrackPt_               .clear();
  jetLeadTrackEta_              .clear();
  jetLeadTrackPhi_              .clear();
  jetLepTrackPID_               .clear();
  jetLepTrackPt_                .clear();
  jetLepTrackEta_               .clear();
  jetLepTrackPhi_               .clear();

  jetetaWidth_                  .clear();
  jetphiWidth_                  .clear();
  //jetnPhotons_                  .clear();
  //jetnCHPions_                  .clear();
  //jetnMisc_                     .clear();
  //jetMiscPdgId_                 .clear();
  jetConstPt_                   .clear();
  jetConstEt_                   .clear();
  jetConstEta_                  .clear();
  jetConstPhi_                  .clear();
  jetConstPdgId_                .clear();

  jetGenJetE_                   .clear();
  jetGenJetPt_                  .clear();
  jetGenJetEta_                 .clear();
  jetGenJetPhi_                 .clear();
  jetGenPartonID_               .clear();
  jetGenE_                      .clear();
  jetGenPt_                     .clear();
  jetGenEta_                    .clear();
  jetGenPhi_                    .clear();
  jetGenPartonMomID_            .clear();

}
