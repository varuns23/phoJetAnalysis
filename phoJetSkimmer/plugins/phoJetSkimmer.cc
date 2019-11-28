// -*- C++ -*-
//
// Package:    phoJetAnalysis/phoJetSkimmer
// Class:      phoJetSkimmer
// 
/**\class phoJetSkimmer phoJetSkimmer.cc phoJetAnalysis/phoJetSkimmer/plugins/phoJetSkimmer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Varun Sharma
//         Created:  Wed, 27 Nov 2019 14:14:22 GMT
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "Math/VectorUtil.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/StreamID.h"
 
#include "DataFormats/PatCandidates/interface/Jet.h"

using namespace std;
using namespace edm;
//
// class declaration
//

class phoJetSkimmer : public edm::stream::EDFilter<> {
   public:
      explicit phoJetSkimmer(const edm::ParameterSet&);
      ~phoJetSkimmer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<edm::View<pat::Jet> > jetsSkimToken_;
      double                                 cutJetEta_;
      double                                 cutJetPt_;

};

// constructors and destructor
//
phoJetSkimmer::phoJetSkimmer(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

  jetsSkimToken_  = consumes<edm::View<pat::Jet> > (iConfig.getParameter<InputTag>("jetsSkimToken"));
  cutJetEta_      = iConfig.getParameter<double> ("cutJetEta");
  cutJetPt_       = iConfig.getParameter<double> ("cutJetPt");
}


phoJetSkimmer::~phoJetSkimmer()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
phoJetSkimmer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<edm::View<pat::Jet> > jetHandle;
   iEvent.getByToken(jetsSkimToken_, jetHandle);

  if (!jetHandle.isValid()) {
    edm::LogWarning("phoJetSkimmer") << "no pat::Jets (AK4) in event";
    return true;
  }

  bool decision = false;
  int count = 0;

  for (edm::View<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {

    float NHF      = iJet->neutralHadronEnergyFraction();
    float NEMF     = iJet->neutralEmEnergyFraction();
    float NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    float CHF      = iJet->chargedHadronEnergyFraction();
    float CHM      = iJet->chargedMultiplicity();
    float CEMF     = iJet->chargedEmEnergyFraction();

    bool tightJetID        = false;
    if (fabs(iJet->eta()) <= 2.7) 
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF < 0.99) || fabs(iJet->eta())>2.4);


    if((fabs(iJet->eta()) < cutJetEta_) && (iJet->pt() > cutJetPt_) && tightJetID)
      count++;

  }//jet loop ends


  if(count > 0){
    decision = true;
  }

  if(!decision) cout<<"--- failed filter"<<endl;

  return decision;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
phoJetSkimmer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
phoJetSkimmer::endStream() {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void


phoJetSkimmer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
//  edm::ParameterSetDescription desc;
//  desc.setUnknown();
//  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(phoJetSkimmer);
