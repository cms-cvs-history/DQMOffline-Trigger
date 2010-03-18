import FWCore.ParameterSet.Config as cms
#########################################################

# edit the maximum number of events
# -1 for all events

maxEvents = 10


# output file name

outputFileName = "/afs/cern.ch/user/s/slaunwhj/scratch0/topMC_test.root"


# edit the files that will be used
# if the files are local,
# make sure to add file: to the beginning of the name

targetFileNames = ['/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0004/7A41D5FD-2C2C-DF11-A691-00261894388D.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/F2CD0ADC-922B-DF11-9622-001731AF6B89.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/D2FF0335-9D2B-DF11-BF27-002618943959.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/BE2231BA-9A2B-DF11-83EE-001A92971BDA.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/B00B8725-9F2B-DF11-BB51-003048678AC8.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/8EA05413-942B-DF11-901A-002618943821.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/689F19CA-992B-DF11-8798-001A928116B2.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/64986EF5-922B-DF11-BC4B-0017312B5F3F.root',
'/store/relval/CMSSW_3_5_4/RelValTTbar/GEN-SIM-RECO/MC_3XY_V24-v1/0003/60BF4888-942B-DF11-9CB7-0017312B5567.root']





###################################################################
process = cms.Process("HLTMuonOfflineAnalysis")


process.load("DQMOffline.Trigger.TopTrigRateAnalyzer_cfi")
process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Components.DQMStoreStats_cfi")






process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(maxEvents)
)


process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),							
	fileNames = cms.untracked.vstring(targetFileNames)
)


# take this out and try to run
process.DQMStore = cms.Service("DQMStore")

process.MessageLogger = cms.Service("MessageLogger",
    debugModules   = cms.untracked.vstring('*'),
    cout           = cms.untracked.PSet(
	# Be careful - this can print a lot of debug info
    #        threshold = cms.untracked.string('DEBUG')
	threshold = cms.untracked.string('INFO')
	#threshold = cms.untracked.string('WARNING')
    ),
    categories     = cms.untracked.vstring('HLTMuonVal'),
    destinations   = cms.untracked.vstring('cout')
)

process.out = cms.OutputModule("PoolOutputModule",
	 outputCommands = cms.untracked.vstring('drop *', 'keep *_MEtoEDMConverter_*_*'),
	 # Disable fast cloning to resolve 34X issue
	 fastCloning = cms.untracked.bool(False),						   
	 fileName = cms.untracked.string(outputFileName)

)

process.analyzerpath = cms.Path(
	process.topTrigOfflineDQM*
    process.MEtoEDMConverter*
	process.dqmStoreStats
)

process.outpath = cms.EndPath(process.out)
