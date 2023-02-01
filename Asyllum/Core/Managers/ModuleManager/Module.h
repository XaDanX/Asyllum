//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_MODULE_H
#define ASYLLUM_MODULE_H

#include <string>
#include "../../Controller/Controller.h"

class Module {
public:
    InputController input;
public:
    virtual void OnTick() = 0;

    virtual void OnLoad() = 0;

    virtual void OnGui() = 0;

    virtual std::string ModuleType() = 0;

    virtual std::string GetName() = 0;
};
#endif //ASYLLUM_MODULE_H
