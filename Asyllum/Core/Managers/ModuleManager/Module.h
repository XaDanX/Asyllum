//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_MODULE_H
#define ASYLLUM_MODULE_H

#include <string>
#include <utility>
#include "../../Controller/Controller.h"
#include "../../Objects/ObjectBase.h"

/*class Module {
public:
    InputController input;
public:
    virtual void OnTick() = 0;

    virtual void OnLoad() = 0;

    virtual void OnGui() = 0;

    virtual std::string ModuleType() = 0;

    virtual std::string GetName() = 0;
};*/

enum ModuleType {
    CHAMPION_SCRIPT = 0,
    UTILITY_SCRIPT = 1,
};


class Module {
public:
    bool enabled = true;
    InputController input;
    std::string name;
    ModuleType type;
    HashName champion;

    Module(std::string _name, ModuleType _type, HashName _champion = HashName::UnknownHash) {
        this->name = std::move(_name);
        this->type = _type;
        this->champion = _champion;
    }

public:
    virtual void OnTick() = 0;

    virtual void OnLoad() = 0;

    virtual void OnGui() = 0;

    virtual void OnConfigLoad() = 0;

    virtual void OnConfigSave() = 0;
};

#endif //ASYLLUM_MODULE_H
