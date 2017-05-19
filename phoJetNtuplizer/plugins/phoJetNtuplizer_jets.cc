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

Int_t          nJet_;
Int_t          jetTotalPt_;
Int_t          jetHT_;
Int_t          nGoodJets_;
vector<float>  jetPt_;
vector<float>  jetPx_;
vector<float>  jetPy_;
vector<float>  jetPz_;
vector<float>  jetEn_;
vector<float>  jetEta_;
vector<float>  jetPhi_;
vector<float>  jetRawPt_;
vector<float>  jetRawEn_;
vector<float>  jetMt_;
vector<float>  jetArea_;
vector<float>  jetMass_;
vector<float>  jetMaxDistance_;
vector<float>  jetPhiPhiMoment_;
vector<float>  jetConstituentEtaPhiSpread_;
vector<float>  jetConstituentPtDistribution_;
vector<float>  jetPileup_;
vector<int>    jetPartonID_;
vector<int>    jetHadFlvr_;
vector<float>  jetLeadTrackPt_;
vector<float>  jetLeadTrackEta_;
vector<float>  jetLeadTrackPhi_;
vector<int>    jetLepTrackPID_;
vector<float>  jetLepTrackPt_;
vector<float>  jetLepTrackEta_;
vector<float>  jetLepTrackPhi_;
vector<float>  jetChargedEmF_;
vector<float>  jetNeutralEmF_;
vector<float>  jetChargedHadF_;
vector<float>  jetNeutralHadF_;
vector<int>    jetPhotonEnF_;
vector<int>    jetElectronEnF_;
vector<float>  jetMuonEnF_;
vector<float>  jetChargedMuonEnF_;
vector<float>  jetHFHAE_;
vector<float>  jetHFEME_;
vector<int>    jetNConst_;
vector<int>    jetNConstituents_;
vector<int>    jetNConst60_;
vector<int>    jetNConst70_;
vector<int>    jetNConst80_;
vector<int>    jetNConst90_;
vector<int>    jetNConst92_;
vector<int>    jetNConst94_;
vector<int>    jetNConst96_;
vector<int>    jetNConst98_;
vector<int>    jetNCharged_; 
vector<int>    jetNNeutral_;
vector<int>    jetNChargedHad_;
vector<int>    jetNNeutralHad_;
vector<int>    jetNPhoton_;
vector<int>    jetNElectron_;
vector<int>    jetNMuon_;
vector<float>  jetetaWidth_;
vector<float>  jetphiWidth_;
vector<float>  jetPFCand12PtSum_;
vector<float>  jetPFCandsPtSum_;
vector<float>  jetPFCand12Ratio_;
vector< vector<double> > jetConstEt_;
vector< vector<double> > jetConstPt_;
vector< vector<int> >    jetConstPdgId_;
vector<float>  jetVtxPt_;
vector<float>  jetVtxMass_;
vector<float>  jetVtxNtrks_;
vector<float>  jetVtx3DVal_;
vector<float>  jetVtx3DSig_;
vector<float>  jetCSV2BJetTags_; // recommended
vector<float>  jetJetProbabilityBJetTags_;
vector<float>  jetpfCombinedMVAV2BJetTags_;
vector<bool>   jetPFLooseId_;
vector<int>    jetID_; 
vector<float>  jetPUID_;
vector<int>    jetPUFullID_;
vector<float>  jetJECUnc_;
vector<float>  jetP4Smear_;
vector<float>  jetP4SmearUp_;
vector<float>  jetP4SmearDo_;
vector<float>  jetGenJetEn_;
vector<float>  jetGenJetPt_;
vector<float>  jetGenJetEta_;
vector<float>  jetGenJetPhi_;
vector<int>    jetGenPartonID_;
vector<float>  jetGenEn_;
vector<float>  jetGenPt_;
vector<float>  jetGenEta_;
vector<float>  jetGenPhi_;
vector<int>    jetGenPartonMomID_;

