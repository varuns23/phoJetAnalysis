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

  double getEtaWidth()       {return etaWidth_;}
  double getPhiWidth()       {return phiWidth_;}

  double getPFCandsPtSum()   {return ptSum_;}
  double getPFCand12PtSum()  {return pfCand12PtSum_;}
  double getPFCand12Ratio()  {return pt12ratio_;}


  double getnPhotons()       {return nPhotons_;}
  double getnCHPions()       {return nCHPions_;}
  double getnMiscParticles() {return nMiscParticles_;}


  vector<double> getConstPt()         {return ConstPt_;}
  vector<double> getConstEt()         {return ConstEt_;}
  vector<double> getConstEta()        {return ConstEta_;}
  vector<double> getConstPhi()        {return ConstPhi_;}
  vector<int>    getConstPdgId()      {return ConstPdgId_;}
  vector<int>    getMiscPdgId()       {return MiscPdgId_;}

private:
                                        
  // No default constructor is possible
  JetWidthCalculator();

  // No copy constructor is needed
  JetWidthCalculator(const JetWidthCalculator&);

  // No equality operator is needed
  const JetWidthCalculator& operator=(const JetWidthCalculator&);

  double etaWidth_;
  double phiWidth_;

  double ptSum_;
  double pfCand12PtSum_;
  double pt12ratio_;

  double nPhotons_;
  double nCHPions_;
  double nMiscParticles_;

  vector<double> ConstPt_;
  vector<double> ConstEt_;
  vector<double> ConstEta_;
  vector<double> ConstPhi_;
  vector<int>    ConstPdgId_;
  vector<int>    MiscPdgId_;
  
};

#endif
