#ifndef ELECTRONSELECTIONS_H
#define ELECTRONSELECTIONS_H
#include "CMS3.h"
#include "TString.h"
#include "Base.h"
#include "TMVA/Reader.h"
#include "TMVA/Config.h"

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
//May 7 Updated Ids
bool isVetoElectronPOGphys14_v2(unsigned int elIdx);
bool isLooseElectronPOGphys14_v2(unsigned int elIdx);
bool isMediumElectronPOGphys14_v2(unsigned int elIdx);
bool isTightElectronPOGphys14_v2(unsigned int elIdx);
//Aug 17 Updated Ids with no Iso requirement
bool isVetoElectronPOGspring15_v1(unsigned int elIdx);
bool isLooseElectronPOGspring15_v1(unsigned int elIdx);
bool isMediumElectronPOGspring15_v1(unsigned int elIdx);
bool isTightElectronPOGspring15_v1(unsigned int elIdx);

//POG IDs for phys14 with no Iso requirement
bool isVetoElectronPOGphys14noIso(unsigned int elIdx);
bool isLooseElectronPOGphys14noIso(unsigned int elIdx);
bool isMediumElectronPOGphys14noIso(unsigned int elIdx);
bool isTightElectronPOGphys14noIso(unsigned int elIdx);
//May 7 Updated Ids with no Iso requirement
bool isVetoElectronPOGphys14noIso_v2(unsigned int elIdx);
bool isLooseElectronPOGphys14noIso_v2(unsigned int elIdx);
bool isMediumElectronPOGphys14noIso_v2(unsigned int elIdx);
bool isTightElectronPOGphys14noIso_v2(unsigned int elIdx);
//Aug 17 Updated Ids with no Iso requirement
bool isVetoElectronPOGspring15noIso_v1(unsigned int elIdx);
bool isLooseElectronPOGspring15noIso_v1(unsigned int elIdx);
bool isMediumElectronPOGspring15noIso_v1(unsigned int elIdx);
bool isTightElectronPOGspring15noIso_v1(unsigned int elIdx);

//Tightest ID passed by electron
int eleTightID(unsigned int elIdx, analysis_t analysis, int version = 1);

//Three charge agree
bool threeChargeAgree(unsigned int elIdx); 
int tightChargeEle(unsigned int elIdx); 

//Electron MVA ID
class readMVA {
  public:
    void InitMVA(string path);
    float MVA(unsigned int index); 
    bool passesElectronMVAid(unsigned int index, id_level_t id_level);
    void DumpValues();

  private:
    //the readers
    vector <TMVA::Reader*> readers;
  
    //the list of BDT files
    vector <string> files;
    
    //the variables
    float ele_kfhits_;         
    float ele_oldsigmaietaieta_;
    float ele_oldsigmaiphiiphi_;
    float ele_oldcircularity_; 
    float ele_oldr9_;          
    float ele_scletawidth_;    
    float ele_sclphiwidth_;    
    float ele_he_;             
    float ele_kfchi2_;         
    float ele_chi2_hits_;      
    float ele_fbrem_;          
    float ele_ep_;             
    float ele_eelepout_;       
    float ele_IoEmIop_;        
    float ele_deltaetain_;     
    float ele_deltaphiin_;     
    float ele_deltaetaseed_;   
    float ele_psEoverEraw_;    
    float ele_pT_;             
    float ele_isbarrel_;       
    float ele_isendcap_;       
    float scl_eta_;            

};

void createAndInitMVA(std::string pathToCORE);
float getMVAoutput(unsigned int index = 0);

struct elIDcache {
public:
  void  setCacheValues(int idx, float mva, float miniiso, float ptratio, float ptrel) {
    idx_ = idx;
    mva_ = mva;
    miniiso_ = miniiso;
    ptratio_ = ptratio;
    ptrel_ = ptrel;
  }
  //make sure it was set for this electron before returning
  float getMVA(int idx) {assert(idx==idx_); return mva_;}
  float getMiniiso(int idx) {assert(idx==idx_); return miniiso_;}
  float getPtratio(int idx) {assert(idx==idx_); return ptratio_;}
  float getPtrel(int idx) {assert(idx==idx_); return ptrel_;}
private:
  int idx_;
  float mva_;
  float miniiso_;
  float ptratio_;
  float ptrel_;
};
namespace elID {
  void setCache(int idx, float mva, float miniiso, float ptratio, float ptrel);
  void unsetCache();
}

#endif
