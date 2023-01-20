//
// Created by XaDanX on 12/1/2422.
//

#include "Asyllum.h"
#include "../Globals/Globals.h"
#include "../Core/Helpers/Helpers.h"
#include "../imgui/imgui.h"
#include "../Protection/XorStr.h"
#include "Objects/ObjectBase.h"
#include "Locator/Locator.h"
#include "../Utils/Utils.h"
#include <filesystem>

namespace {
    std::string deployablePath(XorStr("C:\\Deployable").c_str());
}

bool Asyllum::Initialize() {
    while (locator->GetEngine()->GameTime() < 10.0) {
        Sleep(1000);
    }
    locator->GetGameData()->Load(deployablePath);
    locator->GetHookingService()->Initialize();

    locator->GetModuleManager()->Initialize();

    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        auto info = hero->GetUnitInfo();
        if (!Utils::IsValid(info)) {
            locator->GetConsole()->Print(XorStr("Couldn't find unit data for: %s").c_str(), hero->name.c_str());
        }
        for (int index=0; index < 4; index++) {
            auto spell = hero->GetSpellSlotById(index)->GetSpellInfo();
            if (!Utils::IsValid(spell)) {
                locator->GetConsole()->Print(XorStr("Couldn`t find spell data for: %s | with id: %i").c_str(), hero->name.c_str(), index);
            }
        }
    }

    locator->GetConsole()->Print(XorStr("Initialized!").c_str());
    return true;
}



void Asyllum::OnGui() {
    locator->GetModuleManager()->UpdateModulesGui();
    locator->GetConsole()->Render();

}

void Asyllum::OnTick() {
    locator->GetEngine()->Update();
    locator->GetModuleManager()->UpdateModules();
    locator->GetController()->Update();

}


void Asyllum::OnThreadTick() {
}
