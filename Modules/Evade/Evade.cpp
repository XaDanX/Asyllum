//
// Created by XaDanX on 2/25/2023.
//

#include "Evade.h"
#include "../../Asyllum/Core/Data/GameKeybind.h"
#include "../../Asyllum/Math/Math.h"
#include "../../Asyllum/Core/CollisionEngine/CollisionEngine.h"
#include <ranges>

float Evade::evadeEndTime = 0;
Vector3 Evade::evadePoint{};
DangerLevel Evade::currentDangerLevel = DangerLevel::NoDanger;
bool Evade::isEvading = false;

void Evade::OnTick() {
    spellDetector->Update();
    auto player = locator->GetObjectManager()->GetLocalPlayer();
    auto currentTime = locator->GetEngine()->GetGameTick();



    if (currentTime < Evade::evadeEndTime && Evade::evadePoint.x != 0) { // + (Evade::evadePoint.distance(player->position) / player->movementSpeed) * 0.4
        auto p1 = locator->GetEngine()->WorldToScreen(locator->GetObjectManager()->GetLocalPlayer()->position);
        auto p2 = locator->GetEngine()->WorldToScreen(Evade::evadePoint);
        ImGui::GetBackgroundDrawList()->AddLine({p1.x, p1.y}, {p2.x, p2.y}, ImColor(255, 215, 34, 255), 2);
        locator->GetRenderer()->DrawRiotCircle(Evade::evadePoint, locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->gameplayRadius, ImColor(255, 255, 0, 255), true);
        Vector3 loc = Evade::evadePoint;
        if (extendEvadeMove) {
            auto player = locator->GetObjectManager()->GetLocalPlayer();
            auto length = player->position.distance(Evade::evadePoint);
            auto point = Evade::evadePoint.sub(player->position).normalize();
            loc = player->position.add(point.mult(length*10));
        }
        input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);}, GameKeybind::TargetChampionsOnly);
    } else {
        if (lastMovement.x != 0 && lastMovement.z != 0) {
                if (!IsDangerous(lastMovement)) {
                    if (continueLastMovement) {
                        input.IssueClickAt(CT_RIGHT_CLICK,
                                           [this] { return locator->GetEngine()->WorldToScreen(lastMovement); },
                                           GameKeybind::TargetChampionsOnly);
                    }
                    lastMovement = Vector3(0, 0, 0);
                }

        }
         Evade::isEvading = false;
    }




    if (Evade::isEvading) {
        auto worldPos = locator->GetEngine()->WorldToScreen(player->position);
        ImGui::GetBackgroundDrawList()->AddText({worldPos.x, worldPos.y}, ImColor(0, 255, 0, 255), XorStr("Evading").c_str());
    }

    auto evadable = GetSpellToEvade();

    if (evadable != nullptr) {
        if (evadable->evadeSpellInfo->spellType == SpellType::Linear) {
            Evade::evadePoint = GetLinearEvadePoint(evadable.get(), player->position);
            if (Evade::evadePoint.x != 0) {
                TryEvadeSpell(evadable.get());
            }
        }
    }


    if (!Evade::isEvading) {
        auto pathSafe = IsPathSafe();
        if (!pathSafe.Safe) {
            locator->GetConsole()->Print("PATH FIXED!");
            if (pathSafe.LastSafePoint.x != 0) {
                input.IssueClickAt(CT_RIGHT_CLICK,
                                   [pathSafe] { return locator->GetEngine()->WorldToScreen(pathSafe.LastSafePoint); },
                                   GameKeybind::TargetChampionsOnly);
            } else {
                input.IssueClickAt(CT_RIGHT_CLICK,
                                   [] {
                                       return locator->GetEngine()->WorldToScreen(
                                               locator->GetObjectManager()->GetLocalPlayer()->position);
                                   },
                                   GameKeybind::TargetChampionsOnly);
            }
        }

    }


    for (const auto& spell : spellDetector->detectedSpells) {
        locator->GetRenderer()->DrawPolygon(spell.path, ImColor(255, 0, 0, 255), 3);
        Geometry::Polygon drawable = Geometry::Rectangle(spell.currentPos, spell.endPos, spell.spellInfo->width * 2).ToPolygon();
        locator->GetRenderer()->DrawPolygon(drawable, ImColor(255, 255, 255, 255), 3);

    }



}

