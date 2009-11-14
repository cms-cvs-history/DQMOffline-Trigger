#include "DQMOffline/Trigger/interface/DQMOfflineHLTEventInfoClient.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DQMServices/Core/interface/QReport.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <memory>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "TROOT.h"
#include "TRandom.h"
#include <TH1F.h>
#include <TH2F.h>

using namespace edm;
using namespace std;

/*
class DQMOfflineHLTEventInfoClient: public edm::EDAnalyzer {

public:

  /// Constructor
  DQMOfflineHLTEventInfoClient(const edm::ParameterSet& ps);
  
  /// Destructor
  virtual ~DQMOfflineHLTEventInfoClient();
 
protected:

  /// BeginJob
  void beginJob(const edm::EventSetup& c);

  /// BeginRun
  void beginRun(const edm::Run& r, const edm::EventSetup& c);

  /// Fake Analyze
  void analyze(const edm::Event& e, const edm::EventSetup& c) ;

  void beginLuminosityBlock(const edm::LuminosityBlock& lumiSeg, 
                            const edm::EventSetup& context) ;

  /// DQM Client Diagnostic
  void endLuminosityBlock(const edm::LuminosityBlock& lumiSeg, 
                          const edm::EventSetup& c);

  /// EndRun
  void endRun(const edm::Run& r, const edm::EventSetup& c);

  /// Endjob
  void endJob();

private:

  void initialize();
  edm::ParameterSet parameters_;

  DQMStore* dbe_;  
  bool verbose_;
  int counterLS_;      ///counter
  int counterEvt_;     ///counter
  int prescaleLS_;     ///units of lumi sections
  int prescaleEvt_;    ///prescale on number of events
  // -------- member data --------

  MonitorElement * reportSummary_;
  std::vector<MonitorElement*> reportSummaryContent_;
  MonitorElement * reportSummaryMap_;


};
*/


DQMOfflineHLTEventInfoClient::DQMOfflineHLTEventInfoClient(const edm::ParameterSet& ps)
{
  parameters_=ps;
  initialize();
}

DQMOfflineHLTEventInfoClient::~DQMOfflineHLTEventInfoClient(){
 if(verbose_) cout <<"[TriggerDQM]: ending... " << endl;
}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::initialize(){ 

  counterLS_=0; 
  counterEvt_=0; 
  
  // get back-end interface
  dbe_ = Service<DQMStore>().operator->();
  
  // base folder for the contents of this job
  verbose_ = parameters_.getUntrackedParameter<bool>("verbose", false);
  
  prescaleLS_ = parameters_.getUntrackedParameter<int>("prescaleLS", -1);
  if(verbose_) cout << "DQM lumi section prescale = " << prescaleLS_ << " lumi section(s)"<< endl;
  
  prescaleEvt_ = parameters_.getUntrackedParameter<int>("prescaleEvt", -1);
  if(verbose_) cout << "DQM event prescale = " << prescaleEvt_ << " events(s)"<< endl;
  

      
}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::beginJob(const EventSetup& context){

  if(verbose_) cout <<"[TriggerDQM]: Begin Job" << endl;
  // get backendinterface  
  dbe_ = Service<DQMStore>().operator->();

  dbe_->setCurrentFolder("HLT/EventInfo");

  // reportSummary
  reportSummary_ = dbe_->get("HLT/EventInfo/reportSummary");

  if ( reportSummary_  ) {
      dbe_->removeElement(reportSummary_->getName()); 
   }
  
  reportSummary_ = dbe_->bookFloat("reportSummary");
  //initialize reportSummary to 1
  if (reportSummary_) reportSummary_->Fill(1);

  // CertificationSummary
  CertificationSummary_ = dbe_->get("HLT/EventInfo/CertificationSummary");

  if ( CertificationSummary_  ) {
      dbe_->removeElement(CertificationSummary_->getName()); 
   }
  
  CertificationSummary_ = dbe_->bookFloat("CertificationSummary");
  //initialize CertificationSummary to 1
  if (CertificationSummary_) CertificationSummary_->Fill(1);

  //initialize reportSummary to 1
  if (reportSummary_) reportSummary_->Fill(1);


  // reportSummaryMap
  dbe_->setCurrentFolder("HLT/EventInfo");

  reportSummaryMap_ = dbe_->get("HLT/EventInfo/reportSummaryMap");
  if ( reportSummaryMap_  ) {
  dbe_->removeElement(reportSummaryMap_->getName());
  }


  reportSummaryMap_ = dbe_->book2D("reportSummaryMap", "reportSummaryMap", 1, 1, 2, 6, 1, 7);
  reportSummaryMap_->setAxisTitle("", 1);
  reportSummaryMap_->setAxisTitle("", 2);
  reportSummaryMap_->setBinLabel(1,"Muon",2);
  reportSummaryMap_->setBinLabel(2,"Electron",2);
  reportSummaryMap_->setBinLabel(2,"Electron",2);
  reportSummaryMap_->setBinLabel(4,"JetMET",2);
  reportSummaryMap_->setBinLabel(5,"BJet",2);
  reportSummaryMap_->setBinLabel(6,"Tau",2);
  reportSummaryMap_->setBinLabel(1," ",1);


  CertificationSummaryMap_ = dbe_->get("HLT/EventInfo/CertificationSummaryMap");
  if ( CertificationSummaryMap_  ) {
  dbe_->removeElement(CertificationSummaryMap_->getName());
  }


  CertificationSummaryMap_ = dbe_->book2D("CertificationSummaryMap", "CertificationSummaryMap", 1, 1, 2, 6, 1, 7);
  CertificationSummaryMap_->setAxisTitle("", 1);
  CertificationSummaryMap_->setAxisTitle("", 2);
  CertificationSummaryMap_->setBinLabel(1,"Muon",2);
  CertificationSummaryMap_->setBinLabel(2,"Electron",2);
  CertificationSummaryMap_->setBinLabel(2,"Electron",2);
  CertificationSummaryMap_->setBinLabel(4,"JetMET",2);
  CertificationSummaryMap_->setBinLabel(5,"BJet",2);
  CertificationSummaryMap_->setBinLabel(6,"Tau",2);
  CertificationSummaryMap_->setBinLabel(1," ",1);

}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::beginRun(const Run& r, const EventSetup& context) {
}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::beginLuminosityBlock(const LuminosityBlock& lumiSeg, const EventSetup& context) {
   // optionally reset histograms here
}

