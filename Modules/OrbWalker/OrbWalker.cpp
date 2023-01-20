//
// Created by XaDanX on 12/30/2022.
//

#include "OrbWalker.h"
#include "../../Asyllum/Core/Locator/Locator.h"


namespace OrbWalkerUtils {

    float lastAutoAttackTick = 0;
    float lastMoveTick = 0;

    int GetAttackDelay() {
        return (int)(1000.0f / locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed());
    }
    float GetWindupTime() {
        return (1 / locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed() * 1000 *
                locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->basicAttackWindup) + 2;
    }

    bool CanAttack() {
        return lastAutoAttackTick + GetAttackDelay() + 10.0 < locator->GetEngine()->GetProcessorTime(); //60 = ping
    }

    bool CanMove() {
        return lastMoveTick < locator->GetEngine()->GetProcessorTime();
    }

    Hero* GetBestTarget() {
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
    if (!this->enabled) return;
    /*
    ImGui::Begin("orbwalker debug");
    ImGui::Text("Attack speed %f", player->GetTotalAttackSpeed());
    ImGui::Text("Attack delay: %i", OrbWalkerUtils::GetAttackDelay());
    ImGui::Text("Windup time: %f", OrbWalkerUtils::GetWindupTime());
    ImGui::Text("Can attack: %s", OrbWalkerUtils::CanAttack() ? "true" : "false");
    ImGui::Text("Can move: %s", OrbWalkerUtils::CanMove() ? "true" : "false");
    ImGui::End();*/
    if (GetAsyncKeyState(0x4E) & 0x8000) {
        auto target = OrbWalkerUtils::GetBestTarget();
        if (target) {
            auto targetWorldPos = locator->GetEngine()->WorldToScreen(target->position);
            if (OrbWalkerUtils::CanAttack()) {
                locator->GetController()->IssueClickAt((int)targetWorldPos.x, (int)targetWorldPos.y);
                OrbWalkerUtils::lastAutoAttackTick = locator->GetEngine()->GetProcessorTime();
                OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetProcessorTime() + OrbWalkerUtils::GetWindupTime();
                return;
            }
        }
        if (OrbWalkerUtils::CanMove()) {
            locator->GetController()->IssueClick();
            OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetProcessorTime() + 60;
            return;
        }

    }
}

void OrbWalker::OnLoad() {

}

void OrbWalker::OnGui() {
    ImGui::Checkbox(XorStr("Enabled").c_str(), &this->enabled);
}
