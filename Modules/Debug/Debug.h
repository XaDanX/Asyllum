//
// Created by XaDanX on 4/27/2023.
//

#ifndef ASYLLUM_DEBUG_H
#define ASYLLUM_DEBUG_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../../Asyllum/Core/Locator/Locator.h"


class Debug : public Module {
public:
    Debug(std::string _name, ModuleType _type, HashName _champion) : Module(_name, _type, _champion) {
        this->name = std::move(_name);
        this->type = _type;
        this->champion = _champion;
    }

    void OnTick();

    void OnLoad();

    void OnGui();

    void OnConfigLoad() {};

    void OnConfigSave() {};
};


#endif //ASYLLUM_DEBUG_H
