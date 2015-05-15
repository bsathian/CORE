#include "MuonSelections.h"
#include "Math/VectorUtil.h"
#include "IsolationTools.h"

using namespace tas;

bool isLooseMuonPOG(unsigned int muIdx){
  if (!mus_pid_PFMuon().at(muIdx)) return false;    
  bool isGlobal  = true;
  bool isTracker = true;
  if (((mus_type().at(muIdx)) & (1<<1)) == 0) isGlobal  = false;
  if (((mus_type().at(muIdx)) & (1<<2)) == 0) isTracker = false;
  if (!(isGlobal || isTracker)) return false;  
  return true;
}

bool isMediumMuonPOG(unsigned int muIdx){
  bool isGlobal  = true;
  if (((mus_type().at(muIdx)) & (1<<1)) == 0) isGlobal  = false;
  bool goodGlb = isGlobal && mus_gfit_chi2().at(muIdx)/mus_gfit_ndof().at(muIdx)<3. && 
                 mus_chi2LocalPosition().at(muIdx)<12. && mus_trkKink().at(muIdx)<20.;
  double validFraction = mus_validHits().at(muIdx)/(double)(mus_validHits().at(muIdx)+mus_lostHits().at(muIdx)+mus_exp_innerlayers().at(muIdx)+mus_exp_outerlayers().at(muIdx));
  bool good = validFraction >= 0.8 &&  mus_segmCompatibility().at(muIdx) >= (goodGlb ? 0.303 : 0.451);
  return good;
}

bool isTightMuonPOG(unsigned int muIdx){
  if (!mus_pid_PFMuon()            .at(muIdx)         ) return false;    
  if (((mus_type()                 .at(muIdx))
	   & (1<<1)) == 0                                 ) return false;//global muon
  if (mus_gfit_chi2()              .at(muIdx)		 
	  /mus_gfit_ndof()             .at(muIdx)  >= 10  ) return false; 
  if (mus_gfit_validSTAHits()      .at(muIdx)  == 0   ) return false; 
  if (mus_numberOfMatchedStations().at(muIdx)  <  2   ) return false;
  if (mus_validPixelHits()         .at(muIdx)  == 0   ) return false;
  if (mus_nlayers()                .at(muIdx)  <  6   ) return false;
  if (fabs(mus_dxyPV()             .at(muIdx)) >  0.2 ) return false;
  if (fabs(mus_dzPV()              .at(muIdx)) >  0.5 ) return false;
  return true;
}

