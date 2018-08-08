# MiniAOD analyzer for Dark photon

Instructions:
```
cmsrel CMSSW_9_4_9
cd CMSSW_9_4_9/src
cmsenv
git cms-init
```

For Electrons and Photons:
[1] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2
[2] https://twiki.cern.ch/twiki/bin/view/CMS/Egamma2017DataRecommendations
[3] https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2

For MET:
[4] https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_for_2

``
git cms-merge-topic cms-egamma:EgammaPostRecoTools_940
git cms-merge-topic cms-met:METFixEE2017_949

scram b -j10
```

```
git clone -b 90Xv2 https://github.com/varuns23/phoJetAnalysis.git
```


Data set Info:
DATA:
DAS query: dataset=/*/Run2017*31Mar2018*/MINIAOD
Produced with CMSSW 9_4_5; Global tag: 94X_dataRun2_v6, cmsDriver eras Run2_2017,run2_miniAOD_94XFall17
JECs used: Fall17_17Nov2017BCDEF_V6_DATA
Recommended release: 9_4_6_patch1 or later, Global tag: 94X_dataRun2_v6

MC:
DAS query: dataset=/*/RunIIFall17*12Apr2018*/MINIAODSIM
Produced with CMSSW 9_4_6; Global tag: 94X_mc2017_realistic_v14, cmsDriver eras Run2_2017,run2_miniAOD_94XFall17
JECs used: Fall17_17Nov2017_V6_MC
Recommended release: 9_4_6_patch1 or later, Global tag: 94X_mc2017_realistic_v14
