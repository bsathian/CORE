#include "ElectronSelections.h"
#include "Math/LorentzVector.h"
#include "Math/VectorUtil.h"
#include "IsolationTools.h"

//Development Notes
  //Original Author: Alex (UCSB), who stole functions from Indara, Jason, Giuseppe
  //POG Electron IDs are defined in: 
  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification#Electron_ID_Working_Points

readMVA* globalEleMVAreader = 0;

using namespace tas;

bool isVetoElectronPOG(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false; 
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.8) return false; 
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false; 
    if (els_hOverE().at(elIdx) >= 0.15) return false; 
    if (fabs(els_dxyPV().at(elIdx)) >= 0.04) return false;
    if (fabs(els_dzPV().at(elIdx)) >= 0.2) return false; 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.7) return false; 
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false; 
    if (fabs(els_dxyPV().at(elIdx)) >= 0.04) return false;
    if (fabs(els_dzPV().at(elIdx)) >= 0.2) return false; 
  }
  else return false;

  return true;
}

bool isLooseElectronPOG(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false;
    if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
    if (els_hOverE().at(elIdx) >= 0.12) return false;
    if (els_conv_vtx_flag().at(elIdx)) return false;
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false;
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.15) return false;
    if (fabs(els_dxyPV().at(elIdx)) >= 0.02) return false;
    if (fabs(els_dzPV().at(elIdx)) >= 0.2) return false; 
    if (els_exp_innerlayers().at(elIdx) > 1) return false;
  }
  else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false;
    if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
    if (els_hOverE().at(elIdx) >= 0.1) return false;
    if (els_conv_vtx_flag().at(elIdx) ) return false;
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.009) return false;
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.10) return false;
    if (fabs(els_dxyPV().at(elIdx)) >= 0.02) return false; 
    if (fabs(els_dzPV().at(elIdx)) >= 0.2) return false; 
    if (els_exp_innerlayers().at(elIdx) > 1) return false;
  }
  else return false;
  return true;
}

bool isMediumElectronPOG(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.004) return false;
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.06) return false; 
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false; 
    if (els_hOverE().at(elIdx) >= 0.12) return false; 
    if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
    if (els_conv_vtx_flag().at(elIdx)) return false;
    if (els_exp_innerlayers().at(elIdx) > 1) return false;
    if (fabs(els_dxyPV().at(elIdx)) >= 0.02) return false; 
    if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
  }
  else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
    if (els_conv_vtx_flag().at(elIdx)) return false;
    if (els_exp_innerlayers().at(elIdx) > 0) return false;
    if (fabs(els_dxyPV().at(elIdx)) >= 0.02) return false; 
    if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false;
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.03) return false; 
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false; 
    if (els_hOverE().at(elIdx) >= 0.1) return false; 
    if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
  }
  else return false;
  return true;
}

bool isTightElectronPOG(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.004) return false;
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.03) return false; 
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false; 
    if (els_hOverE().at(elIdx) >= 0.12) return false; 
    if (fabs((1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
    if (fabs(els_dxyPV().at(elIdx)) >= 0.02) return false; 
    if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
    if (els_conv_vtx_flag().at(elIdx)) return false;
    if (els_exp_innerlayers().at(elIdx) > 0) return false;
  }
  else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
    if (fabs(els_dEtaIn().at(elIdx)) >= 0.005) return false;
    if (fabs(els_dPhiIn().at(elIdx)) >= 0.02) return false; 
    if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false; 
    if (els_hOverE().at(elIdx) >= 0.1) return false; 
    if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
    if (fabs(els_dxyPV().at(elIdx)) >= 0.02) return false;
    if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
    if (els_conv_vtx_flag().at(elIdx)) return false;
    if (els_exp_innerlayers().at(elIdx) > 0) return false;
  }
  else return false;
  return true;
}

