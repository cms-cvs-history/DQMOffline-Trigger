#include "DQMOffline/Trigger/interface/EgHLTOfflineSource.h"

#include "DQMOffline/Trigger/interface/EgHLTEleHLTFilterMon.h"
#include "DQMOffline/Trigger/interface/EgHLTPhoHLTFilterMon.h"

#include "DQMOffline/Trigger/interface/EgHLTDebugFuncs.h"
#include "DQMOffline/Trigger/interface/EgHLTDQMCut.h"
#include "DQMOffline/Trigger/interface/EgHLTMonElemFuncs.h"
#include "DQMOffline/Trigger/interface/EgHLTTrigTools.h"

#include "DQMServices/Core/interface/MonitorElement.h"

#include "FWCore/Framework/interface/Run.h"

#include <boost/algorithm/string.hpp>



using namespace egHLT;

EgHLTOfflineSource::EgHLTOfflineSource(const edm::ParameterSet& iConfig)
{
  dbe_ = edm::Service<DQMStore>().operator->();
  if (!dbe_) {
    edm::LogInfo("EgHLTOfflineSource") << "unable to get DQMStore service?";
  }
  if(iConfig.getUntrackedParameter<bool>("DQMStore", false)) {
    dbe_->setVerbose(0);
  }

 
  binData_.setup(iConfig.getParameter<edm::ParameterSet>("binData"));
  cutMasks_.setup(iConfig.getParameter<edm::ParameterSet>("cutMasks"));
  eleHLTFilterNames_ = iConfig.getParameter<std::vector<std::string> >("eleHLTFilterNames");
  phoHLTFilterNames_ = iConfig.getParameter<std::vector<std::string> >("phoHLTFilterNames");
  eleTightLooseTrigNames_ = iConfig.getParameter<std::vector<std::string> >("eleTightLooseTrigNames");
  diEleTightLooseTrigNames_ = iConfig.getParameter<std::vector<std::string> >("diEleTightLooseTrigNames"); 
  phoTightLooseTrigNames_ = iConfig.getParameter<std::vector<std::string> >("phoTightLooseTrigNames");
  diPhoTightLooseTrigNames_ = iConfig.getParameter<std::vector<std::string> >("diPhoTightLooseTrigNames"); 


  std::vector<std::string> hltFiltersUsed;
  getHLTFilterNamesUsed(hltFiltersUsed);
  TrigCodes::setCodes(hltFiltersUsed);
  offEvtHelper_.setup(iConfig,hltFiltersUsed);
  
  dirName_=iConfig.getParameter<std::string>("DQMDirName");//"HLT/EgHLTOfflineSource_" + iConfig.getParameter<std::string>("@module_label");

  if(dbe_) dbe_->setCurrentFolder(dirName_);
  

}


EgHLTOfflineSource::~EgHLTOfflineSource()
{ 
  // LogDebug("EgHLTOfflineSource") << "destructor called";
  for(size_t i=0;i<eleFilterMonHists_.size();i++){
    delete eleFilterMonHists_[i];
  } 
  for(size_t i=0;i<phoFilterMonHists_.size();i++){
    delete phoFilterMonHists_[i];
  }
  for(size_t i=0;i<eleMonElems_.size();i++){
    delete eleMonElems_[i];
  } 
  for(size_t i=0;i<phoMonElems_.size();i++){
    delete phoMonElems_[i];
  }
}

