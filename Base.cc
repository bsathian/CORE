#include "Base.h"
#include <iostream>

analysis_t whichAnalysis(id_level_t id_level){

  switch (id_level){
    case (SS_veto_noiso_v1):
    case (SS_veto_v1):
    case (SS_fo_noiso_v1):
    case (SS_fo_v1):
    case (SS_medium_noiso_v1):
    case (SS_medium_v1):
    case (SS_tight_noiso_v1):
    case (SS_tight_v1):
      return SS;
      break;
    case (HAD_veto_v1):
    case (HAD_loose_v1):
    case (HAD_medium_v1):
    case (HAD_tight_v1):
      return HAD;
      break;
    case (STOP_veto_v1):
    case (STOP_loose_v1):
    case (STOP_medium_v1):
    case (STOP_tight_v1):
      return STOP;
      break;
    default:
      std::cout << "Warning! Not sure which analysis you're doing!" << std::endl;
      std::cout << "Update \"whichAnalysis\" in base.cc with this id_level!" << std::endl;
      return POG;
  }

}
