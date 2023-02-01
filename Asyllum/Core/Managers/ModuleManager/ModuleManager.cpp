//
// Created by XaDanX on 12/1/2022.
//

#include "ModuleManager.h"
#include "../../Locator/Locator.h"
#include "../../../Protection/XorStr.h"
#include "../../../../Modules/OrbWalker/OrbWalker.h"

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
    this->RegisterModule(new OrbWalker());

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
        currentModule->input.UpdateIssuedOperations();
    }
}

void ModuleManager::UpdateModulesGui() {
    ImGui::SetNextWindowSize({800, 900});
    ImGui::Begin(XorStr("Asyllum").c_str());
    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnOffset(1, 150);

    ImGui::BeginChild(XorStr("left").c_str());
    for (int i = 0; i < static_cast<int>(this->moduleList.size()); i++) {
        auto& module = this->moduleList.at(i);
        if (ImGui::Button(module->GetName().c_str(), ImVec2(130, 60))) {
            this->tab = i;
        }
    }
    ImGui::EndChild();

    ImGui::NextColumn();
    ImGui::BeginChild(XorStr("right").c_str(), ImVec2(0,0), true);
    for (int i = 0; i < static_cast<int>(this->moduleList.size()); i++) {
        auto& module = this->moduleList.at(i);
        if (i == this->tab) {
            module->OnGui();
        }
    }

    if (this->tab == -1) {
        ImGui::Text(XorStr("dev version.").c_str());
    }


    ImGui::EndChild();

    ImGui::End();
}

void ModuleManager::OnExit() {
    for (auto& currentModule : this->moduleList) {
        //currentModule->OnExit();
    }
}