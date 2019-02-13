#MiniAOD analyzer for all physics objects 

Instructions:
```
cmsrel CMSSW_10_2_10
cd CMSSW_10_2_10/src
cmsenv
git cms-init

git cms-merge-topic cms-met:METFixEE2017_949_v2_backport_to_102X 
git cms-merge-topic cms-egamma:EgammaPostRecoTools_940

#For 2017 data-taking
git clone https://github.com/varuns23/phoJetAnalysis.git

scram b -j10
```

Electrons and Photons:
```
[1] https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaRunIIRecommendations
[2] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2
[3] https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
[4] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2
```
JetMET
```
[5] https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC#2017_Data
[6] https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_or_10
[7] https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe
```

Taus:
```
[5] https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
[6] https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuidePFTauID/2017v2-recipe.pdf
```
Muons:
```
[7]-https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2
```

For PPD RunII analysis recipe
```
[] https://twiki.cern.ch/twiki/bin/view/CMS/PdmV
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable
```

Data set Info:
DATA:
DAS query: dataset=/*/Run2017*31Mar2018*/MINIAOD

MC:
DAS query: dataset=/*/RunIIFall17*12Apr2018*/MINIAODSIM
