//
// Created by XaDanX on 1/30/2023.
//

#include "Evade.h"
#include "../../Asyllum/Core/Managers/EventManager/Event.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/Core/CollisionEngine/CollisionEngine.h"
#include "../../Asyllum/Utils/Utils.h"
#include <numbers>
#include "../../Asyllum/Math/Math.h"
#include "../../Asyllum/Core/Data/GameKeybind.h"


std::map<int, Spell> Evade::activeSpells;
std::map<HashName, Champion> Evade::championList;
float Evade::evadeTimeEnd = 0;

void OnSpellCasted(Event::OnSpellCast args) {

    EvadeSpell* evadeSpell = Evade::FindSpell(args.caster->characterData->hash, (Slot)args.spell.spellSlot);
    if (Utils::IsValid((void*)evadeSpell)) {

        int uuid = 1000 * ((int) args.spell.endTime + (int) args.spell.castTime + (int) args.spell.startPos.x +
                           (int) args.spell.endPos.z + (int) args.spell.spellSlot);
        if (Evade::activeSpells.contains(uuid))
            return;
        Evade::activeSpells[uuid] = args.spell;


    }


}

void Evade::OnTick() {
    ProcessActiveSpells();

    auto currentTime = locator->GetEngine()->GetProcessorTime();


    if (currentTime < Evade::evadeTimeEnd && Evade::evadePoint.x != 0) {
        auto p1 = locator->GetEngine()->WorldToScreen(locator->GetObjectManager()->GetLocalPlayer()->position);
        auto p2 = locator->GetEngine()->WorldToScreen(Evade::evadePoint);
        ImGui::GetBackgroundDrawList()->AddLine({p1.x, p1.y}, {p2.x, p2.y}, ImColor(255, 215, 34, 255), 2);
        locator->GetRenderer()->DrawRiotCircle(Evade::evadePoint, locator->GetObjectManager()->GetLocalPlayer()->GetUnitInfo()->gameplayRadius, ImColor(255, 255, 0, 255), true);
        // move
        Vector3& loc = Evade::evadePoint;
        input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);}, GameKeybind::TargetChampionsOnly);
    }

    auto evadable = Evade::GetEvadableSpell();
    if (evadable) {
        // check for linear/area
        Evade::evadePoint = GetLinearEvadePoint(evadable.get());
        //Evade::evadeTimeEnd = currentTime + 1000;
        if (Evade::evadePoint.x != 0) {
            TryEvadeSpell(evadable.get());
        }

    }
}

void Evade::OnLoad() {
    locator->GetEventManager()->Subscribe<Event::OnSpellCast>(&OnSpellCasted);
    Evade::InitEvadableSpells();
}

void Evade::OnGui() {
    ImGui::Text("0x%08x", (int)locator->GetObjectManager()->GetLocalPlayer()->GetAiManager());
}

void Evade::ProcessActiveSpells() {
    for (auto it = Evade::activeSpells.cbegin(), next_it = it; it != Evade::activeSpells.cend(); it = next_it) {
        ++next_it;

        if (it->second.endTime < locator->GetEngine()->GameTime()) {
            Evade::activeSpells.erase(it);
        }
    }
}

void Evade::InitEvadableSpells() {

    { // ezreal
        Champion ezreal;
        ezreal.name = XorStr("Ezreal");
        ezreal.hash = HashName::Ezreal;

        EvadeSpell ezrealQ;
        ezrealQ.name = XorStr("ezrealq");
        ezrealQ.displayName = XorStr("Ezreal Q");
        ezrealQ.spellType = SpellType::Linear;
        ezrealQ.spellSlot = Slot::_Q;
        ezrealQ.dangerLevel = DangerLevel::Low;

        ezreal.spells[Slot::_Q] = ezrealQ;

        EvadeSpell ezrealW;
        ezrealW.name = XorStr("ezrealw");
        ezrealW.displayName = XorStr("Ezreal W");
        ezrealW.spellType = SpellType::Linear;
        ezrealW.spellSlot = Slot::_W;
        ezrealW.dangerLevel = DangerLevel::Low;

        ezreal.spells[Slot::_W] = ezrealW;

        EvadeSpell ezrealR;
        ezrealR.name = XorStr("ezrealr");
        ezrealR.displayName = XorStr("Ezreal R");
        ezrealR.spellType = SpellType::Linear;
        ezrealR.spellSlot = Slot::_R;
        ezrealR.dangerLevel = DangerLevel::VeryHigh;

        ezreal.spells[Slot::_R] = ezrealR;

        championList[HashName::Ezreal] = ezreal;
    }


}

