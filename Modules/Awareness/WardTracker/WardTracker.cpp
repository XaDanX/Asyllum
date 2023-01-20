//
// Created by XaDanX on 12/29/2022.
//

#include "WardTracker.h"
#include "../../../Asyllum/Core/Locator/Locator.h"

void WardTracker::DrawWards() {
    if (!this->enabled) return;
    for (auto ward : locator->GetObjectManager()->GetMinionList()) {//
        if (!ward->IsWard()) continue;
        if (!ward->IsOnScreen(100, 100)) continue;
        if (ward->IsAllyTo<Hero*>(locator->GetObjectManager()->GetLocalPlayer())) continue;
        auto worldPos = locator->GetEngine()->WorldToScreen(ward->position);
        locator->GetRenderer()->DrawCircleAt(ward->position, 900, false, 100, ImColor(255, 255, 255, 150), 1);
        locator->GetRenderer()->Text(worldPos, std::to_string(ward->mana).c_str(), ImColor(255, 255, 255, 255));

    }

}

void WardTracker::DrawGui() {
    ImGui::Checkbox(XorStr("Enabled").c_str(), &this->enabled);
}
