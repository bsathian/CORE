#include "SSSelections.h"

using namespace tas;

//Development Notes
  //Original Author: Alex (UCSB), who stole functions from Indara, Jason, Giuseppe
  //Note: these functions are currently only for the SS analysis!
  //Be careful that IDs, etc. are OK before stealing for other analyses

bool makesExtraGammaStar(int iHyp){

  std::vector<unsigned int> ele_idx;
  std::vector<unsigned int> mu_idx;

  int lt_id           = tas::hyp_lt_id().at(iHyp);
  int ll_id           = tas::hyp_ll_id().at(iHyp);
  unsigned int lt_idx = tas::hyp_lt_index().at(iHyp);
  unsigned int ll_idx = tas::hyp_ll_index().at(iHyp);

  (abs(lt_id) == 11) ? ele_idx.push_back(lt_idx) : mu_idx.push_back(lt_idx);
  (abs(ll_id) == 11) ? ele_idx.push_back(ll_idx) : mu_idx.push_back(ll_idx);

  if (ele_idx.size() + mu_idx.size() != 2) {
    std::cout << "ERROR: don't have 2 leptons in hypothesis!!!  Exiting..." << std::endl;
    return false;
  }
      
  if (ele_idx.size() > 0){
    for (unsigned int eidx = 0; eidx < tas::els_p4().size(); eidx++) {
      bool is_hyp_lep = false;
      for (unsigned int vidx = 0; vidx < ele_idx.size(); vidx++){
          if (eidx == ele_idx.at(vidx)) is_hyp_lep = true;
      }
      if (is_hyp_lep) continue;
      if (fabs(tas::els_p4().at(eidx).eta()) > 2.4) continue;
      if (tas::els_p4().at(eidx).pt() < 7.0) continue;
      if (!isGoodVetoElectron(eidx)) continue;

      for (unsigned int vidx = 0; vidx < ele_idx.size(); vidx++) {
          if (tas::els_charge().at(eidx) * tas::els_charge().at(ele_idx.at(vidx)) > 0) continue;
          LorentzVector gamma_p4 = tas::els_p4().at(eidx) + tas::els_p4().at(ele_idx.at(vidx));
          float gammacandmass = sqrt(fabs(gamma_p4.mass2()));
          if (gammacandmass < 12.0) return true;
      }
    } 
  }

  if (mu_idx.size() > 0){
    for (unsigned int midx = 0; midx < tas::mus_p4().size(); midx++) {
      bool is_hyp_lep = false;
      for (unsigned int vidx = 0; vidx < mu_idx.size(); vidx++) {
        if (midx == mu_idx.at(vidx)) is_hyp_lep = true; 
      }

      if (is_hyp_lep) continue;
      if (fabs(tas::mus_p4().at(midx).eta()) > 2.4) continue;
      if (tas::mus_p4().at(midx).pt() < 5.0) continue;
      if (!isGoodVetoMuon(midx)) continue;

      for (unsigned int vidx = 0; vidx < mu_idx.size(); vidx++) {
          if (tas::mus_charge().at(midx) * tas::mus_charge().at(mu_idx.at(vidx)) > 0) continue;
          LorentzVector gamma_p4 = tas::mus_p4().at(midx) + tas::mus_p4().at(mu_idx.at(vidx));
          float gammacandmass = sqrt(fabs(gamma_p4.mass2()));
          if (gammacandmass < 12.0) return true;
      }
    }
  }

  return false;
}

