# 2018 Analyzer: 102X
## MiniAOD analyzer for all physics objects 

- Working for 17Sep2018 Re-Reco of ABC
- For prompt reco refer to 2018_94X branch

Instructions:
```
cmsrel CMSSW_10_2_10
cd CMSSW_10_2_10/src
cmsenv
git cms-init
git config merge.renameLimit 20000

## MET 
git cms-addpkg RecoMET/METFilters
       
##https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2#2018_MiniAOD
git cms-merge-topic cms-egamma:EgammaPostRecoTools                                                              
git cms-merge-topic cms-egamma:PhotonIDValueMapSpeedup1029
git cms-merge-topic cms-egamma:slava77-btvDictFix_10210
git cms-addpkg EgammaAnalysis/ElectronTools
rm EgammaAnalysis/ElectronTools/data -rf
git clone git@github.com:cms-data/EgammaAnalysis-ElectronTools.git EgammaAnalysis/ElectronTools/data


#For 2018 data-taking
git clone -b 2018_102X https://github.com/varuns23/phoJetAnalysis.git

scram b -j10
```

For Electrons and Photons:
[1]-https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2
[2]-https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
[3]-https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2

For MET:
[4]-https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_for_2

For Taus:
[5]-https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
[6]-https://twiki.cern.ch/twiki/pub/CMSPublic/SWGuidePFTauID/2017v2-recipe.pdf

For Muons:
[7]-https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2

