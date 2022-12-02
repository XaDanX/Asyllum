//
// Created by XaDanX on 12/2/2022.
//

#ifndef ASYLLUM_OBJECTEXPLORER_H
#define ASYLLUM_OBJECTEXPLORER_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/Protection/XorStr.h"

class ObjectExplorer : public Module {
public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("ObjectExplorer");};
};


#endif //ASYLLUM_OBJECTEXPLORER_H
