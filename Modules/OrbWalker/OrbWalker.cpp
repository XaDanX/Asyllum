//
// Created by XaDanX on 2/22/2023.
//

#include "OrbWalker.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/Core/Data/GameKeybind.h"
#include "../../Asyllum/Utils/Utils.h"
#include "../../Asyllum/Core/Managers/EventManager/Event.h"
#include "../Evade/Evade.h"


#define TICK_RATE 0.0333;
namespace OrbWalkerUtils {

    float lastAutoAttackTick = 0;
    float lastMoveTick = 0;

    int GetAttackDelay() {
        return (int) (1000.0f / locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed());
    }

    float GetWindupTime() {
        auto player = locator->GetObjectManager()->GetLocalPlayer();
        return (1 / player->GetTotalAttackSpeed() * 1000 *
                player->GetUnitInfo()->basicAttackWindup);
    }

    bool CanAttack() {
        auto player = locator->GetObjectManager()->GetLocalPlayer();//duzy ccchhhuuuj
        if (player->GetAiManager()->isDashing)
            return false;
        if (player->characterData->hash == HashName::Kaisa) {
            if (Utils::IsValid(player->GetSpellCast())) {
                if (player->GetSpellCast()->spellSlot == 0x2) {
                    return false;
                }
            }
        }
        return lastAutoAttackTick + (float) GetAttackDelay() + 60.0 <
                locator->GetEngine()->GetGameTick(); //60 = ping
    }

    bool CanMove() {
        return lastMoveTick < locator->GetEngine()->GetGameTick();
    }

    Hero *GetBestTarget() {
        float oldDistance = FLT_MAX;
        Hero *bestTarget = nullptr;
        for (auto &unit: locator->GetObjectManager()->GetHeroList()) {
            if (!unit->IsAlive()) continue;
            if (unit->IsLocalPlayer()) continue;
            if (!unit->targetable) continue;
            if (!unit->IsOnScreen()) continue;

            if (unit->DistanceTo<Hero*>(locator->GetObjectManager()->GetLocalPlayer()) -
                unit->GetUnitInfo()->gameplayRadius > (locator->GetObjectManager()->GetLocalPlayer()->attackRange +
                                                       locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->gameplayRadius))
                continue;

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
                                           ImColor(0, 255, 50, 150), false);


   ImGui::Begin("OrbWalker DEBUG");
   ImGui::Separator();
   ImGui::Text("Attack speed %f", locator->GetObjectManager()->GetLocalPlayer()->GetTotalAttackSpeed());
   ImGui::Separator();//cipa
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
   ImGui::Text("Moving: %s", locator->GetObjectManager()->GetLocalPlayer()->GetAiManager()->isMoving ? "true" : "false");
   ImGui::Separator();
   ImGui::End();

    if (input.IsDown(this->hotKey) && this->enabled && !Evade::isEvading ) {
        if (!locator->GetEngine()->GetHudInstance()->IsFocused() || locator->GetHookingService()->isMenuOpen)
            return;
        auto target = OrbWalkerUtils::GetBestTarget();
        if (target) {
            if (OrbWalkerUtils::CanAttack()) {
                Vector3 &loc = target->position;
                input.IssueClickAt(CT_RIGHT_CLICK, [loc] { return locator->GetEngine()->WorldToScreen(loc); },
                                   GameKeybind::TargetChampionsOnly);
                OrbWalkerUtils::lastAutoAttackTick = locator->GetEngine()->GetGameTick()  + (float)TICK_RATE;
                OrbWalkerUtils::lastMoveTick =
                        locator->GetEngine()->GetGameTick() + OrbWalkerUtils::GetWindupTime() + OrbWalkerUtils::GetWindupTime() * 0.05 + (float)TICK_RATE;
                return;
            }
        }
        if (OrbWalkerUtils::CanMove()) {
            this->input.IssueClick(CT_RIGHT_CLICK, GameKeybind::TargetChampionsOnly);
            OrbWalkerUtils::lastMoveTick = locator->GetEngine()->GetGameTick() + 90;
            return;
        }

    }


}


void OnRecallListener(Event::OnRecall args) {
    auto player = locator->GetObjectManager()->GetLocalPlayer();
    auto pos2d = locator->GetEngine()->WorldToScreen(player->position);

    auto pos2d2 = locator->GetEngine()->WorldToScreen(args.caster->position);

    ImGui::GetBackgroundDrawList()->AddLine({pos2d.x, pos2d.y}, {pos2d2.x, pos2d2.y}, ImColor(255, 255, 0, 255), 3);
    ImGui::GetBackgroundDrawList()->AddText({pos2d2.x, pos2d2.y}, ImColor(255, 0, 0, 255), "REC");


}

void OrbWalker::OnLoad() {
    locator->GetEventManager()->Subscribe<Event::OnRecall>(&OnRecallListener);
}
