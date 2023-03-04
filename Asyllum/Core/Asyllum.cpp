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

namespace {
    std::string deployablePath(XorStr("C:\\Deployable").c_str());
}

bool Asyllum::Initialize() {
    while (locator->GetEngine()->GameTime() < 2.0) {
        Sleep(1000);
    }


    locator->GetGameData()->Load(deployablePath); // load data, icons
    GameKeybind::InitFromGameConfigs(); // load config
    locator->GetHookingService()->Initialize(); // init hooks

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
    }

    locator->GetConsole()->Print(XorStr("[CORE] Initialized!").c_str());
    locator->GetModuleManager()->Initialize();

    return true;
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
    /*auto missiles = locator->GetObjectManager()->GetMissileList();
    if (!missiles.empty()) {
        for (auto missile : missiles) {
            if (!missile->IsValid())
                continue;

            auto spell = missile->GetSpellObject();
            if (spell.IsValid() && Utils::IsValid((void*)spell.caster)) {
                locator->GetRenderer()->DrawRiotCircle(spell.startPos, 60, ImColor(255, 0, 0, 255), true);
                locator->GetRenderer()->DrawRiotCircle(spell.endPos, 60, ImColor(255, 0, 0, 255), true);
                locator->GetRenderer()->DrawRiotCircle(spell.currentPos, 60, ImColor(255, 0, 255, 255), true);
                locator->GetConsole()->Print("caster: %s", spell.caster->name.c_str());

                Geometry::Polygon path = Geometry::Rectangle(spell.currentPos, spell.endPos, spell.spellInfo->width).ToPolygon();


                ImVec2 points[200];
                int i = 0;
                for (auto& point : path.points) {
                    Vector2 screenSpace = locator->GetEngine()->WorldToScreen(point);
                    points[i].x = screenSpace.x;
                    points[i].y = screenSpace.y;
                    i++;
                }

                ImGui::GetBackgroundDrawList()->AddPolyline(points, i, ImColor(255, 255, 255, 255), true, 1);
            }

            locator->GetConsole()->Print("name: %s | %i", missile->missileInfo->missileData->name.c_str(), missile->slot);
            locator->GetRenderer()->DrawRiotCircle(missile->startPos, 60, ImColor(255, 0, 0, 255), true);
            locator->GetRenderer()->DrawRiotCircle(missile->endPos, 60, ImColor(255, 0, 0, 255), true);
            locator->GetRenderer()->DrawRiotCircle(missile->currentPos, 60, ImColor(255, 0, 255, 255), true);

            auto point = locator->GetEngine()->WorldToScreen(missile->currentPos);
            ImGui::GetBackgroundDrawList()->AddText({point.x, point.y}, ImColor(255, 255,255, 255), missile->missileInfo->missileData->name.c_str());


        }

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

    /*
    }*/

}


void Asyllum::OnThreadTick() {

}