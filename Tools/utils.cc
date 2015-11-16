#include "utils.h"

#include "TMath.h"

float DeltaR(float eta1, float eta2, float phi1, float phi2){
  float dEta = eta1 - eta2;
  float dPhi = DeltaPhi(phi1, phi2);
  return TMath::Sqrt(dEta*dEta + dPhi*dPhi);
}

float DeltaR(LorentzVector v1, LorentzVector v2){
  return DeltaR(v1.eta(), v1.phi(), v2.eta(), v2.phi()); 
}

float DeltaPhi(float phi1, float phi2){
  float dPhi = phi1 - phi2;
  while (dPhi  >  TMath::Pi()) dPhi -= 2*TMath::Pi();
  while (dPhi <= -TMath::Pi()) dPhi += 2*TMath::Pi();
  return fabs(dPhi);
}

float MT(float pt1, float phi1, float pt2, float phi2){
  return sqrt( 2 * pt1 * pt2 * ( 1 - cos( phi1 - phi2 ) ) );
}
