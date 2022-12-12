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

}


void Asyllum::OnThreadTick() {
}
