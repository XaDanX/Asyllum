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


#define COL_TO_D3COL(col) D3DCOLOR_ARGB((int)(col.w*255), (int)(col.x*255), (int)(col.y*255), (int)(col.z*255))

struct Vertex {
    float    pos[3];
    D3DCOLOR col;
    float    uv[2];
};

void OrbWalker::OnTick() {
    auto image = locator->GetTextureManager()->GetTexture("circle1");
    Vector3 pos = locator->GetObjectManager()->GetLocalPlayer()->position;
    Vector2 size = Vector2(240, 240);
    auto color = D3DCOLOR_ARGB(255, 255, 255, 255);

    float halfX = size.x / 2.f;
    float halfY = size.y / 2.f;

    auto p1 = Vector3(pos.x - halfX, pos.y, pos.z + halfY);
    auto p2 = Vector3(pos.x + halfX, pos.y, pos.z + halfY);
    auto p3 = Vector3(pos.x + halfX, pos.y, pos.z - halfY);
    auto p4 = Vector3(pos.x - halfX, pos.y, pos.z - halfY);






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