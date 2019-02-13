#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t          nTau_;
//Tau Kinematics
vector<float>  tau_Eta_;
vector<float>  tau_Phi_;
vector<float>  tau_Pt_;
vector<float>  tau_Et_;
vector<float>  tau_Charge_;
vector<int>    tau_DecayMode_;
vector<float>  tau_P_;
vector<float>  tau_Px_;
vector<float>  tau_Py_;
vector<float>  tau_Pz_;
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
vector<float>  tau_puCorrPtSum_;
vector<int>    tau_NumSignalPFChargedHadrCands_;
vector<int>    tau_NumSignalPFNeutrHadrCands_;
vector<int>    tau_NumSignalPFGammaCands_;
vector<int>    tau_NumSignalPFCands_;
vector<int>    tau_NumIsolationPFChargedHadrCands_;
vector<int>    tau_NumIsolationPFNeutrHadrCands_;
vector<int>    tau_NumIsolationPFGammaCands_;
vector<int>    tau_NumIsolationPFCands_;
vector<bool>   tau_LeadChargedHadronExists_;
vector<float>  tau_LeadChargedHadronEta_;
vector<float>  tau_LeadChargedHadronPhi_;
vector<float>  tau_LeadChargedHadronPt_;
vector<float>  tau_footprintCorrection_;
vector<float>  tau_photonPtSumOutsideSignalCone_;
vector<float>  tau_dz_;
vector<float>  tau_dxy_;

vector<bool>   tau_decayModeFinding_;
vector<bool>   tau_decayModeFindingNewDMs_;
//Muon rejection
vector<bool>   tau_LooseMuonRejection3_;
vector<bool>   tau_TightMuonRejection3_;
//Electron rejection
vector<bool>   tau_VLooseMVA6ElectronRejection_;
vector<bool>   tau_LooseMVA6ElectronRejection_;
vector<bool>   tau_MediumMVA6ElectronRejection_;
vector<bool>   tau_TightMVA6ElectronRejection_;
vector<bool>   tau_VTightMVA6ElectronRejection_;
// Cut based isolation
vector<bool>   tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_;
vector<bool>   tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_;
vector<bool>   tau_byTightCombinedIsolationDeltaBetaCorr3Hits_;

//MVA Based 2017v2 isolation
vector<float>  tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_;
vector<bool>   tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017_;
vector<bool>   tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_;
vector<bool>   tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_;
vector<bool>   tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_;
vector<bool>   tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_;
vector<bool>   tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_;
vector<bool>   tau_byVVTightIsolationMVArun2017v2DBoldDMwLT2017_;

//MVA Based Old isolations
// vector<float>  tauByIsolationMVArun2v1DBnewDMwLTraw_;
// vector<float>  tauByIsolationMVArun2v1DBoldDMwLTraw_;
// vector<float>  tauByIsolationMVArun2v1PWnewDMwLTraw_;
// vector<float>  tauByIsolationMVArun2v1PWoldDMwLTraw_;
// vector<bool>   tauByVTightIsolationMVArun2v1DBnewDMwLT_;
// vector<bool>   tauByVTightIsolationMVArun2v1DBoldDMwLT_;
// vector<bool>   tauByVTightIsolationMVArun2v1PWnewDMwLT_;
// vector<bool>   tauByVTightIsolationMVArun2v1PWoldDMwLT_;
// vector<bool>   tauByTightIsolationMVArun2v1DBnewDMwLT_;
// vector<bool>   tauByTightIsolationMVArun2v1DBoldDMwLT_;
// vector<bool>   tauByTightIsolationMVArun2v1PWnewDMwLT_;
// vector<bool>   tauByTightIsolationMVArun2v1PWoldDMwLT_;
// vector<bool>   tauByMediumIsolationMVArun2v1DBnewDMwLT_;
// vector<bool>   tauByMediumIsolationMVArun2v1DBoldDMwLT_;
// vector<bool>   tauByMediumIsolationMVArun2v1PWnewDMwLT_;
// vector<bool>   tauByMediumIsolationMVArun2v1PWoldDMwLT_;
// vector<bool>   tauByLooseIsolationMVArun2v1DBnewDMwLT_;
// vector<bool>   tauByLooseIsolationMVArun2v1DBoldDMwLT_;
// vector<bool>   tauByLooseIsolationMVArun2v1PWnewDMwLT_;
// vector<bool>   tauByLooseIsolationMVArun2v1PWoldDMwLT_;
// vector<bool>   tauByVLooseIsolationMVArun2v1DBnewDMwLT_;
// vector<bool>   tauByVLooseIsolationMVArun2v1DBoldDMwLT_;
// vector<bool>   tauByVLooseIsolationMVArun2v1PWnewDMwLT_;
// vector<bool>   tauByVLooseIsolationMVArun2v1PWoldDMwLT_;

