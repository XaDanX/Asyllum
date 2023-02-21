//
// Created by XaDanX on 2/2/2023.
//

#ifndef ASYLLUM_SPELLTRACKER_H
#define ASYLLUM_SPELLTRACKER_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"

class SpellTracker : public Module {
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("SpellTracker");};
};




#endif //ASYLLUM_SPELLTRACKER_H
