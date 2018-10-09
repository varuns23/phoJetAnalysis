#ifndef JetWidthCalculator_hh
#define JetWidthCalculator_hh

// This is a simple helper class to compute energy weighted eta and phi
// widths of a jet.  Width in ECal and HCal are available

#include "DataFormats/PatCandidates/interface/Jet.h"
#include <vector>
using namespace std;

class JetWidthCalculator {

public:

  JetWidthCalculator(const pat::Jet&);
  
  virtual ~JetWidthCalculator();

  float getEtaWidth()       {return etaWidth_;}
  float getPhiWidth()       {return phiWidth_;}

  float getPFCandsPtSum()   {return ptSum_;}
  float getPFCand12PtSum()  {return pfCand12PtSum_;}
  float getPFCand12Ratio()  {return pt12ratio_;}


  int getnPhotons()       {return nPhotons_;}
  int getnCHPions()       {return nCHPions_;}
  int getnMiscParticles() {return nMiscParticles_;}


  vector<float> getConstPt()         {return ConstPt_;}
  vector<float> getConstEt()         {return ConstEt_;}
  vector<float> getConstEta()        {return ConstEta_;}
  vector<float> getConstPhi()        {return ConstPhi_;}
  vector<int>   getConstPdgId()      {return ConstPdgId_;}
  vector<int>   getMiscPdgId()       {return MiscPdgId_;}

private:
                                        
  // No default constructor is possible
  JetWidthCalculator();

  // No copy constructor is needed
  JetWidthCalculator(const JetWidthCalculator&);

  // No equality operator is needed
  const JetWidthCalculator& operator=(const JetWidthCalculator&);

  float etaWidth_;
  float phiWidth_;

  float ptSum_;
  float pfCand12PtSum_;
  float pt12ratio_;

  int nPhotons_;
  int nCHPions_;
  int nMiscParticles_;

  vector<float> ConstPt_;
  vector<float> ConstEt_;
  vector<float> ConstEta_;
  vector<float> ConstPhi_;
  vector<int>   ConstPdgId_;
  vector<int>   MiscPdgId_;
  
};

#endif
