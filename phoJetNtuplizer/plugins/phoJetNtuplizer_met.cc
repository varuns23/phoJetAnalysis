#include "FWCore/Common/interface/TriggerNames.h"
#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"


UShort_t metFilters_;
float genMET_;
float genMETPhi_;
float caloMET_;
float caloMETPhi_;
float caloMETsumEt_;
float pfMET_;
float pfMETPhi_;
float pfMETCorr_;
float pfMETPhiCorr_;
float pfMETsumEt_;
float pfMETmEtSig_;
float pfMETSig_;
float pfMET_T1JERUp_;
float pfMET_T1JERDo_;
float pfMET_T1JESUp_;
float pfMET_T1JESDo_;
float pfMET_T1UESUp_;
float pfMET_T1UESDo_;
float pfMET_T1TxyPhi_;
float pfMET_T1TxyPt_;
float pfMETPhi_T1JESUp_;
float pfMETPhi_T1JESDo_;
float pfMETPhi_T1UESUp_;
float pfMETPhi_T1UESDo_;

void phoJetNtuplizer::branchMet(TTree* tree){

  if (!is_Data_) {
    tree->Branch("genMET",      &genMET_);
    tree->Branch("genMETPhi",   &genMETPhi_);
  }
  tree->Branch("metFilters",       &metFilters_);
  tree->Branch("caloMET",          &caloMET_);
  tree->Branch("caloMETPhi",       &caloMETPhi_);
  tree->Branch("caloMETsumEt",     &caloMETsumEt_);
  tree->Branch("pfMETCorr",        &pfMETCorr_);
  tree->Branch("pfMETPhiCorr",     &pfMETPhiCorr_);
  tree->Branch("pfMET",            &pfMET_);
  tree->Branch("pfMETPhi",         &pfMETPhi_);
  tree->Branch("pfMETsumEt",       &pfMETsumEt_);
  tree->Branch("pfMETmEtSig",      &pfMETmEtSig_);
  tree->Branch("pfMETSig",         &pfMETSig_);
  tree->Branch("pfMET_T1JERUp",    &pfMET_T1JERUp_);
  tree->Branch("pfMET_T1JERDo",    &pfMET_T1JERDo_);
  tree->Branch("pfMET_T1JESUp",    &pfMET_T1JESUp_);
  tree->Branch("pfMET_T1JESDo",    &pfMET_T1JESDo_);
  tree->Branch("pfMET_T1UESUp",    &pfMET_T1UESUp_);
  tree->Branch("pfMET_T1UESDo",    &pfMET_T1UESDo_);
  tree->Branch("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp_);
  tree->Branch("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo_);
  tree->Branch("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp_);
  tree->Branch("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo_);
}

void phoJetNtuplizer::fillMet(const edm::Event& iEvent, const edm::EventSetup& iSetup){

  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillMET -->BEGIN<-- "<<std::endl;
  
  initMet();

   // https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Early_2018_data
  
  
  std::vector< string > metFilterNames;
  metFilterNames.push_back("Flag_goodVertices"); //0
  metFilterNames.push_back("Flag_globalSuperTightHalo2016Filter"); //1
  metFilterNames.push_back("Flag_HBHENoiseFilter");  // 2
  metFilterNames.push_back("Flag_HBHENoiseIsoFilter"); // 3
  metFilterNames.push_back("Flag_EcalDeadCellTriggerPrimitiveFilter"); //4
  metFilterNames.push_back("Flag_BadPFMuonFilter"); //5
  metFilterNames.push_back("Flag_BadChargedCandidateFilter"); //6
  if(is_Data_)metFilterNames.push_back("Flag_eeBadScFilter"); //7
  //metFilterNames.push_back("ecalBadCalibReducedMINIAODFilter"); //8 // Need to be RE-RUN - done below

  edm::Handle<edm::TriggerResults> patFilterResultsHandle;                                                          
  //iEvent.getByToken(patTrgResultsToken_, patFilterResultsHandle);
  iEvent.getByToken(recoTrgResultsToken_, patFilterResultsHandle);
  edm::TriggerResults const& patFilterResults = *patFilterResultsHandle;

  auto&& filterNames = iEvent.triggerNames(patFilterResults);

  for (unsigned iFilter = 0; iFilter < metFilterNames.size(); ++iFilter){
    unsigned index = filterNames.triggerIndex(metFilterNames[iFilter]);
    if ( index == filterNames.size() ) 
      LogDebug("METFilters") << metFilterNames[iFilter] << " is missing, exiting";
    else {
      if ( !patFilterResults.accept(index) ) {
	setbit(metFilters_, iFilter);
      }
    }
  }

  edm::Handle< bool > passecalBadCalibFilterUpdate ;
  iEvent.getByToken(ecalBadCalibFilterUpdate_token_,passecalBadCalibFilterUpdate);
  bool  _passecalBadCalibFilterUpdate =  (*passecalBadCalibFilterUpdate );
  if(!_passecalBadCalibFilterUpdate) 
    setbit(metFilters_, 8);
  

  edm::Handle<edm::View<pat::MET> > pfmetHandle;
  iEvent.getByToken(pfmetToken_, pfmetHandle);

  if(pfmetHandle.isValid()){
    const pat::MET *pfMET = 0;
    pfMET = &(pfmetHandle->front());

    caloMET_     = pfMET->caloMETPt();
    caloMETPhi_  = pfMET->caloMETPhi();
    caloMETsumEt_= pfMET->caloMETSumEt();
    
    pfMET_       = pfMET->et();
    pfMETPhi_    = pfMET->phi();
    pfMETsumEt_  = pfMET->sumEt();
    pfMETmEtSig_ = (pfMET->mEtSig() < 1.e10) ? pfMET->mEtSig() : 0;
    pfMETSig_    = (pfMET->significance() < 1.e10) ? pfMET->significance() : 0;

    if (!is_Data_) {
      genMET_    = pfMET->genMET()->et();
      genMETPhi_ = pfMET->genMET()->phi();
    }

    //Type-1 smeared MET:
    pfMETCorr_     = pfMET->corPt(pat::MET::Type1Smear);
    pfMETPhiCorr_  = pfMET->corPhi(pat::MET::Type1Smear);
    // Type-1 MET uncertainties
    pfMET_T1JERUp_ = pfMET->shiftedPt(pat::MET::JetResUp);
    pfMET_T1JERDo_ = pfMET->shiftedPt(pat::MET::JetResDown);
    pfMET_T1JESUp_ = pfMET->shiftedPt(pat::MET::JetEnUp);
    pfMET_T1JESDo_ = pfMET->shiftedPt(pat::MET::JetEnDown);
    pfMET_T1UESUp_ = pfMET->shiftedPt(pat::MET::UnclusteredEnUp);
    pfMET_T1UESDo_ = pfMET->shiftedPt(pat::MET::UnclusteredEnDown);
    pfMETPhi_T1JESUp_ = pfMET->shiftedPhi(pat::MET::JetEnUp);
    pfMETPhi_T1JESDo_ = pfMET->shiftedPhi(pat::MET::JetEnDown);
    pfMETPhi_T1UESUp_ = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp);
    pfMETPhi_T1UESDo_ = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown);
  }
  
  if(debug_) std::cout<< "<<DEBUG>>:: Inside phoJetNtuplizer::fillMET -->END<-- "<<std::endl;
}

void phoJetNtuplizer::initMet(){
  metFilters_       = 0;
  genMET_           = -99.;
  genMETPhi_        = -99.;
  caloMET_          = -99.;
  caloMETPhi_       = -99.;
  caloMETsumEt_     = -99.;
  pfMET_            = -99.;
  pfMETPhi_         = -99.;
  pfMETCorr_        = -99.;
  pfMETPhiCorr_     = -99.;
  pfMETsumEt_       = -99.;
  pfMETmEtSig_      = -99.;
  pfMETSig_         = -99.;
  pfMET_T1JERUp_    = -99.;
  pfMET_T1JERDo_    = -99.;
  pfMET_T1JESUp_    = -99.;
  pfMET_T1JESDo_    = -99.;
  pfMET_T1UESUp_    = -99.;
  pfMET_T1UESDo_    = -99.;
  pfMET_T1TxyPhi_   = -99.;
  pfMET_T1TxyPt_    = -99.;
  pfMETPhi_T1JESUp_ = -99.;
  pfMETPhi_T1JESDo_ = -99.;
  pfMETPhi_T1UESUp_ = -99.;
  pfMETPhi_T1UESDo_ = -99.;

}