bool makesExtraZ(int iHyp){

  std::vector<unsigned int> ele_idx;
  std::vector<unsigned int> mu_idx;

  int lt_id           = tas::hyp_lt_id().at(iHyp);
  int ll_id           = tas::hyp_ll_id().at(iHyp);
  unsigned int lt_idx = tas::hyp_lt_index().at(iHyp);
  unsigned int ll_idx = tas::hyp_ll_index().at(iHyp);

  (abs(lt_id) == 11) ? ele_idx.push_back(lt_idx) : mu_idx.push_back(lt_idx);
  (abs(ll_id) == 11) ? ele_idx.push_back(ll_idx) : mu_idx.push_back(ll_idx);

  if (ele_idx.size() + mu_idx.size() != 2) {
    std::cout << "ERROR: don't have 2 leptons in hypothesis!!!  Exiting" << std::endl;
    return false;
  }
      
  if (ele_idx.size() > 0) {
    for (unsigned int eidx = 0; eidx < tas::els_p4().size(); eidx++) {

      bool is_hyp_lep = false;
      for (unsigned int vidx = 0; vidx < ele_idx.size(); vidx++) {
        if (eidx == ele_idx.at(vidx)) is_hyp_lep = true;                
      }
      if (is_hyp_lep) continue;
      if (fabs(tas::els_p4().at(eidx).eta()) > 2.4) continue;
      if (tas::els_p4().at(eidx).pt() < 10) continue;

      if (!isGoodVetoElectron(eidx)) continue;

      for (unsigned int vidx = 0; vidx < ele_idx.size(); vidx++) {
        if (tas::els_charge().at(eidx) * tas::els_charge().at(ele_idx.at(vidx)) > 0) continue;
        LorentzVector zp4 = tas::els_p4().at(eidx) + tas::els_p4().at(ele_idx.at(vidx));
        float zcandmass = sqrt(fabs(zp4.mass2()));
        if (fabs(zcandmass-91.) < 15.) return true;
      }
    }
  }

  if (mu_idx.size() > 0) {
    for (unsigned int midx = 0; midx < tas::mus_p4().size(); midx++) {

      bool is_hyp_lep = false;
      for (unsigned int vidx = 0; vidx < mu_idx.size(); vidx++) {
        if (midx == mu_idx.at(vidx)) is_hyp_lep = true;                
      }
      if (is_hyp_lep) continue;
      if (fabs(tas::mus_p4().at(midx).eta()) > 2.4) continue;
      if (tas::mus_p4().at(midx).pt() < 10.) continue;

      if (!isGoodVetoMuon(midx)) continue;

      for (unsigned int vidx = 0; vidx < mu_idx.size(); vidx++) {
        if (tas::mus_charge().at(midx) * tas::mus_charge().at(mu_idx.at(vidx)) > 0) continue;
        LorentzVector zp4 = tas::mus_p4().at(midx) + tas::mus_p4().at(mu_idx.at(vidx));
        float zcandmass = sqrt(fabs(zp4.mass2()));
        if (fabs(zcandmass-91.) < 15.) return true;
      }
    }
  }

  return false;
}

bool isLooseIsolatedLepton(int id, int idx){
  if (abs(id) == 11) return eleRelIso03(idx, SS) < 0.5;
  if (abs(id) == 13) return muRelIso03(idx, SS) < 0.5;
  return false;
}
bool isIsolatedLepton(int id, int idx){
  if (abs(id) == 11) return eleRelIso03(idx, SS) < 0.1;
  if (abs(id) == 13) return muRelIso03(idx, SS) < 0.1;
  return false;
}
bool isLooseMiniIsolatedLepton(int id, int idx){
  if (abs(id) == 11) {
    if (getPtRel(id, idx, true)>6.) return elMiniRelIso(idx, 0.1, true) < 0.5;
    return eleRelIso03(idx, SS) < 0.5;
  }
  if (abs(id) == 13) {
    if (getPtRel(id, idx, true)>6.) return muMiniRelIso(idx, 0.1, true) < 0.5;
    return muRelIso03(idx, SS) < 0.5;
  }
  return false;
}
bool isMiniIsolatedLepton(int id, int idx){
  if (abs(id) == 11) {
    if (getPtRel(id, idx, true)>6.) return elMiniRelIso(idx, 0.1, true) < 0.05;
    return eleRelIso03(idx, SS) < 0.1;
  }
  if (abs(id) == 13) {
    if (getPtRel(id, idx, true)>6.) return muMiniRelIso(idx, 0.1, true) < 0.05;
    return muRelIso03(idx, SS) < 0.1;
  }
  return false;
}

bool isGoodLepton(int id, int idx, IsolationMethods isoCase){
  if (isoCase == PtRel) return isGoodLeptonIsoOrPtRel(id,idx);
  else if (isoCase == MiniIso) return isGoodLeptonMiniIso(id,idx); 
  else return isGoodLeptonIso(id,idx);
}

bool isGoodLeptonNoIso(int id, int idx){
  if (abs(id) == 11) return isGoodElectronNoIso(idx);
  else if (abs(id) == 13) return isGoodMuonNoIso(idx);
  return false;
}

bool isGoodLeptonIso(int id, int idx){
  if (isGoodLeptonNoIso(id,idx)==0) return false;
  if (isIsolatedLepton(id,idx)==0) return false;
  return true;
}

bool isGoodLeptonMiniIso(int id, int idx){
  if (isGoodLeptonNoIso(id,idx)==0) return false;
  if (isMiniIsolatedLepton(id,idx)==0) return false;
  return true;
}

bool isGoodLeptonIsoOrPtRel(int id, int idx){
  if (isGoodLeptonNoIso(id,idx)==0) return false;
  if (isIsolatedLepton(id,idx)==0 && passPtRel(id,idx,ptRelCut,true)==0) return false;
  return true;
}

bool isDenominatorLepton(int id, int idx, IsolationMethods isoCase){
  if (isoCase == PtRel) return isDenominatorLeptonIsoOrPtRel(id,idx);
  else if (isoCase == MiniIso) return isDenominatorLeptonMiniIso(id,idx);
  else return isDenominatorLeptonIso(id,idx);
}

