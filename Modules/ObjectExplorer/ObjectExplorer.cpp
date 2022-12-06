//
// Created by XaDanX on 12/2/2022.
//

#include "ObjectExplorer.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../../Asyllum/Protection/XorStr.h"


namespace ObjectExplorerOptions {
    bool drawObjects = false;
    bool linesToObjects = false;
}

void ObjectExplorer::OnTick() {
    if (!ObjectExplorerOptions::drawObjects && !ObjectExplorerOptions::linesToObjects) return;
    auto localPlayerPos = locator->GetEngine()->WorldToScreen(locator->GetObjectManager()->GetLocalPlayer()->position);
    for (auto& hero : locator->GetObjectManager()->GetHeroList()) {
        auto pos = locator->GetEngine()->WorldToScreen(hero->position);
        auto drawList = ImGui::GetBackgroundDrawList();
        if (ObjectExplorerOptions::drawObjects) {
            if (hero->IsHero() && hero->IsAlive()) {
                drawList->AddText(ImVec2(pos.x, pos.y), ImColor(255, 255, 255, 255), hero->name.c_str());
            }
        }
        if (ObjectExplorerOptions::linesToObjects) {
            if (hero->IsHero() && hero->IsAlive()) {
                drawList->AddLine(ImVec2(localPlayerPos.x, localPlayerPos.y), ImVec2(pos.x, pos.y),
                                  ImColor(255, 255, 255, 255), 1);
            }
        }
    }
    for (auto& minion : locator->GetObjectManager()->GetMinionList()) {
        auto pos = locator->GetEngine()->WorldToScreen(minion->position);
        auto drawList = ImGui::GetBackgroundDrawList();
        if (ObjectExplorerOptions::drawObjects) {
            if (minion->IsMinion() && minion->IsAlive()) {
                drawList->AddText(ImVec2(pos.x, pos.y), ImColor(255, 255, 255, 255), minion->name.c_str());
            }
        }
        if (ObjectExplorerOptions::linesToObjects) {
            if (minion->IsMinion() && minion->IsAlive()) {
                drawList->AddLine(ImVec2(localPlayerPos.x, localPlayerPos.y), ImVec2(pos.x, pos.y),
                                  ImColor(255, 255, 255, 255), 1);
            }
        }
    }
    for (auto& turret : locator->GetObjectManager()->GetTurretList()) {
        auto pos = locator->GetEngine()->WorldToScreen(turret->position);
        auto drawList = ImGui::GetBackgroundDrawList();
        if (ObjectExplorerOptions::drawObjects) {
            if (turret->IsTurret() && turret->IsAlive()) {
                drawList->AddText(ImVec2(pos.x, pos.y), ImColor(255, 255, 255, 255), turret->name.c_str());
            }
        }
        if (ObjectExplorerOptions::linesToObjects) {
            if (turret->IsTurret() && turret->IsAlive()) {
                drawList->AddLine(ImVec2(localPlayerPos.x, localPlayerPos.y), ImVec2(pos.x, pos.y),
                                  ImColor(255, 255, 255, 255), 1);
            }
        }
    }
}

void ObjectExplorer::OnLoad() {

}

void ObjectExplorer::OnGui() {
    ImGui::Begin(XorStr("ObjectExplorer").c_str());
    ImGui::Checkbox(XorStr("Draw Objects").c_str(), &ObjectExplorerOptions::drawObjects);
    ImGui::Checkbox(XorStr("Draw Lines To Objects").c_str(), &ObjectExplorerOptions::linesToObjects);
    ImGui::Separator();
    ImGui::Text(XorStr("Hero count: %i").c_str(), locator->GetObjectManager()->GetHeroList().size());
    ImGui::Text(XorStr("Minion count: %i").c_str(), locator->GetObjectManager()->GetMinionList().size());
    ImGui::Text(XorStr("Turret count: %i").c_str(), locator->GetObjectManager()->GetTurretList().size());
    for (auto& hero : locator->GetObjectManager()->GetHeroList()) {
        if (ImGui::TreeNode(&hero->networkId, XorStr("%s (%#010x)").c_str(), hero->name.c_str(), hero->networkId)) {

            ImGui::SliderFloat(XorStr("Health").c_str(), &hero->health, 0, hero->maxHealth);
            ImGui::SliderFloat(XorStr("Mana").c_str(), &hero->mana, 0, hero->maxMana);
            ImGui::Text(XorStr("Position: %f:%f:%f").c_str(), hero->position.x, hero->position.y, hero->position.y);

            ImGui::TreePop();
        }
    }

    for (auto& minion : locator->GetObjectManager()->GetMinionList()) {
        if (ImGui::TreeNode(&minion->networkId, XorStr("%s (%#010x)").c_str(), minion->name.c_str(), minion->networkId)) {

            ImGui::SliderFloat(XorStr("Health").c_str(), &minion->health, 0, minion->maxHealth);
            ImGui::SliderFloat(XorStr("Mana").c_str(), &minion->mana, 0, minion->maxMana);
            ImGui::Text(XorStr("Position: %f:%f:%f").c_str(), minion->position.x, minion->position.y, minion->position.y);

            ImGui::TreePop();
        }
    }

    for (auto& turret : locator->GetObjectManager()->GetTurretList()) {
        if (ImGui::TreeNode(&turret->networkId, XorStr("%s (%#010x)").c_str(), turret->name.c_str(), turret->networkId)) {

            ImGui::SliderFloat(XorStr("Health").c_str(), &turret->health, 0, turret->maxHealth);
            ImGui::SliderFloat(XorStr("Mana").c_str(), &turret->mana, 0, turret->maxMana);
            ImGui::Text(XorStr("Position: %f:%f:%f").c_str(), turret->position.x, turret->position.y, turret->position.y);

            ImGui::TreePop();
        }
    }


    ImGui::End();
}
