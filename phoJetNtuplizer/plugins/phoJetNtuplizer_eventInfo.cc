#include "map"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"

Int_t         run_;
Long64_t      event_;
Int_t         lumis_;
Bool_t        isData_;
Int_t         nVtx_;
float         vtxX_;
float         vtxY_;
float         vtxZ_;
int           vtxNtrks_;
bool          vtx_isFake_;
int           vtx_ndof_;
float         vtx_rho_;
bool          isGoodVtx_;
int           nGoodVtx_;
float         rho_;
float         rhoCentral_;

ULong64_t     HLTEleMuX_;
ULong64_t     HLTEleMuXIsPrescaled_;
ULong64_t     HLTEleMuXRejectedByPS_;

ULong64_t     HLTPho_;
ULong64_t     HLTPhoIsPrescaled_;
ULong64_t     HLTPhoRejectedByPS_;

ULong64_t     HLTTau_;
ULong64_t     HLTTauIsPrescaled_;
ULong64_t     HLTTauRejectedByPS_;

ULong64_t     HLTMet_;
ULong64_t     HLTMetIsPrescaled_;
ULong64_t     HLTMetRejectedByPS_;

ULong64_t     HLTJet_;
ULong64_t     HLTJetIsPrescaled_;
ULong64_t     HLTJetRejectedByPS_;

