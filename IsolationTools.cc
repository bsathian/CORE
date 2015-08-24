#include "Math/VectorUtil.h"
#include "IsolationTools.h"

using namespace std;
using namespace tas;

bool passMultiIso(float cutMiniIso, float cutPtRatio, float cutPtRel, float miniIsoValue, float ptRatioValue, float ptRelValue){
  return (miniIsoValue < cutMiniIso && (ptRatioValue>cutPtRatio || ptRelValue > cutPtRel));
}

bool passMultiIso(int id, int idx, float cutMiniIso, float cutPtRatio, float cutPtRel){
  const LorentzVector& lep_p4 = abs(id)==11 ? els_p4().at(idx) : mus_p4().at(idx);
  const LorentzVector& jet_p4 = closestJet(lep_p4,0.4,2.4);
  float miniIso = abs(id)==11 ? elMiniRelIsoCMS3_EA(idx) : muMiniRelIsoCMS3_EA(idx);
  float closeJetPt = jet_p4.pt();
  float ptratio = ( closeJetPt>0. ? lep_p4.pt()/closeJetPt : 1.);
  float ptrel = ptRel(lep_p4, jet_p4, true);
  return passMultiIso(cutMiniIso, cutPtRatio, cutPtRel, miniIso, ptratio, ptrel);
}

bool passPtRel(int id, int idx, float cut, bool subtractLep) {
  return getPtRel(id, idx, subtractLep) > cut;
}

float getPtRel(int id, int idx, bool subtractLep) {
  LorentzVector lep_p4 = abs(id)==11 ? els_p4().at(idx) : mus_p4().at(idx);
  LorentzVector jet_p4 = closestJet(lep_p4,0.4,2.4);
  return ptRel(lep_p4, jet_p4, subtractLep);
}

float ptRel(const LorentzVector& lepp4, const LorentzVector& jetp4, bool subtractLep) {
  if (jetp4.pt()<=0.) return 0.;
  LorentzVector jp4 = jetp4;
  if (subtractLep) jp4-=lepp4;
  float dot = lepp4.Vect().Dot( jp4.Vect() );
  float ptrel = lepp4.P2() - dot*dot/jp4.P2();
  ptrel = ptrel>0 ? sqrt(ptrel) : 0.0;
  return ptrel;
}

LorentzVector closestJet(const LorentzVector& lep_p4, float dRmin, float maxAbsEta) {
  int closestIdx = -1;
  for (unsigned int pfjidx=0;pfjidx<pfjets_p4().size();++pfjidx) {
    LorentzVector jet_p4 = pfjets_p4().at(pfjidx);
    if (fabs(jet_p4.eta())>maxAbsEta) continue;
    float tmp_dRmin = ROOT::Math::VectorUtil::DeltaR(jet_p4, lep_p4);
    if ( tmp_dRmin < dRmin) {
      closestIdx = pfjidx;
      dRmin = tmp_dRmin;
    }
  }
  if (closestIdx>=0) return pfjets_p4().at(closestIdx);
  else return LorentzVector();
}

float getMiniDR(float pt) {
  float dr = 0.2;
  if (pt>50) dr = 10./pt;
  if (pt>200) dr = 0.05;
  return dr;
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
  if (analysis == WW  ) return muRelIso03EA(muIdx);
  if (analysis == SS  ) return muRelIso03EA(muIdx);
  if (analysis == ZMET) return muRelIso03EA(muIdx);
  return muRelIso03DB(muIdx);
}

float muRelIso04(unsigned int muIdx, analysis_t analysis){
  return muRelIso04DB(muIdx);
}

float muEA03(unsigned int muIdx){
  float ea = 0.;
  if      (fabs(mus_p4().at(muIdx).eta())<=0.800) ea = 0.0913;
  else if (fabs(mus_p4().at(muIdx).eta())<=1.300) ea = 0.0765;
  else if (fabs(mus_p4().at(muIdx).eta())<=2.000) ea = 0.0546;
  else if (fabs(mus_p4().at(muIdx).eta())<=2.200) ea = 0.0728;
  else if (fabs(mus_p4().at(muIdx).eta())<=2.500) ea = 0.1177;
  return ea;
}

