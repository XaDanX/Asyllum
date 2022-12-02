//
// Created by XaDanX on 12/2/2022.
//

#include "ObjectExplorer.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../../Asyllum/Protection/XorStr.h"

void ObjectExplorer::OnTick() {

}

void ObjectExplorer::OnLoad() {

}

void ObjectExplorer::OnGui() {
    ImGui::Begin(XorStr("ObjectExplorer").c_str());
    ImGui::Text(XorStr("Hero count: %i").c_str(), locator->GetObjectManager()->GetHeroList().size());
    for (auto& hero : locator->GetObjectManager()->GetHeroList()) {
        if (ImGui::TreeNode(&hero->networkId, XorStr("%s (%#010x)").c_str(), hero->name.c_str(), hero->networkId)) {

            ImGui::SliderFloat(XorStr("Health").c_str(), &hero->health, 0, hero->maxHealth);
            ImGui::SliderFloat(XorStr("Mana").c_str(), &hero->mana, 0, hero->maxMana);
            ImGui::Text(XorStr("Position: %f:%f:%f").c_str(), hero->position.x, hero->position.y, hero->position.y);

            ImGui::TreePop();
        }
    }

    ImGui::End();
}