void DQMOfflineHLTEventInfoClient::endLuminosityBlock(const edm::LuminosityBlock& lumiSeg, 
                          const edm::EventSetup& c){
}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::analyze(const Event& e, const EventSetup& context){
   
   counterEvt_++;
   if (prescaleEvt_<1) return;
   if (prescaleEvt_>0 && counterEvt_%prescaleEvt_ != 0) return;

   if(verbose_) cout << "DQMOfflineHLTEventInfoClient::analyze" << endl;


}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::endRun(const Run& r, const EventSetup& context){

  float summarySum = 0;
  float reportSummary = 0;

  dbe_->setCurrentFolder("HLT/EventInfo/reportSummaryContents");
  MonitorElement* HLT_Muon = dbe_->get("HLT_Muon");
  if(HLT_Muon) reportSummaryContent_.push_back(HLT_Muon);

  MonitorElement * HLT_Electron = dbe_->get("HLT_Electron");
  if(HLT_Electron) reportSummaryContent_.push_back(HLT_Electron);

  MonitorElement * HLT_Photon = dbe_->get("HLT_Photon");
  if(HLT_Photon) reportSummaryContent_.push_back(HLT_Photon);


  int nSubsystems = reportSummaryContent_.size();

  for (int m = 0; m < nSubsystems; m++) {    
    summarySum += (reportSummaryContent_[m])->getFloatValue();
  }


  if(nSubsystems) {
    reportSummary = summarySum / nSubsystems;;
  }

  reportSummary_->Fill(reportSummary);
  CertificationSummary_->Fill(reportSummary);


  reportSummaryMap_->setBinContent(1,1,HLT_Muon->getFloatValue());//Muon
  reportSummaryMap_->setBinContent(1,2,HLT_Electron->getFloatValue());//Electron
  reportSummaryMap_->setBinContent(1,3,HLT_Photon->getFloatValue());//Photon

  dbe_->setCurrentFolder("HLT/EventInfo/CertificationSummaryContents");
  CertificationSummaryMap_->setBinContent(1,1,HLT_Muon->getFloatValue());//Muon
  CertificationSummaryMap_->setBinContent(1,2,HLT_Electron->getFloatValue());//Electron
  CertificationSummaryMap_->setBinContent(1,3,HLT_Photon->getFloatValue());//Photon
}

//--------------------------------------------------------
void DQMOfflineHLTEventInfoClient::endJob(){
}

