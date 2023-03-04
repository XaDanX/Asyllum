//
// Created by XaDanX on 2/3/2023.
//

#ifndef ASYLLUM_GAMEKEYBIND_H
#define ASYLLUM_GAMEKEYBIND_H

#include <map>
#include "../../Globals/KeyCodes.h"

class GameKeybind {

public:
    static void InitFromGameConfigs();

    static HKey CastSpellQ;
    static HKey CastSpellW;
    static HKey CastSpellE;
    static HKey CastSpellR;
    static HKey CastSpellD;
    static HKey CastSpellF;

    static HKey UseItem1;
    static HKey UseItem2;
    static HKey UseItem3;
    static HKey UseItem4;
    static HKey UseItem5;
    static HKey UseItem6;
    static HKey UseItemTrinket;

    static HKey PingNormal;
    static HKey PingWarn;
    static HKey PingDanger;
    static HKey PingVision;
    static HKey PingMia;
    static HKey PingOmw;
    static HKey PingAssist;
    static HKey Recall;
    static HKey TargetChampionsOnly;

private:
    static HKey GetKeyForConfig(std::string cfg, HKey defaultKey = HKey::NO_KEY);

    static std::map<std::string, std::string> gameKeyCfgs;
    static std::map<std::string, HKey> keyConvert;
};


#endif //ASYLLUM_GAMEKEYBIND_H
