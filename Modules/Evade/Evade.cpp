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

    auto a = locator->GetEngine()->WorldToScreen(lastMovement);
    auto b = locator->GetEngine()->WorldToScreen(player->position);
    ImGui::GetBackgroundDrawList()->AddLine({a.x, a.y}, {b.x, b.y}, ImColor(255, 0, 0, 255), 2);

    auto currentTime = locator->GetEngine()->GetGameTick();


    if (currentTime < Evade::evadeEndTime + (Evade::evadePoint.distance(player->position) / player->movementSpeed) * 0.4 && Evade::evadePoint.x != 0) { // DETECT WHEN SPELL PASSED PLAYER
        auto p1 = locator->GetEngine()->WorldToScreen(locator->GetObjectManager()->GetLocalPlayer()->position);
        auto p2 = locator->GetEngine()->WorldToScreen(Evade::evadePoint);
        ImGui::GetBackgroundDrawList()->AddLine({p1.x, p1.y}, {p2.x, p2.y}, ImColor(255, 215, 34, 255), 2);
        locator->GetRenderer()->DrawRiotCircle(Evade::evadePoint, locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->gameplayRadius, ImColor(255, 255, 0, 255), true);
        Vector3& loc = Evade::evadePoint;
        input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);}, GameKeybind::TargetChampionsOnly);
    } else {
        if (lastMovement.x != 0 && lastMovement.z != 0) { // add path check instead of that xD
            Vector3& last = lastMovement;
            auto playerPos = player->position;
            auto direction = last.sub(playerPos).normalize();
            auto point = playerPos.add(direction.scale(static_cast<float>(locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->gameplayRadius * 2)));
            if (!IsDangerous(point)) {
                if (continueLastMovement) {
                    input.IssueClickAt(CT_RIGHT_CLICK, [last] { return locator->GetEngine()->WorldToScreen(last); },
                                       GameKeybind::TargetChampionsOnly);
                    }
                lastMovement = Vector3(0, 0, 0);
                Evade::isEvading = false;
                }

            }


    }

    if (Evade::isEvading) {
        auto a = locator->GetEngine()->WorldToScreen(player->position);
        ImGui::GetBackgroundDrawList()->AddText({a.x, a.y}, ImColor(0, 255, 0, 255), "Evading");
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


    for (const auto& spell : spellDetector->detectedSpells) {
        locator->GetRenderer()->DrawPolygon(spell.path, ImColor(255, 0, 0, 255), 1);
        Geometry::Polygon drawable = Geometry::Rectangle(spell.currentPos, spell.endPos, spell.spellInfo->width + spell.spellInfo->height).ToPolygon();
        locator->GetRenderer()->DrawPolygon(drawable, ImColor(255, 255, 255, 255), 1);

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
    std::unique_ptr<DetectedSpell> bestCollision = nullptr;
    DangerLevel bestPriority = DangerLevel::NoDanger;

    for (auto& spell : spellDetector->detectedSpells) {
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
        angle = 1.57079633;
    else
        angle = -1.57079633;

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

    if (timeEvade > timeImpact) {
       // locator->GetConsole()->Print("tE: %f | tI: %f | CANT DODGE!", timeEvade, timeImpact);
    }
    //locator->GetConsole()->Print("tE: %f | tI: %f", timeEvade, timeImpact);

    auto now = locator->GetEngine()->GetGameTick();
    Evade::evadeEndTime = now + (Evade::evadePoint.distance(player->position) / player->movementSpeed);

    if (lastMovement.x == 0 && lastMovement.z == 0) {
        lastMovement = player->GetAiManager()->endPath.clone();
    }
    Evade::isEvading = true;
    Vector3& loc = Evade::evadePoint;
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