bool isDenominatorLeptonNoIso(int id, int idx){
  if (abs(id) == 11) return isFakableElectronNoIso(idx);
  else if (abs(id) == 13) return isFakableMuonNoIso(idx);
  else return false;
}

bool isDenominatorLeptonIso(int id, int idx){
  if (isDenominatorLeptonNoIso(id,idx)==0) return false;
  if (isLooseIsolatedLepton(id,idx)==0) return false;
  return true;
}

bool isDenominatorLeptonMiniIso(int id, int idx){
  if (isDenominatorLeptonNoIso(id,idx)==0) return false;
  if (isLooseMiniIsolatedLepton(id,idx)==0) return false;
  return true;
}

bool isDenominatorLeptonIsoOrPtRel(int id, int idx){
  if (isDenominatorLeptonNoIso(id,idx)==0) return false;
  if (isLooseIsolatedLepton(id,idx)==0 && passPtRel(id,idx,ptRelCutLoose,true)==0) return false;
  return true;
}

bool isVetoLepton(int id, int idx, IsolationMethods isoCase){
  if (isoCase == PtRel) return isVetoLeptonIsoOrPtRel(id,idx);
  else return isVetoLeptonIso(id,idx);
}

bool isVetoLeptonNoIso(int id, int idx){
  if (abs(id) == 11) return isGoodVetoElectronNoIso(idx);
  else if (abs(id) == 13) return isGoodVetoMuonNoIso(idx);
  return false;
}

bool isVetoLeptonIso(int id, int idx){
  if (isVetoLeptonNoIso(id,idx)==0) return false;
  if (isLooseIsolatedLepton(id,idx)==0) return false;
  return true;
}

bool isVetoLeptonIsoOrPtRel(int id, int idx){
  if (isVetoLeptonNoIso(id,idx)==0) return false;
  if (isLooseIsolatedLepton(id,idx)==0 && passPtRel(id,idx,ptRelCut,true)==0) return false;
  return true;
}

bool passPtRel(int id, int idx, float cut, bool subtractLep) {
  return getPtRel(id, idx, subtractLep) > cut;
}

float getPtRel(int id, int idx, bool subtractLep) {
  vector<LorentzVector> jetp4s;
  for (unsigned int pfjidx=0;pfjidx<pfjets_p4().size();++pfjidx) {
    Jet jet(pfjidx);
    if (fabs(jet.eta())>2.4) continue;
    if (isLoosePFJet(pfjidx)==false) continue;
    jetp4s.push_back(jet.p4());
  }
  Lep lep = Lep(id,idx);
  return ptRel(lep.p4(), jetp4s, subtractLep);
}

bool hypsFromFirstGoodVertex(size_t hypIdx, float dz_cut){

  int lt_idx = hyp_lt_index()[hypIdx];
  int ll_idx = hyp_ll_index()[hypIdx];

  int lt_id = hyp_lt_id()[hypIdx];
  int ll_id = hyp_ll_id()[hypIdx];

  float lt_dz = abs(lt_id) == 11 ? tas::els_dzPV().at(lt_idx) : tas::mus_dzPV().at(lt_idx);
  float ll_dz = abs(ll_id) == 11 ? tas::els_dzPV().at(ll_idx) : tas::mus_dzPV().at(ll_idx);

  if (fabs(lt_dz) < dz_cut && fabs(ll_dz) < dz_cut) return true;    
  return false;
}

unsigned int analysisCategory(float lep1pt, float lep2pt) {
  unsigned int result = 0;
  if (lep1pt>ptCutHigh && lep2pt>ptCutHigh) {
    result |= 1<<HighHigh;
  } else if (lep1pt>ptCutHigh && lep2pt>ptCutLow) {
    result |= 1<<HighLow;
  } else if (lep1pt>ptCutLow && lep2pt>ptCutLow) {
    result |= 1<<LowLow;
  }
  return result;
}

void passesBaselineCuts(int njets, int nbtag, float met, float ht, unsigned int& analysisBitMask) {
  if (analysisBitMask & 1<<HighHigh) {
    if (!(ht>80 && njets>=2 && (met>30 || ht>500)))  analysisBitMask &= ~(1<<HighHigh);
  } 
  //if (!(ht>250 && njets>=2 && (met>30 || ht>500))) {
  if (!(ht>80 && njets>=2 && (met>30 || ht>500))) {//fixme
    analysisBitMask &= ~(1<<HighLow);
    analysisBitMask &= ~(1<<LowLow);
  }
}

int baselineRegion(int nbtag) {
  if (nbtag==0) return 0;
  else if (nbtag==1) return 10;
  else if (nbtag==2) return 20;
  else return 30;
}