bool electronID(unsigned int elIdx, id_level_t id_level){

  analysis_t analysis = whichAnalysis(id_level);

  switch (id_level){

   //////////////////
   // SS veto v1 ////
   //////////////////

    case(SS_veto_noiso_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false; 
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.8) return false; 
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false; 
        if (els_hOverE().at(elIdx) >= 0.15) return false; 
      }
      else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.7) return false; 
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false; 
      }
      else return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 1) return false;
      if (fabs(els_dxyPV().at(elIdx)) >= 0.05) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
      break;

    case(SS_veto_v1):
      if (electronID(elIdx, SS_veto_noiso_v1)==0) return false; 
      if (eleRelIso03(elIdx, analysis) >= 0.50) return false; 
      return true;
      break;

   ////////////////////
   /// SS veto v2 ///
   ////////////////////

    case(SS_veto_noiso_v2):
      //trigger match cuts
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.15) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.011) return false; 
        if (els_hOverE().at(elIdx) >= 0.12) return false; 
      }
      else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.1) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.031) return false; 
        if (els_hOverE().at(elIdx) >= 0.1) return false; 
      }
      else return false;
      if (fabs(els_etaSC().at(elIdx)) > 2.4) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 1) return false;
      if (fabs(els_dxyPV().at(elIdx)) >= 0.05) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
      if (globalEleMVAreader==0) {
	cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	return false;
      }
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);
      break;

    case(SS_veto_v2):
      if (electronID(elIdx, SS_veto_noiso_v2)==0) return false; 
      if (eleRelIso03(elIdx, analysis) >= 0.50) return false; 
      return true;
      break;

   ////////////////////
   /// SS veto v3 ///
   ////////////////////

    case(SS_veto_noiso_v3):
      //trigger match cuts fixme and fix noip below
      /*
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.15) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.011) return false; 
        if (els_hOverE().at(elIdx) >= 0.12) return false; 
      }
      else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.1) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.031) return false; 
        if (els_hOverE().at(elIdx) >= 0.1) return false; 
      }
      else return false;
      */
      if (fabs(els_etaSC().at(elIdx)) > 2.5) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 1) return false;
      if (fabs(els_dxyPV().at(elIdx)) >= 0.05) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
      if (globalEleMVAreader==0){
	    cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	    return false;
      }
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);
      break;

    case(SS_veto_v3):
      if (electronID(elIdx, SS_veto_noiso_v3)==0) return false; 
      if (elMiniRelIso(elIdx, true, 0.0, false, true) >= 0.40) return false;
      return true;
      break;

    case(SS_veto_noiso_noip_v3):
      if (fabs(els_etaSC().at(elIdx)) > 2.5) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 1) return false;
      //if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false; 
      if (globalEleMVAreader==0){
	    cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	    return false;
      }
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);
      break;

   ////////////////////
   /// HAD veto v1 ////
   ////////////////////

      // same as POG veto, except using sigmaIEtaIEta (not _full5x5)
    case(HAD_veto_noiso_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
	if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false; 
	if (fabs(els_dPhiIn().at(elIdx)) >= 0.8) return false; 
	if (els_sigmaIEtaIEta().at(elIdx) >= 0.01) return false; 
	if (els_hOverE().at(elIdx) >= 0.15) return false; 
	if (fabs(els_dxyPV().at(elIdx)) >= 0.04) return false;
	if (fabs(els_dzPV().at(elIdx)) >= 0.2) return false; 
      }
      else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
	if (fabs(els_dEtaIn().at(elIdx)) >= 0.01) return false; 
	if (fabs(els_dPhiIn().at(elIdx)) >= 0.7) return false; 
	if (els_sigmaIEtaIEta().at(elIdx) >= 0.03) return false; 
	if (fabs(els_dxyPV().at(elIdx)) >= 0.04) return false;
	if (fabs(els_dzPV().at(elIdx)) >= 0.2) return false; 
      }
      return true;
      break;

    case(HAD_veto_v1):
      if (electronID(elIdx, HAD_veto_noiso_v1)==0) return false;
      if (eleRelIso03(elIdx, analysis) >= 0.15) return false; 
      return true;
      break;

   ////////////////////
   /// HAD veto v2 ////
   ////////////////////

    // same as POG phys14 veto
    case(HAD_veto_noiso_v2):
      if (!isVetoElectronPOGphys14noIso(elIdx)) return false;
      return true;
      break;

    // now using mini iso
    case(HAD_veto_v2):
      if (electronID(elIdx, HAD_veto_noiso_v2)==0) return false;
      if (elMiniRelIso(elIdx) > 0.1) return false; 
      return true;
      break;

   /////////////////////
   /// STOP veto v1 ////
   /////////////////////

    case(STOP_veto_v1):
      if (!isVetoElectronPOG(elIdx)) return false;
      return true;
      break;

    case(STOP_veto_v2):
      if (!isVetoElectronPOGphys14_v2(elIdx)) return false;
      return true;
      break;


   /////////////////////
   /// STOP loose    ///
   /////////////////////

    case(STOP_loose_v1):
      if (!isLooseElectronPOG(elIdx)) return false;
      if (eleRelIso03(elIdx, STOP) >= 0.15) return false; 
      return true;
      break;

    case(STOP_loose_v2):
      if (!isLooseElectronPOGphys14noIso_v2(elIdx)) return false;
      if ( elMiniRelIso(elIdx, true, 0.0, true, false) >= 0.1) return false;
      return true;
      break;

   ///////////////////
   /// SS FO v1 /// same as medium, but no SIP3D cut and looser iso
   ///////////////////

    case(SS_fo_noiso_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.004) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.06) return false; 
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false; 
        if (els_hOverE().at(elIdx) >= 0.12) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.03) return false; 
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false; 
        if (els_hOverE().at(elIdx) >= 0.1) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      break;

    case(SS_fo_v1):
      if (electronID(elIdx, SS_fo_noiso_v1)==0) return false; 
      if (eleRelIso03(elIdx, analysis) >= 0.50) return false; 
      return true;
      break;

   ///////////////////
   /// SS FO v2 /// same as medium, but no SIP3D cut and looser iso
   ///////////////////

    case(SS_fo_noiso_v2):
      if (electronID(elIdx, SS_veto_noiso_v2)==0) return false;//make sure it's tighter than veto
      if (globalEleMVAreader==0) {
	cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	return false;
      }
      if (fabs(els_etaSC().at(elIdx)) > 2.4) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      //if (fabs(els_ip3d().at(elIdx))/els_ip3derr().at(elIdx) >= 4) return false;
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);

    case(SS_fo_v2):
      if (electronID(elIdx, SS_fo_noiso_v2)==0) return false; 
      if (eleRelIso03(elIdx, analysis) >= 0.50) return false; 
      return true;
      break;

   ///////////////////
   /// SS FO v3 /// same as medium, but no SIP3D cut and looser iso
   ///////////////////

    case(SS_fo_noiso_v3):
    case(SS_fo_looseMVA_noiso_v3):
      if (electronID(elIdx, SS_veto_noiso_v3)==0) return false;//make sure it's tighter than veto
      if (globalEleMVAreader==0){
	    cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	    return false;
      }
      if (fabs(els_etaSC().at(elIdx)) > 2.5) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      if (fabs(els_dxyPV().at(elIdx)) > 0.05) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);

    case(SS_fo_looseMVA_noiso_noip_v3):
      if (electronID(elIdx, SS_veto_noiso_noip_v3)==0) return false;//make sure it's tighter than veto
      if (globalEleMVAreader==0){
        cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
        return false;
      }
      if (fabs(els_etaSC().at(elIdx)) > 2.5) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      //if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);
      break;

    case(SS_fo_v3):
      if (electronID(elIdx, SS_fo_noiso_v3)==0) return false; 
      if (elMiniRelIso(elIdx, true, 0.0, false, true) >= 0.40) return false;
      return true;
      break;

    case(SS_fo_looseMVA_v3):
      if (electronID(elIdx, SS_fo_looseMVA_noiso_v3)==0) return false; 
      if (elMiniRelIso(elIdx, true, 0.0, false, true) >= 0.40) return false;
      return true;
      break;

   ////////////////////
   /// HAD loose v1 ///
   ////////////////////

    case(HAD_loose_noiso_v1):
    case(HAD_loose_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (els_sigmaIEtaIEta().at(elIdx) >= 0.01) return false;
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
        if (els_hOverE().at(elIdx) >= 0.12) return false;
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.15) return false;
      }
      else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (els_sigmaIEtaIEta().at(elIdx) >= 0.03) return false;
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
        if (els_hOverE().at(elIdx) >= 0.1) return false;
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.009) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.10) return false;
      }
      else return false;
      break;

   /////////////////////
   /// HAD loose v2 ////
   /////////////////////

    // same as POG phys14 loose
    case(HAD_loose_noiso_v2):
      if (!isLooseElectronPOGphys14noIso(elIdx)) return false;
      return true;
      break;

    case(HAD_loose_v2):
      if (electronID(elIdx, HAD_loose_noiso_v2)==0) return false;
      if (elMiniRelIso(elIdx) > 0.1) return false; 
      return true;
      break;

   //////////////////////
   /// STOP sync      ///
   //////////////////////
    case(STOP_sync_v1):
      if (!isMediumElectronPOGphys14(elIdx)) return false;
      return true;
      break;

   //////////////////////
   /// STOP medium  ///
   //////////////////////

    case(STOP_medium_v1):
      if (!isMediumElectronPOG(elIdx)) return false;
      if (eleRelIso03(elIdx, STOP) >= 0.15) return false; 
      return true;
      break;

    case(STOP_medium_v2):
      if (!isMediumElectronPOGphys14noIso_v2(elIdx)) return false;
      if ( elMiniRelIso(elIdx, true, 0.0, true, false) >= 0.1) return false;
      return true;
      break;

   /////////////////////
   /// HAD medium v1 ///
   /////////////////////

    case(HAD_medium_noiso_v1):
    case(HAD_medium_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.004) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.06) return false; 
        if (els_sigmaIEtaIEta().at(elIdx) >= 0.01) return false; 
        if (els_hOverE().at(elIdx) >= 0.12) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.03) return false; 
        if (els_sigmaIEtaIEta().at(elIdx) >= 0.03) return false; 
        if (els_hOverE().at(elIdx) >= 0.1) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else return false;
      break;

   //////////////////////
   /// HAD medium v2 ////
   //////////////////////

    // same as POG phys14 medium
    case(HAD_medium_noiso_v2):
      if (!isMediumElectronPOGphys14noIso(elIdx)) return false;
      return true;
      break;

    case(HAD_medium_v2):
      if (electronID(elIdx, HAD_medium_noiso_v2)==0) return false;
      if (elMiniRelIso(elIdx) > 0.1) return false; 
      return true;
      break;

   ////////////////////
   /// SS medium v1 ///
   ////////////////////

    case(SS_medium_noiso_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.004) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.06) return false; 
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.01) return false; 
        if (els_hOverE().at(elIdx) >= 0.12) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.007) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.03) return false; 
        if (els_sigmaIEtaIEta_full5x5().at(elIdx) >= 0.03) return false; 
        if (els_hOverE().at(elIdx) >= 0.1) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      if (fabs(els_ip3d().at(elIdx))/els_ip3derr().at(elIdx) >= 4) return false;
      break;

    case(SS_medium_v1):
      if (electronID(elIdx, SS_medium_noiso_v1)==0) return false; 
      if (eleRelIso03(elIdx, analysis) >= 0.10) return false; 
      return true;
      break;

   ////////////////////
   /// SS medium v2 ///
   ////////////////////

    case(SS_medium_noiso_v2):
      if (electronID(elIdx, SS_fo_noiso_v2)==0) return false;//make sure it's tighter than FO
      if (globalEleMVAreader==0) {
	cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	return false;
      }
      if (fabs(els_etaSC().at(elIdx)) > 2.4) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      if (fabs(els_ip3d().at(elIdx))/els_ip3derr().at(elIdx) >= 4) return false;
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);

    case(SS_medium_v2):
      if (electronID(elIdx, SS_medium_noiso_v2)==0) return false; 
      if (eleRelIso03(elIdx, analysis) >= 0.10) return false; 
      return true;
      break;

   ////////////////////
   /// SS medium v3 ///
   ////////////////////

    case(SS_medium_noiso_v3):
      if (electronID(elIdx, SS_fo_noiso_v3)==0) return false;//make sure it's tighter than FO
      if (globalEleMVAreader==0) {
	    cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	    return false;
      }
      if (fabs(els_etaSC().at(elIdx)) > 2.5) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      if (fabs(els_ip3d().at(elIdx))/els_ip3derr().at(elIdx) >= 4) return false;
      return globalEleMVAreader->passesElectronMVAid(elIdx, id_level);

    case(SS_medium_v3):
      if (electronID(elIdx, SS_medium_noiso_v3)==0) return false; 
      return passMultiIso(11, elIdx, 0.10, 0.70, 7.0);
      break;

    case(SS_medium_noip_v3):
      if (electronID(elIdx, SS_fo_looseMVA_noiso_noip_v3)==0) return false;//make sure it's tighter than FO
      if (globalEleMVAreader==0) {
	    cout << "readMVA=0, please create and init it (e.g with createAndInitMVA function)" << endl;
	    return false;
      }
      if (fabs(els_etaSC().at(elIdx)) > 2.5) return false;
      if (els_conv_vtx_flag().at(elIdx)) return false;
      if (els_exp_innerlayers().at(elIdx) > 0) return false;
      if (threeChargeAgree(elIdx)==0) return false;
      //if (fabs(els_dzPV().at(elIdx)) >= 0.1) return false;
      if (!globalEleMVAreader->passesElectronMVAid(elIdx, id_level)) return false;
      //return passMultiIso(11, elIdx, 0.40, 0.7, 7.0);
      return true;
      break;

   /////////////////////
   /// STOP tigh     ///
   /////////////////////

    case(STOP_tight_v1):
      if (!isTightElectronPOG(elIdx)) return false;
      if (eleRelIso03(elIdx, STOP) >= 0.10) return false; 
      return true;
      break;
  
    case(STOP_tight_v2):
      if (!isTightElectronPOGphys14noIso_v2(elIdx)) return false;
      if ( elMiniRelIso(elIdx, true, 0.0, true, false) >= 0.1) return false;
      return true;
      break;

   ////////////////////
   /// HAD tight v1 ///
   ////////////////////

    case(HAD_tight_noiso_v1):
    case(HAD_tight_v1):
      if (fabs(els_etaSC().at(elIdx)) <= 1.479){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.004) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.03) return false; 
        if (els_sigmaIEtaIEta().at(elIdx) >= 0.01) return false; 
        if (els_hOverE().at(elIdx) >= 0.12) return false; 
        if (fabs((1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else if((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){
        if (fabs(els_dEtaIn().at(elIdx)) >= 0.005) return false;
        if (fabs(els_dPhiIn().at(elIdx)) >= 0.02) return false; 
        if (els_sigmaIEtaIEta().at(elIdx) >= 0.03) return false; 
        if (els_hOverE().at(elIdx) >= 0.1) return false; 
        if (fabs( (1.0/els_ecalEnergy().at(elIdx)) - (els_eOverPIn().at(elIdx)/els_ecalEnergy().at(elIdx)) ) >= 0.05) return false;
      }
      else return false;
      break;

   /////////////////////
   /// HAD tight v2 ////
   /////////////////////

    // same as POG phys14 tight
    case(HAD_tight_noiso_v2):
      if (!isTightElectronPOGphys14noIso(elIdx)) return false;
      return true;
      break;

    case(HAD_tight_v2):
      if (electronID(elIdx, HAD_tight_noiso_v2)==0) return false;
      if (elMiniRelIso(elIdx) > 0.1) return false; 
      return true;
      break;

	/////////////////////
	/// ZMET loose v1 ///
	/////////////////////


  case(ZMET_loose_v2):
	if (!isLooseElectronPOGphys14noIso(elIdx)) return false;
	if (elMiniRelIso(elIdx) >= 0.1) return false; 
	else return true;
	break;

  case(ZMET_loose_v1):
	if (!isLooseElectronPOGphys14noIso(elIdx)) return false;
	if (eleRelIso03(elIdx, analysis) >= 0.15) return false; 
	else return true;
	break;

  case(ZMET_loose_noiso_v1):
	if (!isLooseElectronPOGphys14noIso(elIdx)) return false;
	else return true;
	break;

   ///////////////
   /// Default ///
   ///////////////
  default:
    {
      cout << "Warning! Electron ID not defined for this id_level!" << endl;
      return false;
    }

  }//switch
  return true;
}

bool isVetoElectronPOGphys14(unsigned int elIdx){
  if (!isVetoElectronPOGphys14noIso(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03DB(elIdx)                                          >= 0.164369) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03DB(elIdx)                                          >= 0.212604) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isVetoElectronPOGphys14_v2(unsigned int elIdx){
  if (!isVetoElectronPOGphys14noIso_v2(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03EA(elIdx)                                          >= 0.158721) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03EA(elIdx)                                          >= 0.177032) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isLooseElectronPOGphys14(unsigned int elIdx){
  if (!isLooseElectronPOGphys14noIso(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03DB(elIdx)                                          >= 0.120026) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03DB(elIdx)                                          >= 0.162914) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isLooseElectronPOGphys14_v2(unsigned int elIdx){
  if (!isLooseElectronPOGphys14noIso_v2(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03EA(elIdx)                                          >= 0.130136) return false;// PF isolation w/EA PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03EA(elIdx)                                          >= 0.163368) return false;// PF isolation w/EA PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isMediumElectronPOGphys14(unsigned int elIdx){
  if (!isMediumElectronPOGphys14noIso(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03DB(elIdx)                                          >= 0.097213) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03DB(elIdx)                                          >= 0.116708) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isMediumElectronPOGphys14_v2(unsigned int elIdx){
  if (!isMediumElectronPOGphys14noIso_v2(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03EA(elIdx)                                          >= 0.107587) return false;// PF isolation w/EA PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03EA(elIdx)                                          >= 0.113254) return false;// PF isolation w/EA PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isTightElectronPOGphys14(unsigned int elIdx){
  if (!isTightElectronPOGphys14noIso(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03DB(elIdx)                                          >= 0.074355) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03DB(elIdx)                                          >= 0.090185) return false;// PF isolation w/dBeta PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isTightElectronPOGphys14_v2(unsigned int elIdx){
  if (!isTightElectronPOGphys14noIso_v2(elIdx)) return false;
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (eleRelIso03EA(elIdx)                                          >= 0.069537) return false;// PF isolation w/EA PU correction / pT (cone dR=0.3) 
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (eleRelIso03EA(elIdx)                                          >= 0.078265) return false;// PF isolation w/EA PU correction / pT (cone dR=0.3) 
  }
  else return false;
  return true;
}

bool isVetoElectronPOGphys14noIso(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.011100) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.016315) return false;// abs(dEtaIn) 			   
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.252044) return false;// abs(dPhiIn) 			   
    if (els_hOverE()                                     .at(elIdx)   >= 0.345843) return false;// hOverE 				   	
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.248070) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.060279) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.800538) return false;// abs(dz) 				   
	if (els_exp_innerlayers()       .at(elIdx)                        > 2        ) return false;// expectedMissingInnerHits 
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.033987) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.010671) return false;// abs(dEtaIn) 			    
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.245263) return false;// abs(dPhiIn) 			    
    if (els_hOverE()                                     .at(elIdx)   >= 0.134691) return false;// hOverE 				    
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.157160) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.273097) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.885860) return false;// abs(dz) 				    
	if (els_exp_innerlayers()       .at(elIdx)                        > 3        ) return false;// expectedMissingInnerHits
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isVetoElectronPOGphys14noIso_v2(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.011586) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.013625) return false;// abs(dEtaIn)                     
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.230374) return false;// abs(dPhiIn)                     
    if (els_hOverE()                                     .at(elIdx)   >= 0.181130) return false;// hOverE                                       
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.295751) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.094095) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.713070) return false;// abs(dz)                                 
        if (els_exp_innerlayers()       .at(elIdx)                        > 2        ) return false;// expectedMissingInnerHits 
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.031849) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.011932) return false;// abs(dEtaIn)                      
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.255450) return false;// abs(dPhiIn)                      
    if (els_hOverE()                                     .at(elIdx)   >= 0.223870) return false;// hOverE                                   
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.155501) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.342293) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.953461) return false;// abs(dz)                                  
        if (els_exp_innerlayers()       .at(elIdx)                        > 3        ) return false;// expectedMissingInnerHits
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isLooseElectronPOGphys14noIso(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.010557) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.012442) return false;// abs(dEtaIn) 			   
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.072624) return false;// abs(dPhiIn) 			   
    if (els_hOverE()                                     .at(elIdx)   >= 0.121476) return false;// hOverE 				   
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.221803) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.022664) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.173670) return false;// abs(dz) 				   
	if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits 
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.032602) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.010654) return false;// abs(dEtaIn) 			    
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.145129) return false;// abs(dPhiIn) 			    
    if (els_hOverE()                                     .at(elIdx)   >= 0.131862) return false;// hOverE 				    
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.142283) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.097358) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.198444) return false;// abs(dz) 				    
	if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isLooseElectronPOGphys14noIso_v2(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.010331) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.009277) return false;// abs(dEtaIn)                     
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.094739) return false;// abs(dPhiIn)                     
    if (els_hOverE()                                     .at(elIdx)   >= 0.093068) return false;// hOverE                                  
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.189968) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.035904) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.075496) return false;// abs(dz)                                 
        if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits 
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.031838) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.009833) return false;// abs(dEtaIn)                      
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.149934) return false;// abs(dPhiIn)                      
    if (els_hOverE()                                     .at(elIdx)   >= 0.115754) return false;// hOverE                                   
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.140662) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.099266) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.197897) return false;// abs(dz)                                  
        if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isMediumElectronPOGphys14noIso(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.010399) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.007641) return false;// abs(dEtaIn) 			   
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.032643) return false;// abs(dPhiIn) 			   
    if (els_hOverE()                                     .at(elIdx)   >= 0.060662) return false;// hOverE 				   
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.153897) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.011811) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.070775) return false;// abs(dz) 				   
	if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits 
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.029524) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.009285) return false;// abs(dEtaIn) 			    
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.042447) return false;// abs(dPhiIn) 			    
    if (els_hOverE()                                     .at(elIdx)   >= 0.104263) return false;// hOverE 				    
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.137468) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.051682) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.180720) return false;// abs(dz) 				    
	if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isMediumElectronPOGphys14noIso_v2(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.009996) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.008925) return false;// abs(dEtaIn)                     
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.035973) return false;// abs(dPhiIn)                     
    if (els_hOverE()                                     .at(elIdx)   >= 0.050537) return false;// hOverE                                  
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.091942) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.012235) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.042020) return false;// abs(dz)                                 
        if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits 
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.030135) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.007429) return false;// abs(dEtaIn)                      
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.067879) return false;// abs(dPhiIn)                      
    if (els_hOverE()                                     .at(elIdx)   >= 0.086782) return false;// hOverE                                   
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.100683) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.036719) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.138142) return false;// abs(dz)                                  
        if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isTightElectronPOGphys14noIso(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.010181) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.006574) return false;// abs(dEtaIn) 			   
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.022868) return false;// abs(dPhiIn) 			   
    if (els_hOverE()                                     .at(elIdx)   >= 0.037553) return false;// hOverE 				   
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.131191) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.009924) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.015310) return false;// abs(dz) 				   
	if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits 
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.028766) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.005681) return false;// abs(dEtaIn) 			    
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.032046) return false;// abs(dPhiIn) 			    
    if (els_hOverE()                                     .at(elIdx)   >= 0.081902) return false;// hOverE 				    
	if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) - 							                           
			  (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.106055) return false;// ooEmooP				   
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.027261) return false;// abs(d0)				   
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.147154) return false;// abs(dz) 				    
	if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits
	if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