float muRelIso03EA(unsigned int muIdx){
  float chiso     = mus_isoR03_pf_ChargedHadronPt().at(muIdx);
  float nhiso     = mus_isoR03_pf_NeutralHadronEt().at(muIdx);
  float emiso     = mus_isoR03_pf_PhotonEt().at(muIdx);
  float ea = muEA03(muIdx);
  float absiso = chiso + std::max(float(0.0), nhiso + emiso - evt_fixgridfastjet_all_rho() * ea);
  return absiso/(mus_p4().at(muIdx).pt());
}
 
float muRelIso03_noCorr(unsigned int muIdx){
  float chiso  = mus_isoR03_pf_ChargedHadronPt().at(muIdx);
  float nhiso  = mus_isoR03_pf_NeutralHadronEt().at(muIdx);
  float emiso  = mus_isoR03_pf_PhotonEt().at(muIdx);
  float absiso = chiso + nhiso + emiso;
  return absiso/(mus_p4().at(muIdx).pt());
}

float muRelIsoCustomCone(unsigned int muIdx, float dr, bool useVetoCones, float ptthresh, bool useDBcor, bool useEAcor, float mindr){
  float chiso     = 0.;
  float nhiso     = 0.;
  float emiso     = 0.;
  float correction = 0.;
  float deltaBeta = 0.;
  float deadcone_ch = 0.0001;
  float deadcone_pu = 0.01;
  float deadcone_ph = 0.01;
  float deadcone_nh = 0.01;

  for (unsigned int i=0; i<pfcands_particleId().size(); ++i){
    float thisDR = fabs(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(i),mus_p4().at(muIdx)));
    if (thisDR<mindr) continue;
    if (thisDR>dr) continue;  
    if ( fabs(pfcands_particleId().at(i))==211 ) {
      if (pfcands_fromPV().at(i) > 1 && (!useVetoCones || thisDR > deadcone_ch) ) chiso+=pfcands_p4().at(i).pt();
      else if (useDBcor && pfcands_fromPV().at(i) <= 1 && (pfcands_p4().at(i).pt() > ptthresh) && (!useVetoCones || thisDR > deadcone_pu)) deltaBeta+=pfcands_p4().at(i).pt();
    }
    if (fabs(pfcands_particleId().at(i))==130 && (pfcands_p4().at(i).pt() > ptthresh) && (!useVetoCones || thisDR > deadcone_nh)) nhiso+=pfcands_p4().at(i).pt();
    if (fabs(pfcands_particleId().at(i))==22 && (pfcands_p4().at(i).pt() > ptthresh) && (!useVetoCones || thisDR > deadcone_ph)) emiso+=pfcands_p4().at(i).pt();
  }

  if (useDBcor) correction = 0.5 * deltaBeta;
  else if (useEAcor) correction = evt_fixgridfastjet_all_rho() * muEA03(muIdx) * (dr/0.3) * (dr/0.3);
  float absiso = chiso + std::max(float(0.0), nhiso + emiso - correction);
  return absiso/(mus_p4().at(muIdx).pt());
}

float muMiniRelIso(unsigned int idx, bool useVetoCones, float ptthresh, bool useDBcor, bool useEAcor){
  float pt = mus_p4().at(idx).pt();
  float dr = getMiniDR(pt);
  return  muRelIsoCustomCone(idx,dr,useVetoCones,ptthresh,useDBcor,useEAcor);
}

float muMiniRelIsoCMS3_DB(unsigned int idx) {
  float correction = 0.5 * mus_miniIso_db().at(idx);
  float absiso = mus_miniIso_ch().at(idx) + std::max(float(0.0), mus_miniIso_nh().at(idx) + mus_miniIso_em().at(idx) - correction);
  return absiso/(mus_p4().at(idx).pt());
}

