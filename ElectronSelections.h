#ifndef ELECTRONSELECTIONS_H
#define ELECTRONSELECTIONS_H
#include "CMS3.h"
#include "TString.h"
#include "Base.h"

//POG IDs
bool isVetoElectronPOG(unsigned int elIdx);
bool isLooseElectronPOG(unsigned int elIdx);
bool isMediumElectronPOG(unsigned int elIdx);
bool isTightElectronPOG(unsigned int elIdx);

//Main Electron ID function
bool electronID(unsigned int elIdx, id_level_t id_level);

//POG IDs for phys14
bool isVetoElectronPOGphys14(unsigned int elIdx);
bool isLooseElectronPOGphys14(unsigned int elIdx);
bool isMediumElectronPOGphys14(unsigned int elIdx);
bool isTightElectronPOGphys14(unsigned int elIdx);

//POG IDs for phys14 with no Iso requirement
bool isVetoElectronPOGphys14noIso(unsigned int elIdx);
bool isLooseElectronPOGphys14noIso(unsigned int elIdx);
bool isMediumElectronPOGphys14noIso(unsigned int elIdx);
bool isTightElectronPOGphys14noIso(unsigned int elIdx);

//Isolation
float eleRelIso03(unsigned int elIdx, analysis_t analysis);
float eleRelIso03DB(unsigned int elIdx);
float eleRelIso03EA(unsigned int elIdx);
float elRelIsoCustomCone(unsigned int idx, float dr, float deltaZCut=0.1, bool useVetoCones=false);
float elRelIsoCustomConeDB(unsigned int idx, float dr, float deltaZCut=0.1, bool useVetoCones=false);
float elMiniRelIso(unsigned int idx, float deltaZCut=0.1, bool useVetoCones=false, bool useDBcor=false);

//Tightest ID passed by electron
int eleTightID(unsigned int elIdx, analysis_t analysis);

//Three charge agree
bool threeChargeAgree(unsigned int elIdx); 
int tightChargeEle(unsigned int elIdx); 

#endif
