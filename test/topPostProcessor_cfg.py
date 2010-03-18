import FWCore.ParameterSet.Config as cms

maxEvents = -1 
outputDirectory = '/afs/cern.ch/user/s/slaunwhj/scratch0'
outputFileNamePattern = '/DQMTest/Top/Histos'
inputFile = 'file:/afs/cern.ch/user/s/slaunwhj/scratch0/topMC_test.root'

#################################################

process = cms.Process("EDMtoMEConvert")



process.load('Configuration.StandardSequences.EDMtoMEAtRunEnd_cff')
process.load("DQMServices.Components.DQMEnvironment_cfi")
process.load("DQMOffline.Trigger.MuonPostProcessor_cfi")
process.load("DQMServices.Components.DQMStoreStats_cfi")




process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(maxEvents)
)

process.MessageLogger = cms.Service("MessageLogger",
									destinations = cms.untracked.vstring('cout'),
									#categories = cms.untracked.vstring('DQMGenericClient'),
									categories = cms.untracked.vstring('HLTMuonVal'),
									debugModules = cms.untracked.vstring('*'),
									threshold = cms.untracked.string('WARNING'),
									HLTMuonVal = cms.untracked.PSet(
	                                     #threshold = cms.untracked.string('DEBUG'),
	                                     limit = cms.untracked.int32(100000)
										 )
									)

process.source = cms.Source("PoolSource",
							fileNames = cms.untracked.vstring(inputFile),
)


process.dqmSaver.workflow = outputFileNamePattern
process.dqmSaver.dirName = outputDirectory




process.path = cms.Path(process.EDMtoME*process.hLTMuonPostVal*process.dqmStoreStats)


process.endpath = cms.EndPath(process.dqmSaver)