bool isTightElectronPOGphys14noIso_v2(unsigned int elIdx){
  if (fabs(els_etaSC().at(elIdx)) <= 1.479){                                                    // Barrel 
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.009947) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.006046) return false;// abs(dEtaIn)                     
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.028092) return false;// abs(dPhiIn)                     
    if (els_hOverE()                                     .at(elIdx)   >= 0.045772) return false;// hOverE                                  
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.020118) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.008790) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.021226) return false;// abs(dz)                                 
        if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits 
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else if ((fabs(els_etaSC().at(elIdx)) > 1.479) && (fabs(els_etaSC().at(elIdx)) < 2.5)){       // Endcap
    if (els_sigmaIEtaIEta_full5x5()                      .at(elIdx)   >= 0.028237) return false;// full5x5_sigmaIetaIeta   
    if (fabs(els_dEtaIn()                                .at(elIdx))  >= 0.007057) return false;// abs(dEtaIn)                      
    if (fabs(els_dPhiIn()                                .at(elIdx))  >= 0.030159) return false;// abs(dPhiIn)                      
    if (els_hOverE()                                     .at(elIdx)   >= 0.067778) return false;// hOverE                                   
        if (fabs( (1.0/els_ecalEnergy()                      .at(elIdx)) -
                          (els_eOverPIn().at(elIdx)/els_ecalEnergy() .at(elIdx))) >= 0.098919) return false;// ooEmooP                             
    if (fabs(els_dxyPV()            .at(elIdx))                       >= 0.027984) return false;// abs(d0)                                 
    if (fabs(els_dzPV()             .at(elIdx))                       >= 0.133431) return false;// abs(dz)                                  
        if (els_exp_innerlayers()       .at(elIdx)                        > 1        ) return false;// expectedMissingInnerHits
        if (els_conv_vtx_flag()         .at(elIdx)                                   ) return false;// pass conversion veto    
  }
  else return false;
  return true;
}

