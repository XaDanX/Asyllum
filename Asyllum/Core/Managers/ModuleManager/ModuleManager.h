//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_MODULEMANAGER_H
#define ASYLLUM_MODULEMANAGER_H


#include <vector>
#include <memory>
#include "Module.h"

class ModuleManager {
private:
    void RegisterModules();

    int tab = -1;

public:
    std::vector<std::unique_ptr<Module>> moduleList;

    void Initialize();

    void UpdateModules();

    void OnExit();

    void RegisterModule(Module *module);
};


#endif //ASYLLUM_MODULEMANAGER_H
