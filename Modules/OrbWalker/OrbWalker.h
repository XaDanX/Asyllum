//
// Created by XaDanX on 2/22/2023.
//

#ifndef ASYLLUM_ORBWALKER_H
#define ASYLLUM_ORBWALKER_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/imgui/imgui.h"



class OrbWalker : public Module {
public:
    OrbWalker(std::string _name, ModuleType _type, HashName _champion) : Module(_name, _type, _champion) {
        this->name = std::move(_name);
        this->type = _type;
        this->champion = _champion;
    }
    void OnTick();
    void OnLoad();
    void OnGui(){};
    void OnConfigLoad(){};
    void OnConfigSave(){};

public: // config
    bool enabled = true;
    HKey hotKey = HKey::N;
};



#endif //ASYLLUM_ORBWALKER_H