int eleTightID(unsigned int elIdx, analysis_t analysis, int version){
  switch (analysis){
    case (POG):
      if (!isTightElectronPOG(elIdx)) return 3;
      if (!isMediumElectronPOG(elIdx)) return 2;
      if (!isLooseElectronPOG(elIdx)) return 1;
      if (!isVetoElectronPOG(elIdx)) return 0;
      break;
    case (SS):
      if (electronID(elIdx, SS_medium_v3)) return 2;
      if (electronID(elIdx, SS_fo_v3)) return 1;
      if (electronID(elIdx, SS_veto_v3)) return 0;
      break;
    case (HAD):
      if (version == 1){
        if (electronID(elIdx, HAD_tight_v1)) return 3;
        if (electronID(elIdx, HAD_medium_v1)) return 2;
        if (electronID(elIdx, HAD_loose_v1)) return 1;
        if (electronID(elIdx, HAD_veto_v1)) return 0;
      }
      if (version == 2){
        if (electronID(elIdx, HAD_tight_v2)) return 3;
        if (electronID(elIdx, HAD_medium_v2)) return 2;
        if (electronID(elIdx, HAD_loose_v2)) return 1;
        if (electronID(elIdx, HAD_veto_v2)) return 0;
      }
      break;
    case (STOP):
      if (electronID(elIdx, STOP_tight_v2)) return 3;
      if (electronID(elIdx, STOP_medium_v2)) return 2;
      if (electronID(elIdx, STOP_loose_v2)) return 1;
      if (electronID(elIdx, STOP_veto_v2)) return 0;
      break;
    case (ZMET):
      if (electronID(elIdx, ZMET_loose_v1)) return 0;
  }
  return -1;
}

