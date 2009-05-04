import FWCore.ParameterSet.Config as cms

# This is how you would get muons and cut on them
# allGlobalMuonTracks = cms.EDProducer ("MuonSelector",
#									  src = cms.InputTag("muons"),
#									  cut = cms.string ("pt > 40")
#									  )
									  
# This is how you would get muon tracks and cut on them
#highPtMuonTracks = cms.EDProducer ("TrackSelector",
#									  src = cms.InputTag("globalMuons"),
#									  cut = cms.string ("pt > 20")
#									  )

#barrelMuonTracks = cms.EDProducer ("TrackSelector",
#								   src = cms.InputTag("globalMuons"),
#								   cut = cms.string ("abs(eta) < 0.9")
#								   )

barrelMuons = cms.EDProducer ("MuonSelector",
								   src = cms.InputTag("muons"),
								   cut = cms.string ("abs(eta) < 0.9")
								   )



overlapMuons = cms.EDProducer ("MuonSelector",
									src = cms.InputTag("muons"),
									cut = cms.string (" (abs(eta) > 0.9) & (abs(eta) < 1.3)")
									)

endcapMuons = cms.EDProducer ("MuonSelector",
								   src = cms.InputTag("muons"),
								   cut = cms.string ("(abs(eta) > 1.3) & (abs(eta) < 2.1) ")
								   )
									  

externalMuons = cms.EDProducer ("MuonSelector",
									 src = cms.InputTag("muons"),
									 cut = cms.string ("(abs(eta) > 2.1) & (abs(eta) < 2.4) ")
									 )

