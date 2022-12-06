//
// Created by XaDanX on 12/1/2022.
//

#include "Asyllum.h"
#include "../Globals/Globals.h"
#include "../Core/Helpers/Helpers.h"
#include "../imgui/imgui.h"
#include "../Protection/XorStr.h"
#include "Objects/ObjectBase.h"
#include "../Math/Math.h"
#include "Locator/Locator.h"
#include "Objects/Hero/Hero.h"
#include "Helpers/StringUtils.h"

namespace {
    std::string deployablePath(XorStr("C:\\Deployable").c_str());
}

bool Asyllum::Initialize() { // load resources etc
    while (locator->GetEngine()->GameTime() < 10.0) {
        Sleep(1000);
    }

    locator->GetGameData()->Load(deployablePath);
    locator->GetHookingService()->Initialize();
    locator->GetModuleManager()->Initialize();
    return true;
}

void Asyllum::OnGui() {
    locator->GetModuleManager()->UpdateModulesGui();
    auto localQ = locator->GetObjectManager()->GetLocalPlayer()->GetSpellSlotById(1);


    ImGui::Begin(XorStr("DEV").c_str());
    ImGui::Text(XorStr("BaseAddress: %#08x").c_str(), Globals::baseAddress);
    ImGui::Text(XorStr("CD: %f").c_str(), localQ->readyTime);
    ImGui::Text(XorStr("NAM: %s").c_str(), localQ->GetName().c_str());
    ImGui::End();
}

void Asyllum::OnTick() {
    locator->GetEngine()->Update();
    locator->GetModuleManager()->UpdateModules();

    auto hero = locator->GetObjectManager()->GetLocalPlayer();
    auto pos = hero->GetHealthBarPosition();
    ImGui::GetOverlayDrawList()->AddCircle(ImVec2(pos.x, pos.y), 20, ImColor(255, 0, 0, 255), 40, 1);
}


void Asyllum::OnThreadTick() {
}