bool threeChargeAgree(unsigned int elIdx){
  return els_isGsfCtfScPixChargeConsistent().at(elIdx);
}

int tightChargeEle(unsigned int elIdx){
  if (threeChargeAgree(elIdx))                                          return 2;
  else if (els_trk_charge().at(elIdx) == els_sccharge().at(elIdx))      return 1;
  else                                                                  return 0;
}

void readMVA::InitMVA(string path){

  //Declare all variables
  ele_kfhits_           = 0;  
  ele_oldsigmaietaieta_ = 0;  
  ele_oldsigmaiphiiphi_ = 0;  
  ele_oldcircularity_   = 0;  
  ele_oldr9_            = 0;  
  ele_scletawidth_      = 0;  
  ele_sclphiwidth_      = 0;  
  ele_he_               = 0;  
  ele_kfchi2_           = 0;  
  ele_chi2_hits_        = 0;  
  ele_fbrem_            = 0;  
  ele_ep_               = 0;  
  ele_eelepout_         = 0;  
  ele_IoEmIop_          = 0;  
  ele_deltaetain_       = 0;  
  ele_deltaphiin_       = 0;  
  ele_deltaetaseed_     = 0;  
  ele_psEoverEraw_      = 0;
  ele_pT_               = 0; 
  ele_isbarrel_         = 0; 
  ele_isendcap_         = 0; 
  scl_eta_              = 0; 

  //Declare Reader
  TMVA::Reader *reader1 = new TMVA::Reader();
  TMVA::Reader *reader2 = new TMVA::Reader();
  TMVA::Reader *reader3 = new TMVA::Reader();
  TMVA::Reader *reader4 = new TMVA::Reader();
  TMVA::Reader *reader5 = new TMVA::Reader();
  TMVA::Reader *reader6 = new TMVA::Reader();
  readers.push_back(reader1);
  readers.push_back(reader2);
  readers.push_back(reader3);
  readers.push_back(reader4);
  readers.push_back(reader5);
  readers.push_back(reader6);

  //Shut the hell up
  TMVA::gConfig().SetSilent( kTRUE );

  //Find files
  files.push_back(Form("%s/data/EIDmva_EE_10_oldscenario2phys14_BDT.weights.xml" , path.c_str()));
  files.push_back(Form("%s/data/EIDmva_EB1_10_oldscenario2phys14_BDT.weights.xml", path.c_str()));
  files.push_back(Form("%s/data/EIDmva_EB2_10_oldscenario2phys14_BDT.weights.xml", path.c_str()));
  files.push_back(Form("%s/data/EIDmva_EE_5_oldscenario2phys14_BDT.weights.xml"  , path.c_str()));
  files.push_back(Form("%s/data/EIDmva_EB1_5_oldscenario2phys14_BDT.weights.xml" , path.c_str()));
  files.push_back(Form("%s/data/EIDmva_EB2_5_oldscenario2phys14_BDT.weights.xml" , path.c_str()));

  //Loop over Files
  for (unsigned int i = 0; i < 6; i++){

    //Add all variables to reader
    readers[i]->AddVariable( "ele_kfhits"           , &ele_kfhits_           );
    readers[i]->AddVariable( "ele_oldsigmaietaieta" , &ele_oldsigmaietaieta_ );
    readers[i]->AddVariable( "ele_oldsigmaiphiiphi" , &ele_oldsigmaiphiiphi_ );
    readers[i]->AddVariable( "ele_oldcircularity"   , &ele_oldcircularity_   );
    readers[i]->AddVariable( "ele_oldr9"            , &ele_oldr9_            );
    readers[i]->AddVariable( "ele_scletawidth"      , &ele_scletawidth_      );
    readers[i]->AddVariable( "ele_sclphiwidth"      , &ele_sclphiwidth_      );
    readers[i]->AddVariable( "ele_he"               , &ele_he_               );
    if (i == 0 || i == 3){
      readers[i]->AddVariable( "ele_psEoverEraw"      , &ele_psEoverEraw_      );
    }
    readers[i]->AddVariable( "ele_kfchi2"           , &ele_kfchi2_           );
    readers[i]->AddVariable( "ele_chi2_hits"        , &ele_chi2_hits_        );
    readers[i]->AddVariable( "ele_fbrem"            , &ele_fbrem_            );
    readers[i]->AddVariable( "ele_ep"               , &ele_ep_               );
    readers[i]->AddVariable( "ele_eelepout"         , &ele_eelepout_         );
    readers[i]->AddVariable( "ele_IoEmIop"          , &ele_IoEmIop_          );
    readers[i]->AddVariable( "ele_deltaetain"       , &ele_deltaetain_       );
    readers[i]->AddVariable( "ele_deltaphiin"       , &ele_deltaphiin_       );
    readers[i]->AddVariable( "ele_deltaetaseed"     , &ele_deltaetaseed_     );
    readers[i]->AddSpectator("ele_pT"               , &ele_pT_               );
    readers[i]->AddSpectator("ele_isbarrel"         , &ele_isbarrel_         );
    readers[i]->AddSpectator("ele_isendcap"         , &ele_isendcap_         );
    readers[i]->AddSpectator("scl_eta"              , &scl_eta_              );

    //Book MVA
    readers[i]->BookMVA("BDT", files[i]);
  }

}