void passesSignalRegionCuts(float ht, float met, unsigned int& analysisBitMask) {
  if (met<50.) {
    analysisBitMask &= ~(1<<HighHigh);
    analysisBitMask &= ~(1<<HighLow);
    analysisBitMask &= ~(1<<LowLow);
  }
  if (analysisBitMask & 1<<HighHigh) {
    if (ht<200.)  analysisBitMask &= ~(1<<HighHigh);
  } 
  if (ht<200.) {//fixme
    analysisBitMask &= ~(1<<HighLow);
    analysisBitMask &= ~(1<<LowLow);
  }
}

//this assumes that the event has already passed all selections (including min ht and met)
int signalRegion(int njets, int nbtag, float met, float ht, int njetscut, float metcut, float htcut) {
  int result = 1;
  if (nbtag==1) result+=10;
  else if (nbtag==2) result+=20;
  else if (nbtag>=3) result+=30;
  if (met>metcut) result+=4;
  if (njets>=njetscut) result+=2;
  if (ht>htcut) result+=1;
  return result;
}

float computeLD(DilepHyp hyp, vector<Jet> alljets, float met, float minmt) {
  //fixme: should variables be truncated?
  int njets25 = 0;
  float ht25 = 0;
  float htratio25 = 0;
  for (unsigned int j=0;j<alljets.size();j++) {
    float jetpt = alljets[j].pt();
    if (jetpt<25) continue;
    njets25++;
    ht25+=jetpt;
    if (fabs(alljets[j].eta())<1.2) htratio25+=jetpt;
  }
  htratio25/=ht25;
  ht25+=(hyp.leadLep().pt()+hyp.traiLep().pt());
  float maxlepeta = std::max(fabs(hyp.leadLep().eta()),fabs(hyp.traiLep().eta()));
  if (hyp.leadLep().pt()>ptCutHigh) {
    return 0.147*met/100. + 0.178*ht25/1000. + 0.045*minmt/100. + 0.036*njets25 - 0.105*maxlepeta + 0.196*htratio25;
  } else {
    return 0.099*met/100. + 0.80*ht25/1000. + 0.004*njets25 - 0.046*maxlepeta + 0.094*htratio25 - 0.5;
  }
}

bool isGoodVetoElectronNoIso(unsigned int elidx){
  if (els_p4().at(elidx).pt() < 7.) return false;
  if (!electronID(elidx, SS_veto_noiso_v2)) return false;
  return true;
}
bool isGoodVetoElectron(unsigned int elidx){
  if (els_p4().at(elidx).pt() < 7.) return false;
  if (!electronID(elidx, SS_veto_v2)) return false;
  return true;
}
bool isFakableElectronNoIso(unsigned int elidx){
  if (els_p4().at(elidx).pt() < 10.) return false;
  if (!electronID(elidx, SS_fo_noiso_v2)) return false;
  return true;
}
bool isFakableElectron(unsigned int elidx){
  if (els_p4().at(elidx).pt() < 10.) return false;
  if (!electronID(elidx, SS_fo_v2)) return false;
  return true;
}
bool isGoodElectronNoIso(unsigned int elidx){
  if (els_p4().at(elidx).pt() < 10.) return false;
  if (!electronID(elidx, SS_medium_noiso_v2)) return false;
  return true;
}
bool isGoodElectron(unsigned int elidx){
  if (els_p4().at(elidx).pt() < 10.) return false;
  if (!electronID(elidx, SS_medium_v2)) return false;
  return true;
}

bool isGoodVetoMuonNoIso(unsigned int muidx){
  if (mus_p4().at(muidx).pt() < 5.)         return false;
  if (!muonID(muidx, SS_veto_noiso_v2))     return false;
  return true;
}
bool isGoodVetoMuon(unsigned int muidx){
  if (mus_p4().at(muidx).pt() < 5.)         return false;
  if (!muonID(muidx, SS_veto_v2))           return false;
  return true;
}
bool isFakableMuonNoIso(unsigned int muidx){
  if (mus_p4().at(muidx).pt() < 10.)        return false;
  if (!muonID(muidx, SS_fo_noiso_v2))       return false;
  return true;
}
bool isFakableMuon(unsigned int muidx){
  if (mus_p4().at(muidx).pt() < 10.)        return false;
  if (!muonID(muidx, SS_fo_v2))             return false;
  return true;
}
bool isGoodMuonNoIso(unsigned int muidx){
  if (mus_p4().at(muidx).pt() < 10.)        return false;
  if (!muonID(muidx, SS_tight_noiso_v2))    return false;
  return true;
}
bool isGoodMuon(unsigned int muidx){
  if (mus_p4().at(muidx).pt() < 10.)        return false;
  if (!muonID(muidx, SS_tight_v2))          return false;
  return true;
}