Vector3 Evade::GetMovePath() {
    auto player = locator->GetObjectManager()->GetLocalPlayer();
    auto aiMgr = player->GetAiManager();
    auto array = aiMgr->GetNavigationArray();
    if (!aiMgr->isMoving || array.size() < 1)
        return Vector3();

    return array.at(array.size() - 1);
}

bool Evade::IsDangerous(Vector3 pos) {
    for (auto spell : spellDetector->detectedSpells) {
        if (spell.path.IsInside(pos)) {
            return true;
        }
    }
    return false;
}

std::unique_ptr<DetectedSpell> Evade::GetSpellToEvade() { // PATH, GET FIRST NODE, GET DIRECTION, EXTEND LENGTH + ...
    auto player = locator->GetObjectManager()->GetLocalPlayer();
    std::unique_ptr<DetectedSpell> bestCollision = nullptr;
    DangerLevel bestPriority = DangerLevel::NoDanger;

    for (auto& spell : spellDetector->detectedSpells) {
        if (spell.caster->IsAllyTo<Hero*>(player))
            continue;


        auto res = CollisionEngine::FindCollisionLine(spell);
        auto collision = (!res.hitList.empty() && res.CollideWithPlayer);
        if (collision || spell.path.IsInside(GetMovePath())) {

            if (spell.evadeSpellInfo->dangerLevel >= bestPriority) {
                bestPriority = spell.evadeSpellInfo->dangerLevel;
                bestCollision = std::make_unique<DetectedSpell>(spell);
            }
        }
    }

    if (Evade::evadeEndTime > locator->GetEngine()->GetGameTick() and currentDangerLevel >= bestPriority)
        return nullptr;
    if (bestCollision != nullptr) {
        currentDangerLevel = bestPriority;
        return bestCollision;
    }
    return nullptr;

}

Vector3 Evade::GetLinearEvadePoint(DetectedSpell* spell, Vector3 pos) {

    auto player = locator->GetObjectManager()->GetLocalPlayer();
    auto position = pos.clone();

    auto direction = spell->endPos.sub(spell->startPos).normalize();

    auto lineEnd = Vector2(spell->endPos.x, spell->endPos.z);
    auto lineStart = Vector2(spell->startPos.x, spell->startPos.z);


    auto determinant = ((lineEnd.x - lineStart.x) * (position.z - lineStart.y)) - ((lineEnd.y - lineStart.y) * (position.x - lineStart.x));

    auto spellDir = direction.clone();
    spellDir.y = 0;

    auto pDist = PerpedincularDistToSegment(Vector2(position.x, position.z), lineStart, lineEnd);
    auto distThreshold = extraEvadeLength + (spell->spellInfo->width + spell->evadeSpellInfo->extraWidth) + 10 + player->GetUnitInfo()->gameplayRadius;
    if (pDist > distThreshold)
        return position;

    float distance = distThreshold - pDist;
    distance += distance * 0.2;
    float angle;
    if (determinant < 0.0)
        angle = 1.57079633f;
    else
        angle = -1.57079633f;

    auto point = player->position.add(spellDir.rotate_y(angle).mult(distance));
    if (!locator->GetEngine()->IsNotWall(point)) {
        point = player->position.add(spellDir.rotate_y(-angle).mult(distance));
        if (!locator->GetEngine()->IsNotWall(point)) {
            return Vector3(0, 0, 0);
        }
    }

    return point;

}

