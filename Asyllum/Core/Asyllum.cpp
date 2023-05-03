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
#include "Data/GameKeybind.h"
#include "../Math/Geometry.h"
#include <filesystem>
#include <format>
#include <iostream>
#include <inttypes.h>

namespace {
    std::string deployablePath(XorStr("C:\\Deployable").c_str());
}

bool Asyllum::Initialize() {

    while (locator->GetEngine()->GameTime() < 1.1) {
        Sleep(50);
    }


    locator->GetGameData()->Load(deployablePath); // load data, icons
    GameKeybind::InitFromGameConfigs(); // load config

    locator->GetHookingService()->Initialize(); // init hooks

    /* FIX
    for (auto hero: locator->GetObjectManager()->GetHeroList()) {
        if (hero->IsDummy())
            continue;
        auto info = hero->GetUnitInfo();
        if (!Utils::IsValid(info)) {
            locator->GetConsole()->Print(XorStr("[CORE] Could not find unit data for: %s").c_str(), hero->name.c_str());
        }
        for (int index = 0; index < 4; index++) {
            auto spell = hero->GetSpellSlotById(index)->GetSpellInfo();
            if (!Utils::IsValid(spell)) {
                locator->GetConsole()->Print(XorStr("[CORE] Could not find spell data for: %s | with id: %i").c_str(),
                                             hero->name.c_str(), index);
            }
        }
    }*/

    locator->GetConsole()->Print(XorStr("[CORE] Initialized! %f %s").c_str(), locator->GetEngine()->GameTime(),  locator->GetObjectManager()->GetLocalPlayer()->name.c_str());//
    locator->GetModuleManager()->Initialize();



    /*
    typedef void(__thiscall* fnPrintChat)(__int64, const char*, int);
    fnPrintChat PrintChat = (fnPrintChat)((__int64)GetModuleHandle(NULL) + 0x78f2a0);

    PrintChat((__int64) GetModuleHandle(NULL) + 0x392f258, "<font color=\"#032dff\">Asyllum is here ^w^</font>", 1);*/

    return true;//
}


void Asyllum::OnGui() {
    locator->GetMenu()->Update();
    locator->GetConsole()->Render();
}

float peakUpdateTime = 0;

void Asyllum::OnTick() {
    auto timeBegin = std::chrono::high_resolution_clock::now();
    locator->GetEngine()->Update();
    locator->GetModuleManager()->UpdateModules();

    /*auto player = locator->GetObjectManager()->GetLocalPlayer();

    auto pos = locator->GetEngine()->WorldToScreen(player->position);
    ImGui::GetBackgroundDrawList()->AddText({pos.x, pos.y}, ImColor(255, 0, 0, 255), ":)");

    auto test = locator->GetEngine()->WorldToScreen(locator->GetEngine()->GetHudInstance()->mouseInstance->cursorWorldPos);
    ImGui::GetBackgroundDrawList()->AddText({test.x, test.y}, ImColor(255, 0, 0, 255), "AAAAAAAAA");




    auto ai = player->GetAiManager();

    auto missiles = locator->GetObjectManager()->GetMissileList();

    for (auto m : missiles) {
        locator->GetRenderer()->DrawRiotCircle(m->startPos, 70, ImColor(255, 0, 0, 255), true);
        locator->GetRenderer()->DrawRiotCircle(m->currentPos, 70, ImColor(255, 0, 0, 255), true);
        locator->GetConsole()->Print("0x%llx | %s | %i", (__int64)m, m->missileInfo->missileData->name, m->missileInfo->slot);
    }*/





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