std::vector<Lep> getBestSSLeps(std::vector<Lep> leps) {
  vector<Lep> hypleps;
  //select best hyp in case >3 good leps
  if (leps.size()>2) {
    vector<Lep> lepsp, lepsn;
    for (unsigned int gl=0;gl<leps.size();++gl) {
      if (leps[gl].pdgId()>0) lepsn.push_back(leps[gl]);
      else lepsp.push_back(leps[gl]);
    }
    //sort leps by muon and then by pt
    std::sort(lepsp.begin(),lepsp.end(),lepsort);
    std::sort(lepsn.begin(),lepsn.end(),lepsort);
    //take first SS hyp
    if (lepsp.size()<2) {
      hypleps.push_back(lepsn[0]);
      hypleps.push_back(lepsn[1]);
      for (unsigned int ln1=0;ln1<lepsn.size();++ln1) {
	for (unsigned int ln2=ln1;ln2<lepsn.size();++ln2) {
	  if ( abs(lepsn[ln1].pdgId()+lepsn[ln2].pdgId())>=abs(hypleps[0].pdgId()+hypleps[1].pdgId()) && 
	       (lepsn[ln1].p4()+lepsn[ln2].p4()).pt()>(hypleps[0].p4()+hypleps[1].p4()).pt() ) {
	    hypleps[0] = lepsn[ln1];
	    hypleps[1] = lepsn[ln2];  
	  }
	}
      }
    } else if (lepsn.size()<2) {
      hypleps.push_back(lepsp[0]);
      hypleps.push_back(lepsp[1]);
      for (unsigned int lp1=0;lp1<lepsp.size();++lp1) {
	for (unsigned int lp2=lp1;lp2<lepsp.size();++lp2) {
	  if ( abs(lepsp[lp1].pdgId()+lepsp[lp2].pdgId())>=abs(hypleps[0].pdgId()+hypleps[1].pdgId()) && 
	       (lepsp[lp1].p4()+lepsp[lp2].p4()).pt()>(hypleps[0].p4()+hypleps[1].p4()).pt() ) {
	    hypleps[0] = lepsp[lp1];
	    hypleps[1] = lepsp[lp2];  
	  }
	}
      }
    } else {
      if ( abs(lepsn[0].pdgId()+lepsn[1].pdgId())>abs(lepsp[0].pdgId()+lepsp[1].pdgId()) ) {
	hypleps.push_back(lepsn[0]);
	hypleps.push_back(lepsn[1]);
      } else if ( abs(lepsn[0].pdgId()+lepsn[1].pdgId())<abs(lepsp[0].pdgId()+lepsp[1].pdgId()) ) {
	hypleps.push_back(lepsp[0]);
	hypleps.push_back(lepsp[1]);
      } else if ( (lepsn[0].p4()+lepsn[1].p4()).pt()>(lepsp[0].p4()+lepsp[1].p4()).pt() ) {
	hypleps.push_back(lepsn[0]);
	hypleps.push_back(lepsn[1]);
      } else {
	hypleps.push_back(lepsp[0]);
	hypleps.push_back(lepsp[1]);
      }
    }
  } else if (leps.size()==2) {
    hypleps.push_back(leps[0]);
    hypleps.push_back(leps[1]);	
  }      
  return hypleps;
}


int lepMotherID(Lep lep){
  if (tas::evt_isRealData()) return 1;
  else if (isFromZ(lep.pdgId(),lep.idx()) || isFromW(lep.pdgId(),lep.idx())){
    if (sgn(lep.pdgId()) == sgn(lep.mc_id())) return 1;
    else return 2;
  }
  else if (isFromB(lep.pdgId(),lep.idx())) return -1;
  else if (isFromC(lep.pdgId(),lep.idx())) return -2;
  return 0;
}

