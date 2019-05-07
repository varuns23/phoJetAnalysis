#MiniAOD analyzer for all physics objects 

Instructions:
```
cmsrel CMSSW_10_2_10
cd CMSSW_10_2_10/src
cmsenv
git cms-init

git cms-addpkg RecoMET/METFilters                              
git cms-merge-topic cms-egamma:EgammaPostRecoTools             
git cms-merge-topic cms-met:METFixEE2017_949_v2_backport_to_102X

#For 2017 data-taking
git clone -b 2017_102X https://github.com/varuns23/phoJetAnalysis.git

scram b -j10
```

Electrons and Photons:
```
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaRunIIRecommendations
[] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2
[] https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
[] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2
```
JetMET
```
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
[] https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC#2017_Data
[] https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_or_10
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1ECALPrefiringWeightRecipe
```

Taus:
```
[] https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
[] https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuidePFTauID/2017v2-recipe.pdf
[] https://indico.cern.ch/event/810741/contributions/3384093/attachments/1827349/2991114/TauID_CMSweek_10042019.pdf 
```
Muons:
```
[] https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2
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