std::vector<Spell> Evade::GetDangerousSpells() {
    std::vector<Spell> result;
    for (auto it = Evade::activeSpells.cbegin(), next_it = it; it != Evade::activeSpells.cend(); it = next_it) {
        ++next_it;

        auto res = CollisionEngine::FindCollisionLine(it->second);
        if (res.hitList.empty()) continue;
        if (!res.CollideWithPlayer) continue;
        result.push_back(it->second);
    }
    return result;
}

std::unique_ptr<Spell> Evade::GetEvadableSpell() {
    auto dangerousSpells = GetDangerousSpells();

    std::unique_ptr<Spell> bestCollision = nullptr;
    DangerLevel bestPriority = DangerLevel::NoDanger;

    if (!dangerousSpells.empty()) {
        for (auto spell : dangerousSpells) {
            EvadeSpell* evadeSpell = Evade::FindSpell(spell.caster->characterData->hash, (Slot)spell.spellSlot);

            if (evadeSpell->dangerLevel >= bestPriority) {
                bestPriority = evadeSpell->dangerLevel;
                bestCollision = std::make_unique<Spell>(spell);
            }
        }
        if (evadeTimeEnd > locator->GetEngine()->GetProcessorTime() and currentDangerLevel >= bestPriority)
            return nullptr;

        this->currentDangerLevel = bestPriority;
        return bestCollision;
    }
    return nullptr;

}

Vector3 Evade::GetLinearEvadePoint(Spell *spell) {
    auto player = locator->GetObjectManager()->GetLocalPlayer();

    auto direction = spell->endPos.sub(spell->startPos).normalize();

    auto length = spell->startPos.distance(player->position);

    auto lineEnd = Vector2(spell->endPos.x, spell->endPos.z);
    auto lineStart = Vector2(spell->startPos.x, spell->startPos.z);


    auto determinant = ((lineEnd.x - lineStart.x) * (player->position.z - lineStart.y)) - ((lineEnd.y - lineStart.y) * (player->position.x - lineStart.x));

    auto spellDir = direction.clone();
    spellDir.y = 0;

    auto pDist = PerpedincularDistToSegment(Vector2(player->position.x, player->position.z), lineStart, lineEnd);
    auto distThreshold = extraEvadeLength + spell->spellInfo->width + player->GetUnitInfo()->gameplayRadius;
    locator->GetConsole()->Print("pDist: %f | distTh: %f | width: %f | rad: %f", pDist, distThreshold, spell->spellInfo->width, player->GetUnitInfo()->gameplayRadius);
    if (pDist > distThreshold)
        return player->position;

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

void Evade::TryEvadeSpell(Spell *spell) {
    auto player = locator->GetObjectManager()->GetLocalPlayer();//

    auto timeEvade = player->position.distance(Evade::evadePoint) / player->movementSpeed;
    auto timeImpact = spell->TimeToCollision(player->position) + extraEvadeLength / player->movementSpeed;

    if (timeEvade > timeImpact) {
        locator->GetConsole()->Print("tE: %f | tI: %f | CANT DODGE!", timeEvade, timeImpact);
    }
    locator->GetConsole()->Print("tE: %f | tI: %f", timeEvade, timeImpact);

    auto now = locator->GetEngine()->GetProcessorTime();
    Evade::evadeTimeEnd = now + (Evade::evadePoint.distance(player->position) / player->movementSpeed);

    Vector3& loc = Evade::evadePoint;
    input.IssueClickAt(CT_RIGHT_CLICK, [loc] {return locator->GetEngine()->WorldToScreen(loc);}, GameKeybind::TargetChampionsOnly);
}