int isGoodHyp(int iHyp, IsolationMethods isoCase, bool verbose){

  //Bunch o' variables
  float pt_ll = tas::hyp_ll_p4().at(iHyp).pt(); 
  float pt_lt = tas::hyp_lt_p4().at(iHyp).pt(); 
  float eta_ll = tas::hyp_ll_p4().at(iHyp).eta();
  float eta_lt = tas::hyp_lt_p4().at(iHyp).eta();
  int idx_ll = tas::hyp_ll_index().at(iHyp);
  int idx_lt = tas::hyp_lt_index().at(iHyp);
  int id_ll = tas::hyp_ll_id().at(iHyp);
  int id_lt = tas::hyp_lt_id().at(iHyp);
  bool isss = false;
  if (sgn(id_ll) == sgn(id_lt)) isss = true;  
  bool passed_id_numer_ll = isGoodLepton(id_ll, idx_ll, isoCase);
  bool passed_id_numer_lt = isGoodLepton(id_lt, idx_lt, isoCase);
  bool passed_id_denom_ll = isDenominatorLepton(id_ll, idx_ll, isoCase);
  bool passed_id_denom_lt = isDenominatorLepton(id_lt, idx_lt, isoCase);
  bool extraZ = makesExtraZ(iHyp);
  bool extraGammaStar = makesExtraGammaStar(iHyp);

  //Verbose info:
  if (verbose && pt_ll > ptCutLow && pt_lt > ptCutLow){
    cout << "hyp " << iHyp << " leptons: " << id_ll << " " << pt_ll << " " << id_lt << " " << pt_lt << endl;
    cout << "   isss: " << isss << endl;
    cout << "   extraZ: " << extraZ << endl;
    cout << "   extraG: " << extraGammaStar << endl;
    cout << "   invt mass: " << (tas::hyp_ll_p4().at(iHyp) + tas::hyp_lt_p4().at(iHyp)).M() << endl;
    cout << "   passes eta: " << (fabs(eta_ll) < 2.4 && fabs(eta_lt) < 2.4) << " etas are " << eta_ll << " and " << eta_lt << endl;
    cout << "   passes hypsFromFirstGoodVertex: " << hypsFromFirstGoodVertex(iHyp) << endl;
    cout << "   lepton with pT " << pt_ll << " passes id: " << passed_id_numer_ll << endl;
    cout << "   lepton with pT " << pt_lt << " passes id: " << passed_id_numer_lt << endl;
    if (abs(id_ll) == 11) cout << "   lepton with pT " << pt_ll << " passes 3chg: " << threeChargeAgree(idx_ll) << endl;
    if (abs(id_lt) == 11) cout << "   lepton with pT " << pt_lt << " passes 3chg: " << threeChargeAgree(idx_lt) << endl;
  }

  //Other Cuts
  if      (abs(id_ll) == 11 && pt_ll < 7) return 0;
  else if (abs(id_ll) == 13 && pt_ll < 5) return 0;
  if      (abs(id_lt) == 11 && pt_lt < 7) return 0;
  else if (abs(id_lt) == 13 && pt_lt < 5) return 0;
  if (fabs(eta_ll) > 2.4) return 0;
  if (fabs(eta_lt) > 2.4) return 0;

  //Other cuts
  if (extraZ) return 0;
  if (extraGammaStar) return 0;
  if ((tas::hyp_ll_p4().at(iHyp) + tas::hyp_lt_p4().at(iHyp)).M() < 8) return 0; 
  if (!hypsFromFirstGoodVertex(iHyp)) return 0;

  //Results
  if (passed_id_numer_ll == 0 && passed_id_denom_ll == 0) return 0; // 0 if ll fails denom
  if (passed_id_numer_lt == 0 && passed_id_denom_lt == 0) return 0; // 0 if lt fails denom
  else if (passed_id_numer_lt == 1 && passed_id_numer_ll == 1 && isss == 1) return 3;  // 3 if both numer pass, SS
  else if (passed_id_numer_lt == 1 && passed_id_numer_ll == 1 && isss == 0) return 4;  // 4 if both numer pass, OS
  else if (passed_id_numer_lt == 0 && passed_id_numer_ll == 0 && passed_id_denom_lt == 1 && passed_id_denom_ll == 1 && isss == true) return 1; // 1 SS, if both denom and no numer pass
  else if (isss == true) return 2; //2 SS, one numer and one denom not numer
  else return 0; //non-highpass OS
}

