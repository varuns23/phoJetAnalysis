#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t          nTau_;
//Tau Kinematics
vector<float>  tau_Pt_;
vector<float>  tau_Et_;
vector<float>  tau_Eta_;
vector<float>  tau_Phi_;
vector<float>  tau_Charge_;
vector<int>    tau_DecayMode_;
vector<float>  tau_P_;
vector<float>  tau_Vz_;
vector<float>  tau_Energy_;
vector<float>  tau_Mass_;
vector<float>  tau_Dxy_;
vector<float>  tau_ZImpact_;

//Tau Ingredients
vector<float>  tau_byCombinedIsolationDeltaBetaCorrRaw3Hits_;
vector<float>  tau_chargedIsoPtSum_;
vector<float>  tau_neutralIsoPtSum_;
vector<float>  tau_neutralIsoPtSumWeight_;
vector<float>  tau_footprintCorrection_;
vector<float>  tau_photonPtSumOutsideSignalCone_;
vector<float>  tau_puCorrPtSum_;
vector<int>    tau_NumSignalPFChargedHadrCands_;
vector<int>    tau_NumSignalPFNeutrHadrCands_;
vector<int>    tau_NumSignalPFGammaCands_;
vector<int>    tau_NumSignalPFCands_;
vector<int>    tau_NumIsolationPFChargedHadrCands_;
vector<int>    tau_NumIsolationPFNeutrHadrCands_;
vector<int>    tau_NumIsolationPFGammaCands_;
vector<int>    tau_NumIsolationPFCands_;
//vector<bool>   tau_LeadChargedHadronExists_;
vector<float>  tau_LeadChargedHadronEta_;
vector<float>  tau_LeadChargedHadronPhi_;
vector<float>  tau_LeadChargedHadronPt_;
vector<float>  tau_LeadChargedHadron_dz_;
vector<float>  tau_LeadChargedHadron_dxy_;

vector<UInt_t> tau_IDbits_;
vector<float>  tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_;

void phoJetNtuplizer::branchTaus (TTree* tree){

  tree->Branch("nTau",         &nTau_);
  //Tau Kinematics
  tree->Branch("tau_Pt",        &tau_Pt_);
  tree->Branch("tau_Et",        &tau_Et_);
  tree->Branch("tau_Eta",       &tau_Eta_);
  tree->Branch("tau_Phi",       &tau_Phi_);
  tree->Branch("tau_Charge",    &tau_Charge_);
  tree->Branch("tau_DecayMode", &tau_DecayMode_);
  tree->Branch("tau_P",         &tau_P_);
  tree->Branch("tau_Vz",        &tau_Vz_);
  tree->Branch("tau_Energy",    &tau_Energy_);
  tree->Branch("tau_Mass",      &tau_Mass_);
  tree->Branch("tau_Dxy",       &tau_Dxy_);
  tree->Branch("tau_ZImpact",   &tau_ZImpact_);

  // Tau Ingredients
  tree->Branch("tau_byCombinedIsolationDeltaBetaCorrRaw3Hits",          &tau_byCombinedIsolationDeltaBetaCorrRaw3Hits_);
  tree->Branch("tau_chargedIsoPtSum",                                   &tau_chargedIsoPtSum_);
  tree->Branch("tau_neutralIsoPtSum",                                   &tau_neutralIsoPtSum_);
  tree->Branch("tau_neutralIsoPtSumWeight",                             &tau_neutralIsoPtSumWeight_);
  tree->Branch("tau_footprintCorrection",                               &tau_footprintCorrection_);
  tree->Branch("tau_photonPtSumOutsideSignalCone",                      &tau_photonPtSumOutsideSignalCone_);
  tree->Branch("tau_puCorrPtSum",                                       &tau_puCorrPtSum_);
  tree->Branch("tau_NumSignalPFChargedHadrCands",                       &tau_NumSignalPFChargedHadrCands_);
  tree->Branch("tau_NumSignalPFNeutrHadrCands",                         &tau_NumSignalPFNeutrHadrCands_);
  tree->Branch("tau_NumSignalPFGammaCands",                             &tau_NumSignalPFGammaCands_);
  tree->Branch("tau_NumSignalPFCands",                                  &tau_NumSignalPFCands_);
  tree->Branch("tau_NumIsolationPFChargedHadrCands",                    &tau_NumIsolationPFChargedHadrCands_);
  tree->Branch("tau_NumIsolationPFNeutrHadrCands",                      &tau_NumIsolationPFNeutrHadrCands_);
  tree->Branch("tau_NumIsolationPFGammaCands",                          &tau_NumIsolationPFGammaCands_);
  tree->Branch("tau_NumIsolationPFCands",                               &tau_NumIsolationPFCands_);
//  tree->Branch("tau_LeadChargedHadronExists",                           &tau_LeadChargedHadronExists_);
  tree->Branch("tau_LeadChargedHadronEta",                              &tau_LeadChargedHadronEta_);
  tree->Branch("tau_LeadChargedHadronPhi",                              &tau_LeadChargedHadronPhi_);
  tree->Branch("tau_LeadChargedHadronPt",                               &tau_LeadChargedHadronPt_);
  tree->Branch("tau_LeadChargedHadron_dz",                              &tau_LeadChargedHadron_dz_);
  tree->Branch("tau_LeadChargedHadron_dxy",                             &tau_LeadChargedHadron_dxy_);

  //Tau Id & Isolation
  tree->Branch("tau_IDbits",                                            &tau_IDbits_);
  tree->Branch("tau_byIsolationMVArun2017v2DBoldDMwLTraw2017",          &tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_);

}


