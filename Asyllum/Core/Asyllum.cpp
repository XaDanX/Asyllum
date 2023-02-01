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
#include "Managers/EventManager/Event.h"
#include <filesystem>
#include <format>
#include <iostream>




void TestEventManager(Event::OnSpellCast args) {
    auto startPos = locator->GetEngine()->WorldToScreen(args.spell.startPos);
    auto endPos = locator->GetEngine()->WorldToScreen(args.spell.endPos);

    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(startPos.x, startPos.y), ImVec2(endPos.x, endPos.y), ImColor(255, 255, 255, 255), 2);
    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(startPos.x, startPos.y), args.spell.spellInfo->width / 2, ImColor(255, 0, 0, 255), 50);
    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(endPos.x, endPos.y), args.spell.spellInfo->width / 2, ImColor(255, 0, 0, 255), 50);
    endPos.y -= 10;
    locator->GetRenderer()->Text(endPos, args.spell.name.c_str(), ImColor(255, 255, 255, 255));

    if (!Utils::IsValid(args.spell.spellInfo)) {
        locator->GetConsole()->Print("Invalid spell info for: %s", args.spell.name.c_str());
    } else {
        locator->GetConsole()->Print("Casted: %s", args.spell.name.c_str());
    }

}


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

    locator->GetEventManager()->Subscribe<Event::OnSpellCast>(&TestEventManager);

    return true;
}


void Asyllum::OnGui() {
    locator->GetModuleManager()->UpdateModulesGui();
    locator->GetConsole()->Render();
}

float peakUpdateTime = 0;
void Asyllum::OnTick() {
    auto timeBegin = std::chrono::high_resolution_clock::now();
    locator->GetEngine()->Update();
    locator->GetModuleManager()->UpdateModules();

    std::chrono::duration<float, std::milli> updateTime = std::chrono::high_resolution_clock::now() - timeBegin;
    ImGui::Begin(XorStr("DEBUG INFO").c_str(), 0,
                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);


    ImGui::Text(XorStr("Update: %f ms").c_str(), static_cast<float>(updateTime.count()));
    ImGui::Text(XorStr("Peak: %f ms").c_str(), peakUpdateTime);
    if (ImGui::Button(XorStr("RESET").c_str())) {
        peakUpdateTime = 0;
    }
    ImGui::End();
    if (static_cast<float>(updateTime.count()) > peakUpdateTime)
        peakUpdateTime = static_cast<float>(updateTime.count());



}


void Asyllum::OnThreadTick() {
}
