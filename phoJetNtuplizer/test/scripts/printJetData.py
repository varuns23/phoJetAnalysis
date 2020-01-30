# import ROOT in batch mode
import sys
oldargv = sys.argv[:]
sys.argv = [ '-b-' ]
import ROOT
ROOT.gROOT.SetBatch(True)
sys.argv = oldargv
# load FWLite C++ libraries
ROOT.gSystem.Load("libFWCoreFWLite.so");
ROOT.gSystem.Load("libDataFormatsFWLite.so");
ROOT.FWLiteEnabler.enable()
# load FWlite python libraries
from DataFormats.FWLite import Handle, Events

#import argparse
#parser = argparse.ArgumentParser(description='prints physics objects (Jets) user data')
#parser.add_argument('filename',help='input filename')
#args = parser.parse_args()
#events = Events(args.filename)



jets = Handle("std::vector<pat::Jet>")
fatjets, fatjetLabel = Handle("std::vector<pat::Jet>"), "slimmedJetsAK8"
seenIt = {} # list of things we've seen (so that we dump them in full only once)

# open file (you can use 'edmFileUtil -d /store/whatever.root' to get the physical file name)
#events = Events("root://eoscms//eos/cms/store/relval/CMSSW_8_0_3/RelValTTbarLepton_13/MINIAODSIM/80X_mcRun2_asymptotic_2016_v3_gs7120p2NewGTv3-v1/00000/4E291B64-DCEF-E511-B99D-0025905A60B0.root")
events = Events("/hdfs/store/user/varuns/TEST-INPUTFILES/test_mc_12Apr2018_94X.root")

for iev,event in enumerate(events):
    if iev >= 10: break
    event.getByLabel(fatjetLabel, fatjets)

    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())

#    # Jets (AK4, CHS and Puppi)
#    for jetLabel, algo in ("slimmedJets", "CHS"), ("slimmedJetsPuppi", "PUPPI"):
#        event.getByLabel(jetLabel, jets)
#        for i,j in enumerate(jets.product()):
#            if j.pt() < 20: continue
#            print "jet %s %3d: pt %5.1f (raw pt %5.1f, matched-calojet pt %5.1f), eta %+4.2f, btag CSVIVFv2 %.3f, CMVAv2 %.3f, pileup mva disc %+.2f" % (
#                algo, i, j.pt(), j.pt()*j.jecFactor('Uncorrected'), j.userFloat("caloJetMap:pt") if algo == "CHS" else -99.0, j.eta(), max(0,j.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")), max(0,j.bDiscriminator("pfCombinedMVAV2BJetTags")), j.userFloat("pileupJetId:fullDiscriminant") if algo == "CHS" else -99)
#            if 'jetAk4'+algo not in seenIt:
#                constituents = [ j.daughter(i2) for i2 in xrange(j.numberOfDaughters()) ]
#                constituents.sort(key = lambda c:c.pt(), reverse=True)
#                for i2, cand in enumerate(constituents):
#                    if i2 > 12:
#                            print "         ....."
#                            break
#                    print "         constituent %3d: pt %6.2f, dz(pv) %+.3f, pdgId %+3d, hcal energy fraction %.2f, puppi weight %.3f " % (i2,cand.pt(),cand.dz(PV.position()),cand.pdgId(),cand.hcalFraction(),cand.puppiWeight())
#                print "   btag discriminators:"
#                for btag in j.getPairDiscri():
#                    print  "\t%s %s" % (btag.first, btag.second)
#                print "   userFloats:"
#                for ufl in j.userFloatNames():
#                    print  "\t%s %s" % (ufl, j.userFloat(ufl))
#                seenIt['jetAk4'+algo] = True

    # Fat AK8 Jets
    for i,j in enumerate(fatjets.product()):
        if j.pt() < 200: continue
        print "jetAK8 %3d: pt %5.1f (raw pt %5.1f), eta %+4.2f, mass %5.1f ungroomed, %5.1f softdrop, %5.1f pruned CHS. " % (
            i, j.pt(), j.pt()*j.jecFactor('Uncorrected'), j.eta(), j.mass(), j.userFloat('ak8PFJetsPuppiSoftDropMass'), j.userFloat('ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass'))
	print "jetAK8 MUF %3.4f" % (j.muonEnergyFraction())
        # If you use CMSSW_9_4_<=6 to read MiniAOD, to get the constituents of the AK8 jets, you have to loop over all of the
        # daughters recursively. To save space, the first two constituents are actually
        # the Soft Drop SUBJETS, which will then point to their daughters.
        # The remaining constituents are those constituents removed by soft drop but
        # still in the AK8 jet.
        if 'jetAk8' not in seenIt:
            print "   btag discriminators:"
            for btag in j.getPairDiscri():
                print  "\t%s %s" % (btag.first, btag.second)
            print "   userFloats:"
            for ufl in j.userFloatNames():
                print  "\t%s %s" % (ufl, j.userFloat(ufl))
            #seenIt['jetAk8'] = True
        # Print Subjets
       # if 'jetAk8SD' not in seenIt:
       #     wSubjets = j.subjets('SoftDropPuppi')
       #     for isd,sdsub in enumerate( sdSubjets ) :
       #         print "   w subjet %3d: pt %5.1f (raw pt %5.1f), eta %+4.2f, mass %5.1f " % (
       #             isd, sdsub.pt(), sdsub.pt()*sdsub.jecFactor('Uncorrected'), sdsub.eta(), sdsub.mass()
       #             )
       #         print "   \tbtag discriminators:"
       #         for btag in sdsub.getPairDiscri():
       #             print  "\t\t%s %s" % (btag.first, btag.second)
       #         print "   \tuserFloats:"
       #         for ufl in sdsub.userFloatNames():
       #             print  "\t\t%s %s" % (ufl, sdsub.userFloat(ufl))
       #         seenIt['jetAk8SD'] = True