void phoJetNtuplizer::fillTaus (const edm::Event& iEvent){

  initTaus();

  edm::Handle<vector<pat::Tau> > tauHandle;
  iEvent.getByToken(tausToken_, tauHandle);

  if (!tauHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no Tau in event";
    return;
  }

  for(vector<pat::Tau>::const_iterator itau = tauHandle->begin(); itau != tauHandle->end(); ++itau) {

    //Tau Kinematics
    tau_Pt_            .push_back(itau->pt());
    tau_Et_            .push_back(itau->et());
    tau_Eta_           .push_back(itau->eta());
    tau_Phi_           .push_back(itau->phi());
    tau_Charge_        .push_back(itau->charge());
    tau_DecayMode_     .push_back(itau->decayMode());
    tau_P_             .push_back(itau->p());
    tau_Vz_            .push_back(itau->vz());
    tau_Energy_        .push_back(itau->energy() );
    tau_Mass_          .push_back(itau->mass());
    tau_Dxy_           .push_back(itau->dxy() );
    tau_ZImpact_       .push_back(itau->vertex().z() + 130./tan(itau->theta()));

    // Tau Ingredients
    tau_byCombinedIsolationDeltaBetaCorrRaw3Hits_    .push_back(itau->tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits"));
    tau_chargedIsoPtSum_                             .push_back(itau->tauID("chargedIsoPtSum") );
    tau_neutralIsoPtSum_                             .push_back(itau->tauID("neutralIsoPtSum")  );
    tau_neutralIsoPtSumWeight_                       .push_back(itau->tauID("neutralIsoPtSumWeight"));
    tau_footprintCorrection_                         .push_back(itau->tauID("footprintCorrection"));
    tau_photonPtSumOutsideSignalCone_                .push_back(itau->tauID("photonPtSumOutsideSignalCone"));
    tau_puCorrPtSum_                                 .push_back(itau->tauID("puCorrPtSum"));

    tau_NumSignalPFChargedHadrCands_       .push_back(itau->signalChargedHadrCands().size());
    tau_NumSignalPFNeutrHadrCands_         .push_back(itau->signalNeutrHadrCands().size());
    tau_NumSignalPFGammaCands_             .push_back(itau->signalGammaCands().size());
    tau_NumSignalPFCands_                  .push_back(itau->signalCands().size());
    tau_NumIsolationPFChargedHadrCands_    .push_back(itau->isolationChargedHadrCands().size());
    tau_NumIsolationPFNeutrHadrCands_      .push_back(itau->isolationNeutrHadrCands().size());
    tau_NumIsolationPFGammaCands_          .push_back(itau->isolationGammaCands().size());
    tau_NumIsolationPFCands_               .push_back(itau->isolationCands().size());


    edm::Handle<reco::VertexCollection> vertexs;
    iEvent.getByToken(vtxToken_, vertexs);
    if (vertexs->size()>0) {
      pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(itau->leadChargedHadrCand().get());
      // tau_LeadChargedHadronExists_         .push_back(true);
      tau_LeadChargedHadronEta_            .push_back(packedLeadTauCand->eta());
      tau_LeadChargedHadronPhi_            .push_back(packedLeadTauCand->phi());
      tau_LeadChargedHadronPt_             .push_back(packedLeadTauCand->pt());
      tau_LeadChargedHadron_dz_            .push_back(packedLeadTauCand->dz());
      tau_LeadChargedHadron_dxy_           .push_back(packedLeadTauCand->dxy());
    }

    UInt_t tmpIDbits_ = 0;
    // Decay Mode Finding
    bool isdecayModeFinding           = itau->tauID("decayModeFinding");
    if (isdecayModeFinding)  setbit(tmpIDbits_, 0);
    bool isdecayModeFindingNewDMs     = itau->tauID("decayModeFindingNewDMs");
    if (isdecayModeFindingNewDMs)  setbit(tmpIDbits_, 1);

    // Muon rejection
    bool isMuonLoose3                 = itau->tauID("againstMuonLoose3");
    if (isMuonLoose3)  setbit(tmpIDbits_, 2);
    bool isMuonTight3                 = itau->tauID("againstMuonTight3");
    if (isMuonTight3)  setbit(tmpIDbits_, 3);

    //Electron rejection
    bool isElectronVLooseMVA6         = itau->tauID("againstElectronVLooseMVA6");
    if (isElectronVLooseMVA6)  setbit(tmpIDbits_, 4);
    bool isElectronLooseMVA6          = itau->tauID("againstElectronLooseMVA6");
    if (isElectronLooseMVA6)  setbit(tmpIDbits_, 5);
    bool isElectronMediumMVA6         = itau->tauID("againstElectronMediumMVA6");
    if (isElectronMediumMVA6)  setbit(tmpIDbits_, 6);
    bool isElectronTightMVA6          = itau->tauID("againstElectronTightMVA6");
    if (isElectronTightMVA6)  setbit(tmpIDbits_, 7);
    bool isElectronVTightMVA6         = itau->tauID("againstElectronVTightMVA6");
    if (isElectronVTightMVA6)  setbit(tmpIDbits_, 8);

    //Cut basedID
    bool isLooseCombinedIsolation     = itau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits");
    if (isLooseCombinedIsolation)  setbit(tmpIDbits_, 9);
    bool isMediumCombinedIsolation    = itau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits");
    if (isMediumCombinedIsolation)  setbit(tmpIDbits_, 10);
    bool isTightCombinedIsolation     = itau->tauID("byTightCombinedIsolationDeltaBetaCorr3Hits");
    if (isTightCombinedIsolation)  setbit(tmpIDbits_, 11);

    //MVA based 2017v2 discriminators
    bool isVVLooseIsolation           = itau->tauID("byVVLooseIsolationMVArun2017v2DBoldDMwLT2017");
    if (isVVLooseIsolation)  setbit(tmpIDbits_, 12);
    bool isVLooseIsolation            = itau->tauID("byVLooseIsolationMVArun2017v2DBoldDMwLT2017");
    if (isVLooseIsolation)  setbit(tmpIDbits_, 13);
    bool isLooseIsolation             = itau->tauID("byLooseIsolationMVArun2017v2DBoldDMwLT2017");
    if (isLooseIsolation)  setbit(tmpIDbits_, 14);
    bool isMediumIsolation            = itau->tauID("byMediumIsolationMVArun2017v2DBoldDMwLT2017");
    if (isMediumIsolation)  setbit(tmpIDbits_, 15);
    bool isTightIsolation             = itau->tauID("byTightIsolationMVArun2017v2DBoldDMwLT2017");
    if (isTightIsolation)  setbit(tmpIDbits_, 16);
    bool isVTightIsolation            = itau->tauID("byVTightIsolationMVArun2017v2DBoldDMwLT2017");
    if (isVTightIsolation)  setbit(tmpIDbits_, 17);
    bool isVVTightIsolation           = itau->tauID("byVVTightIsolationMVArun2017v2DBoldDMwLT2017");
    if (isVVTightIsolation)  setbit(tmpIDbits_, 18);

    tau_IDbits_               .push_back(tmpIDbits_);

    tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_          .push_back(itau->tauID("byIsolationMVArun2017v2DBoldDMwLTraw2017"));


    ++nTau_;

  } // loop over tau candidates

}

void phoJetNtuplizer::initTaus(){

  nTau_ = 0;

  tau_Eta_                                            .clear();
  tau_Phi_                                            .clear();
  tau_Pt_                                             .clear();
  tau_Et_                                             .clear();
  tau_Charge_                                         .clear();
  tau_DecayMode_                                      .clear();
  tau_P_                                              .clear();
  tau_Vz_                                             .clear();
  tau_Energy_                                         .clear();
  tau_Mass_                                           .clear();
  tau_Dxy_                                            .clear();
  tau_ZImpact_                                        .clear();

  tau_byCombinedIsolationDeltaBetaCorrRaw3Hits_       .clear();
  tau_chargedIsoPtSum_                                .clear();
  tau_neutralIsoPtSum_                                .clear();
  tau_neutralIsoPtSumWeight_                          .clear();
  tau_footprintCorrection_                            .clear();
  tau_photonPtSumOutsideSignalCone_                   .clear();
  tau_puCorrPtSum_                                    .clear();
  tau_NumSignalPFChargedHadrCands_                    .clear();
  tau_NumSignalPFNeutrHadrCands_                      .clear();
  tau_NumSignalPFGammaCands_                          .clear();
  tau_NumSignalPFCands_                               .clear();
  tau_NumIsolationPFChargedHadrCands_                 .clear();
  tau_NumIsolationPFNeutrHadrCands_                   .clear();
  tau_NumIsolationPFGammaCands_                       .clear();
  tau_NumIsolationPFCands_                            .clear();
  // tau_LeadChargedHadronExists_                        .clear();
  tau_LeadChargedHadronEta_                           .clear();
  tau_LeadChargedHadronPhi_                           .clear();
  tau_LeadChargedHadronPt_                            .clear();
  tau_LeadChargedHadron_dz_                           .clear();
  tau_LeadChargedHadron_dxy_                          .clear();

  tau_IDbits_                                         .clear();
  tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_       .clear();

}
