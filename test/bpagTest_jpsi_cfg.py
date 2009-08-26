import FWCore.ParameterSet.Config as cms

process = cms.Process("HLTMuonOfflineAnalysis")

#process.load("DQMOffline.Trigger.MuonTrigRateAnalyzer_cosmics_cfi")
process.load("DQMOffline.Trigger.BPAGTrigRateAnalyzer_cfi")
process.load("DQMServices.Components.MEtoEDMConverter_cfi")

# load this thing to count bins
process.load("DQMServices.Components.DQMStoreStats_cfi")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),


							# ---- J/PSI
							# ---- Local
							#fileNames = cms.untracked.vstring ( 'file:/data/ndpc0/b/slaunwhj/RelValJPsi/EA6BFAD3-505A-DE11-8313-0018F3D0961A.root',
							#									'file:/data/ndpc0/b/slaunwhj/RelValJPsi/E4CFF5DE-6658-DE11-B9C1-0018F3D0970A.root',
							#									'file:/data/ndpc0/b/slaunwhj/RelValJPsi/3ACDB108-C859-DE11-B62D-0018F3D09608.root'
							#									),

							# ---- Castor

							fileNames = cms.untracked.vstring ( '/store/relval/CMSSW_3_1_0_pre10/RelValJpsiMM_Pt_0_20/GEN-SIM-RECO/STARTUP_31X_v1/0001/EA6BFAD3-505A-DE11-8313-0018F3D0961A.root',
																'/store/relval/CMSSW_3_1_0_pre10/RelValJpsiMM_Pt_0_20/GEN-SIM-RECO/STARTUP_31X_v1/0001/E4CFF5DE-6658-DE11-B9C1-0018F3D0970A.root',
																'/store/relval/CMSSW_3_1_0_pre10/RelValJpsiMM_Pt_0_20/GEN-SIM-RECO/STARTUP_31X_v1/0001/3ACDB108-C859-DE11-B62D-0018F3D09608.root'
															  ),


)

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
	 fileName = cms.untracked.string('file:/data/ndpc0/b/slaunwhj/scratch0/EDM_jpsi_pre10_vTest.root')
)

process.analyzerpath = cms.Path(
    process.bpagTrigOffDQM*
    process.MEtoEDMConverter*
	process.dqmStoreStats
)

process.outpath = cms.EndPath(process.out)
