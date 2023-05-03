//
// Created by XaDanX on 4/27/2023.
//

#include "Debug.h"

void Debug::OnTick() {

}

void Debug::OnLoad() {

}

void Debug::OnGui() {
    ImGui::BeginTabBar(XorStr("#Debug").c_str());
    if (ImGui::BeginTabItem(XorStr("HeroList").c_str())) {
        ImGui::Text("Count: %i", static_cast<int>(locator->GetObjectManager()->GetHeroList().size()));
        ImGui::Separator();
        for (auto hero : locator->GetObjectManager()->GetHeroList()) {
            if (!hero->IsHero() || hero->IsDummy())
                continue;
            if (ImGui::TreeNode(&hero->networkId, "%s", hero->name.c_str())) {
                ImGui::Text(XorStr("Index: 0x%08x").c_str(), hero->index);
                ImGui::Text(XorStr("Team: %i").c_str(), hero->team);
                ImGui::Text(XorStr("NetworkId: 0x%08x").c_str(), hero->networkId);
                ImGui::Text(XorStr("Position: %f | %f | %f").c_str(), hero->position.x, hero->position.y, hero->position.z);
                ImGui::Text(XorStr("Visibility: %s").c_str(), hero->visibility ? XorStr("true").c_str() : XorStr("false").c_str());
                ImGui::Text(XorStr("SpawnCount: %i").c_str(), hero->spawnCount);
                ImGui::SliderFloat(XorStr("Mana").c_str(), &hero->mana, 0.f, hero->maxMana);
                ImGui::Text(XorStr("Dead: %s").c_str(), hero->dead ? XorStr("true").c_str() : XorStr("false").c_str());
                ImGui::SliderFloat(XorStr("Health").c_str(), &hero->health, 0.f, hero->maxHealth);
                ImGui::Text(XorStr("Name: %s").c_str(), hero->name.c_str());
                ImGui::Text(XorStr("AttackRange: %f").c_str(), hero->attackRange);
                ImGui::Text(XorStr("Scale: %f").c_str(), hero->scale);
                ImGui::Text(XorStr("Targetable: %s").c_str(), hero->targetable ? XorStr("true").c_str() : XorStr("false").c_str());
                ImGui::Text(XorStr("AttackSpeedMultiplier: %f").c_str(), hero->attackSpeedMultiplier);
                ImGui::Text(XorStr("MovementSpeed: %f").c_str(), hero->movementSpeed);
                ImGui::TreePop();
            }
        }
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}
