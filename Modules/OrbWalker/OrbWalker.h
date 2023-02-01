//
// Created by XaDanX on 1/28/2023.
//

#ifndef ASYLLUM_ORBWALKER_H
#define ASYLLUM_ORBWALKER_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"

class OrbWalker : public Module {
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("OrbWalker");};
};


#endif //ASYLLUM_ORBWALKER_H
