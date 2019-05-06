#include "phoJetAnalysis/phoJetNtuplizer/interface/phoJetNtuplizer.h"


vector<float>    pdf_;
float            pthat_;
float            processID_;
float            genWeight_;
float            genHT_;
float            pdfWeight_;     
vector<float>    pdfSystWeight_;
vector<double>    psWeight_;

Int_t            nPUInfo_;
vector<int>      nPU_;
vector<int>      puBX_;
vector<float>    puTrue_;

Int_t            nMC_;
vector<int>      mcPID;
vector<float>    mcVtx;
vector<float>    mcVty;
vector<float>    mcVtz;
vector<float>    mcPt;
vector<float>    mcMass;
vector<float>    mcEta;
vector<float>    mcPhi;
vector<float>    mcE;
vector<float>    mcEt;
vector<int>      mcStatus;
vector<UShort_t> mcStatusFlag;
vector<int>      mcIndex;

void phoJetNtuplizer::branchGenInfo(TTree* tree){

  tree->Branch("pdf",           &pdf_);
  tree->Branch("pthat",         &pthat_);
  tree->Branch("processID",     &processID_);
  tree->Branch("genWeight",     &genWeight_);
  tree->Branch("genHT",         &genHT_);
  tree->Branch("pdfWeight",     &pdfWeight_);
  tree->Branch("pdfSystWeight", &pdfSystWeight_);
  tree->Branch("psWeight",      &psWeight_);

  tree->Branch("nPUInfo",       &nPUInfo_);
  tree->Branch("nPU",           &nPU_);
  tree->Branch("puBX",          &puBX_);
  tree->Branch("puTrue",        &puTrue_);

  tree->Branch("nMC",          &nMC_);
  tree->Branch("mcPID",        &mcPID);
  tree->Branch("mcVtx",        &mcVtx);
  tree->Branch("mcVty",        &mcVty);
  tree->Branch("mcVtz",        &mcVtz);
  tree->Branch("mcPt",         &mcPt);
  tree->Branch("mcMass",       &mcMass);
  tree->Branch("mcEta",        &mcEta);
  tree->Branch("mcPhi",        &mcPhi);
  tree->Branch("mcE",          &mcE);
  tree->Branch("mcEt",         &mcEt);
  tree->Branch("mcStatus",     &mcStatus);     // status of the particle
  tree->Branch("mcStatusFlag", &mcStatusFlag); //-999:non W or Z, 1:hardronic, 2:e, 3:mu, 4:tau
  tree->Branch("mcIndex",      &mcIndex);

}

