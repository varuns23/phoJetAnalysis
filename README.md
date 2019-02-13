#MiniAOD analyzer for all physics objects 

Instructions:
```
cmsrel CMSSW_10_2_10
cd CMSSW_10_2_10/src
cmsenv
git cms-init

#For 2017 data-taking
git clone -b 102X_2017 https://github.com/varuns23/phoJetAnalysis.git

scram b -j10
```

For Electrons and Photons:
[1]-https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2
[2]-https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
[3]-https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2

For Taus:
[5]-https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
[6]-https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuidePFTauID/2017v2-recipe.pdf

For Muons:
[7]-https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2


Data set Info:
DATA:
DAS query: dataset=/*/Run2017*31Mar2018*/MINIAOD

MC:
DAS query: dataset=/*/RunIIFall17*12Apr2018*/MINIAODSIM
