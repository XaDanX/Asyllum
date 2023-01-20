//
// Created by XaDanX on 12/30/2022.
//

#ifndef ASYLLUM_ORBWALKER_H
#define ASYLLUM_ORBWALKER_H
#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/Protection/XorStr.h"


class OrbWalker : public Module {
private:
    bool enabled = false;
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("OrbWalker");};
};


#endif //ASYLLUM_ORBWALKER_H