void EgHLTOfflineSource::beginJob(const edm::EventSetup& iSetup)
{
  //the one monitor element the source fills directly
  dqmErrsMonElem_ =dbe_->book1D("dqmErrors","EgHLTOfflineSource Errors",101,-0.5,100.5);
  

  //each trigger path with generate object distributions and efficiencies (BUT not trigger efficiencies...)
  for(size_t i=0;i<eleHLTFilterNames_.size();i++) addEleTrigPath(eleHLTFilterNames_[i]);
  for(size_t i=0;i<phoHLTFilterNames_.size();i++) addPhoTrigPath(phoHLTFilterNames_[i]);
 
  //efficiencies of one trigger path relative to another
  MonElemFuncs::initTightLooseTrigHists(eleMonElems_,eleTightLooseTrigNames_,binData_,
					new EgHLTDQMVarCut<OffEle>(~0x0,&OffEle::cutCode)); 
  MonElemFuncs::initTightLooseTrigHistsTrigCuts(eleMonElems_,eleTightLooseTrigNames_,binData_);


  MonElemFuncs::initTightLooseTrigHists(phoMonElems_,phoTightLooseTrigNames_,binData_,
					new EgHLTDQMVarCut<OffPho>(~0x0,&OffPho::cutCode)); 
  MonElemFuncs::initTightLooseTrigHistsTrigCuts(phoMonElems_,phoTightLooseTrigNames_,binData_);


  MonElemFuncs::initTightLooseTrigHists(eleMonElems_,diEleTightLooseTrigNames_,binData_,
					new EgDiEleCut(~0x0,&OffEle::cutCode));
  MonElemFuncs::initTightLooseTrigHists(phoMonElems_,diPhoTightLooseTrigNames_,binData_,
					new EgDiPhoCut(~0x0,&OffPho::cutCode));

  MonElemFuncs::initTightLooseDiObjTrigHistsTrigCuts(eleMonElems_,diEleTightLooseTrigNames_,binData_);
  MonElemFuncs::initTightLooseDiObjTrigHistsTrigCuts(phoMonElems_,diPhoTightLooseTrigNames_,binData_);

  //tag and probe trigger efficiencies
  //this is to do measure the trigger efficiency with respect to a fully selected offline electron
  //using a tag and probe technique (note: this will be different to the trigger efficiency normally calculated) 
  MonElemFuncs::initTrigTagProbeHists(eleMonElems_,eleHLTFilterNames_,binData_);
  
  //tag and probe not yet implimented for photons (attemping to see if it makes sense first)
  // MonElemFuncs::initTrigTagProbeHists(phoMonElems,phoHLTFilterNames_);


}

void EgHLTOfflineSource::endJob() 
{
  //  LogDebug("EgHLTOfflineSource") << "ending job";
}

void EgHLTOfflineSource::beginRun(const edm::Run& run, const edm::EventSetup& c)
{
  //LogDebug("EgHLTOfflineSource") << "beginRun, run " << run.id();
}


void EgHLTOfflineSource::endRun(const edm::Run& run, const edm::EventSetup& c)
{
  //LogDebug("EgHLTOfflineSource") << "endRun, run " << run.id();
}


void EgHLTOfflineSource::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 
  //debugging info, commented out for prod
  //  int nrProducts = debug::listAllProducts<edm::ValueMap<double> >(iEvent,"EgHLTOfflineSource");
  //edm::LogInfo("EgHLTOfflineSource")<<" HERE ";
  
  const double weight=1.; //we have the ability to weight but its disabled for now

  int errCode = offEvtHelper_.makeOffEvt(iEvent,iSetup,offEvt_);
  if(errCode!=0){
    dqmErrsMonElem_->Fill(errCode);
    return;
  }

  for(size_t pathNr=0;pathNr<eleFilterMonHists_.size();pathNr++){
    eleFilterMonHists_[pathNr]->fill(offEvt_,weight);
  } 
  for(size_t pathNr=0;pathNr<phoFilterMonHists_.size();pathNr++){
    phoFilterMonHists_[pathNr]->fill(offEvt_,weight);
  }

  for(size_t monElemNr=0;monElemNr<eleMonElems_.size();monElemNr++){
    const std::vector<OffEle>& eles = offEvt_.eles();
    for(size_t eleNr=0;eleNr<eles.size();eleNr++){
      eleMonElems_[monElemNr]->fill(eles[eleNr],offEvt_,weight);
    }
  }  

  for(size_t monElemNr=0;monElemNr<phoMonElems_.size();monElemNr++){
    const std::vector<OffPho>& phos = offEvt_.phos();
    for(size_t phoNr=0;phoNr<phos.size();phoNr++){
      phoMonElems_[monElemNr]->fill(phos[phoNr],offEvt_,weight);
    }
  }
}