float muMiniRelIsoCMS3_EA(unsigned int idx) {
  float pt = mus_p4().at(idx).pt();
  float dr = getMiniDR(pt);
  float correction = evt_fixgridfastjet_all_rho() * muEA03(idx) * (dr/0.3) * (dr/0.3);
  float absiso = mus_miniIso_ch().at(idx) + std::max(float(0.0), mus_miniIso_nh().at(idx) + mus_miniIso_em().at(idx) - correction);
  return absiso/(mus_p4().at(idx).pt());
}

float muRelIsoAn04(unsigned int idx, bool useDBcor) {
  float pt = mus_p4().at(idx).pt();
  float dr = getMiniDR(pt);
  return muRelIsoCustomCone(idx, 0.4, false, 0.0, useDBcor, false, dr);
}

float eleRelIso03(unsigned int elIdx, analysis_t analysis){
  if (analysis == HAD ) return eleRelIso03DB(elIdx);
  if (analysis == STOP) return eleRelIso03DB(elIdx);
  if (analysis == WW  ) return eleRelIso03_90ContEA(elIdx);
  if (analysis == SS  ) return eleRelIso03EA(elIdx);
  if (analysis == ZMET) return eleRelIso03EA(elIdx);

  else return eleRelIso03EA(elIdx);
}

float eleRelIso03DB(unsigned int elIdx){
  float chiso     = els_pfChargedHadronIso().at(elIdx);
  float nhiso     = els_pfNeutralHadronIso().at(elIdx);
  float emiso     = els_pfPhotonIso().at(elIdx);
  float deltaBeta = els_pfPUIso().at(elIdx);
  float absiso    = chiso + std::max(0.0, nhiso + emiso - 0.5 * deltaBeta);
  return absiso/(els_p4().at(elIdx).pt());
}

float elEA03(unsigned int elIdx) {
  float ea = 0.;
  if      (fabs(els_p4().at(elIdx).eta())<=0.800) ea = 0.1013;
  else if (fabs(els_p4().at(elIdx).eta())<=1.300) ea = 0.0988;
  else if (fabs(els_p4().at(elIdx).eta())<=2.000) ea = 0.0572;
  else if (fabs(els_p4().at(elIdx).eta())<=2.200) ea = 0.0842;
  else if (fabs(els_p4().at(elIdx).eta())<=2.500) ea = 0.1530;
  return ea;
}

float el90ContEA03(unsigned int elIdx) {
  float ea = 0.;
  if      (fabs(els_p4().at(elIdx).eta())<=1.000) ea = 0.1752;
  else if (fabs(els_p4().at(elIdx).eta())<=1.479) ea = 0.1862;
  else if (fabs(els_p4().at(elIdx).eta())<=2.000) ea = 0.1411;
  else if (fabs(els_p4().at(elIdx).eta())<=2.200) ea = 0.1534;
  else if (fabs(els_p4().at(elIdx).eta())<=2.300) ea = 0.1903;
  else if (fabs(els_p4().at(elIdx).eta())<=2.400) ea = 0.2243;
  else if (fabs(els_p4().at(elIdx).eta())<=2.500) ea = 0.2687;
  return ea;
}

float eleRelIso03EA(unsigned int elIdx){
  float chiso = els_pfChargedHadronIso().at(elIdx);
  float nhiso = els_pfNeutralHadronIso().at(elIdx);
  float emiso = els_pfPhotonIso().at(elIdx);
  float ea    = elEA03(elIdx);
  float absiso = chiso + std::max(float(0.0), nhiso + emiso - evt_fixgridfastjet_all_rho() * ea);
  return absiso/(els_p4().at(elIdx).pt());
}

float eleRelIso03_90ContEA(unsigned int elIdx){
  float chiso = els_pfChargedHadronIso().at(elIdx);
  float nhiso = els_pfNeutralHadronIso().at(elIdx);
  float emiso = els_pfPhotonIso().at(elIdx);
  float ea    = el90ContEA03(elIdx);
  float absiso = chiso + std::max(float(0.0), nhiso + emiso - evt_fixgridfastjet_all_rho() * ea);
  return absiso/(els_p4().at(elIdx).pt());
}

