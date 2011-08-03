import FWCore.ParameterSet.Config as cms

process = cms.Process("EDMtoMEConvert")
process.load("DQMServices.Core.DQM_cfg")

process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.load("DQMServices.Components.DQMEnvironment_cfi")
process.load("DQMServices.Components.EDMtoMEConverter_cff")

process.load("DQMOffline.Trigger.EgHLTOfflineClient_cfi")
#process.load("DQMOffline.Trigger.TopElectronHLTOfflineClient_cfi")
process.load("DQMOffline.Trigger.EgHLTOfflineSummaryClient_cfi")
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")
#process.load("Geometry.CaloEventSetup.CaloTopology_cfi")
#process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")

#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkSummary = cms.untracked.PSet(
    reportEvery = cms.untracked.int32(1),
    limit = cms.untracked.int32(10000000)
)
process.MessageLogger.cerr.FwkReport = cms.untracked.PSet(
    reportEvery = cms.untracked.int32(1),
    limit = cms.untracked.int32(10000000)
)

    

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(),
                            processingMode = cms.untracked.string("RunsLumisAndEvents"),
)
process.source.fileNames=cms.untracked.vstring(
  #  'file:/data/ndpc3/c/dmorse/HLTDQMrootFiles/May18/SourceTest_420.root',

  #  'file:/data/ndpc3/c/dmorse/HLTDQMrootFiles/May18/SourceTest_420_2.root',
    'rfio:/castor/cern.ch/user/d/dmorse/DQMOfflineSource/DQMOfflineSource_1_1_vMy.root'
    )
#process.source.processingMode = cms.untracked.string("RunsLumisAndEvents"),

#process.source.processingMode = cms.untracked.string("RunsAndLumis")
process.source.processingMode = cms.untracked.string("Runs")


process.qTester = cms.EDAnalyzer("QualityTester",
     qtList = cms.untracked.FileInPath('DQMOffline/Trigger/data/EgHLTOffQualityTests.xml'),
     verboseQT = cms.untracked.bool(True),
     qtestOnEndJob =cms.untracked.bool(False),
     qtestOnEndRun =cms.untracked.bool(True),                         
                               
 )


process.DQMStore.collateHistograms = True
process.EDMtoMEConverter.convertOnEndLumi = False
process.EDMtoMEConverter.convertOnEndRun = True

#process.p1 = cms.Path(process.EDMtoMEConverter*process.egHLTOffDQMClient*process.topElectronHLTOffDQMClient*process.qTester*process.egHLTOffDQMSummaryClient*process.dqmSaver)
process.p1 = cms.Path(process.EDMtoMEConverter*process.egHLTOffDQMClient*process.egHLTOffDQMSummaryClient*process.dqmSaver)


process.DQMStore.verbose = 1
process.DQM.collectorHost = ''
process.dqmSaver.convention = cms.untracked.string('Offline')
process.dqmSaver.saveByRun = cms.untracked.int32(-1)
process.dqmSaver.saveAtJobEnd = cms.untracked.bool(True)
process.dqmSaver.workflow = cms.untracked.string('/Run2011A/SingleElectron/RECO')
process.dqmSaver.forceRunNumber = cms.untracked.int32(1)
process.dqmSaver.dirName = '/data/ndpc3/c/dmorse/HLTDQMrootFiles/SourceClientTest'
