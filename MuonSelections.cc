#include "MuonSelections.h"
#include "Math/VectorUtil.h"

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

bool isTightMuonPOG(unsigned int muIdx){
  if (!mus_pid_PFMuon().at(muIdx)) return false;    
  if (((mus_type().at(muIdx)) & (1<<1)) == 0) return false;//global muon
  if (mus_gfit_chi2().at(muIdx)/mus_gfit_ndof().at(muIdx) >= 10) return false; 
  if (mus_gfit_validSTAHits().at(muIdx) == 0) return false; 
  if (mus_numberOfMatchedStations().at(muIdx) < 2) return false;
  if (mus_validPixelHits().at(muIdx) == 0) return false;
  if (mus_nlayers().at(muIdx) < 6) return false;
  if (fabs(mus_dxyPV().at(muIdx)) > 0.2) return false;
  if (fabs(mus_dzPV().at(muIdx)) > 0.5) return false;
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
   /// SS veto v1 ///
   ///////////////////
  
    case(SS_veto_noiso_v1):
      if (fabs(mus_p4().at(muIdx).eta()) > 2.4) return false;
      return isLooseMuonPOG(muIdx);
      break;

    case(SS_veto_v1):
      if (muonID(muIdx, SS_veto_noiso_v1)==0) return false;
      if (muRelIso03(muIdx, SS) > 0.50) return false;
      return true;
      break;
  
   ////////////////////
   /// HAD loose v1 ///
   ////////////////////
  
    case(HAD_loose_v1):
      if (!isLooseMuonPOG(muIdx)) return false;
      if (fabs(mus_dxyPV().at(muIdx)) > 0.5) return false;
      if (fabs(mus_dzPV().at(muIdx)) > 1.0) return false;
      if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
      break;

   ///////////////////
   /// SS FO v1 ///  same as medium, but no SIP3D cut and looser iso
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

   /////////////////////
   /// STOP tight v1 ///
   /////////////////////
  
    case(STOP_tight_v1):
      return isTightMuonPOG(muIdx);
       break;

   ////////////////////
   /// HAD tight v1 ///
   ////////////////////
  
    case(HAD_tight_v1):
      if (!isTightMuonPOG(muIdx)) return false;
      if (muRelIso03(muIdx, analysis) >= 0.15) return false; 
      break;

   ///////////////
   /// Default ///
   ///////////////
    default:
      {
        cout << "Warning! Muon ID not defined for this id_level!" << endl;
        return false;
      }
   
  
  }//cases
  return true;
}

float muRelIso03DB(unsigned int muIdx){
  float chiso     = mus_isoR03_pf_ChargedHadronPt().at(muIdx);
  float nhiso     = mus_isoR03_pf_NeutralHadronEt().at(muIdx);
  float emiso     = mus_isoR03_pf_PhotonEt().at(muIdx);
  float deltaBeta = mus_isoR03_pf_PUPt().at(muIdx);
  float absiso = chiso + std::max(0.0, nhiso + emiso - 0.5 * deltaBeta);
  return absiso/(mus_p4().at(muIdx).pt());
}

float muRelIso04DB(unsigned int muIdx){
  float chiso     = mus_isoR04_pf_ChargedHadronPt().at(muIdx);
  float nhiso     = mus_isoR04_pf_NeutralHadronEt().at(muIdx);
  float emiso     = mus_isoR04_pf_PhotonEt().at(muIdx);
  float deltaBeta = mus_isoR04_pf_PUPt().at(muIdx);
  float absiso = chiso + std::max(0.0, nhiso + emiso - 0.5 * deltaBeta);
  return absiso/(mus_p4().at(muIdx).pt());
}

float muRelIso03(unsigned int muIdx, analysis_t analysis){
  if (analysis == SS) return muRelIso03EA(muIdx);
  return muRelIso03DB(muIdx);
}

float muRelIso04(unsigned int muIdx, analysis_t analysis){
  return muRelIso04DB(muIdx);
}

