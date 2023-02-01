//
// Created by XaDanX on 1/30/2023.
//

#ifndef ASYLLUM_EVADE_H
#define ASYLLUM_EVADE_H
#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"

class Evade : public Module {
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("Evade");};
};



#endif //ASYLLUM_EVADE_H
