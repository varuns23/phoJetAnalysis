#!/usr/bin/env python

def convert_to_str(vec_str):
    output = ""
    for entry in vec_str:
        if output != "": output+="\n  "
        output+=entry
    return output

#def convertpair_to_str(vec_str):
#    output = ""
#    for entry in vec_str:
#        if output != "": output+="\n  "
#        output+=entry.first
#    return output
#
#def print_jetAK4_user_data(jetAK4):
#    print "jetAK4 userfloats:"
#    print "  "+convert_to_str(jetAK4.userFloatNames())
#    print "jetAK4 userints:"
#    print "  "+convert_to_str(jetAK4.userIntNames())
#    print "jetAK4 IDs:"
#    print "  "+convertpair_to_str(jetAK4.electronIDs())
#
def print_jetAK8_user_data(jet):
    print "jet userfloats:"
    print "  "+convert_to_str(jet.userFloatNames())
    print "jet userints:"
    print "  "+convert_to_str(jet.userIntNames())
    print "jet userData:"
    print "  "+convert_to_str(jet.userDataNames())
#    print "jet IDs:"
#    print "  "+convertpair_to_str(jet.photonIDs())


import sys
oldargv = sys.argv[:]
sys.argv = [ '-b-' ]
import ROOT
ROOT.gROOT.SetBatch(True)
sys.argv = oldargv
ROOT.gSystem.Load("libFWCoreFWLite.so");
ROOT.gSystem.Load("libDataFormatsFWLite.so");
ROOT.FWLiteEnabler.enable()
from DataFormats.FWLite import Events, Handle

import argparse
parser = argparse.ArgumentParser(description='prints E/gamma pat::Jets user data')
parser.add_argument('filename',help='input filename')
args = parser.parse_args()

jetsAK4, jetAK4_label = Handle("std::vector<pat::Jet>"), "slimmedJets"
jetsAK8, jetAK8_label = Handle("std::vector<pat::Jet>"), "slimmedJetsPuppi"


min_jet_et = 20

done_jetsAK4 = False
done_jetsAK8 = False

events = Events(args.filename)
for event_nr,event in enumerate(events):
    if done_jetsAK4 and done_jetsAK8: break
    
    if not done_jetsAK8:
        event.getByLabel(jetAK8_label,jetsAK8)
    
        for jetAK8_nr,jetAK8 in enumerate(jetsAK8.product()): 
#	     print(jetAK8_nr, jetAK8)
            if jetAK8.et()<min_jet_et: continue
            else:
                print_jetAK8_user_data(jetAK8)
                done_jetsAK8 = True
#    if not done_jetsAK4:
#        event.getByLabel(jetAK4_label,jetsAK4)
#    
#        for jetAK4_nr,jetAK4 in enumerate(jetsAK4.product()):
#            if jetAK4.et()<min_jet_et: continue
#            else:
#                print_jetAK4_user_data(jetAK4)
#                done_jetsAK4 = True