void Evade::TryEvadeSpell(DetectedSpell *spell) {
    auto player = locator->GetObjectManager()->GetLocalPlayer();

    auto timeEvade = player->position.distance(Evade::evadePoint) / player->movementSpeed;
    auto timeImpact = spell->TimeToCollision(player->position) + extraEvadeLength / player->movementSpeed;

    if (lastMovement.x == 0 && lastMovement.z == 0) {
        lastMovement = player->GetAiManager()->endPath.clone();
    }

    if (timeEvade > timeImpact) {
       // locator->GetConsole()->Print("tE: %f | tI: %f | CANT DODGE!", timeEvade, timeImpact);
        /*Evade::isEvading = true;
        Evade::evadeEndTime = locator->GetEngine()->GetGameTick() + 30;
        if (player->GetSpellSlotById(2)->IsReady()) {
            input.IssuePressKeyAt(GameKeybind::CastSpellE,
                                  [] { return locator->GetEngine()->WorldToScreen(Evade::evadePoint); });
        }

       return;*/
    }
    //locator->GetConsole()->Print("tE: %f | tI: %f", timeEvade, timeImpact);

    auto now = locator->GetEngine()->GetGameTick();
    Evade::evadeEndTime = now + (Evade::evadePoint.distance(player->position) / player->movementSpeed);

    Evade::isEvading = true;
    Vector3 loc = Evade::evadePoint;
    if (extendEvadeMove) {
        auto length = player->position.distance(Evade::evadePoint);
        auto point = Evade::evadePoint.sub(player->position).normalize();
        loc = player->position.add(point.mult(length + extendEvadeMoveBy));
    }
    input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);}, GameKeybind::TargetChampionsOnly);
}

void Evade::OnGui() {
    for (auto champion : locator->GetObjectManager()->GetHeroList()) {
        if (champion->IsAllyTo<Hero*>(locator->GetObjectManager()->GetLocalPlayer()))
            continue;
        if (ImGui::TreeNode(&champion->networkId, "%s", champion->name.c_str())) {
            auto championIt = SpellLibrary::championList.find(champion->characterData->hash);
            if (championIt != SpellLibrary::championList.end()) {
                Champion& championObj = championIt->second;
                for (auto& spell : championObj.spells) {
                    ImGui::Image(locator->GetTextureManager()->GetTexture(locator->GetGameData()->GetSpellInfoByName(spell.second.name)->icon), ImVec2(16, 16));
                    ImGui::SameLine();
                    ImGui::Text("%s", spell.second.displayName.c_str());
                    ImGui::SameLine();
                    ImGui::PushID(champion->characterData->hash + (int)spell.second.spellSlot);
                    ImGui::SliderInt("Danger level", reinterpret_cast<int*>(&spell.second.dangerLevel), 0, 4);
                    ImGui::PopID();
                }
            }


            ImGui::TreePop();
        }
    }
}

PathResult Evade::IsPathSafe() {

    auto aiManager = locator->GetObjectManager()->GetLocalPlayer()->GetAiManager();
    auto navArray = aiManager->GetNavigationArray();

    if (navArray.size() > 1) {
        auto last = navArray.at(aiManager->currentSegment-1);

        for (int x = aiManager->currentSegment; x < navArray.size(); x++) {
            auto safe = true;
            auto unsafeAt = 0;

            auto current = navArray.at(x);
            auto p1 = locator->GetEngine()->WorldToScreen(current);
            auto p2 = locator->GetEngine()->WorldToScreen(last);

            auto length = current.distance(last);
            auto direction = current.sub(last).normalize();

            auto multiplier = static_cast<int>((length / 100) + 1);

            auto scale = length / multiplier; //check 7 points per path?

            for (int i = 0; i < multiplier; i++) {
                auto toCheck = last.add(direction.mult(scale * i));
                if (IsDangerous(toCheck)) {
                    safe = false;
                    unsafeAt = i;
                    locator->GetRenderer()->DrawRiotCircle(toCheck, 20, ImColor(255, 0, 0, 255), true);

                    PathResult result;
                    if (i > 1)
                        result.LastSafePoint = last.add(direction.mult(scale * (i - 2)));
                    else if (i == 0) {
                        result.LastSafePoint = last;
                    }
                    result.UnsafePoint = i;
                    result.UnsafSegment = x;
                    result.Safe = false;
                    return result;
                } else {

                    locator->GetRenderer()->DrawRiotCircle(toCheck, 20, ImColor(0, 255, 0, 255), true);
                }
            }

            //locator->GetRenderer()->Text(p1, "%f", length);
            ImGui::GetBackgroundDrawList()->AddText({p1.x, p1.y}, ImColor(255, 255, 255, 255), std::to_string(length).c_str());

            last = current;
        }
    }
    PathResult result;
    result.Safe = true;
    return result;

}

