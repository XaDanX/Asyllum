//
// Created by XaDanX on 12/1/2022.
//

#include "ModuleManager.h"
#include "../../Locator/Locator.h"
#include "../../../Protection/XorStr.h"
#include "../../../../Modules/OrbWalker/OrbWalker.h"
#include "../../../../Modules/Evade/Evade.h"

void ModuleManager::RegisterModule(Module *module) {

    if (module->type != ModuleType::UTILITY_SCRIPT) {
        if (locator->GetObjectManager()->GetLocalPlayer()->characterData->hash == module->champion) {
            this->moduleList.emplace_back(module);
        } else {
            delete module;
        }
    } else {
        this->moduleList.emplace_back(module);
    }
}

void ModuleManager::RegisterModules() {
    /*
        Append all modules here
    */
    RegisterModule(new OrbWalker(XorStr("OrbWalker"), ModuleType::UTILITY_SCRIPT, HashName::UnknownHash));
    RegisterModule(new Evade(XorStr("Evade"), ModuleType::UTILITY_SCRIPT, HashName::UnknownHash));
}

void ModuleManager::Initialize() {
    this->RegisterModules();
    for (auto &currentModule: this->moduleList) {
        locator->GetConsole()->Print(XorStr("[MODULE MANAGER] Loaded module: %s!").c_str(),
                                     currentModule->name.c_str());
        currentModule->OnLoad();
    }
}


void ModuleManager::UpdateModules() {
    /*__try{
        for (auto &currentModule : this->moduleList) {
            currentModule->OnTick();
            currentModule->input.UpdateIssuedOperations();
        }
    } __except (1) {
        locator->GetConsole()->Print(XorStr("[MODULE MANAGER] Exception occurred in one of modules!").c_str());
    }*/
    for (auto &currentModule: this->moduleList) {
        try {
            currentModule->OnTick();
            currentModule->input.UpdateIssuedOperations();
        } catch (const std::exception &e) {
            locator->GetConsole()->Print(
                    ("[MODULE MANAGER] Exception occurred in module " + currentModule->name + ": " + e.what()).c_str());
        }
    }


}

void ModuleManager::OnExit() {
    for (auto &currentModule: this->moduleList) {
        //currentModule->OnExit();
    }
}