float muRelIso03EA(unsigned int muIdx){
  float chiso     = mus_isoR03_pf_ChargedHadronPt().at(muIdx);
  float nhiso     = mus_isoR03_pf_NeutralHadronEt().at(muIdx);
  float emiso     = mus_isoR03_pf_PhotonEt().at(muIdx);
  float ea = 0.;
  if      (fabs(mus_p4().at(muIdx).eta())<=0.800) ea = 0.0913;
  else if (fabs(mus_p4().at(muIdx).eta())<=1.300) ea = 0.0765;
  else if (fabs(mus_p4().at(muIdx).eta())<=2.000) ea = 0.0546;
  else if (fabs(mus_p4().at(muIdx).eta())<=2.200) ea = 0.0728;
  else if (fabs(mus_p4().at(muIdx).eta())<=2.500) ea = 0.1177;
  float absiso = chiso + std::max(float(0.0), nhiso + emiso - evt_fixgrid_all_rho() * ea);
  return absiso/(mus_p4().at(muIdx).pt());
}

float muRelIsoCustomCone(unsigned int muIdx, float dr, float deltaZCut){
  float chiso     = 0.;
  float nhiso     = 0.;
  float emiso     = 0.;
  for (unsigned int i=0; i<pfcands_particleId().size(); ++i){
    if ( fabs(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(i),mus_p4().at(muIdx)))>dr ) continue;  
    if ( fabs(pfcands_particleId().at(i))==211 && fabs(pfcands_dz().at(i)) < deltaZCut ) chiso+=pfcands_p4().at(i).pt();
    if ( fabs(pfcands_particleId().at(i))==130 ) nhiso+=pfcands_p4().at(i).pt();
    if ( fabs(pfcands_particleId().at(i))==22  ) emiso+=pfcands_p4().at(i).pt();
  }
  float absiso = chiso + std::max(float(0.0), nhiso + emiso);
  return absiso/(mus_p4().at(muIdx).pt());
}
float muRelIsoCustomConeDB(unsigned int muIdx, float dr, float deltaZCut){
  float chiso     = 0.;
  float nhiso     = 0.;
  float emiso     = 0.;
  float deltaBeta = 0.;
  for (unsigned int i=0; i<pfcands_particleId().size(); ++i){
    if ( fabs(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(i),mus_p4().at(muIdx)))>dr ) continue;  
    if ( fabs(pfcands_particleId().at(i))==211 ) {
      if (fabs(pfcands_dz().at(i)) < deltaZCut) chiso+=pfcands_p4().at(i).pt();
      else deltaBeta+=pfcands_p4().at(i).pt();
    }
    if ( fabs(pfcands_particleId().at(i))==130 ) nhiso+=pfcands_p4().at(i).pt();
    if ( fabs(pfcands_particleId().at(i))==22  ) emiso+=pfcands_p4().at(i).pt();
  }
  float absiso = chiso + std::max(0.0, nhiso + emiso - 0.5 * deltaBeta);
  return absiso/(mus_p4().at(muIdx).pt());
}
float muMiniRelIso(unsigned int idx, float deltaZCut) {
  float pt = mus_p4().at(idx).pt();
  float dr = 0.2;
  if (pt>50) dr = 10./pt;
  if (pt>200) dr = 0.05;
  return muRelIsoCustomCone(idx,dr,deltaZCut);
}

int muTightID(unsigned int muIdx, analysis_t analysis){
  switch (analysis){
    case (POG):
      if (!isTightMuonPOG(muIdx)) return 1;
      if (!isLooseMuonPOG(muIdx)) return 0;
      break;
    case (SS):
      if (muonID(muIdx, SS_tight_v1)) return 2;
      if (muonID(muIdx, SS_fo_v1))    return 1;
      if (muonID(muIdx, SS_veto_v1))  return 0;
      break;
    case (HAD):
      if (muonID(muIdx, HAD_tight_v1)) return 1;
      if (muonID(muIdx, HAD_loose_v1)) return 0;
      break;
    case (STOP):
      if (muonID(muIdx, STOP_tight_v1)) return 1;
      if (muonID(muIdx, STOP_loose_v1)) return 0;
      break;
  }
  return -1;
}

int tightChargeMuon(unsigned int muIdx){
  if ( mus_ptErr().at(muIdx) / mus_p4().at(muIdx).pt() < 0.2 )          return 2;
  else                                                                  return 0;
}

