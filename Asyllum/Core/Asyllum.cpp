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

bool Asyllum::Initialize() { // load resources etc
    return true;
}

void Asyllum::OnGui() {

    locator->GetModuleManager()->UpdateModulesGui();

    auto localPlayer = *reinterpret_cast<Hero**>(RVA(0x3143DA0));
    ImGui::Begin(XorStr("DEVV").c_str());
    ImGui::Text(XorStr("BaseAddress: %#08x").c_str(), Globals::baseAddress);
    ImGui::Text(XorStr("Health: %f").c_str(), localPlayer->health);
    ImGui::Text(XorStr("Name: %s").c_str(), localPlayer->name);
    ImGui::Text(XorStr("Units: %i").c_str(), locator->GetGameData()->Units.size());

    ImGui::End();
}

void Asyllum::OnTick() {
    locator->GetEngine()->Update();
    locator->GetModuleManager()->UpdateModules();

    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        auto pos = locator->GetEngine()->WorldToScreen(hero->position);
        ImGui::SetNextWindowPos(ImVec2(pos.x - 20, pos.y));
        ImGui::SetNextWindowBgAlpha(0.7f);
        ImGui::Begin(hero->name, 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove );
        ImGui::Text(XorStr("Name: %s").c_str(), hero->name);
        ImGui::End();
    }
}


void Asyllum::OnThreadTick() {
}