hyp_result_t chooseBestHyp(IsolationMethods isoCase, bool verbose){

  //List of good hyps
  vector <int> good_hyps_ss; //same sign, tight tight
  vector <int> good_hyps_sf; //same sign, single fail
  vector <int> good_hyps_df; //same sign, double fail
  vector <int> good_hyps_os; //opposite sign, tight tight
  for (unsigned int i = 0; i < tas::hyp_type().size(); i++){
    int good_hyp_result = isGoodHyp(i, isoCase, verbose);
    if (good_hyp_result == 3) good_hyps_ss.push_back(i); 
    if (good_hyp_result == 2) good_hyps_sf.push_back(i); 
    else if (good_hyp_result == 1) good_hyps_df.push_back(i); 
    else if (good_hyp_result == 4) good_hyps_os.push_back(i); 
  }

  //hyp_class_ to track SS(3), SF(2), DF(1), OS(4), or none(0)
  int hyp_class_;

  //Load good hyps in, SS then SF then DF then OS
  vector <int> good_hyps;
  if (good_hyps_ss.size() != 0){
     good_hyps = good_hyps_ss;
     hyp_class_ = 3;
  }
  else if (good_hyps_sf.size() != 0){
    good_hyps = good_hyps_sf;
    hyp_class_ = 2;
  }
  else if (good_hyps_df.size() != 0){
     good_hyps = good_hyps_df;
     hyp_class_ = 1;
  }
  else if (good_hyps_os.size() != 0){
    good_hyps = good_hyps_os;
    hyp_class_ = 4;
  }
  else hyp_class_ = 0; 

  //If no hyps or one hyps, know what to do
  int best_hyp_ = -1;
  if (good_hyps.size() == 1) best_hyp_ = good_hyps.at(0);

  //Otherwise, pick ones with more muons, then highest pT  
  if (good_hyps.size() > 1){
    best_hyp_ = good_hyps.at(0); 
    for (unsigned int i = 1; i < good_hyps.size(); i++){
      int hyp = good_hyps.at(i);
      if (tas::hyp_type().at(hyp) < tas::hyp_type().at(best_hyp_)) best_hyp_ = hyp;
      else if (tas::hyp_type().at(hyp) == tas::hyp_type().at(best_hyp_) && (tas::hyp_ll_p4().at(hyp)+tas::hyp_lt_p4().at(hyp)).pt() > (tas::hyp_ll_p4().at(best_hyp_) + tas::hyp_lt_p4().at(best_hyp_)).pt()) best_hyp_ = hyp;
    }
  }

  if (best_hyp_ < 0){
    hyp_result_t null = { -1, -1 };
    return null;
  }

  hyp_result_t temp;
  temp.best_hyp = best_hyp_;
  temp.hyp_class = hyp_class_; 
  return temp;
}

vector <particle_t> getGenPair(bool verbose){

  vector <particle_t> gen_particles;

  //First get all gen leptons 
  for (unsigned int gidx = 0; gidx < tas::genps_p4().size(); gidx++){
    if (tas::genps_status().at(gidx) != 1) continue;
    int id = tas::genps_id().at(gidx);
    if (abs(id) != 11 && abs(id) != 13 && abs(id) != 15) continue;
    float eta = tas::genps_p4().at(gidx).eta();
    if (fabs(eta) > 2.4) continue;
    int did = -1;
    int didx = -1;
    if (abs(id) == 15){  
      float dpt = -1;
      for (unsigned int didx_ = 0; didx_ < tas::genps_lepdaughter_id().at(gidx).size(); didx_++){
        int did_ = tas::genps_lepdaughter_id().at(gidx).at(didx_);
        if (abs(did_) != 11 && abs(did_) != 13) continue;
        if (fabs(tas::genps_lepdaughter_p4().at(gidx).at(didx_).eta()) > 2.4) continue;
        float dpt_ = tas::genps_lepdaughter_p4().at(gidx).at(didx_).pt();
        if (dpt_ <= dpt) continue;
        dpt = dpt_;
        didx = didx_;
        did = did_;
      }
    }
    particle_t temp;
    temp.id = abs(id) == 15 ? did : id;
    if (abs(id) == 15 && didx < 0) continue;
    temp.idx = abs(id) == 15 ? tas::genps_lepdaughter_idx().at(gidx).at(didx) : gidx;
    temp.p4 = abs(id) == 15 ? tas::genps_lepdaughter_p4().at(gidx).at(didx) : tas::genps_p4().at(gidx);
    if (temp.id != -1) gen_particles.push_back(temp);
  }
 
  if (gen_particles.size() < 2) return gen_particles;

  //Now loop over gen hyps and pick the best
  int gen_hyp_class = 5; 
  int type = 5; 
  particle_t lep1; 
  particle_t lep2;
  lep1.id = -1;
  lep2.id = -1;
  for (unsigned int idx1 = 0; idx1 < gen_particles.size(); idx1++){
    if (verbose) cout << "gen lep " << idx1 << ": " << gen_particles.at(idx1).id << " " << gen_particles.at(idx1).p4.pt() << endl;
    for (unsigned int idx2 = idx1+1; idx2 < gen_particles.size(); idx2++){
      int id1 = gen_particles.at(idx1).id;
      int id2 = gen_particles.at(idx2).id;
      int gen_hyp_class_ = 5;
      int type_ = 5;
      LorentzVector p41 = gen_particles.at(idx1).p4;
      LorentzVector p42 = gen_particles.at(idx2).p4;
      if (id1*id2 < 0) gen_hyp_class_ = 4; 
      if (id1*id2 > 0) gen_hyp_class_ = 3; 
      if (min(p41.pt(), p42.pt()) < 5) continue;
      if (max(p41.pt(), p42.pt()) < 5) continue;
      if (abs(id1) == 11 && abs(id2) == 11) type_ = 3; 
      if (abs(id1) == 13 && abs(id2) == 13) type_ = 0; 
      if ((abs(id1) == 13 && abs(id2) == 11) || (abs(id1) == 11 && abs(id2) == 13)) type_ = 1; 
      if (gen_hyp_class_ < gen_hyp_class){
        gen_hyp_class = gen_hyp_class_;
        type = type_;
        lep1 = gen_particles.at(idx1);
        lep2 = gen_particles.at(idx2);
      }
      else if (gen_hyp_class_ == gen_hyp_class && type_ < type){
        gen_hyp_class = gen_hyp_class_;
        type = type_;
        lep1 = gen_particles.at(idx1);
        lep2 = gen_particles.at(idx2);
      } 
      else if (gen_hyp_class_ == gen_hyp_class && type_ == type && p41.pt()+p42.pt() > lep1.p4.pt()+lep2.p4.pt()){
        gen_hyp_class = gen_hyp_class_;
        type = type_;
        lep1 = gen_particles.at(idx1);
        lep2 = gen_particles.at(idx2);
      }
    }
  }
  
  //Return leptons you found
  vector <particle_t> selected_gen_leptons;
  if (lep1.p4.pt() > lep2.p4.pt()){
    selected_gen_leptons.push_back(lep1);
    selected_gen_leptons.push_back(lep2);
  }
  else{ 
    selected_gen_leptons.push_back(lep2);
    selected_gen_leptons.push_back(lep1);
  }

  return selected_gen_leptons;

}