float readMVA::MVA(unsigned int index){

  //Load all variables from tree
  ele_kfhits_           = tas::els_ckf_laywithmeas().at(index);
  ele_oldsigmaietaieta_ = tas::els_sigmaIEtaIEta_full5x5().at(index); 
  ele_oldsigmaiphiiphi_ = tas::els_sigmaIPhiIPhi_full5x5().at(index);
  ele_oldcircularity_   = 1.0 - tas::els_e1x5_full5x5().at(index)/tas::els_e5x5_full5x5().at(index); 
  ele_oldr9_            = tas::els_r9_full5x5().at(index); 
  ele_scletawidth_      = tas::els_etaSCwidth().at(index);
  ele_sclphiwidth_      = tas::els_phiSCwidth().at(index);
  ele_he_               = tas::els_hOverE().at(index);
  ele_psEoverEraw_      = tas::els_eSCPresh().at(index)/tas::els_eSCRaw().at(index);
  ele_kfchi2_           = tas::els_ckf_chi2().at(index)/tas::els_ckf_ndof().at(index);
  ele_chi2_hits_        = tas::els_chi2().at(index)/tas::els_ndof().at(index);
  ele_fbrem_            = tas::els_fbrem().at(index);
  ele_ep_               = tas::els_eOverPIn().at(index);
  ele_eelepout_         = tas::els_eOverPOut().at(index);
  ele_IoEmIop_          = tas::els_ecalEnergy().at(index) != 0 ? 1.0/tas::els_ecalEnergy().at(index) - tas::els_eOverPIn().at(index)/tas::els_ecalEnergy().at(index) : 999999;
  ele_deltaetain_       = tas::els_dEtaIn().at(index);
  ele_deltaphiin_       = tas::els_dPhiIn().at(index);
  ele_deltaetaseed_     = tas::els_dEtaOut().at(index);
  ele_pT_               = tas::els_p4().at(index).pt(); 
  ele_isbarrel_         = fabs(tas::els_etaSC().at(index)) < 1.479 ? 1 : 0; 
  ele_isendcap_         = fabs(tas::els_etaSC().at(index)) > 1.479 ? 1 : 0; 
  scl_eta_              = tas::els_etaSC().at(index); 

  float disc = -1.0;
  if (ele_pT_ >= 10.0){
    if      (fabs(scl_eta_) < 0.8) disc = readers[1]->EvaluateMVA( "BDT" );
    else if (fabs(scl_eta_) <= 1.479 && fabs(scl_eta_) >= 0.8) disc = readers[2]->EvaluateMVA( "BDT" );
    else  disc = readers[0]->EvaluateMVA( "BDT" );
  }
  else if (ele_pT_ >= 5.0){
    if      (fabs(scl_eta_) < 0.8) disc = readers[4]->EvaluateMVA( "BDT" );
    else if (fabs(scl_eta_) <= 1.479 && fabs(scl_eta_) >= 0.8) disc = readers[5]->EvaluateMVA( "BDT" );
    else  disc = readers[3]->EvaluateMVA( "BDT" );
  }

  return disc;

}

