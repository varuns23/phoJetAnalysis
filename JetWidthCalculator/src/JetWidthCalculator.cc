#include "phoJetAnalysis/JetWidthCalculator/interface/JetWidthCalculator.hh"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include <math.h>

JetWidthCalculator::JetWidthCalculator(const pat::Jet& jet) {

  double pfCand1pt_      = 0;
  double pfCand2pt_      = 0;  
 
  double etSum_          = 0;
  double etaSum_         = 0;
  double etaSqSum_       = 0;
  double phiSum_         = 0;
  double phiSqSum_       = 0;
  
  etaWidth_              = 0;
  phiWidth_              = 0;

  ptSum_                 = 0;
  pfCand12PtSum_         = 0;
  pt12ratio_             = 0;

  ConstEt_         .clear();
  ConstPt_         .clear();
  ConstPdgId_ .clear();
  
  const uint32_t packedCands = jet.numberOfDaughters();
  
  for(uint32_t i = 0; i < packedCands; i++) {

    const reco::Candidate *pfCand = jet.daughter(i);

    ConstEt_    .push_back(pfCand->et());
    ConstPt_    .push_back(pfCand->pt());
    ConstPdgId_ .push_back(pfCand->pdgId());
    
    etSum_ += pfCand->et();
    ptSum_ += pfCand->pt();
    
    etaSum_   += (pfCand->eta() * pfCand->et());
    etaSqSum_ += (pfCand->eta() * pfCand->eta() * pfCand->et());
    
    phiSum_   += (pfCand->phi() * pfCand->et());
    phiSqSum_ += (pfCand->phi() * pfCand->phi() * pfCand->et());
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
  double etaAve_   = etaSum_/etSum_;
  double etaSqAve_ = etaSqSum_/etSum_;
  etaWidth_        = sqrt(etaSqAve_ - (etaAve_ * etaAve_));
  
  double phiAve_   = phiSum_ / etSum_;
  double phiSqAve_ = phiSqSum_ / etSum_;
  phiWidth_        = sqrt(phiSqAve_ - (phiAve_ * phiAve_));
  
}

JetWidthCalculator::~JetWidthCalculator(){
}