void EgHLTOfflineSource::addEleTrigPath(const std::string& name)
{
  EleHLTFilterMon* filterMon = new EleHLTFilterMon(name,TrigCodes::getCode(name.c_str()),binData_,cutMasks_);  
  eleFilterMonHists_.push_back(filterMon);
  std::sort(eleFilterMonHists_.begin(),eleFilterMonHists_.end(),EleHLTFilterMon::ptrLess<EleHLTFilterMon>()); //takes a minor efficiency hit at initalisation to ensure that the vector is always sorted
}

void EgHLTOfflineSource::addPhoTrigPath(const std::string& name)
{
  PhoHLTFilterMon* filterMon = new PhoHLTFilterMon(name,TrigCodes::getCode(name.c_str()),binData_,cutMasks_);
  phoFilterMonHists_.push_back(filterMon);
  std::sort(phoFilterMonHists_.begin(),phoFilterMonHists_.end(),PhoHLTFilterMon::ptrLess<PhoHLTFilterMon>()); //takes a minor efficiency hit at initalisation to ensure that the vector is always sorted
}

//this function puts every filter name used in a std::vector
//due to the design, to ensure we get every filter, filters will be inserted multiple times
//eg electron filters will contain photon triggers which are also in the photon filters
//but only want one copy in the vector
//this function is intended to be called once per job so some inefficiency can can be tolerated
//therefore we will use a std::set to ensure ensure that each filtername is only inserted once
//and then convert to a std::vector
void EgHLTOfflineSource::getHLTFilterNamesUsed(std::vector<std::string>& filterNames)const
{ 
  std::set<std::string> filterNameSet;
  for(size_t i=0;i<eleHLTFilterNames_.size();i++) filterNameSet.insert(eleHLTFilterNames_[i]);
  for(size_t i=0;i<phoHLTFilterNames_.size();i++) filterNameSet.insert(phoHLTFilterNames_[i]);
  //here we are little more complicated as entries are of the form "tightTrig:looseTrig" 
  //so we need to split them first
  for(size_t tightLooseNr=0;tightLooseNr<eleTightLooseTrigNames_.size();tightLooseNr++){
    std::vector<std::string> trigNames;
    boost::split(trigNames,eleTightLooseTrigNames_[tightLooseNr],boost::is_any_of(":"));
    if(trigNames.size()!=2) continue; //format incorrect
    filterNameSet.insert(trigNames[0]);
    filterNameSet.insert(trigNames[1]);
  }
  for(size_t tightLooseNr=0;tightLooseNr<diEleTightLooseTrigNames_.size();tightLooseNr++){
    std::vector<std::string> trigNames;
    boost::split(trigNames,diEleTightLooseTrigNames_[tightLooseNr],boost::is_any_of(":"));
    if(trigNames.size()!=2) continue; //format incorrect
    filterNameSet.insert(trigNames[0]);
    filterNameSet.insert(trigNames[1]);
  }
  for(size_t tightLooseNr=0;tightLooseNr<phoTightLooseTrigNames_.size();tightLooseNr++){
    std::vector<std::string> trigNames;
    boost::split(trigNames,phoTightLooseTrigNames_[tightLooseNr],boost::is_any_of(":"));
    if(trigNames.size()!=2) continue; //format incorrect
    filterNameSet.insert(trigNames[0]);
    filterNameSet.insert(trigNames[1]);
  } 
  for(size_t tightLooseNr=0;tightLooseNr<diPhoTightLooseTrigNames_.size();tightLooseNr++){
    std::vector<std::string> trigNames;
    boost::split(trigNames,diPhoTightLooseTrigNames_[tightLooseNr],boost::is_any_of(":"));
    if(trigNames.size()!=2) continue; //format incorrect
    filterNameSet.insert(trigNames[0]);
    filterNameSet.insert(trigNames[1]);
  }
  //right all the triggers are inserted once and only once in the set, convert to vector
  //very lazy, create a new vector so can use the constructor and then use swap to transfer
  std::vector<std::string>(filterNameSet.begin(),filterNameSet.end()).swap(filterNames);
}