void phoJetNtuplizer::fillGenInfo(const edm::Event& iEvent){

  initGenInfo();

  edm::Handle<GenEventInfoProduct> genEventInfoHandle;
  iEvent.getByToken(generatorToken_, genEventInfoHandle);

  if (genEventInfoHandle.isValid()) {
    if (genEventInfoHandle->pdf()) {
      pdf_.push_back(genEventInfoHandle->pdf()->id.first);    //[0] PDG ID of incoming parton #1
      pdf_.push_back(genEventInfoHandle->pdf()->id.second);   //[1] PDG ID of incoming parton #2
      pdf_.push_back(genEventInfoHandle->pdf()->x.first);     //[2] x value of parton #1
      pdf_.push_back(genEventInfoHandle->pdf()->x.second);    //[3] x value of parton #2
      pdf_.push_back(genEventInfoHandle->pdf()->xPDF.first);  //[4] PDF weight for parton #1
      pdf_.push_back(genEventInfoHandle->pdf()->xPDF.second); //[5] PDF weight for parton #2
      pdf_.push_back(genEventInfoHandle->pdf()->scalePDF);    //[6] scale of the hard interaction
    }

    if (genEventInfoHandle->hasBinningValues())
      pthat_ = genEventInfoHandle->binningValues()[0];
    processID_ = genEventInfoHandle->signalProcessID();
    genWeight_ = genEventInfoHandle->weight();

    //PS weights:
    std::vector<double> ps_Weight_ = genEventInfoHandle->weights();
    // Normalize all Parton-Shower weights to the nominal one
    if(ps_Weight_.size() > 0){
      const double nominal_psWeight = ps_Weight_.at(0);
      if(nominal_psWeight == 0.){
	throw cms::Exception("input") << "nominal PS-Weight equal to zero (failed to normalize other PS-Weights";
      }

      for(uint iweights =0; iweights< ps_Weight_.size(); iweights++){
	ps_Weight_.at(iweights) /= nominal_psWeight;
	psWeight_.at(iweights) = ps_Weight_.at(iweights);
      }
    }
    

  }else{
    edm::LogWarning("phoJetNtuplizer") << "no generator info in event";
  }

  // access generator level HT  
  edm::Handle<LHEEventProduct> lheEventProduct;
  iEvent.getByToken(lheEventToken_, lheEventProduct);

  double lheHt = 0.;
  if (lheEventProduct.isValid()){

    const lhef::HEPEUP& lheEvent = lheEventProduct->hepeup();
    std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
    size_t numParticles = lheParticles.size();
    for ( size_t idxParticle = 0; idxParticle < numParticles; ++idxParticle ) {
      int absPdgId = TMath::Abs(lheEvent.IDUP[idxParticle]);
      int status = lheEvent.ISTUP[idxParticle];
      if ( status == 1 && ((absPdgId >= 1 && absPdgId <= 6) || absPdgId == 21) ) { // quarks and gluons
	lheHt += TMath::Sqrt(TMath::Power(lheParticles[idxParticle][0], 2.) + TMath::Power(lheParticles[idxParticle][1], 2.)); // first entry is px, second py
      }                          
    }

    pdfWeight_ = lheEventProduct->originalXWGTUP(); // PDF weight of this event !
    for (unsigned i = 0; i < lheEventProduct->weights().size(); ++i) {
      pdfSystWeight_.push_back(lheEventProduct->weights()[i].wgt);
    }
  } else{ 
    edm::LogWarning("phoJetNtuplizer") << "no lheEventProduct info in event";
  }
  genHT_=lheHt;

  edm::Handle<vector<PileupSummaryInfo> > genPileupHandle;           
  iEvent.getByToken(puCollection_, genPileupHandle);       

  if (!genPileupHandle.isValid()) { 
    edm::LogWarning("phoJetNtuplizer") << "no PileupSummaryInfo info in event";
    return;                                 
  }

  for (vector<PileupSummaryInfo>::const_iterator pu = genPileupHandle->begin(); pu != genPileupHandle->end(); ++pu) {

    nPU_   .push_back(pu->getPU_NumInteractions());                
    puTrue_.push_back(pu->getTrueNumInteractions());               
    puBX_  .push_back(pu->getBunchCrossing());                     

    nPUInfo_++;                                                    
  }

  ///---------

  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;        
  iEvent.getByToken(genParticlesToken_, genParticlesHandle);         

  if (!genParticlesHandle.isValid()) {                               
    edm::LogWarning("ggNtuplizer") << "no gen particle info in event";                         
    return;                                                          
  }                                                                  

  int genIndex = 0;  

  for (vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {
    genIndex++;

    /*
    int status = ip->status();
    //bool stableFinalStateParticle = status == 1 && ip->pt() > 5.0;
    
    bool quarks = abs(ip->pdgId())<7;
       
    // keep non-FSR photons with pT > 5.0 and all leptons with pT > 3.0;
    bool photonOrLepton =
      (ip->pdgId() == 22 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
      (status == 1 && abs(ip->pdgId()) == 11 && (ip->isPromptFinalState() || ip->isLastCopy())) ||               
      (status == 1 && abs(ip->pdgId()) == 13 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
      (status == 1 && (abs(ip->pdgId()) == 12 || abs(ip->pdgId()) == 14 || abs(ip->pdgId()) == 16)) ||
      (status == 1 && ( abs(ip->pdgId()) >= 11 && abs(ip->pdgId()) <= 16 ) && ip->pt() > 3.0)  ||
      (status < 10 && abs(ip->pdgId()) == 15 && ip->pt() > 3.0);
       
    // select also Z, W, H, top and b 
    bool heavyParticle =
      ((    ip->pdgId()  == 23 && ip->isHardProcess()) || 
       (abs(ip->pdgId()) == 24 && ip->isHardProcess()) || 
       (    ip->pdgId()  == 25 && ip->isHardProcess()) ||
       (abs(ip->pdgId()) ==  6 && ip->isHardProcess()) || 
       (abs(ip->pdgId()) ==  5 && ip->isHardProcess()));
       */

    const reco::Candidate *p = (const reco::Candidate*)&(*ip);
    if (!p->mother()) continue;

//    if(heavyParticle || photonOrLepton || quarks){
    if(ip->isPromptFinalState() || ip->isHardProcess() || ip->isLastCopy() || ip->fromHardProcessFinalState()){

      mcPID    .push_back(p->pdgId());
      mcVtx    .push_back(p->vx());
      mcVty    .push_back(p->vy());
      mcVtz    .push_back(p->vz());
      mcPt     .push_back(p->pt());
      mcMass   .push_back(p->mass());
      mcEta    .push_back(p->eta());
      mcPhi    .push_back(p->phi());
      mcE      .push_back(p->energy());
      mcEt     .push_back(p->et());
      mcStatus .push_back(p->status());

      UShort_t tmpStatusFlag = 0;
      if (ip->fromHardProcessFinalState()) setbit(tmpStatusFlag, 0);
      if (ip->isPromptFinalState())        setbit(tmpStatusFlag, 1);
      if (ip->isHardProcess())             setbit(tmpStatusFlag, 2);

      // if genParticle is W or Z, check its decay type
      if ( ip->pdgId() == 23 || abs(ip->pdgId()) == 24 ) {
	for (size_t k=0; k < p->numberOfDaughters(); ++k) {
	  const reco::Candidate *dp = p->daughter(k);
	  if (abs(dp->pdgId())<=6)                               setbit(tmpStatusFlag, 4);
	  else if (abs(dp->pdgId())==11 || abs(dp->pdgId())==12) setbit(tmpStatusFlag, 5);
	  else if (abs(dp->pdgId())==13 || abs(dp->pdgId())==14) setbit(tmpStatusFlag, 6);
	  else if (abs(dp->pdgId())==15 || abs(dp->pdgId())==16) setbit(tmpStatusFlag, 7);
	}
      } 
      mcStatusFlag.push_back(tmpStatusFlag);
      mcIndex.push_back(genIndex-1);


      nMC_++;
    }
  } // loop over gen-level particle

}



void phoJetNtuplizer::initGenInfo(){

  pdf_           .clear();
  pthat_         = -99;
  processID_     = -99;
  genWeight_     = -99;
  genHT_         = -99;
  pdfWeight_     = -99;
  pdfSystWeight_  .clear();
  psWeight_       .clear();

  nPUInfo_       = 0;
  nPU_          .clear();
  puBX_         .clear();
  puTrue_       .clear();

  nMC_         = 0;
  mcPID       .clear();
  mcVtx       .clear();
  mcVty       .clear();
  mcVtz       .clear();
  mcPt        .clear();
  mcMass      .clear();
  mcEta       .clear();
  mcPhi       .clear();
  mcE         .clear();
  mcEt        .clear();
  mcStatus    .clear();
  mcStatusFlag.clear();
  mcIndex     .clear();

}
