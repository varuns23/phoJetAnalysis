from WMCore.DataStructs.LumiList import LumiList

originalLumiList1 = LumiList(filename='lumisToProcess.json')
originalLumiList2 = LumiList(filename='my_lumi_mask.json')
newLumiList = originalLumiList1 - originalLumiList2
newLumiList.writeJSON('my-diff.json')

#config.Data.lumiMask = 'my_lumi_mask.json'