void phoJetNtuplizer::branchJets(TTree* tree){

  tree->Branch("nJet",                         &nJet_);
  tree->Branch("jetTotalPt",                   &jetTotalPt_);
  tree->Branch("jetHT",                        &jetHT_);
  tree->Branch("nGoodJets",                    &nGoodJets_);
  tree->Branch("jetPt",                        &jetPt_);
  tree->Branch("jetPx",                        &jetPx_);
  tree->Branch("jetPy",                        &jetPy_);
  tree->Branch("jetPz",                        &jetPz_);
  tree->Branch("jetEn",                        &jetEn_);
  tree->Branch("jetEta",                       &jetEta_);
  tree->Branch("jetPhi",                       &jetPhi_);
  tree->Branch("jetRawPt",                     &jetRawPt_);
  tree->Branch("jetRawEn",                     &jetRawEn_);
  tree->Branch("jetMt",                        &jetMt_);
  tree->Branch("jetArea",                      &jetArea_);
  tree->Branch("jetMass",                      &jetMass_);
  tree->Branch("jetMaxDistance",               &jetMaxDistance_);
  tree->Branch("jetPhiPhiMoment",              &jetPhiPhiMoment_);
  tree->Branch("jetConstituentEtaPhiSpread",   &jetConstituentEtaPhiSpread_);
  tree->Branch("jetConstituentPtDistribution", &jetConstituentPtDistribution_);
  tree->Branch("jetPileup",                    &jetPileup_);
  tree->Branch("jetPartonID",                  &jetPartonID_);
  tree->Branch("jetHadFlvr",                   &jetHadFlvr_);
  tree->Branch("jetLeadTrackPt",               &jetLeadTrackPt_);
  tree->Branch("jetLeadTrackEta",              &jetLeadTrackEta_);
  tree->Branch("jetLeadTrackPhi",              &jetLeadTrackPhi_);
  tree->Branch("jetLepTrackPID",               &jetLepTrackPID_);
  tree->Branch("jetLepTrackPt",                &jetLepTrackPt_);
  tree->Branch("jetLepTrackEta",               &jetLepTrackEta_);
  tree->Branch("jetLepTrackPhi",               &jetLepTrackPhi_);
  tree->Branch("jetChargedEmF",                &jetChargedEmF_);
  tree->Branch("jetNeutralEmF",                &jetNeutralEmF_);
  tree->Branch("jetChargedHadF",               &jetChargedHadF_);
  tree->Branch("jetNeutralHadF",               &jetNeutralHadF_);
  tree->Branch("jetPhotonEnF",                 &jetPhotonEnF_);
  tree->Branch("jetElectronEnF",               &jetElectronEnF_);
  tree->Branch("jetMuonEnF",                   &jetMuonEnF_);
  tree->Branch("jetChargedMuonEnF",            &jetChargedMuonEnF_);
  tree->Branch("jetHFHAE",                     &jetHFHAE_);
  tree->Branch("jetHFEME",                     &jetHFEME_);
  tree->Branch("jetNConst",                    &jetNConst_);
  tree->Branch("jetNConstituents",             &jetNConstituents_);
  tree->Branch("jetNConst60",                  &jetNConst60_);
  tree->Branch("jetNConst70",                  &jetNConst70_);
  tree->Branch("jetNConst80",                  &jetNConst80_);
  tree->Branch("jetNConst90",                  &jetNConst90_);
  tree->Branch("jetNConst92",                  &jetNConst92_);
  tree->Branch("jetNConst94",                  &jetNConst94_);
  tree->Branch("jetNConst96",                  &jetNConst96_);
  tree->Branch("jetNConst98",                  &jetNConst98_);
  tree->Branch("jetNCharged",                  &jetNCharged_); 
  tree->Branch("jetNNeutral",                  &jetNNeutral_);
  tree->Branch("jetNChargedHad",               &jetNChargedHad_);
  tree->Branch("jetNNeutralHad",               &jetNNeutralHad_);
  tree->Branch("jetNPhoton",                   &jetNPhoton_);
  tree->Branch("jetNElectron",                 &jetNElectron_);
  tree->Branch("jetNMuon",                     &jetNMuon_);
  tree->Branch("jetetaWidth",                  &jetetaWidth_);
  tree->Branch("jetphiWidth",                  &jetphiWidth_);
  tree->Branch("jetPFCand12PtSum",             &jetPFCand12PtSum_);
  tree->Branch("jetPFCandsPtSum",              &jetPFCandsPtSum_);
  tree->Branch("jetPFCand12Ratio",             &jetPFCand12Ratio_);
  tree->Branch("jetConstEt",                   &jetConstEt_);
  tree->Branch("jetConstPt",                   &jetConstPt_);
  tree->Branch("jetConstPdgId",                &jetConstPdgId_);
  tree->Branch("jetVtxPt",                     &jetVtxPt_);
  tree->Branch("jetVtxMass",                   &jetVtxMass_);
  tree->Branch("jetVtxNtrks",                  &jetVtxNtrks_);
  tree->Branch("jetVtx3DVal",                  &jetVtx3DVal_);
  tree->Branch("jetVtx3DSig",                  &jetVtx3DSig_);
  tree->Branch("jetCSV2BJetTags",              &jetCSV2BJetTags_);
  tree->Branch("jetJetProbabilityBJetTags",    &jetJetProbabilityBJetTags_);
  tree->Branch("jetpfCombinedMVAV2BJetTags",   &jetpfCombinedMVAV2BJetTags_);
  tree->Branch("jetPFLooseId",                 &jetPFLooseId_);
  tree->Branch("jetID",                        &jetID_); 
  tree->Branch("jetPUID",                      &jetPUID_);
  tree->Branch("jetPUFullID",                  &jetPUFullID_);
  tree->Branch("jetJECUnc",                    &jetJECUnc_);
  if(runGenInfo_){
    tree->Branch("jetP4Smear",                   &jetP4Smear_);
    tree->Branch("jetP4SmearUp",                 &jetP4SmearUp_);
    tree->Branch("jetP4SmearDo",                 &jetP4SmearDo_);
    tree->Branch("jetGenJetEn",                  &jetGenJetEn_);
    tree->Branch("jetGenJetPt",                  &jetGenJetPt_);
    tree->Branch("jetGenJetEta",                 &jetGenJetEta_);
    tree->Branch("jetGenJetPhi",                 &jetGenJetPhi_);
    tree->Branch("jetGenPartonID",               &jetGenPartonID_);
    tree->Branch("jetGenEn",                     &jetGenEn_);
    tree->Branch("jetGenPt",                     &jetGenPt_);
    tree->Branch("jetGenEta",                    &jetGenEta_);
    tree->Branch("jetGenPhi",                    &jetGenPhi_);
    tree->Branch("jetGenPartonMomID",            &jetGenPartonMomID_);
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

  // Accessing the JEC uncertainties 
  //ak4  
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  JetCorrectionUncertainty *jecUnc=0;
  jecUnc = new JetCorrectionUncertainty(JetCorPar);

  for (edm::View<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {

    jetPt_                        .push_back(iJet->pt());
    jetPx_                        .push_back(iJet->px());
    jetPy_                        .push_back(iJet->py());
    jetPz_                        .push_back(iJet->pz());
    jetEn_                        .push_back(iJet->energy());
    jetEta_                       .push_back(iJet->eta());
    jetPhi_                       .push_back(iJet->phi());
    jetRawPt_                     .push_back((*iJet).correctedJet("Uncorrected").pt());
    jetRawEn_                     .push_back((*iJet).correctedJet("Uncorrected").energy());
    jetMt_                        .push_back(iJet->mt());
    jetArea_                      .push_back(iJet->jetArea());
    jetMass_                      .push_back(iJet->mass());
    jetMaxDistance_               .push_back(iJet->maxDistance());
    jetPhiPhiMoment_              .push_back(iJet->phiphiMoment());
    jetConstituentEtaPhiSpread_   .push_back(iJet->constituentEtaPhiSpread());
    jetConstituentPtDistribution_ .push_back(iJet->constituentPtDistribution());
    jetPileup_                    .push_back(iJet->pileup());

    jetChargedEmF_     .push_back(iJet->chargedEmEnergyFraction());
    jetNeutralEmF_     .push_back(iJet->neutralEmEnergyFraction());
    jetChargedHadF_    .push_back(iJet->chargedHadronEnergyFraction());
    jetNeutralHadF_    .push_back(iJet->neutralHadronEnergyFraction());
    jetPhotonEnF_      .push_back(iJet->photonEnergyFraction());
    jetElectronEnF_    .push_back(iJet->electronEnergyFraction());
    jetMuonEnF_        .push_back(iJet->muonEnergyFraction());
    jetChargedMuonEnF_ .push_back(iJet->chargedMuEnergyFraction());
    jetHFHAE_          .push_back( iJet->HFHadronEnergy());
    jetHFEME_          .push_back( iJet->HFEMEnergy());


    jetNConst_         .push_back(iJet->nConstituents());
    jetNConstituents_  .push_back(iJet->numberOfDaughters());
    jetNConst60_       .push_back(iJet->nCarrying(0.60)); //return # of consitutents carrying 60% of energy
    jetNConst70_       .push_back(iJet->nCarrying(0.70));
    jetNConst80_       .push_back(iJet->nCarrying(0.80));
    jetNConst90_       .push_back(iJet->nCarrying(0.90));
    jetNConst92_       .push_back(iJet->nCarrying(0.92));
    jetNConst94_       .push_back(iJet->nCarrying(0.94));
    jetNConst96_       .push_back(iJet->nCarrying(0.96));
    jetNConst98_       .push_back(iJet->nCarrying(0.98));

    jetNCharged_       .push_back(iJet->chargedMultiplicity());
    jetNNeutral_       .push_back(iJet->neutralMultiplicity());
    jetNChargedHad_    .push_back(iJet->chargedHadronMultiplicity());
    jetNNeutralHad_    .push_back(iJet->neutralHadronMultiplicity());
    jetNPhoton_        .push_back(iJet->photonMultiplicity());
    jetNElectron_      .push_back(iJet->electronMultiplicity());
    jetNMuon_          .push_back(iJet->muonMultiplicity());

    const pat::Jet &jet = (*jetHandle)[nJet_];
    JetWidthCalculator jwc(jet);
    jetetaWidth_       .push_back(jwc.getEtaWidth());
    jetphiWidth_       .push_back(jwc.getPhiWidth());
    jetPFCand12PtSum_  .push_back(jwc.getPFCand12PtSum());
    jetPFCandsPtSum_   .push_back(jwc.getPFCandsPtSum());
    jetPFCand12Ratio_  .push_back(jwc.getPFCand12Ratio());
    jetConstEt_        .push_back(jwc.getConstEt());
    jetConstPt_        .push_back(jwc.getConstPt());
    jetConstPdgId_     .push_back(jwc.getConstPdgId());

    if (fabs(iJet->eta()) < 5.2) {
      jecUnc->setJetEta(iJet->eta());
      jecUnc->setJetPt(iJet->pt()); // here you must use the CORRECTED jet pt
      jetJECUnc_.push_back(jecUnc->getUncertainty(true));
    } else {
      jetJECUnc_.push_back(-1.);
    }   

    //Searching for leading track and lepton
    float leadTrkPt  = -99;
    float leadTrkEta = -99;
    float leadTrkPhi = -99;
    int   lepTrkPID  = -99;
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

	if (abs(daughter->pdgId()) == 11 || abs(daughter->pdgId()) == 13) {
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
    jetVtxPt_       .push_back(sqrt(pow(iJet->userFloat("vtxPx"),2)+pow(iJet->userFloat("vtxPy"),2)));
    jetVtxMass_     .push_back(iJet->userFloat("vtxMass"));
    jetVtxNtrks_    .push_back(iJet->userFloat("vtxNtracks"));
    jetVtx3DVal_    .push_back(iJet->userFloat("vtx3DVal"));
    jetVtx3DSig_    .push_back(iJet->userFloat("vtx3DSig"));

    //b-tagging
    jetCSV2BJetTags_           .push_back(iJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    jetJetProbabilityBJetTags_ .push_back(iJet->bDiscriminator("pfJetProbabilityBJetTags"));
    jetpfCombinedMVAV2BJetTags_.push_back(iJet->bDiscriminator("pfCombinedMVAV2BJetTags"));

    //parton id
    jetPartonID_.push_back(iJet->partonFlavour());
    jetHadFlvr_.push_back(iJet->hadronFlavour());

    //jet PF Loose ID
    double NHF      = iJet->neutralHadronEnergyFraction();
    double NEMF     = iJet->neutralEmEnergyFraction();
    double NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    double CHF      = iJet->chargedHadronEnergyFraction();
    double CHM      = iJet->chargedMultiplicity();
    double CEMF     = iJet->chargedEmEnergyFraction();
    double NNP      = iJet->neutralMultiplicity();
    double MUF      = iJet->muonEnergyFraction();

    bool looseJetID        = false;    
    bool tightJetID        = false;
    bool tightLepVetoJetID = false;
    if (fabs(iJet->eta()) <= 2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
      tightLepVetoJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
    } else if (fabs(iJet->eta()) <= 3.0) {
      looseJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
      tightJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
    } else {
      looseJetID = (NEMF<0.90 && NNP>10); 
      tightJetID = (NEMF<0.90 && NNP>10);
    }
    jetPFLooseId_.push_back(looseJetID);
    Int_t jetIDdecision = 0;
    if (looseJetID) jetIDdecision += pow(2, 1);
    if (tightJetID) jetIDdecision += pow(2, 2);
    if (tightLepVetoJetID) jetIDdecision += pow(2, 3);
    jetID_.push_back(jetIDdecision);    

    // PUJet ID from slimmedJets
    jetPUID_.push_back(iJet->userFloat("pileupJetId:fullDiscriminant"));
    jetPUFullID_.push_back(iJet->userInt("pileupJetId:fullId"));


    // gen jet and parton
    if (runGenInfo_ && genParticlesHandle.isValid()) {
      int jetGenPartonID    = -99;
      int jetGenPartonMomID = -99;
      float jetGenEn        = -999.;
      float jetGenPt        = -999.;
      float jetGenEta       = -999.;
      float jetGenPhi       = -999.;      
      if ((*iJet).genParton()) {
	jetGenPartonID = (*iJet).genParton()->pdgId();
	jetGenEn = (*iJet).genParton()->energy();
	jetGenPt = (*iJet).genParton()->pt();
	jetGenEta = (*iJet).genParton()->eta();
	jetGenPhi = (*iJet).genParton()->phi();
	if ((*iJet).genParton()->mother()) {
	  jetGenPartonMomID = (*iJet).genParton()->mother()->pdgId();
	}
      }

      jetGenPartonID_.push_back(jetGenPartonID);
      jetGenPartonMomID_.push_back(jetGenPartonMomID);
      jetGenEn_ .push_back(jetGenEn);
      jetGenPt_ .push_back(jetGenPt);
      jetGenEta_ .push_back(jetGenEta);
      jetGenPhi_ .push_back(jetGenPhi);

      float jetGenJetEn  = -999.;
      float jetGenJetPt  = -999.;
      float jetGenJetEta = -999.;
      float jetGenJetPhi = -999.;
      if ((*iJet).genJet()) {
	jetGenJetEn = (*iJet).genJet()->energy();
	jetGenJetPt = (*iJet).genJet()->pt();
	jetGenJetEta = (*iJet).genJet()->eta();
	jetGenJetPhi = (*iJet).genJet()->phi();
      }
      jetGenJetEn_.push_back(jetGenJetEn);
      jetGenJetPt_.push_back(jetGenJetPt);
      jetGenJetEta_.push_back(jetGenJetEta);
      jetGenJetPhi_.push_back(jetGenJetPhi);

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
      if (jetGenJetPt > 0 && deltaR(iJet->eta(), iJet->phi(), jetGenJetEta, jetGenJetPhi) < 0.2 && fabs(iJet->pt()-jetGenJetPt) < 3*jetResolution*iJet->pt()) {
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
    }

    jetTotalPt_ += iJet->pt(); // Use all jets 
    if(iJet->pt() > 30.) { // Good jets have high pt
      jetHT_ += iJet->pt();
      nGoodJets_++;
    }
    nJet_++;
  }
}

void phoJetNtuplizer::initJets(){

  nJet_                          = 0;
  jetTotalPt_                    = 0;
  jetHT_                         = 0;
  nGoodJets_                     = 0;
  jetPt_                        .clear();
  jetPx_                        .clear();
  jetPy_                        .clear();
  jetPz_                        .clear();
  jetEn_                        .clear();
  jetEta_                       .clear();
  jetPhi_                       .clear();
  jetRawPt_                     .clear();
  jetRawEn_                     .clear();
  jetMt_                        .clear();
  jetArea_                      .clear();
  jetMass_                      .clear();
  jetMaxDistance_               .clear();
  jetPhiPhiMoment_              .clear();
  jetConstituentEtaPhiSpread_   .clear();
  jetConstituentPtDistribution_ .clear();
  jetPileup_                  .clear();
  jetPartonID_                .clear();
  jetHadFlvr_                 .clear();
  jetLeadTrackPt_             .clear();
  jetLeadTrackEta_            .clear();
  jetLeadTrackPhi_            .clear();
  jetLepTrackPID_             .clear();
  jetLepTrackPt_              .clear();
  jetLepTrackEta_             .clear();
  jetLepTrackPhi_             .clear();
  jetChargedEmF_              .clear();
  jetNeutralEmF_              .clear();
  jetChargedHadF_             .clear();
  jetNeutralHadF_             .clear();
  jetPhotonEnF_               .clear();
  jetElectronEnF_             .clear();
  jetMuonEnF_                 .clear();
  jetChargedMuonEnF_          .clear();
  jetHFHAE_                   .clear();
  jetHFEME_                   .clear();
  jetNConst_                  .clear();
  jetNConstituents_           .clear();
  jetNConst60_                .clear();
  jetNConst70_                .clear();
  jetNConst80_                .clear();
  jetNConst90_                .clear();
  jetNConst92_                .clear();
  jetNConst94_                .clear();
  jetNConst96_                .clear();
  jetNConst98_                .clear();
  jetNCharged_                .clear(); 
  jetNNeutral_                .clear();
  jetNChargedHad_             .clear();
  jetNNeutralHad_             .clear();
  jetNPhoton_                 .clear();
  jetNElectron_               .clear();
  jetNMuon_                   .clear();
  jetetaWidth_                .clear();
  jetphiWidth_                .clear();
  jetPFCand12PtSum_           .clear();
  jetPFCandsPtSum_            .clear();
  jetPFCand12Ratio_           .clear();
  jetConstEt_                 .clear();
  jetConstPt_                 .clear();
  jetConstPdgId_              .clear();
  jetVtxPt_                   .clear();
  jetVtxMass_                 .clear();
  jetVtxNtrks_                .clear();
  jetVtx3DVal_                .clear();
  jetVtx3DSig_                .clear();
  jetCSV2BJetTags_            .clear();
  jetJetProbabilityBJetTags_  .clear();
  jetpfCombinedMVAV2BJetTags_ .clear();
  jetPFLooseId_               .clear();
  jetID_                      .clear(); 
  jetPUID_                    .clear();
  jetPUFullID_                .clear();
  jetJECUnc_                  .clear();
  jetP4Smear_                 .clear();
  jetP4SmearUp_               .clear();
  jetP4SmearDo_               .clear();
  jetGenJetEn_                .clear();
  jetGenJetPt_                .clear();
  jetGenJetEta_               .clear();
  jetGenJetPhi_               .clear();
  jetGenPartonID_             .clear();
  jetGenEn_                   .clear();
  jetGenPt_                   .clear();
  jetGenEta_                  .clear();
  jetGenPhi_                  .clear();
  jetGenPartonMomID_          .clear();

}