void phoJetNtuplizer::branchTaus (TTree* tree){

    tree->Branch("nTau",         &nTau_);
    //Tau Kinematics
    tree->Branch("tau_Eta",       &tau_Eta_);
    tree->Branch("tau_Phi",       &tau_Phi_);
    tree->Branch("tau_Pt",        &tau_Pt_);
    tree->Branch("tau_Et",        &tau_Et_);
    tree->Branch("tau_Charge",    &tau_Charge_);
    tree->Branch("tau_DecayMode", &tau_DecayMode_);
    tree->Branch("tau_P",         &tau_P_);
    tree->Branch("tau_Px",        &tau_Px_);
    tree->Branch("tau_Py",        &tau_Py_);
    tree->Branch("tau_Pz",        &tau_Pz_);
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
    tree->Branch("tau_puCorrPtSum",                                       &tau_puCorrPtSum_);
    tree->Branch("tau_NumSignalPFChargedHadrCands",                       &tau_NumSignalPFChargedHadrCands_);
    tree->Branch("tau_NumSignalPFNeutrHadrCands",                         &tau_NumSignalPFNeutrHadrCands_);
    tree->Branch("tau_NumSignalPFGammaCands",                             &tau_NumSignalPFGammaCands_);
    tree->Branch("tau_NumSignalPFCands",                                  &tau_NumSignalPFCands_);
    tree->Branch("tau_NumIsolationPFChargedHadrCands",                    &tau_NumIsolationPFChargedHadrCands_);
    tree->Branch("tau_NumIsolationPFNeutrHadrCands",                      &tau_NumIsolationPFNeutrHadrCands_);
    tree->Branch("tau_NumIsolationPFGammaCands",                          &tau_NumIsolationPFGammaCands_);
    tree->Branch("tau_NumIsolationPFCands",                               &tau_NumIsolationPFCands_);
    tree->Branch("tau_LeadChargedHadronExists",                           &tau_LeadChargedHadronExists_);
    tree->Branch("tau_LeadChargedHadronEta",                              &tau_LeadChargedHadronEta_);
    tree->Branch("tau_LeadChargedHadronPhi",                              &tau_LeadChargedHadronPhi_);
    tree->Branch("tau_LeadChargedHadronPt",                               &tau_LeadChargedHadronPt_);
    tree->Branch("tau_footprintCorrection",                               &tau_footprintCorrection_);
    tree->Branch("tau_photonPtSumOutsideSignalCone",                      &tau_photonPtSumOutsideSignalCone_);
    tree->Branch("tau_dz",                                                &tau_dz_);
    tree->Branch("tau_dxy",                                               &tau_dxy_);
  
    //Tau Id & Isolation
    tree->Branch("tau_decayModeFinding",                                  &tau_decayModeFinding_);
    tree->Branch("tau_decayModeFindingNewDMs",                            &tau_decayModeFindingNewDMs_);
    tree->Branch("tau_VLooseMVA6ElectronRejection",                       &tau_VLooseMVA6ElectronRejection_);
    tree->Branch("tau_LooseMVA6ElectronRejection",                        &tau_LooseMVA6ElectronRejection_);
    tree->Branch("tau_MediumMVA6ElectronRejection",                       &tau_MediumMVA6ElectronRejection_);
    tree->Branch("tau_TightMVA6ElectronRejection",                        &tau_TightMVA6ElectronRejection_);
    tree->Branch("tau_VTightMVA6ElectronRejection",                       &tau_VTightMVA6ElectronRejection_);
    tree->Branch("tau_LooseMuonRejection3",                               &tau_LooseMuonRejection3_);
    tree->Branch("tau_TightMuonRejection3",                               &tau_TightMuonRejection3_);
    tree->Branch("tau_byLooseCombinedIsolationDeltaBetaCorr3Hits",        &tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_);
    tree->Branch("tau_byMediumCombinedIsolationDeltaBetaCorr3Hits",       &tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_);
    tree->Branch("tau_ByTightCombinedIsolationDeltaBetaCorr3Hits",        &tau_byTightCombinedIsolationDeltaBetaCorr3Hits_);

    tree->Branch("tau_byIsolationMVArun2017v2DBoldDMwLTraw2017",          &tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_);
    tree->Branch("tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017",      &tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017",       &tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017",       &tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017",        &tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017",       &tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byTightIsolationMVArun2017v2DBoldDMwLT2017",        &tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017",       &tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_);
    tree->Branch("tau_byVVTightIsolationMVArun2017v2DBoldDMwLT2017",      &tau_byVVTightIsolationMVArun2017v2DBoldDMwLT2017_);
    
//    tree->Branch("tauByIsolationMVArun2v1DBnewDMwLTraw",                 &tauByIsolationMVArun2v1DBnewDMwLTraw_);
//    tree->Branch("tauByIsolationMVArun2v1DBoldDMwLTraw",                 &tauByIsolationMVArun2v1DBoldDMwLTraw_);
//    tree->Branch("tauByIsolationMVArun2v1PWnewDMwLTraw",                 &tauByIsolationMVArun2v1PWnewDMwLTraw_);
//    tree->Branch("tauByIsolationMVArun2v1PWoldDMwLTraw",                 &tauByIsolationMVArun2v1PWoldDMwLTraw_);
//    tree->Branch("tauByVTightIsolationMVArun2v1DBnewDMwLT",              &tauByVTightIsolationMVArun2v1DBnewDMwLT_);
//    tree->Branch("tauByVTightIsolationMVArun2v1DBoldDMwLT",              &tauByVTightIsolationMVArun2v1DBoldDMwLT_);
//    tree->Branch("tauByVTightIsolationMVArun2v1PWnewDMwLT",              &tauByVTightIsolationMVArun2v1PWnewDMwLT_);
//    tree->Branch("tauByVTightIsolationMVArun2v1PWoldDMwLT",              &tauByVTightIsolationMVArun2v1PWoldDMwLT_);
//    tree->Branch("tauByTightIsolationMVArun2v1DBnewDMwLT",               &tauByTightIsolationMVArun2v1DBnewDMwLT_);
//    tree->Branch("tauByTightIsolationMVArun2v1DBoldDMwLT",               &tauByTightIsolationMVArun2v1DBoldDMwLT_);
//    tree->Branch("tauByTightIsolationMVArun2v1PWnewDMwLT",               &tauByTightIsolationMVArun2v1PWnewDMwLT_);
//    tree->Branch("tauByTightIsolationMVArun2v1PWoldDMwLT",               &tauByTightIsolationMVArun2v1PWoldDMwLT_);
//    tree->Branch("tauByMediumIsolationMVArun2v1DBnewDMwLT",              &tauByMediumIsolationMVArun2v1DBnewDMwLT_);
//    tree->Branch("tauByMediumIsolationMVArun2v1DBoldDMwLT",              &tauByMediumIsolationMVArun2v1DBoldDMwLT_);
//    tree->Branch("tauByMediumIsolationMVArun2v1PWnewDMwLT",              &tauByMediumIsolationMVArun2v1PWnewDMwLT_);
//    tree->Branch("tauByMediumIsolationMVArun2v1PWoldDMwLT",              &tauByMediumIsolationMVArun2v1PWoldDMwLT_);
//    tree->Branch("tauByLooseIsolationMVArun2v1DBnewDMwLT",               &tauByLooseIsolationMVArun2v1DBnewDMwLT_);
//    tree->Branch("tauByLooseIsolationMVArun2v1DBoldDMwLT",               &tauByLooseIsolationMVArun2v1DBoldDMwLT_);
//    tree->Branch("tauByLooseIsolationMVArun2v1PWnewDMwLT",               &tauByLooseIsolationMVArun2v1PWnewDMwLT_);
//    tree->Branch("tauByLooseIsolationMVArun2v1PWoldDMwLT",               &tauByLooseIsolationMVArun2v1PWoldDMwLT_);
//    tree->Branch("tauByVLooseIsolationMVArun2v1DBnewDMwLT",              &tauByVLooseIsolationMVArun2v1DBnewDMwLT_);
//    tree->Branch("tauByVLooseIsolationMVArun2v1DBoldDMwLT",              &tauByVLooseIsolationMVArun2v1DBoldDMwLT_);
//    tree->Branch("tauByVLooseIsolationMVArun2v1PWnewDMwLT",              &tauByVLooseIsolationMVArun2v1PWnewDMwLT_);
//    tree->Branch("tauByVLooseIsolationMVArun2v1PWoldDMwLT",              &tauByVLooseIsolationMVArun2v1PWoldDMwLT_);

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
    tau_Eta_           .push_back(itau->eta());
    tau_Phi_           .push_back(itau->phi());
    tau_Pt_            .push_back(itau->pt());
    tau_Et_            .push_back(itau->et());
    tau_Charge_        .push_back(itau->charge());
    tau_DecayMode_     .push_back(itau->decayMode());
    tau_P_             .push_back(itau->p());
    tau_Px_            .push_back(itau->px());
    tau_Py_            .push_back(itau->py());
    tau_Pz_            .push_back(itau->pz());
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
      tau_LeadChargedHadronExists_         .push_back(true);
      tau_LeadChargedHadronEta_            .push_back(packedLeadTauCand->eta());
      tau_LeadChargedHadronPhi_            .push_back(packedLeadTauCand->phi());
      tau_LeadChargedHadronPt_             .push_back(packedLeadTauCand->pt());
      tau_dz_                              .push_back(packedLeadTauCand->dz());
      tau_dxy_                             .push_back(packedLeadTauCand->dxy());
    }

    tau_decayModeFinding_                                  .push_back(itau->tauID("decayModeFinding"));
    tau_decayModeFindingNewDMs_                            .push_back(itau->tauID("decayModeFindingNewDMs"));
   
    //Muon rejection
    tau_LooseMuonRejection3_                               .push_back(itau->tauID("againstMuonLoose3"));
    tau_TightMuonRejection3_                               .push_back(itau->tauID("againstMuonTight3"));
    
    //Electron rejection
    tau_VLooseMVA6ElectronRejection_                       .push_back(itau->tauID("againstElectronVLooseMVA6"));
    tau_LooseMVA6ElectronRejection_                        .push_back(itau->tauID("againstElectronLooseMVA6"));
    tau_MediumMVA6ElectronRejection_                       .push_back(itau->tauID("againstElectronMediumMVA6"));
    tau_TightMVA6ElectronRejection_                        .push_back(itau->tauID("againstElectronTightMVA6"));
    tau_VTightMVA6ElectronRejection_                       .push_back(itau->tauID("againstElectronVTightMVA6"));

    //Cut basedID
    tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_        .push_back(itau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits"));
    tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_       .push_back(itau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits"));
    tau_byTightCombinedIsolationDeltaBetaCorr3Hits_        .push_back(itau->tauID("byTightCombinedIsolationDeltaBetaCorr3Hits"));
    
    //MVA based 2017v2 discriminators
    tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_          .push_back(itau->tauID("byIsolationMVArun2017v2DBoldDMwLTraw2017"));
    tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017_      .push_back(itau->tauID("byVVLooseIsolationMVArun2017v2DBoldDMwLT2017"));
    tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_       .push_back(itau->tauID("byVLooseIsolationMVArun2017v2DBoldDMwLT2017"));
    tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_        .push_back(itau->tauID("byLooseIsolationMVArun2017v2DBoldDMwLT2017"));
    tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_       .push_back(itau->tauID("byMediumIsolationMVArun2017v2DBoldDMwLT2017"));
    tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_        .push_back(itau->tauID("byTightIsolationMVArun2017v2DBoldDMwLT2017"));
    tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_       .push_back(itau->tauID("byVTightIsolationMVArun2017v2DBoldDMwLT2017"));
    tau_byVVTightIsolationMVArun2017v2DBoldDMwLT2017_      .push_back(itau->tauID("byVVTightIsolationMVArun2017v2DBoldDMwLT2017"));



    //Old discriminators
    //- tauByIsolationMVArun2v1DBnewDMwLTraw_                   .push_back(itau->tauID("byIsolationMVArun2v1DBnewDMwLTraw"));
    //- tauByIsolationMVArun2v1PWnewDMwLTraw_                   .push_back(itau->tauID("byIsolationMVArun2v1PWnewDMwLTraw"));
    //- tauByVTightIsolationMVArun2v1DBnewDMwLT_                .push_back(itau->tauID("byVTightIsolationMVArun2v1DBnewDMwLT"));
    //- tauByVTightIsolationMVArun2v1PWnewDMwLT_                .push_back(itau->tauID("byVTightIsolationMVArun2v1PWnewDMwLT"));
    //- tauByTightIsolationMVArun2v1DBnewDMwLT_                 .push_back(itau->tauID("byTightIsolationMVArun2v1DBnewDMwLT"));
    //- tauByTightIsolationMVArun2v1PWnewDMwLT_                 .push_back(itau->tauID("byTightIsolationMVArun2v1PWnewDMwLT"));
    //- tauByMediumIsolationMVArun2v1DBnewDMwLT_                .push_back(itau->tauID("byMediumIsolationMVArun2v1DBnewDMwLT"));
    //- tauByMediumIsolationMVArun2v1PWnewDMwLT_                .push_back(itau->tauID("byMediumIsolationMVArun2v1PWnewDMwLT"));
    //- tauByLooseIsolationMVArun2v1DBnewDMwLT_                 .push_back(itau->tauID("byLooseIsolationMVArun2v1DBnewDMwLT"));
    //- tauByLooseIsolationMVArun2v1PWnewDMwLT_                 .push_back(itau->tauID("byLooseIsolationMVArun2v1PWnewDMwLT"));
    //- tauByVLooseIsolationMVArun2v1DBnewDMwLT_                .push_back(itau->tauID("byVLooseIsolationMVArun2v1DBnewDMwLT"));
    //- tauByVLooseIsolationMVArun2v1PWnewDMwLT_                .push_back(itau->tauID("byVLooseIsolationMVArun2v1PWnewDMwLT"));
    //- tauByIsolationMVArun2v1DBoldDMwLTraw_                   .push_back(itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw"));
    //- tauByIsolationMVArun2v1PWoldDMwLTraw_                   .push_back(itau->tauID("byIsolationMVArun2v1PWoldDMwLTraw"));
    //- tauByVTightIsolationMVArun2v1DBoldDMwLT_                .push_back(itau->tauID("byVTightIsolationMVArun2v1DBoldDMwLT"));
    //- tauByVTightIsolationMVArun2v1PWoldDMwLT_                .push_back(itau->tauID("byVTightIsolationMVArun2v1PWoldDMwLT"));
    //- tauByTightIsolationMVArun2v1DBoldDMwLT_                 .push_back(itau->tauID("byTightIsolationMVArun2v1DBoldDMwLT"));
    //- tauByTightIsolationMVArun2v1PWoldDMwLT_                 .push_back(itau->tauID("byTightIsolationMVArun2v1PWoldDMwLT"));
    //- tauByMediumIsolationMVArun2v1DBoldDMwLT_                .push_back(itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT"));
    //- tauByMediumIsolationMVArun2v1PWoldDMwLT_                .push_back(itau->tauID("byMediumIsolationMVArun2v1PWoldDMwLT"));
    //- tauByLooseIsolationMVArun2v1DBoldDMwLT_                 .push_back(itau->tauID("byLooseIsolationMVArun2v1DBoldDMwLT"));
    //- tauByLooseIsolationMVArun2v1PWoldDMwLT_                 .push_back(itau->tauID("byLooseIsolationMVArun2v1PWoldDMwLT"));
    //- tauByVLooseIsolationMVArun2v1DBoldDMwLT_                .push_back(itau->tauID("byVLooseIsolationMVArun2v1DBoldDMwLT"));
    //- tauByVLooseIsolationMVArun2v1PWoldDMwLT_                .push_back(itau->tauID("byVLooseIsolationMVArun2v1PWoldDMwLT"));
    
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
  tau_Px_                                             .clear();
  tau_Py_                                             .clear();
  tau_Pz_                                             .clear();
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
  tau_LeadChargedHadronExists_                        .clear();
  tau_LeadChargedHadronEta_                           .clear();
  tau_LeadChargedHadronPhi_                           .clear();
  tau_LeadChargedHadronPt_                            .clear();
  tau_dz_                                             .clear();
  tau_dxy_                                            .clear();

  tau_decayModeFinding_                              .clear();
  tau_decayModeFindingNewDMs_                        .clear();
  tau_VLooseMVA6ElectronRejection_                   .clear();
  tau_LooseMVA6ElectronRejection_                    .clear();
  tau_MediumMVA6ElectronRejection_                   .clear();
  tau_TightMVA6ElectronRejection_                    .clear();
  tau_VTightMVA6ElectronRejection_                   .clear();
  tau_LooseMuonRejection3_                           .clear();
  tau_TightMuonRejection3_                           .clear();
  tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_    .clear();
  tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_   .clear();
  tau_byTightCombinedIsolationDeltaBetaCorr3Hits_    .clear();

  tau_byIsolationMVArun2017v2DBoldDMwLTraw2017_       .clear();
  tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017_   .clear();
  tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_    .clear();
  tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_     .clear();
  tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_    .clear();
  tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_     .clear();
  tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_    .clear();
  tau_byVVTightIsolationMVArun2017v2DBoldDMwLT2017_   .clear();

  // tauByIsolationMVArun2v1DBnewDMwLTraw_              .clear();
  // tauByIsolationMVArun2v1DBoldDMwLTraw_              .clear();
  // tauByIsolationMVArun2v1PWnewDMwLTraw_              .clear();
  // tauByIsolationMVArun2v1PWoldDMwLTraw_              .clear();
  // tauByVTightIsolationMVArun2v1DBnewDMwLT_           .clear();
  // tauByVTightIsolationMVArun2v1DBoldDMwLT_           .clear();
  // tauByVTightIsolationMVArun2v1PWnewDMwLT_           .clear();
  // tauByVTightIsolationMVArun2v1PWoldDMwLT_           .clear();
  // tauByTightIsolationMVArun2v1DBnewDMwLT_            .clear();
  // tauByTightIsolationMVArun2v1DBoldDMwLT_            .clear();
  // tauByTightIsolationMVArun2v1PWnewDMwLT_            .clear();
  // tauByTightIsolationMVArun2v1PWoldDMwLT_            .clear();
  // tauByMediumIsolationMVArun2v1DBnewDMwLT_           .clear();
  // tauByMediumIsolationMVArun2v1DBoldDMwLT_           .clear();
  // tauByMediumIsolationMVArun2v1PWnewDMwLT_           .clear();
  // tauByMediumIsolationMVArun2v1PWoldDMwLT_           .clear();
  // tauByLooseIsolationMVArun2v1DBnewDMwLT_            .clear();
  // tauByLooseIsolationMVArun2v1DBoldDMwLT_            .clear();
  // tauByLooseIsolationMVArun2v1PWnewDMwLT_            .clear();
  // tauByLooseIsolationMVArun2v1PWoldDMwLT_            .clear();
  // tauByVLooseIsolationMVArun2v1DBnewDMwLT_           .clear();
  // tauByVLooseIsolationMVArun2v1DBoldDMwLT_           .clear();
  // tauByVLooseIsolationMVArun2v1PWnewDMwLT_           .clear();
  // tauByVLooseIsolationMVArun2v1PWoldDMwLT_           .clear();

}