bool readMVA::passesElectronMVAid(unsigned int index, id_level_t id_level){
  float disc = MVA(index); 
  float aeta = fabs(scl_eta_);   

  switch (id_level){
  case(SS_veto_noiso_v2):
    if (aeta < 0.8) return disc > 0.35;
    if ((aeta >= 0.8 && aeta <= 1.479)) return disc > 0.20;
    if (aeta > 1.479) return disc > -0.52;
    break;

  case(SS_veto_noiso_v3):
  case (SS_veto_noiso_noip_v3):
  case(SS_fo_looseMVA_noiso_v3):
    if (aeta < 0.8) return disc > -0.11;
    if ((aeta >= 0.8 && aeta <= 1.479)) return disc > -0.35;
    if (aeta > 1.479) return disc > -0.55;
    break;

  case(SS_fo_noiso_v2):
  case(SS_medium_noiso_v2):
  case(SS_fo_noiso_v3):
  case(SS_medium_noiso_v3):
  case(SS_medium_noip_v3):
  case (SS_fo_looseMVA_noiso_noip_v3):
    if (aeta < 0.8) return disc > 0.73;
    if ((aeta >= 0.8 && aeta <= 1.479)) return disc > 0.57;
    if (aeta > 1.479) return disc > 0.05;
    break;

  default:
    cout << "WARNING: bad id level" << endl;
    break;
  }
  return -99999;

}

void createAndInitMVA(std::string pathToCORE){
  globalEleMVAreader = new readMVA();
  globalEleMVAreader->InitMVA(pathToCORE); 
}
