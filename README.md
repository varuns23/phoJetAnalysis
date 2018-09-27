# MiniAOD analyzer 

Instructions:
```
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src
cmsenv
git cms-init
```

For consistent version of the EGMSmearer with the 80X regression.

Following twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMRegression
```
git cms-merge-topic cms-egamma:EGM_gain_v1
cd EgammaAnalysis/ElectronTools/data
git clone -b Moriond17_gainSwitch_unc https://github.com/ECALELFS/ScalesSmearings.git
cd $CMSSW_BASE/src
```

Following twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMRegression

For application of regression outside training boundary -
```
git cms-merge-topic rafaellopesdesa:RegressionCheckNegEnergy
```

For electron and photon identification and isolation

Follow twiki: https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2#Recipe_for_regular_users_for_8_0
```
git cms-merge-topic ikrav:egm_id_80X_v3_photons
```
 
For MET follow https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes#MET_Recipes
```
git cms-merge-topic cms-met:METRecipe_8020 -u
git cms-merge-topic cms-met:METRecipe_80X_part2 -u
```
                                                                                                                                                                                   
For Electron follow: https://twiki.cern.ch/twiki/bin/viewauth/CMS/HEEPElectronIdentificationRun2
```
git cms-merge-topic Sam-Harper:HEEPV70VID_8010_ReducedCheckout
```
Finally download analyzer
```
git clone https://github.com/varuns23/phoJetAnalysis.git
```