float eleRelIso03_noCorr(unsigned int elIdx){
  float chiso = els_pfChargedHadronIso().at(elIdx);
  float nhiso = els_pfNeutralHadronIso().at(elIdx);
  float emiso = els_pfPhotonIso().at(elIdx);
  float absiso = chiso + nhiso + emiso;
  return absiso/(els_p4().at(elIdx).pt());
}

float elRelIsoCustomCone(unsigned int elIdx, float dr, bool useVetoCones, float ptthresh, bool useDBcor, bool useEAcor, float mindr){
  float chiso     = 0.;
  float nhiso     = 0.;
  float emiso     = 0.;
  float correction = 0.;
  float deltaBeta = 0.;
  float deadcone_ch = 0.;
  float deadcone_pu = 0.;
  float deadcone_ph = 0.;
  // veto cones only in the endcap for electrons
  if (useVetoCones && fabs(els_etaSC().at(elIdx)) > 1.479) {
    deadcone_ch = 0.015;
    deadcone_pu = 0.015;
    deadcone_ph = 0.08;
  }
  for (unsigned int i=0; i<pfcands_particleId().size(); ++i){
    float thisDR = fabs(ROOT::Math::VectorUtil::DeltaR(pfcands_p4().at(i),els_p4().at(elIdx)));
    if ( thisDR<mindr ) continue;
    if ( thisDR>dr ) continue;  
    if ( fabs(pfcands_particleId().at(i))==211 ) {
      if (pfcands_fromPV().at(i) > 1 && (!useVetoCones || thisDR > deadcone_ch) ) chiso+=pfcands_p4().at(i).pt();
      else if (useDBcor && pfcands_fromPV().at(i) <= 1 && (pfcands_p4().at(i).pt() > ptthresh) && (!useVetoCones || thisDR > deadcone_pu)) deltaBeta+=pfcands_p4().at(i).pt();
    }
    if ( fabs(pfcands_particleId().at(i))==130 && (pfcands_p4().at(i).pt() > ptthresh) ) nhiso+=pfcands_p4().at(i).pt();
    if ( fabs(pfcands_particleId().at(i))==22 && (pfcands_p4().at(i).pt() > ptthresh) && (!useVetoCones || thisDR > deadcone_ph) ) emiso+=pfcands_p4().at(i).pt();
  }
  if (useDBcor) correction = 0.5 * deltaBeta;
  else if (useEAcor) correction = evt_fixgridfastjet_all_rho() * elEA03(elIdx) * (dr/0.3) * (dr/0.3);
  float absiso = chiso + std::max(float(0.0), nhiso + emiso - correction);
  return absiso/(els_p4().at(elIdx).pt());
}
float elMiniRelIso(unsigned int idx, bool useVetoCones, float ptthresh, bool useDBcor, bool useEAcor){

  float pt = els_p4().at(idx).pt();
  float dr = getMiniDR(pt);
  return elRelIsoCustomCone(idx,dr,useVetoCones,ptthresh,useDBcor,useEAcor);
}

float elMiniRelIsoCMS3_DB(unsigned int idx) {
  float correction = 0.5 * els_miniIso_db().at(idx);
  float absiso = els_miniIso_ch().at(idx) + std::max(float(0.0), els_miniIso_nh().at(idx) + els_miniIso_em().at(idx) - correction);
  return absiso/(els_p4().at(idx).pt());
}

float elMiniRelIsoCMS3_EA(unsigned int idx) {
  float pt = els_p4().at(idx).pt();
  float dr = getMiniDR(pt);
  float correction = evt_fixgridfastjet_all_rho() * elEA03(idx) * (dr/0.3) * (dr/0.3);
  float absiso = els_miniIso_ch().at(idx) + std::max(float(0.0), els_miniIso_nh().at(idx) + els_miniIso_em().at(idx) - correction);
  return absiso/(els_p4().at(idx).pt());
}

float elRelIsoAn04(unsigned int idx, bool useDBcor) {
  float pt = els_p4().at(idx).pt();
  float dr = getMiniDR(pt);
  return elRelIsoCustomCone(idx, 0.4, false, 0.0, useDBcor, false, dr);
}

