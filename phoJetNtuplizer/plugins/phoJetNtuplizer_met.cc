#include "FWCore/Common/interface/TriggerNames.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"


Int_t metFilters_;
float genMET_;
float genMETPhi_;
float pfMET_;
float pfMETPhi_;
float pfMETsumEt_;
float pfMETmEtSig_;
float pfMETSig_;

void phoJetNtuplizer::branchMet(TTree* tree){

  if (runGenInfo_) {
    tree->Branch("genMET",      &genMET_);
    tree->Branch("genMETPhi",   &genMETPhi_);
  }
  tree->Branch("metFilters",       &metFilters_);
  tree->Branch("pfMET",            &pfMET_);
  tree->Branch("pfMETPhi",         &pfMETPhi_);
  tree->Branch("pfMETsumEt",       &pfMETsumEt_);
  tree->Branch("pfMETmEtSig",      &pfMETmEtSig_);
  tree->Branch("pfMETSig",         &pfMETSig_);
}

void phoJetNtuplizer::fillMet(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  initMet();

  std::vector< string > metFilterNames;
  metFilterNames.push_back("Flag_HBHENoiseFilter");  // 2**1
  metFilterNames.push_back("Flag_HBHENoiseIsoFilter"); // 2**2
  metFilterNames.push_back("Flag_globalTightHalo2016Filter"); //2**3
  metFilterNames.push_back("Flag_goodVertices"); //2**4
  metFilterNames.push_back("Flag_eeBadScFilter"); //2**5
  metFilterNames.push_back("Flag_EcalDeadCellTriggerPrimitiveFilter"); //2**6
  metFilterNames.push_back("Flag_badMuons"); //2**7
  metFilterNames.push_back("Flag_duplicateMuons"); //2**8
  metFilterNames.push_back("Flag_noBadMuons"); //2**9

  edm::Handle<edm::TriggerResults> patFilterResultsHandle;                                                          
  iEvent.getByToken(patTrgResultsToken_, patFilterResultsHandle);
  edm::TriggerResults const& patFilterResults = *patFilterResultsHandle;

  auto&& filterNames = iEvent.triggerNames(patFilterResults);

  for (unsigned iFilter = 0; iFilter < metFilterNames.size(); ++iFilter){
    unsigned index = filterNames.triggerIndex(metFilterNames[iFilter]);
    if ( index == filterNames.size() ) 
      LogDebug("METFilters") << metFilterNames[iFilter] << " is missing, exiting";
    else {
      if ( !patFilterResults.accept(index) ) {
	if (iFilter <= 5) metFilters_ += pow(2, iFilter+1);
	else metFilters_ += pow(2, iFilter+3);
      }
    }
  }

  //edm::EDGetTokenT<bool> BadChCandFilterToken_;
  //BadChCandFilterToken_ = consumes<bool>(edm::InputTag("BadChargedCandidateFilter"));

  edm::Handle<bool> ifilterbadChCand;
  iEvent.getByToken(BadChCandFilterToken_, ifilterbadChCand);
  bool filterbadChCandidate = *ifilterbadChCand;

  //edm::EDGetTokenT<bool> BadPFMuonFilterToken_;
  //BadPFMuonFilterToken_ = consumes<bool>(edm::InputTag("BadPFMuonFilter"));

  edm::Handle<bool> ifilterbadPFMuon;
  iEvent.getByToken(BadPFMuonFilterToken_, ifilterbadPFMuon);
  bool filterbadPFMuon = *ifilterbadPFMuon;


  if ( filterbadPFMuon      ) metFilters_ += pow(2, 7);
  if ( filterbadChCandidate ) metFilters_ += pow(2, 8);

  edm::Handle<edm::View<pat::MET> > pfmetHandle;
  iEvent.getByToken(pfmetToken_, pfmetHandle);

  if(pfmetHandle.isValid()){
    const pat::MET *pfMET = 0;
    pfMET = &(pfmetHandle->front());

    pfMET_       = pfMET->et();
    pfMETPhi_    = pfMET->phi();
    pfMETsumEt_  = pfMET->sumEt();
    pfMETmEtSig_ = (pfMET->mEtSig() < 1.e10) ? pfMET->mEtSig() : 0;
    pfMETSig_    = (pfMET->significance() < 1.e10) ? pfMET->significance() : 0;;

    if (!isData_) {
      genMET_    = pfMET->genMET()->et();
      genMETPhi_ = pfMET->genMET()->phi();
    }
  }
}

void phoJetNtuplizer::initMet(){
  metFilters_ = 0;
  genMET_     = -99.;
  genMETPhi_  = -99.;
  pfMET_      = -99.;
  pfMETPhi_   = -99.;
  pfMETsumEt_ = -99.;
  pfMETmEtSig_= -99.;
  pfMETSig_   = -99.;
}
