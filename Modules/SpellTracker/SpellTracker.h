//
// Created by XaDanX on 12/10/2022.
//

#ifndef ASYLLUM_SPELLTRACKER_H
#define ASYLLUM_SPELLTRACKER_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/Protection/XorStr.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../../Asyllum/Core/Objects/Hero/SpellBook/SpellSlot.h"

class SpellTracker : public Module {
private:
    void DrawSpell(SpellSlot* spellSlot, ImVec2 pos);
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("SpellTracker");};
};


#endif //ASYLLUM_SPELLTRACKER_H
