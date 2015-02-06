#ifndef JETSELECTIONS_H
#define JETSELECTIONS_H
#include "CMS3.h"
#include "TString.h"
#include "Base.h"

bool isLoosePFJet(unsigned int pfJetIdx);
bool isMediumPFJet(unsigned int pfJetIdx);
bool isTightPFJet(unsigned int pfJetIdx);
bool loosePileupJetId(unsigned int pfJetIdx);

bool JetIsElectron(LorentzVector pfJet, id_level_t id_level, float ptcut = 7., float deltaR = 0.4);
bool JetIsMuon(LorentzVector pfJet, id_level_t id_level, float ptcut = 5., float deltaR = 0.4);

#endif