bool muonID(unsigned int muIdx, id_level_t id_level){

  analysis_t analysis = whichAnalysis(id_level);

  switch (id_level){

   /////////////////////
   /// stop loose v1 ///
   /////////////////////
  
    case(STOP_loose_v1):
      return isLooseMuonPOG(muIdx);
      break;
 
   ///////////////////
   /// SS veto v1, v2 ///
   ///////////////////
  
    case(SS_veto_noiso_v1):
    case(SS_veto_noiso_v2):
      if (fabs(mus_p4().at(muIdx).eta()) > 2.4) return false;
      return isLooseMuonPOG(muIdx);
      break;

    case(SS_veto_v1):
    case(SS_veto_v2):
      if (muonID(muIdx, SS_veto_noiso_v1)==0) return false;
      if (muRelIso03(muIdx, SS) > 0.50) return false;
      return true;
      break;

   ///////////////////
   /// SS veto v3 ///
   ///////////////////
  
    case(SS_veto_noiso_v3):
      if (fabs(mus_p4().at(muIdx).eta()) > 2.4) return false;
      if (fabs(mus_dxyPV().at(muIdx)) > 0.05) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      return isLooseMuonPOG(muIdx);
      break;

    case(SS_veto_v3):
      if (muonID(muIdx, SS_veto_noiso_v3)==0) return false;
      if (muMiniRelIso(muIdx, true, 0.5, false, true) > 0.40) return false;
      return true;
      break;

    case(SS_veto_noiso_noip_v3):
      if (fabs(mus_p4().at(muIdx).eta()) > 2.4) return false;
      //if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      return isLooseMuonPOG(muIdx);
      break;

   ////////////////////
   /// HAD loose v1 ///
   ////////////////////
  
    case(HAD_loose_noiso_v1):
    case(HAD_loose_noiso_v2):
      if (!isLooseMuonPOG(muIdx)) return false;
      if (fabs(mus_dxyPV().at(muIdx)) > 0.5) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 1.0) return false;
      return true;
      break;

    case(HAD_loose_v1):
      if (muonID(muIdx, HAD_loose_noiso_v1)==0) return false;
      if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
      return true;
      break;

   ////////////////////
   /// HAD loose v2 ///
   ////////////////////
  
    // now using mini iso
    case(HAD_loose_v2):
      if (muonID(muIdx, HAD_loose_noiso_v2)==0) return false;
      if (muMiniRelIso(muIdx) > 0.2) return false;
      return true;
      break;

   ///////////////////
   /// SS FO v1 ///  same as tight, but no SIP3D cut and looser iso
   ///////////////////
  
    case(SS_fo_noiso_v1):
      if (fabs(mus_p4().at(muIdx).eta()) > 2.4) return false;
      if (!mus_pid_PFMuon().at(muIdx)) return false;    
      if (((mus_type().at(muIdx)) & (1<<1)) == 0) return false;//global muon
      if (mus_gfit_chi2().at(muIdx)/mus_gfit_ndof().at(muIdx) >= 10) return false; 
      if (mus_gfit_validSTAHits().at(muIdx) == 0) return false; 
      if (mus_numberOfMatchedStations().at(muIdx) < 2) return false;
      if (mus_validPixelHits().at(muIdx) == 0) return false;
      if (mus_nlayers().at(muIdx) < 6) return false;
      //if (fabs(mus_ip3d().at(muIdx))/mus_ip3derr().at(muIdx) >= 4) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      break;
 
   case(SS_fo_v1):
      if (muonID(muIdx, SS_fo_noiso_v1)==0) return false;
      if (muRelIso03(muIdx, SS) > 0.50) return false;
      return true;
      break;

  
   ///////////////////
   /// SS FO v2   ///  same as tight, but no SIP3D cut and looser iso
   ///////////////////

    case(SS_fo_noiso_v2):
      if (muonID(muIdx, SS_veto_noiso_v2)==0) return false;//make sure it's tighter than veto
      //if (fabs(mus_ip3d().at(muIdx))/mus_ip3derr().at(muIdx) >= 4) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      if (mus_ptErr().at(muIdx)/mus_trk_p4().at(muIdx).pt() >= 0.2) return false;
      return isMediumMuonPOG(muIdx);
      break;

   case(SS_fo_v2):
      if (muonID(muIdx, SS_fo_noiso_v2)==0) return false;
      if (muRelIso03(muIdx, SS) > 0.50) return false;
      return true;
      break;

   ///////////////////
   /// SS FO v3   ///  same as tight, but no SIP3D cut and looser iso
   ///////////////////

    case(SS_fo_noiso_v3):
      if (!muonID(muIdx, SS_veto_noiso_v3)) return false;
      if (fabs(mus_dxyPV().at(muIdx)) > 0.05) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      if (mus_ptErr().at(muIdx)/mus_trk_p4().at(muIdx).pt() >= 0.2) return false;
      return isMediumMuonPOG(muIdx);
      break;

    case(SS_fo_noiso_noip_v3):
      if (!muonID(muIdx, SS_veto_noiso_noip_v3)) return false;
      //if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      if (mus_ptErr().at(muIdx)/mus_trk_p4().at(muIdx).pt() >= 0.2) return false;
      return isMediumMuonPOG(muIdx);
      break;

   case(SS_fo_v3):
      if (!muonID(muIdx, SS_fo_noiso_v3)) return false;
      if (muMiniRelIso(muIdx, true, 0.5, false, true) > 0.40) return false;
      return true;
      break;

   ///////////////////
   /// SS tight v1 ///
   ///////////////////
  
    case(SS_tight_noiso_v1):
      if (fabs(mus_p4().at(muIdx).eta()) > 2.4) return false;
      if (!mus_pid_PFMuon().at(muIdx)) return false;    
      if (((mus_type().at(muIdx)) & (1<<1)) == 0) return false;//global muon
      if (mus_gfit_chi2().at(muIdx)/mus_gfit_ndof().at(muIdx) >= 10) return false; 
      if (mus_gfit_validSTAHits().at(muIdx) == 0) return false; 
      if (mus_numberOfMatchedStations().at(muIdx) < 2) return false;
      if (mus_validPixelHits().at(muIdx) == 0) return false;
      if (mus_nlayers().at(muIdx) < 6) return false;
      if (fabs(mus_ip3d().at(muIdx))/mus_ip3derr().at(muIdx) >= 4) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      break;
 
   case(SS_tight_v1):
      if (muonID(muIdx, SS_tight_noiso_v1)==0) return false;
      if (muRelIso03(muIdx, SS) > 0.10) return false;
      return true;
      break;

   ///////////////////
   /// SS tight v2 ///
   ///////////////////
  
    case(SS_tight_noiso_v2):
      if (muonID(muIdx, SS_fo_noiso_v2)==0) return false;//make sure it's tighter than FO
      if (fabs(mus_ip3d().at(muIdx))/mus_ip3derr().at(muIdx) >= 4) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      if (mus_ptErr().at(muIdx)/mus_trk_p4().at(muIdx).pt() >= 0.2) return false;
      return isMediumMuonPOG(muIdx);
      break;

   case(SS_tight_v2):
      if (muonID(muIdx, SS_tight_noiso_v2)==0) return false;
      if (muRelIso03(muIdx, SS) > 0.10) return false;
      return true;
      break;

   ///////////////////
   /// SS tight v3 ///
   ///////////////////
  
    case(SS_tight_noiso_v3):
      if (muonID(muIdx, SS_fo_noiso_v3)==0) return false;//make sure it's tighter than FO
      if (fabs(mus_ip3d().at(muIdx))/mus_ip3derr().at(muIdx) >= 4) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      if (mus_ptErr().at(muIdx)/mus_trk_p4().at(muIdx).pt() >= 0.2) return false;
      return isMediumMuonPOG(muIdx);
      break;

   case(SS_tight_v3):
      if (muonID(muIdx, SS_tight_noiso_v3)==0) return false;
      return passMultiIso(13, muIdx, 0.14, 0.68, 6.7);
      break;

   case(SS_tight_noip_v3):
      if (muonID(muIdx, SS_fo_noiso_noip_v3)==0) return false;
      //if (fabs(mus_ip3d().at(muIdx))/mus_ip3derr().at(muIdx) >= 4) return false;
      //if (fabs(mus_dzPV().at(muIdx)) > 0.1) return false;
      if (mus_ptErr().at(muIdx)/mus_trk_p4().at(muIdx).pt() >= 0.2) return false;
      if (!isMediumMuonPOG(muIdx)) return false;
      return passMultiIso(13, muIdx, 0.40, 0.68, 6.7);
      break;


   /////////////////////
   /// STOP tight v1 ///
   /////////////////////
  
    case(STOP_tight_v1):
      return isTightMuonPOG(muIdx);
       break;

   ////////////////////
   /// HAD tight v1 ///
   ////////////////////
  
    case(HAD_tight_noiso_v1):
    case(HAD_tight_noiso_v2):
      if (!isTightMuonPOG(muIdx)) return false;
      return true;
      break;

    case(HAD_tight_v1):
      if (muonID(muIdx, HAD_tight_noiso_v1)==0) return false;
      if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
      return true;
      break;

   ////////////////////
   /// HAD tight v2 ///
   ////////////////////
  
    // now using mini iso
    case(HAD_tight_v2):
      if (muonID(muIdx, HAD_tight_noiso_v2)==0) return false;
      if (muMiniRelIso(muIdx) > 0.2) return false;
      return true;
      break;

   /////////////////////
   /// ZMET loose v1 ///
   /////////////////////
  
    case(ZMET_loose_v1):
      if (!isLooseMuonPOG(muIdx)) return false;
      if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
	  return true;
      break;

    case(ZMET_loose_noiso_v1):
      if (!isLooseMuonPOG(muIdx)) return false;
      // if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
	  return true;
      break;

   /////////////////////
   /// ZMET tight v1 ///
   /////////////////////
  
    case(ZMET_tight_v2):
      if (!isTightMuonPOG(muIdx)) return false;
      if (muMiniRelIso(muIdx) >= 0.1) return false; 
	  return true;
      break;
  
    case(ZMET_tight_v1):
      if (!isTightMuonPOG(muIdx)) return false;
      if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
	  return true;
      break;

    case(ZMET_tight_noiso_v1):
      if (!isTightMuonPOG(muIdx)) return false;
      // if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
	  return true;
      break;

   ///////////////
   /// Default ///
   ///////////////
    default:
      {
        cout << "Warning! Muon ID not defined for this id_level! " << id_level << endl;
        return false;
      }
   
  
  }//cases
  return true;
}