pair<particle_t, int> getThirdLepton(int hyp){

  //Selected Lepton Information
  int ll_id = tas::hyp_ll_id().at(hyp);
  int lt_id = tas::hyp_lt_id().at(hyp);
  unsigned int ll_idx = tas::hyp_ll_index().at(hyp);
  unsigned int lt_idx = tas::hyp_lt_index().at(hyp);

  //Store best lepton
  int lep3_id_ = -1;
  int lep3_idx_ = -1;
  int quality = 0;
  LorentzVector lep3_p4_; 

  //Electron Loop 
  for (unsigned int i = 0; i < tas::els_p4().size(); i++){

    //Remove electrons already selected
    if (abs(ll_id) == 11 && ll_idx == i) continue; 
    if (abs(lt_id) == 11 && lt_idx == i) continue; 

    //Remove electrons that fail kinematically
    if (tas::els_p4().at(i).pt() < 20) continue;
    if (fabs(tas::els_p4().at(i).eta()) > 2.4) continue;

    //Remove electrons that fail loosest ID, determine tighter IDs
    int quality_ = 0;
    if (!isGoodVetoElectron(i)) continue;
    if (isFakableElectron(i)) quality_ = 1;
    if (isGoodElectron(i)) quality_ = 2;

    //Choose the highest-quality, highest-pT electron 
    if (quality_ > quality || (quality_ == quality && tas::els_p4().at(i).pt() > lep3_p4_.pt())){
       quality = quality_;
       lep3_p4_ = tas::els_p4().at(i); 
       lep3_id_ = -11*tas::els_charge().at(i);
    } 
  }
  
  //Muon Loop
  for (unsigned int i = 0; i < tas::mus_p4().size(); i++){

    //Remove electrons already selected
    if (abs(ll_id) == 13 && ll_idx == i) continue; 
    if (abs(lt_id) == 13 && lt_idx == i) continue; 
   
    //Remove electrons that fail kinematically
    if (tas::mus_p4().at(i).pt() < 20) continue;
    if (fabs(tas::mus_p4().at(i).eta()) > 2.4) continue;

    //Remove muons that fail ID
    int quality_ = 0; 
    if (!isGoodVetoMuon(i)) continue;
    if (isFakableMuon(i)) quality_ = 1;
    if (isGoodMuon(i)) quality_ = 2;

    //Choose the highest-quality, highest-pT electron 
    if (quality_ > quality || (quality_ == quality && tas::mus_p4().at(i).pt() > lep3_p4_.pt())){
       quality = quality_;
       lep3_p4_ = tas::mus_p4().at(i); 
       lep3_id_ = -11*tas::mus_charge().at(i);
    } 

  }//Muon loop

  particle_t result;
  result.id = lep3_id_;
  result.p4 = lep3_p4_;
  result.idx = lep3_idx_;

  return pair<particle_t, int>(result, quality);

}

bool ptsort (int i,int j) { return (genps_p4()[i].pt()>genps_p4()[j].pt()); }

bool lepsort (Lep i,Lep j) { 
  if ( abs(i.pdgId())==abs(j.pdgId()) ) return ( i.pt()>j.pt() ); //sort by pt if same flavor
  else return ( abs(i.pdgId())>abs(j.pdgId()) ); //prefer muons over electrons, but check that mu have pt>25//fixme, need to sync // && i.pt()>ptCutHigh
}

bool jetptsort (Jet i,Jet j) { return (i.pt()>j.pt()); }
