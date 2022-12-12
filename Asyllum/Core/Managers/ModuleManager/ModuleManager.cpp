//
// Created by XaDanX on 12/1/2022.
//

#include "ModuleManager.h"
#include "../../Locator/Locator.h"
#include "../../../Protection/XorStr.h"
#include "../../../../Modules/ObjectExplorer/ObjectExplorer.h"
#include "../../../../Modules/SpellTracker/SpellTracker.h"

void ModuleManager::RegisterModule(Module* module) {

    if (module->ModuleType() != XorStr("utility").c_str()) {
        if (locator->GetObjectManager()->GetLocalPlayer()->name.str() == module->ModuleType()) {
            this->moduleList.emplace_back(module);
        }
        else {
            delete module;
        }
    }
    else {
        this->moduleList.emplace_back(module);
    }
}

void ModuleManager::RegisterModules() {
    /*
        Append all modules here
    */
    this->RegisterModule(new SpellTracker());
    this->RegisterModule(new ObjectExplorer());
}

void ModuleManager::Initialize() {
    this->RegisterModules();
    for (auto& currentModule : this->moduleList) {
        currentModule->OnLoad();
    }
}

void ModuleManager::UpdateModules() {
    for (auto &currentModule : this->moduleList) {
        currentModule->OnTick();
    }
}

void ModuleManager::UpdateModulesGui() {
    for (auto& currentModule : this->moduleList) {
        currentModule->OnGui();
    }
}

void ModuleManager::OnExit() {
    for (auto& currentModule : this->moduleList) {
        //currentModule->OnExit();
    }
}