void phoJetNtuplizer::branchEventInfo(TTree* tree) {

  tree->Branch("run",                  &run_);
  tree->Branch("event",                &event_);
  tree->Branch("lumis",                &lumis_);
  tree->Branch("isData",               &isData_);
  tree->Branch("nVtx",                 &nVtx_);
  tree->Branch("vtxX",                 &vtxX_);
  tree->Branch("vtxY",                 &vtxY_);
  tree->Branch("vtxZ",                 &vtxZ_);
  tree->Branch("vtxNtrks",             &vtxNtrks_);
  tree->Branch("vtx_isFake",           &vtx_isFake_);
  tree->Branch("vtx_ndof",             &vtx_ndof_);
  tree->Branch("vtx_rho",              &vtx_rho_);
  tree->Branch("isGoodVtx",            &isGoodVtx_);
  tree->Branch("nGoodVtx",             &nGoodVtx_);
  tree->Branch("rho",                  &rho_);
  tree->Branch("rhoCentral",           &rhoCentral_);
  tree->Branch("HLTEleMuX",            &HLTEleMuX_);
  tree->Branch("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled_);
  tree->Branch("HLTEleMuXRejectedByPS",&HLTEleMuXRejectedByPS_); 
  tree->Branch("HLTPho",               &HLTPho_);
  tree->Branch("HLTPhoIsPrescaled",    &HLTPhoIsPrescaled_);
  tree->Branch("HLTPhoRejectedByPS",   &HLTPhoRejectedByPS_);
  tree->Branch("HLTTau",               &HLTTau_);
  tree->Branch("HLTTauIsPrescaled",    &HLTTauIsPrescaled_);
  tree->Branch("HLTTauRejectedByPS",   &HLTTauRejectedByPS_);
  tree->Branch("HLTMet",               &HLTMet_);
  tree->Branch("HLTMetIsPrescaled",    &HLTMetIsPrescaled_);
  tree->Branch("HLTMetRejectedByPS",   &HLTMetRejectedByPS_);
  tree->Branch("HLTJet",               &HLTJet_);
  tree->Branch("HLTJetIsPrescaled",    &HLTJetIsPrescaled_);
  tree->Branch("HLTJetRejectedByPS",   &HLTJetRejectedByPS_);
}

void phoJetNtuplizer::fillEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillEventInfo -->BEGIN<-- "<<std::endl;
  
  initEventInfo();

  edm::Handle<double> rhoHandle;
  iEvent.getByToken(rhoToken_, rhoHandle);

  edm::Handle<double> rhoCentralHandle;
  iEvent.getByToken(rhoCentralToken_, rhoCentralHandle);

  // Run Event Lumi
  run_    = iEvent.id().run();
  event_  = iEvent.id().event();
  lumis_  = iEvent.luminosityBlock();
  isData_ = iEvent.isRealData();
  rho_    = *(rhoHandle.product());
  if (rhoCentralHandle.isValid()) 
    rhoCentral_ = *(rhoCentralHandle.product());
  else 
    rhoCentral_ = -99.;

  // Vertex Information---
  edm::Handle<reco::VertexCollection> vtxHandle;
  iEvent.getByToken(vtxToken_, vtxHandle);

  if (!vtxHandle.isValid()) {
    edm::LogWarning("phoJetNtuplizer") << "no vertex info in event";
    return;
  }

  for(reco::VertexCollection::const_iterator iv = vtxHandle->begin(); iv != vtxHandle->end(); ++iv){

    if(nVtx_ == 0){
      vtxX_       = iv->x();
      vtxY_       = iv->y();
      vtxZ_       = iv->z();
      vtxNtrks_   = iv->nTracks();

      vtx_isFake_ = iv->isFake();
      vtx_ndof_   = iv->ndof();
      vtx_rho_    = iv->position().rho();


      isGoodVtx_ = false;
      if (!iv->isFake() && iv->ndof() > 4. && fabs(iv->z()) <= 24. && fabs(iv->position().rho()) <= 2.)
	isGoodVtx_ = true;
    }
    if (!iv->isFake() && iv->ndof() > 4. && fabs(iv->z()) <= 24. && fabs(iv->position().rho()) <= 2.) 
      nGoodVtx_++;
    
    nVtx_++;
  }

  edm::Handle<edm::TriggerResults> trgResultsHandle;
  iEvent.getByToken(trgResultsToken_, trgResultsHandle);

  bool cfg_changed = true;
  HLTConfigProvider hltCfg;
  hltCfg.init(iEvent.getRun(), iSetup, trgResultsProcess_, cfg_changed);

  hltPrescaleProvider_.init(iEvent.getRun(), iSetup, trgResultsProcess_, cfg_changed);
  const int prescleSet = hltPrescaleProvider_.prescaleSet(iEvent, iSetup);

  const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);

  for (size_t i = 0; i < trgNames.size(); ++i) {
    const string &name = trgNames.triggerName(i);

    // HLT name => bit correspondence
    // Electron or Muon or Cross triggers
    int bitEleMuX = -1;
    if      (name.find("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v")                         != string::npos) bitEleMuX = 0;
    else if (name.find("HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v")                         != string::npos) bitEleMuX = 1;
    else if (name.find("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v")                         != string::npos) bitEleMuX = 2;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v")                                    != string::npos) bitEleMuX = 3; 
    else if (name.find("HLT_Ele27_eta2p1_WPLoose_Gsf_v")                             != string::npos) bitEleMuX = 4;
    else if (name.find("HLT_Ele35_WPTight_Gsf_v")                                    != string::npos) bitEleMuX = 5; 
    else if (name.find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v")                            != string::npos) bitEleMuX = 6; 
    else if (name.find("HLT_Ele135_CaloIdVT_GsfTrkIdT_v")                            != string::npos) bitEleMuX = 7; 
    else if (name.find("HLT_Ele145_CaloIdVT_GsfTrkIdT_v")                            != string::npos) bitEleMuX = 8; 
    else if (name.find("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v")                    != string::npos) bitEleMuX = 9;
    else if (name.find("HLT_DoubleEle25_CaloIdL_MW_v")                               != string::npos) bitEleMuX = 10;
    else if (name.find("HLT_DoubleEle33_CaloIdL_MW_v")                               != string::npos) bitEleMuX = 11;
    else if (name.find("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v")                    != string::npos) bitEleMuX = 12;
    else if (name.find("HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v")                 != string::npos) bitEleMuX = 13;
    else if (name.find("HLT_Ele17_Ele12_CaloId_TrackId_Iso_DZ_v")                    != string::npos) bitEleMuX = 14;
    else if (name.find("HLT_DoubleEle33_CaloId_GsfTrackIdVL_v")                      != string::npos) bitEleMuX = 15;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v")                   != string::npos) bitEleMuX = 16;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")                != string::npos) bitEleMuX = 17;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v") != string::npos) bitEleMuX = 18;
    else if (name.find("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v")                    != string::npos) bitEleMuX = 19;
    else if (name.find("HLT_IsoTkMu24_v")                                            != string::npos) bitEleMuX = 20;
    else if (name.find("HLT_IsoMu27_v")                                              != string::npos) bitEleMuX = 21;
    else if (name.find("HLT_Mu50_v")                                                 != string::npos) bitEleMuX = 22;
    else if (name.find("HLT_DoubleMu20_7_Mass0to30_L1_DM4_v")                        != string::npos) bitEleMuX = 23;
    else if (name.find("HLT_DoubleMu20_7_Mass0to30_Photon23_v")                      != string::npos) bitEleMuX = 24;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v")                         != string::npos) bitEleMuX = 25;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v")                      != string::npos) bitEleMuX = 26;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v")                != string::npos) bitEleMuX = 27;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v")              != string::npos) bitEleMuX = 28;
    else if (name.find("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")                  != string::npos) bitEleMuX = 29;
    else if (name.find("HLT_DoubleIsoMu20_eta2p1_v")                                 != string::npos) bitEleMuX = 30;
    else if (name.find("HLT_TripleMu_10_5_5_DZ_v")                                   != string::npos) bitEleMuX = 31;
    else if (name.find("HLT_TripleMu_12_10_5_v")                                     != string::npos) bitEleMuX = 32;
    else if (name.find("HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v")                  != string::npos) bitEleMuX = 33;
    else if (name.find("HLT_Mu17_Photon30_CaloIdL_L1ISO_v")                          != string::npos) bitEleMuX = 34;
    else if (name.find("HLT_Mu17_Photon35_CaloIdL_L1ISO_v")                          != string::npos) bitEleMuX = 35;
    else if (name.find("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v")          != string::npos) bitEleMuX = 36;
    else if (name.find("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")       != string::npos) bitEleMuX = 37;
    else if (name.find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v")           != string::npos) bitEleMuX = 38;
    else if (name.find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v")        != string::npos) bitEleMuX = 39;
    else if (name.find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v")                         != string::npos) bitEleMuX = 40;
    else if (name.find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v")                          != string::npos) bitEleMuX = 41;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v")             != string::npos) bitEleMuX = 42;
    else if (name.find("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v")             != string::npos) bitEleMuX = 43;
    else if (name.find("HLT_IsoMu17_eta2p1_LooseIsoPFTau20_v")                       != string::npos) bitEleMuX = 44;
    else if (name.find("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_v")                       != string::npos) bitEleMuX = 45;
    else if (name.find("HLT_Ele27_WPTight_Gsf_L1JetTauSeeded_v")                     != string::npos) bitEleMuX = 46;
    else if (name.find("HLT_Ele30_WPTight_Gsf_L1JetTauSeeded_v")                     != string::npos) bitEleMuX = 47;
    else if (name.find("HLT_Ele32_WPTight_Gsf_L1JetTauSeeded_v")                     != string::npos) bitEleMuX = 48;
    else if (name.find("HLT_Ele32_WPTight_Gsf_L1DoubleEG_v")                         != string::npos) bitEleMuX = 49;
    else if (name.find("HLT_DiEle27_WPTightCaloOnly_L1DoubleEG_v")                   != string::npos) bitEleMuX = 50;
    else if (name.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v")          != string::npos) bitEleMuX = 51;
    else if (name.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")       != string::npos) bitEleMuX = 52;
    else if (name.find("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v")                 != string::npos) bitEleMuX = 53;
    else if (name.find("HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v")                       != string::npos) bitEleMuX = 54;
    else if (name.find("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v")                 != string::npos) bitEleMuX = 55;
    else if (name.find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v")                       != string::npos) bitEleMuX = 56;
    else if (name.find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v")                      != string::npos) bitEleMuX = 57;
    else if (name.find("HLT_Mu12_DoublePhoton20_v")                                  != string::npos) bitEleMuX = 58;

    // Photon triggers
    int bitPho    = -1;
    if      (name.find("HLT_Photon22_v")                    != string::npos) bitPho =  0; //bit0(lowest)
    else if (name.find("HLT_Photon30_v")                    != string::npos) bitPho =  1; 
    else if (name.find("HLT_Photon33_v")                    != string::npos) bitPho =  2; // 2017
    else if (name.find("HLT_Photon36_v")                    != string::npos) bitPho =  3; 
    else if (name.find("HLT_Photon50_v")                    != string::npos) bitPho =  4; 
    else if (name.find("HLT_Photon75_v")                    != string::npos) bitPho =  5; 
    else if (name.find("HLT_Photon90_v")                    != string::npos) bitPho =  6; 
    else if (name.find("HLT_Photon120_v")                   != string::npos) bitPho =  7; 
    else if (name.find("HLT_Photon150_v")                   != string::npos) bitPho =  8; // 2017
    else if (name.find("HLT_Photon165_HE10_v")              != string::npos) bitPho =  9; 
    else if (name.find("HLT_Photon175_v")                   != string::npos) bitPho = 10; 
    else if (name.find("HLT_Photon200_v")                   != string::npos) bitPho = 11; // 2017
    else if (name.find("HLT_Photon250_v")                   != string::npos) bitPho = 12; // 2017
    else if (name.find("HLT_Photon250_NoHE_v")              != string::npos) bitPho = 13; 
    else if (name.find("HLT_Photon300_NoHE_v")              != string::npos) bitPho = 14; 
    else if (name.find("HLT_Photon500_v")                   != string::npos) bitPho = 15; 
    else if (name.find("HLT_Photon600_v")                   != string::npos) bitPho = 16;
    else if (name.find("HLT_DoublePhoton33_CaloIdL_v")      != string::npos) bitPho = 17; // 2017
    else if (name.find("HLT_DoublePhoton70_v")              != string::npos) bitPho = 18; // 2017
    else if (name.find("HLT_DoublePhoton85_v")              != string::npos) bitPho = 19; // 2017
    else if (name.find("HLT_TriplePhoton_20_20_20_CaloIdLV2_v")             != string::npos) bitPho = 20; //2017
    else if (name.find("HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_v")      != string::npos) bitPho = 21; //2017
    else if (name.find("HLT_TriplePhoton_30_30_10_CaloIdLV2_v")             != string::npos) bitPho = 22; //2017
    else if (name.find("HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_v")      != string::npos) bitPho = 23; //2017
    else if (name.find("HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_v")       != string::npos) bitPho = 24; //2017
    else if (name.find("HLT_Photon90_CaloIdL_PFHT600_v")                    != string::npos) bitPho = 25;
    else if (name.find("HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v")  != string::npos) bitPho = 26;
    else if (name.find("HLT_Photon135_PFMET100_v")                          != string::npos) bitPho = 27;
    else if (name.find("HLT_Photon22_R9Id90_HE10_IsoM_v")                   != string::npos) bitPho = 28;
    else if (name.find("HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_v")       != string::npos) bitPho = 29;
    else if (name.find("HLT_Photon50_R9Id90_HE10_IsoM_v")                   != string::npos) bitPho = 30;
    else if (name.find("HLT_Photon60_R9Id90_CaloIdL_IsoL_v")                != string::npos) bitPho = 31;
    else if (name.find("HLT_Photon75_R9Id90_HE10_IsoM_v")                   != string::npos) bitPho = 32;
    else if (name.find("HLT_Photon90_R9Id90_HE10_IsoM_v")                   != string::npos) bitPho = 33;
    else if (name.find("HLT_Photon120_R9Id90_HE10_IsoM_v")                  != string::npos) bitPho = 34;
    else if (name.find("HLT_Photon165_R9Id90_HE10_IsoM_v")                  != string::npos) bitPho = 35;
    else if (name.find("HLT_ECALHT800_v")                                   != string::npos) bitPho = 36;
    else if (name.find("HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15_v") != string::npos) bitPho = 37; 
    else if (name.find("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v")                             != string::npos) bitPho = 38;
    else if (name.find("HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70_v")        != string::npos) bitPho = 39;
    else if (name.find("HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v")        != string::npos) bitPho = 40;
    else if (name.find("HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v")         != string::npos) bitPho = 41;

    //Tau triggers
    int bitTau = -1;
    if      (name.find("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1")           != string::npos) bitTau =  0;
    else if (name.find("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1") != string::npos) bitTau =  1;
    else if (name.find("HLT_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1")         != string::npos) bitTau =  2;
    else if (name.find("HLT_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1")        != string::npos) bitTau =  3;
    else if (name.find("HLT_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1")                 != string::npos) bitTau =  4;

    // MET triggers
    int bitMet = -1;
    if      (name.find("HLT_PFMET120_PFMHT120_IDTight_PFHT60_v")         != string::npos) bitMet =  0;
    else if (name.find("HLT_PFMET120_PFMHT120_IDTight_v")                != string::npos) bitMet =  1;
    else if (name.find("HLT_PFMET130_PFMHT130_IDTight_v")                != string::npos) bitMet =  2;
    else if (name.find("HLT_PFMET140_PFMHT140_IDTight_v")                != string::npos) bitMet =  3;
    else if (name.find("HLT_PFMET200_HBHE_BeamHaloCleaned_v")            != string::npos) bitMet =  4;
    else if (name.find("HLT_PFMET250_HBHECleaned_v")                     != string::npos) bitMet =  5;
    else if (name.find("HLT_PFMET300_HBHECleaned_v")                     != string::npos) bitMet =  6;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v") != string::npos) bitMet =  7; 
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")        != string::npos) bitMet =  8; 
    else if (name.find("HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_v")        != string::npos) bitMet =  9;
    else if (name.find("HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_v")        != string::npos) bitMet = 10;
    else if (name.find("HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_v")  != string::npos) bitMet = 11;
    else if (name.find("HLT_PFMETTypeOne130_PFMHT130_IDTight_v")         != string::npos) bitMet = 12;
    else if (name.find("HLT_PFMETTypeOne140_PFMHT140_IDTight_v")         != string::npos) bitMet = 13;
    else if (name.find("HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v")     != string::npos) bitMet = 14;


    //Jet triggers
    int bitJet    = -1;
    if      (name.find("HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v")                    != string::npos) bitJet =  0;
    else if (name.find("HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v")                    != string::npos) bitJet =  1; 
    else if (name.find("HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v")                != string::npos) bitJet =  2; 
    else if (name.find("HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v")                != string::npos) bitJet =  3; 
    else if (name.find("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v")                      != string::npos) bitJet =  4;
    else if (name.find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v")                    != string::npos) bitJet =  5;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")                    != string::npos) bitJet =  6;
    else if (name.find("HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != string::npos) bitJet =  7;
    else if (name.find("HLT_PFMET170_HBHECleaned_v")                                 != string::npos) bitJet =  8;
    else if (name.find("HLT_CaloJet500_NoJetID_v")                                   != string::npos) bitJet =  9;
    else if (name.find("HLT_PFJet40_v")                                              != string::npos) bitJet = 10; 
    else if (name.find("HLT_PFJet60_v")                                              != string::npos) bitJet = 11; 
    else if (name.find("HLT_PFJet80_v")                                              != string::npos) bitJet = 12; 
    else if (name.find("HLT_PFJet140_v")                                             != string::npos) bitJet = 13; 
    else if (name.find("HLT_PFJet200_v")                                             != string::npos) bitJet = 14; 
    else if (name.find("HLT_PFJet260_v")                                             != string::npos) bitJet = 15; 
    else if (name.find("HLT_PFJet320_v")                                             != string::npos) bitJet = 16; 
    else if (name.find("HLT_PFJet400_v")                                             != string::npos) bitJet = 17; 
    else if (name.find("HLT_PFJet450_v")                                             != string::npos) bitJet = 18;     
    else if (name.find("HLT_PFJet500_v")                                             != string::npos) bitJet = 19; 
    else if (name.find("HLT_AK8PFHT700_TrimR0p1PT0p3Mass50_v")                       != string::npos) bitJet = 20; 
    else if (name.find("HLT_AK8PFJet360_TrimMass30_v")                               != string::npos) bitJet = 21;
    else if (name.find("HLT_PFHT300_PFMET110_v")                                     != string::npos) bitJet = 22;
    else if (name.find("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067_v")   != string::npos) bitJet = 23;
    else if (name.find("HLT_PFMET170_HBHE_BeamHaloCleaned_v")                        != string::npos) bitJet = 24;
    else if (name.find("HLT_PFMET300_v")                                             != string::npos) bitJet = 25;
    else if (name.find("HLT_PFMET110_PFMHT110_IDTight_v")                            != string::npos) bitJet = 26;
    else if (name.find("HLT_PFMET120_PFMHT120_IDTight_v")                            != string::npos) bitJet = 27;
    else if (name.find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v")                    != string::npos) bitJet = 28;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")                    != string::npos) bitJet = 29;
    else if (name.find("HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != string::npos) bitJet = 30;
    else if (name.find("HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_v") != string::npos) bitJet = 31;
    else if (name.find("HLT_PFHT800_v")                                              != string::npos) bitJet = 32;
    else if (name.find("HLT_PFHT900_v")                                              != string::npos) bitJet = 33;
    else if (name.find("HLT_PFHT750_4JetPt50_v")                                     != string::npos) bitJet = 34;
    else if (name.find("HLT_PFHT750_4JetPt70_v")                                     != string::npos) bitJet = 35;
    else if (name.find("HLT_PFHT800_4JetPt50_v")                                     != string::npos) bitJet = 36;

    // indicates prescaling and whether trigger was fired or not
    ULong64_t isPrescaled       = (hltCfg.prescaleValue(prescleSet, name)!=1) ? 1 : 0;
    ULong64_t isFired           = (trgResultsHandle->accept(i)) ? 1 : 0;
    ULong64_t isRejectedByHLTPS = (hltCfg.moduleType(hltCfg.moduleLabel(i,trgResultsHandle->index(i)))=="HLTPrescaler") ? 1: 0;

    if(bitEleMuX >= 0){
      HLTEleMuX_             |= (isFired << bitEleMuX);
      HLTEleMuXIsPrescaled_  |= (isPrescaled << bitEleMuX);
      HLTEleMuXRejectedByPS_ |= (isRejectedByHLTPS << bitEleMuX);
    }

    if (bitPho >= 0) {                                                                                                
      HLTPho_             |= (isFired << bitPho);
      HLTPhoIsPrescaled_  |= (isPrescaled << bitPho);
      HLTPhoRejectedByPS_ |= (isRejectedByHLTPS << bitPho);
    }

    if (bitTau >= 0) {                                                                                                
      HLTTau_             |= (isFired << bitTau);
      HLTTauIsPrescaled_  |= (isPrescaled << bitTau);
      HLTTauRejectedByPS_ |= (isRejectedByHLTPS << bitTau);
    }

    if (bitMet >= 0) {                                                                                                
      HLTMet_             |= (isFired << bitMet);
      HLTMetIsPrescaled_  |= (isPrescaled << bitMet);
      HLTMetRejectedByPS_ |= (isRejectedByHLTPS << bitMet);
    }

    if (bitJet >= 0) {                                                                                                
      HLTJet_             |= (isFired << bitJet);
      HLTJetIsPrescaled_  |= (isPrescaled << bitJet);
      HLTJetRejectedByPS_ |= (isRejectedByHLTPS << bitJet);
    }

  }

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillEventInfo -->END<-- "<<std::endl;
}

void phoJetNtuplizer::initEventInfo(){
  nVtx_      = 0;
  run_       = -1;
  event_     = -1;
  lumis_     = -1;
  vtxX_      = -99999.;
  vtxY_      = -99999.;
  vtxZ_      = -99999.;
  vtxNtrks_  = -1;
  vtx_isFake_= true;
  vtx_ndof_  = -1;
  vtx_rho_   = -1.;
  isGoodVtx_ = false;
  nGoodVtx_  = 0;
  rho_       = -99;
  rhoCentral_= -99;

  HLTEleMuX_            = 0;
  HLTEleMuXIsPrescaled_ = 0;
  HLTEleMuXRejectedByPS_ = 0;
  HLTPho_               = 0;                    
  HLTPhoIsPrescaled_    = 0;                    
  HLTPhoRejectedByPS_   = 0;
  HLTTau_               = 0;
  HLTTauIsPrescaled_    = 0;
  HLTTauRejectedByPS_   = 0;
  HLTMet_               = 0;
  HLTMetIsPrescaled_    = 0;
  HLTMetRejectedByPS_   = 0;
  HLTJet_               = 0;
  HLTJetIsPrescaled_    = 0;
  HLTJetRejectedByPS_   = 0;

}
