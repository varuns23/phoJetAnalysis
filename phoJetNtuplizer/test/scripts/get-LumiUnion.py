from WMCore.DataStructs.LumiList import LumiList

originalLumiList1 = LumiList(filename='notFinishedLumis-input-EgammaAv1-1.json')
originalLumiList2 = LumiList(filename='notFinishedLumis-input-EgammaAv1-2.json')
originalLumiList3 = LumiList(filename='notFinishedLumis-input-EgammaAv1-3.json')
originalLumiList4 = LumiList(filename='notFinishedLumis-input-EgammaAv1-4.json')
originalLumiList5 = LumiList(filename='processedLumis.json')
newLumiList = originalLumiList1 + originalLumiList2 + originalLumiList3 + originalLumiList4 + originalLumiList5
newLumiList.writeJSON('my_lumi_mask.json')

#config.Data.lumiMask = 'my_lumi_mask.json'
