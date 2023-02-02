//
// Created by XaDanX on 1/28/2023.
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
    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        auto radius = hero->GetUnitInfo()->gameplayRadius + hero->attackRange;

        locator->GetRenderer()->DrawRiotCircle(hero->position, radius, ImColor(0, 255, 0, 255));
        //locator->GetRenderer()->DrawCircleAt(hero->position, radius, false, 100, ImColor(0, 255, 0, 255), 1);
    }

    for (auto minion : locator->GetObjectManager()->GetMinionList()) {
        auto radius = 46;

        locator->GetRenderer()->DrawRiotCircle(minion->position, radius, ImColor(0, 255, 0, 255));

    }


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
    ImGui::End();
     */

    /*
    if (input.IsDown(HKey::N)) {
        auto target = OrbWalkerUtils::GetBestTarget();
        if (target) {
            if (OrbWalkerUtils::CanAttack()) {
                Vector3& loc = target->position;
                input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);});
                OrbWalkerUtils::lastAutoAttackTick = locator->GetEngine()->GetProcessorTime();
                OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetProcessorTime() + OrbWalkerUtils::GetWindupTime();
                return;
            }
        }
        if (OrbWalkerUtils::CanMove()) {
            this->input.IssueClick(CT_RIGHT_CLICK);
            OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetProcessorTime() + 60;
            return;
        }

    }
     */

}

void OrbWalker::OnLoad() {

}

void OrbWalker::OnGui() {

}