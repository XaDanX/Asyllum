//
// Created by XaDanX on 12/10/2022.
//

#ifndef ASYLLUM_AWARENESS_H
#define ASYLLUM_AWARENESS_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/Protection/XorStr.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../../Asyllum/Core/Objects/Hero/SpellBook/SpellSlot.h"

class Awareness : public Module {
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("Awareness");};
};


#endif //ASYLLUM_AWARENESS_H
