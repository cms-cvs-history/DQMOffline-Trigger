import FWCore.ParameterSet.Config as cms

process = cms.Process('BPAGPOSTPROCESSOR')

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load("DQMOffline.Trigger.BPAGPostProcessor_cff")
process.JpsiTrigEff.SavePlotsInRootFileName = cms.untracked.string("/tmp/jpsiPlots.root")
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    fileMode = cms.untracked.string('FULLMERGE')
)

process.source = cms.Source("PoolSource",
    processingMode = cms.untracked.string('RunsAndLumis'),
    fileNames = cms.untracked.vstring('file:/tmp/jpsi.root')
)

process.load('Configuration/StandardSequences/EDMtoMEAtJobEnd_cff')
process.dqmSaver.workflow = '/BPAG/Post/Processor'
process.dqmSaver.dirName = '/tmp/'
process.path = cms.Path(process.EDMtoME*process.bPAGPostProcessor)

process.endpath = cms.EndPath(process.DQMSaver)

