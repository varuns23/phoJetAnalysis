#include "phoJetAnalysis/JetWidthCalculator/interface/JetWidthCalculator.hh"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include <math.h>

JetWidthCalculator::JetWidthCalculator(const pat::Jet& jet) {

  float pfCand1pt_      = 0.;
  float pfCand2pt_      = 0.;  
 
  float etSum_          = 0.;
  float etaSum_         = 0.;
  float etaSqSum_       = 0.;
  float phiSum_         = 0.;
  float phiSqSum_       = 0.;
  
  etaWidth_              = 0.;
  phiWidth_              = 0.;

  ptSum_                 = 0.;
  pfCand12PtSum_         = 0.;
  pt12ratio_             = 0.;

  nPhotons_              = 0;
  nCHPions_              = 0;
  nMiscParticles_        = 0;

  ConstPt_         .clear();
  ConstEt_         .clear();
  ConstEta_        .clear();
  ConstPhi_        .clear();
  ConstPdgId_      .clear();
  MiscPdgId_       .clear();

  std::vector<std::pair<float, const reco::Candidate*>> jetDaughters;
  const uint32_t packedCands = jet.numberOfDaughters();
  
  for(uint32_t i = 0; i < packedCands; i++) {


    const reco::Candidate *pfCand = jet.daughter(i);

    jetDaughters.push_back({pfCand->pt(), pfCand});

    //if(abs(pfCand->pdgId()) == 211){
    //  nCHPions_++;
    //} else if(pfCand->pdgId() == 22){
    //  nPhotons_++;
    //}
    //else{
    //  nMiscParticles_++;
    //  MiscPdgId_ .push_back(pfCand->pdgId());
    //}
    
    etSum_ += pfCand->et();
    ptSum_ += pfCand->pt();
    
    etaSum_   += (pfCand->eta() * pfCand->et());
    etaSqSum_ += (pfCand->eta() * pfCand->eta() * pfCand->et());
    
    phiSum_   += (pfCand->phi() * pfCand->et());
    phiSqSum_ += (pfCand->phi() * pfCand->phi() * pfCand->et());
  }

  std::sort(jetDaughters.begin(),jetDaughters.end(),[](const auto& p1, const auto& p2){return p1.first>p2.first;});
  for(uint32_t j = 0; j < jetDaughters.size(); j++){
    const reco::Candidate *pfCand = jetDaughters.at(j).second;

    ConstPt_    .push_back(pfCand->pt());
    ConstEt_    .push_back(pfCand->et());
    ConstEta_   .push_back(pfCand->eta());
    ConstPhi_   .push_back(pfCand->phi());
    ConstPdgId_ .push_back(pfCand->pdgId());
  }

 
  if (packedCands>1){
    pfCand1pt_  = jet.daughter(0)->pt();
    pfCand2pt_  = jet.daughter(1)->pt();
  }
  else{
    pfCand1pt_ = jet.daughter(0)->pt(); 
  }

  pfCand12PtSum_ = pfCand1pt_ + pfCand2pt_;
  pt12ratio_     = (pfCand12PtSum_/ptSum_);
  
  if(etSum_ < 0.000001) etSum_ = 0.000001; // To avoid NaNs
  float etaAve_   = etaSum_/etSum_;
  float etaSqAve_ = etaSqSum_/etSum_;
  etaWidth_        = sqrt(etaSqAve_ - (etaAve_ * etaAve_));
  
  float phiAve_   = phiSum_ / etSum_;
  float phiSqAve_ = phiSqSum_ / etSum_;
  phiWidth_        = sqrt(phiSqAve_ - (phiAve_ * phiAve_));
  
}

JetWidthCalculator::~JetWidthCalculator(){
}