int muTightID(unsigned int muIdx, analysis_t analysis, int version){
  switch (analysis){
    case (POG):
      if (!isTightMuonPOG(muIdx)) return 1;
      if (!isLooseMuonPOG(muIdx)) return 0;
      break;
    case (SS):
      if (muonID(muIdx, SS_tight_v3)) return 2;
      if (muonID(muIdx, SS_fo_v3))    return 1;
      if (muonID(muIdx, SS_veto_v3))  return 0;
      break;
    case (HAD):
      if (version == 1){
        if (muonID(muIdx, HAD_tight_v1)) return 1;
        if (muonID(muIdx, HAD_loose_v1)) return 0;
      }
      if (version == 2){
        if (muonID(muIdx, HAD_tight_v2)) return 1;
        if (muonID(muIdx, HAD_loose_v2)) return 0;
      }
      break;
    case (STOP):
      if (muonID(muIdx, STOP_tight_v1)) return 1;
      if (muonID(muIdx, STOP_loose_v1)) return 0;
      break;
    case (ZMET):
      if (muonID(muIdx, ZMET_tight_v1)) return 1;
      if (muonID(muIdx, ZMET_loose_v1)) return 0;
  }
  return -1;
}

int tightChargeMuon(unsigned int muIdx){
  if ( mus_ptErr().at(muIdx) / mus_p4().at(muIdx).pt() < 0.2 )          return 2;
  else                                                                  return 0;
}

