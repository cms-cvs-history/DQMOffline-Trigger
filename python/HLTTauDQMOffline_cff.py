import FWCore.ParameterSet.Config as cms

from DQMOffline.Trigger.HLTTauDQMOffline_cfi import *

HLTTauDQMOffline = cms.Sequence(TauRefProducer+
                                hltTauOfflineMonitor_PFTaus
#                                hltTauOfflineMonitor_Electrons+
##                                hltTauOfflineMonitor_Muons+
#                                hltTauOfflineMonitor_Inclusive
                                )

                                


