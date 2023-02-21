//
// Created by XaDanX on 1/28/2023.
//

#include "OrbWalker.h"

#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/Core/Data/GameKeybind.h"
#include "../../Asyllum/Utils/Utils.h"

#define TICK_RATE 0.0333;
namespace OrbWalkerUtils {

    float lastAutoAttackTick = 0;
    float lastMoveTick = 0;

    int GetAttackDelay() {
        return (int)(1000.0f / locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed());
    }
    float GetWindupTime() {
        return (1 / locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed() * 1000 *
                locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->basicAttackWindup);
    }

    bool CanAttack() {
        if (locator->GetObjectManager()->GetLocalPlayer()->GetAiManager()->isDashing)
            return false;
        if (locator->GetObjectManager()->GetLocalPlayer()->name.str().contains(XorStr("Kaisa").c_str())) {
            if (Utils::IsValid(locator->GetObjectManager()->GetLocalPlayer()->GetSpellCast())) {
                if (locator->GetObjectManager()->GetLocalPlayer()->GetSpellCast()->spellSlot == 0x2) {
                    return false;
                }
            }
        }
        return lastAutoAttackTick + GetAttackDelay() + 60.0 < locator->GetEngine()->GetProcessorTime(); //60 = ping
    }

    bool CanMove() {
        return lastMoveTick < locator->GetEngine()->GetProcessorTime();
    }

    Hero* GetBestTarget() { // CLOSEST ONE // TODO: TARGET SELECTOR
        float oldDistance = FLT_MAX;
        Hero* bestTarget = nullptr;
        for (auto& unit : locator->GetObjectManager()->GetHeroList())
        {
            if (!unit->IsAlive()) continue;
            if (unit->IsLocalPlayer()) continue;
            if (!unit->targetable) continue;
            if (!unit->IsOnScreen()) continue;

            if (unit->DistanceTo<Hero*>(locator->GetObjectManager()->GetLocalPlayer()) - unit->GetUnitInfo()->gameplayRadius > (locator->GetObjectManager()->GetLocalPlayer()->attackRange + locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->gameplayRadius)) continue;

            auto distance = locator->GetObjectManager()->GetLocalPlayer()->DistanceTo<Hero*>(unit);

            if (distance < oldDistance) {
                oldDistance = distance;
                bestTarget = unit;
            }
        }
        return bestTarget;
    }
}



void OrbWalker::OnTick() {
    auto localPlayer = locator->GetObjectManager()->GetLocalPlayer();
    locator->GetRenderer()->DrawRiotCircle(localPlayer->position,
                                           localPlayer->GetUnitInfo()->gameplayRadius + localPlayer->attackRange,
                                           ImColor(0, 255, 50, 150), true);
    /*
    ImGui::Begin("OrbWalker DEBUG");
    ImGui::Separator();
    ImGui::Text("Attack speed %f", locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed());
    ImGui::Separator();
    ImGui::Text("Attack delay: %i", OrbWalkerUtils::GetAttackDelay());
    ImGui::Separator();
    ImGui::Text("Windup time: %f", OrbWalkerUtils::GetWindupTime());
    ImGui::Separator();
    ImGui::Text("Can attack: %s", OrbWalkerUtils::CanAttack() ? "true" : "false");
    ImGui::Separator();
    ImGui::Text("Can move: %s", OrbWalkerUtils::CanMove() ? "true" : "false");
    ImGui::Separator();
    ImGui::Text("Lethal tempo: %s", locator->GetObjectManager()->GetLocalPlayer()->IsLethalTempoActive() ? "true" : "false");
    ImGui::Separator();
    ImGui::Text("Dashing: %s", locator->GetObjectManager()->GetLocalPlayer()->GetAiManager()->isDashing ? "true" : "false");
    ImGui::Separator();
    ImGui::Text("AiManager: 0x%08x", (int)locator->GetObjectManager()->GetLocalPlayer()->GetAiManager());
    ImGui::End();*/
    if (input.IsDown(this->hotKey) && this->enabled) {
        if (!locator->GetEngine()->GetHudInstance()->IsFocused() || locator->GetHookingService()->isMenuOpen) return;
        auto target = OrbWalkerUtils::GetBestTarget();
        if (target) {
            if (OrbWalkerUtils::CanAttack()) {
                Vector3& loc = target->position;
                input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);}, GameKeybind::TargetChampionsOnly);
                OrbWalkerUtils::lastAutoAttackTick = locator->GetEngine()->GetProcessorTime() + (float)TICK_RATE;
                OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetProcessorTime() + OrbWalkerUtils::GetWindupTime() + (float)TICK_RATE;
                return;
            }
        }
        if (OrbWalkerUtils::CanMove()) {
            this->input.IssueClick(CT_RIGHT_CLICK, GameKeybind::TargetChampionsOnly);
            OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetProcessorTime() + 70;
            return;
        }

    }


}

void OrbWalker::OnLoad() {

}

void OrbWalker::OnGui() {
    ImGui::Checkbox(XorStr("Enabled").c_str(), &this->enabled);
    this->hotKey = (HKey)input.ImGuiKeySelect(XorStr("OrbWalker key").c_str(), this->hotKey);
}