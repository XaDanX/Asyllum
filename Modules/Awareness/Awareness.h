//
// Created by XaDanX on 12/10/2022.
//

#ifndef ASYLLUM_AWARENESS_H
#define ASYLLUM_AWARENESS_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/Protection/XorStr.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../../Asyllum/Core/Objects/Hero/SpellBook/SpellSlot.h"
#include "SpellTracker/SpellTracker.h"
#include "WardTracker/WardTracker.h"

class Awareness : public Module {
private:
    std::unique_ptr<SpellTracker> spellTracker = std::make_unique<SpellTracker>();
    std::unique_ptr<WardTracker> wardTracker = std::make_unique<WardTracker>();

    bool traceLines = true;
    bool playerRanges = true;
    bool enemyRanges = true;
    bool lastSeen = true;
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("Awareness");};
};


#endif //ASYLLUM_AWARENESS_H
