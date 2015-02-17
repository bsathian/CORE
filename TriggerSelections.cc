#include "TriggerSelections.h"

#include "Math/VectorUtil.h"

using namespace tas;

//---------------------------------------------
// Utility to print trigger names in the file
//---------------------------------------------
void PrintTriggers(){
  for( unsigned int i = 0; i < hlt_trigNames().size(); i++ ){
    cout << passHLTTrigger(hlt_trigNames().at(i).Data()) << "\t"
         << hlt_prescales().at(i) << "\t" 
         << hlt_trigNames().at(i).Data() << endl;

  } 
  cout << endl;
}

bool passesTriggerVeryLowPt(int hyp_type){
  if (!evt_isRealData()) return true; 

  if (hyp_type == 0){
      if (passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFNoPUHT175_v")) {return true;}
      if (passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFHT175_v"    )) {return true;}
  }

  else if ((hyp_type == 1 || hyp_type == 2)){
      if (passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v")) {return true;}
      if (passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v"    )) {return true;}
  }

  else if (hyp_type == 3){
      if (passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v")) {return true;}
      if (passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFHT175_v"    )) {return true;}
  }

  return false;
}

bool passUnprescaledHLTTrigger(const char* arg){

  //Put the trigger name into a string
  TString HLTTrigger( arg );

  //Did the trigger pass?
  if ( !(passHLTTrigger(HLTTrigger)) ) return false;

  //The trigger passed, check the pre-scale
  int trigIndx = -1;
  vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
  vector<TString>::const_iterator end_it   = hlt_trigNames().end();
  vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger );
  if( (found_it != end_it) ){
    trigIndx = found_it - begin_it;
  }
  else {
    cout << "passUnprescaledTrigger: Cannot find Trigger " << arg << endl;
    return false;
  }

  if( strcmp( arg , hlt_trigNames().at(trigIndx) ) != 0 ){
    cout << "Error! trig names don't match" << endl;
    cout << "Found trig name " << hlt_trigNames().at(trigIndx) << endl;
    cout << "Prescale        " << hlt_prescales().at(trigIndx) << endl;
    exit(0);
  }

  if( hlt_prescales().at(trigIndx) == 1) return true;

  return false;

}

bool passUnprescaledHLTTriggerPattern(const char* arg){
  TString HLTTriggerPattern(arg);
  TString HLTTrigger = triggerName( HLTTriggerPattern );
  if( HLTTrigger.Contains("TRIGGER_NOT_FOUND")) return false;
  return passUnprescaledHLTTrigger( HLTTrigger );
}

bool passHLTTriggerPattern(const char* arg){
  TString HLTTriggerPattern(arg);
  TString HLTTrigger = triggerName( HLTTriggerPattern );
  if( HLTTrigger.Contains("TRIGGER_NOT_FOUND")) return false;
  return passHLTTrigger( HLTTrigger );
}

TString triggerName(TString triggerPattern){

  bool    foundTrigger  = false;
  TString exact_hltname = "";

  for( unsigned int itrig = 0 ; itrig < hlt_trigNames().size() ; ++itrig ){
    if( TString( hlt_trigNames().at(itrig) ).Contains( triggerPattern ) ){
      foundTrigger  = true;
      exact_hltname = hlt_trigNames().at(itrig);
      break;
    }
  }

  if( !foundTrigger) return "TRIGGER_NOT_FOUND";

  return exact_hltname;

}


//this function returns the HLT pre-scale for a given trigger name
int HLT_prescale( const char* arg ){

 // put the trigger name into a string
  TString HLTTrigger( arg );

  // Did the trigger pass?
  if ( !(passHLTTrigger(HLTTrigger)) ) return -1;

  // The trigger passed, check the pre-scale
  int trigIndx = -1;
  vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
  vector<TString>::const_iterator end_it   = hlt_trigNames().end();
  vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger );
  if( (found_it != end_it) ){
    trigIndx = found_it - begin_it;
  }
  else {
    //this should not happen
    cout << "passUnprescaledTrigger: Cannot find Trigger " << arg << endl;
    return false;
  }

  //sanity check (this should not happen)
  if( strcmp( arg , hlt_trigNames().at(trigIndx) ) != 0 ){
    cout << "Error! trig names don't match" << endl;
    cout << "Found trig name " << hlt_trigNames().at(trigIndx) << endl;
    cout << "Prescale        " << hlt_prescales().at(trigIndx) << endl;
    exit(0);
  }

  //return prescale
  return hlt_prescales().at(trigIndx);
}

//---------------------------------------------
// Check if trigger is unprescaled and passes
// for a specific object, specified by a p4
//---------------------------------------------
bool passUnprescaledHLTTrigger(const char* arg, const LorentzVector &obj){

  // put the trigger name into a string
  TString HLTTrigger( arg );

  // find the index of this trigger
  int trigIdx = -1;
  vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
  vector<TString>::const_iterator end_it = hlt_trigNames().end();
  vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger);
  if(found_it != end_it) trigIdx = found_it - begin_it;
  else return false; // trigger was not found

  // get the vector of p4 passing this trigger
  std::vector<LorentzVector> trigObjs = hlt_trigObjs_p4()[trigIdx];

  // if no trigger objects then fail
  if (trigObjs.size() == 0) return false; 

  // does the trigger match this lepton
  float drMin = 999.99;
  for (size_t i = 0; i < trigObjs.size(); ++i)
  {
    float dr = ROOT::Math::VectorUtil::DeltaR(trigObjs[i], obj);
    if (dr < drMin) drMin = dr;
  }

  // if the closest trigger object
  // is further than 0.1 then fail
  if (drMin > 0.1) return false;

  // if we got to here then
  // the trigger passed, check the pre-scale

  //sanity check (this should not happen)
  if( strcmp( arg , hlt_trigNames().at(trigIdx) ) != 0 ){
    cout << "Error! trig names don't match" << endl;
    cout << "Found trig name " << hlt_trigNames().at(trigIdx) << endl;
    cout << "Prescale        " << hlt_prescales().at(trigIdx) << endl;
    exit(0);
  }

  //return true only if pre-scale = 1
  if( hlt_prescales().at(trigIdx) == 1 ) return true;

  return false;

}


//--------------------------------------------------------
// Returns the number of objects passing a given trigger
// Returns zero if the trigger failed
// Returns -1 if the trigger passed but no onjects were found
//--------------------------------------------------------
int nHLTObjects(const char* arg ){

  // put the trigger name into a string
  TString HLTTrigger( arg );

  // Did the trigger pass?
  if ( !(passHLTTrigger(HLTTrigger)) ) return 0;

  // The trigger passed, see how many associated objects there are
  int trigIndx = -1;
  vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
  vector<TString>::const_iterator end_it = hlt_trigNames().end();
  vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger );
  if( (found_it != end_it) ){
    trigIndx = found_it - begin_it;
    //cout << "nHLTObjects: Found Trigger: " << arg << endl;
  }
  else {
    cout << "nHLTObjects: Cannot find Trigger " << arg << endl;
    return 0;
  }

  int nobj = hlt_trigObjs_p4().at(trigIndx).size();
  /*
  for( unsigned int i=0; i < nobj; i++ ){
    cout << "\t" << i << ", (pt, eta, phi): " << hlt_trigObjs_p4().at(trigIndx).at(i).pt() << " "
                  << hlt_trigObjs_p4().at(trigIndx).at(i).eta() << " " << hlt_trigObjs_p4().at(trigIndx).at(i).phi() << endl;
  }
  */

  // cout << " Number of jets = " << njets << endl;

  if (nobj == 0) return -1;
  return nobj;
}


//-----------------------------------------------------
// Returns the nth object that passes a given trigger
// (n starts from 0)
///----------------------------------------------------
LorentzVector p4HLTObject(const char* arg, int objNumber){
 
  TString HLTTrigger( arg );
  int trigIndx = -1;
  vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
  vector<TString>::const_iterator end_it = hlt_trigNames().end();
  vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger );
  if( (found_it != end_it) ){
    trigIndx = found_it - begin_it;
    //cout << "p4HLTObject: Found Trigger: " << arg << endl;
  }
  else {
    cout << "p4HLTObject: Cannot find Trigger: " << arg << endl;
    assert(0);
  }

  int nobj = hlt_trigObjs_p4().at(trigIndx).size();
  if (nobj == 0 ) {
    cout << "ERROR: nobj == 0" << endl;
    assert(0);
  }

  if (objNumber > (nobj-1)) {
    cout << "ERROR: requested object number " << objNumber << " but we only have " << nobj <<endl;
    assert(0);
  }

  return hlt_trigObjs_p4().at(trigIndx).at(objNumber);

}

// trigger id
int idHLTObject(const char* arg, int objNumber){

  TString HLTTrigger( arg );
  int trigIndx = -1;
  vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
  vector<TString>::const_iterator end_it = hlt_trigNames().end();
  vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger );
  if( (found_it != end_it) ){
    trigIndx = found_it - begin_it;
    //cout << "idHLTObject: Found Trigger: " << arg << endl;
  }
  else {
    cout << "idHLTObject: Cannot find Trigger: " << arg << endl;
    assert(0);
  }

  int nobj = hlt_trigObjs_id().at(trigIndx).size();
  if (nobj == 0 ) {
    cout << "ERROR: nobj == 0" << endl;
    assert(0);
  }

  if (objNumber > (nobj-1)) {
    cout << "ERROR: requested object number " << objNumber << " but we only have " << nobj <<endl;
    assert(0);
  }

  return hlt_trigObjs_id().at(trigIndx).at(objNumber);

}
