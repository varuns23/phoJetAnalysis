#ifndef phoJetNtuplizer_h
#define phoJetNtuplizer_h

// system include files
#include <memory>
// user include files
#include "TTree.h"
#include "Math/VectorUtil.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/Candidate.h"
//GenInfo
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//Trigger
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
//Photons
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "HiggsAnalysis/HiggsTo2photons/interface/CiCPhotonID.h"
#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"
//Electrons
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"
//Jet
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
//#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//MET
#include "DataFormats/PatCandidates/interface/MET.h"
//Muons Taus
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "TLorentzVector.h"
#include <vector>
#include <memory>

using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class phoJetNtuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources>{
  public:
    explicit phoJetNtuplizer(const edm::ParameterSet&);
    ~phoJetNtuplizer();

  private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

    // ----------member data ---------------------------
    void branchEventInfo (TTree*);
    void branchPhotons   (TTree*);
    void branchJets      (TTree*);
    void branchElectrons (TTree*);
    void branchMuons     (TTree*);
    void branchMet       (TTree*);
    void branchGenInfo   (TTree*);

    void fillEventInfo  (const edm::Event&, const edm::EventSetup&);
    void fillPhotons    (const edm::Event&, const edm::EventSetup&);
    void fillJets       (const edm::Event&, const edm::EventSetup&);
    void fillElectrons  (const edm::Event&, const edm::EventSetup&, math::XYZPoint&);
    void fillMuons      (const edm::Event&, math::XYZPoint&, const reco::Vertex);
    void fillMet        (const edm::Event&, const edm::EventSetup&);
    void fillGenInfo    (const edm::Event&);

    void initEventInfo();
    void initPhotons();
    void initJets();
    void initElectrons();
    void initMuons();
    void initMet();
    void initGenInfo();

    bool isData_;
    bool debug_;

    bool                                             runEventInfo_;
    edm::EDGetTokenT<double>                         rhoToken_;
    edm::EDGetTokenT<double>                         rhoCentralToken_;
    edm::EDGetTokenT<reco::VertexCollection>         vtxToken_;
    edm::EDGetTokenT<reco::VertexCollection>         vtxBSToken_;

    //Trigger Info
    edm::EDGetTokenT<trigger::TriggerEvent>                  trgEventToken_;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> trgObjectsToken_;
    edm::EDGetTokenT<edm::TriggerResults>                    trgResultsToken_;
    edm::EDGetTokenT<edm::TriggerResults>                    patTrgResultsToken_;
    std::string                                              trgResultsProcess_;

    //Photon Info
    bool                                             runPhotons_;
    edm::EDGetTokenT<edm::View<pat::Photon> >        photonToken_;
    edm::EDGetTokenT<edm::View<pat::Photon> >        calibPhotonToken_;
    EnergyScaleCorrection_class                      *egmScaler_;

    edm::EDGetTokenT<EcalRecHitCollection>           ebReducedRecHitCollection_;
    edm::EDGetTokenT<EcalRecHitCollection>           eeReducedRecHitCollection_;
    edm::EDGetTokenT<EcalRecHitCollection>           esReducedRecHitCollection_;

    //photon ID Map for full5x5
    edm::EDGetTokenT<edm::ValueMap<float> >          full5x5SigmaIEtaIEtaMapToken_;
    //photon ID isolations maps
    edm::EDGetTokenT<edm::ValueMap<float> >          phoChargedIsolationToken_; 
    edm::EDGetTokenT<edm::ValueMap<float> >          phoChargedWorstIsolationToken_; 
    edm::EDGetTokenT<edm::ValueMap<float> >          phoNeutralHadronIsolationToken_; 
    edm::EDGetTokenT<edm::ValueMap<float> >          phoPhotonIsolationToken_; 
    // photon VID decision objects
    edm::EDGetTokenT<edm::ValueMap<bool> >           phoLooseIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           phoMediumIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           phoTightIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<float> >          phoMVAValuesMapToken_;

    //Jet Info
    bool                                             runJets_;
    edm::EDGetTokenT<edm::View<pat::Jet> >           jetsAK4Token_;
    JME::JetResolution                               jetResolution_;
    JME::JetResolutionScaleFactor                    jetResolutionSF_;

    //Electron Info
    bool                                             runEle_;
    edm::EDGetTokenT<edm::View<pat::Electron> >      electronToken_;
    edm::EDGetTokenT<edm::View<pat::Electron> >      calibelectronToken_;
    edm::EDGetTokenT<pat::PackedCandidateCollection> packedPFCandsToken_;
    edm::EDGetTokenT<reco::PFCandidateCollection>    pfAllCandidateToken_;

    // elecontr ID decisions objects
    edm::EDGetTokenT<edm::ValueMap<bool> >           eleVetoIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           eleLooseIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           eleMediumIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           eleTightIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           eleHLTIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> >           eleHEEPIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<float> >          eleMVAValuesMapToken_;
    edm::EDGetTokenT<edm::ValueMap<float> >          elePFClusEcalIsoToken_;
    edm::EDGetTokenT<edm::ValueMap<float> >          elePFClusHcalIsoToken_;

    //Muon Info
    bool                                             runMuon_;
    edm::EDGetTokenT<edm::View<pat::Muon> >          muonToken_;

    //MET Info
    bool                                             runMet_;
    edm::EDGetTokenT<edm::View<pat::MET> >           pfmetToken_;
    edm::EDGetTokenT<bool>                           BadChCandFilterToken_;
    edm::EDGetTokenT<bool>                           BadPFMuonFilterToken_;

    //Gen Particle Info
    bool                                             runGenInfo_;
    edm::EDGetTokenT<GenEventInfoProduct>            generatorToken_;
    edm::EDGetTokenT<LHEEventProduct>                lheEventToken_;
    edm::EDGetTokenT<vector<PileupSummaryInfo> >     puCollection_;
    edm::EDGetTokenT<vector<reco::GenParticle> >     genParticlesToken_;

    TTree * tree_;
};

#endif
