import FWCore.ParameterSet.Config as cms

from DQM.L1TMonitor.L1TGT_readout_cff import *
from DQM.L1TMonitor.L1TGCT_readout_cff import *
from DQM.L1TMonitor.L1TFED_cfi import *
l1tmonitor = cms.Sequence(l1tgt*l1tgmt*l1trpctf*l1tcsctf*l1tdttf*l1trct*l1tgct*l1tfed)
l1tgt.gtSource = 'gtDigis::'
l1tgmt.gmtSource = 'gtDigis::'
l1tdttf.dttpgSource = 'dttfDigis::'
l1tcsctf.statusProducer = 'csctfDigis::'
l1tcsctf.lctProducer = 'csctfDigis::'
l1tcsctf.trackProducer = 'csctfDigis::'
l1trpctf.rpctfSource = 'gtDigis::'
l1tgct.gctCentralJetsSource = 'gctDigis:cenJets:'
l1tgct.gctForwardJetsSource = 'gctDigis:forJets:'
l1tgct.gctTauJetsSource = 'gctDigis:tauJets:'
l1tgct.gctEnergySumsSource = 'gctDigis::'
l1tgct.gctIsoEmSource = 'gctDigis:isoEm:'
l1tgct.gctNonIsoEmSource = 'gctDigis:nonIsoEm:'
l1trct.rctSource = 'gctDigis::'

from DQM.L1TMonitor.L1TDEMON_cfi import *
l1temumonitor = cms.Sequence(l1demon) 

# AlCa
from DQM.HLTEvF.HLTAlCaMonPi0_cfi import *
from DQM.HLTEvF.HLTAlCaMonEcalPhiSym_cfi import *
# JetMET
from DQM.HLTEvF.HLTMonJetMET_E28_cfi import *
from DQM.HLTEvF.HLTMonJetMETDQMSource_cfi import *
# Electron
from DQM.HLTEvF.HLTMonEleBits_cfi import *
# Muon
from DQM.HLTEvF.HLTMonMuonDQM_cfi import *
from DQM.HLTEvF.HLTMonMuonBits_cfi import *
# Photon
#from DQM.HLTEvF.HLTMonPhotonBits_cfi import *
# Tau
from DQM.HLTEvF.HLTMonTau_cfi import *
#from DQM.HLTEvF.hltMonBTagIPSource_cfi import *
#from DQM.HLTEvF.hltMonBTagMuSource_cfi import *
# hltMonjmDQM  bombs
# hltMonMuDQM dumps names of all histograms in the directory
# hltMonPhotonBits in future releases
# *hltMonJetMET makes a log file, need to learn how to turn it off
# *hltMonEleBits causes SegmentFaults in HARVESTING(step3) in inlcuded in step2

#onlineHLTSource = cms.Sequence(EcalPi0Mon*EcalPhiSymMon*hltMonEleBits*hltMonMuBits*hltMonTauReco*hltMonBTagIPSource*hltMonBTagMuSource)
onlineHLTSource = cms.Sequence(EcalPi0Mon*EcalPhiSymMon*hltMonMuBits*hltMonTauReco)


# FourVector
from DQMOffline.Trigger.FourVectorHLTOffline_cfi import *
# Egamma
from DQMOffline.Trigger.EgHLTOfflineSource_cfi import *
from DQMOffline.Trigger.TopElectronHLTOfflineSource_cfi import *
# Muon
from DQMOffline.Trigger.MuonOffline_Trigger_cff import *
# Top
from DQMOffline.Trigger.QuadJetAna_cfi import *
# Tau
from DQMOffline.Trigger.HLTTauDQMOffline_cff import *
# JetMET
from DQMOffline.Trigger.JetMETHLTOfflineSource_cfi import *
# TnP
from DQMOffline.Trigger.TnPEfficiency_cff import *

offlineHLTSource = cms.Sequence(hltResults*egHLTOffDQMSource*topElectronHLTOffDQMSource*muonFullOfflineDQM*quadJetAna*HLTTauDQMOffline*jetMETHLTOfflineSource*TnPEfficiency)

triggerOfflineDQMSource =  cms.Sequence(offlineHLTSource*l1temumonitor*l1tmonitor*onlineHLTSource)
 
