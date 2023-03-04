//
// Created by XaDanX on 1/22/2023.
//

#include "CollisionEngine.h"
#include "../Locator/Locator.h"
#include "../../Utils/Utils.h"


CollisionInfo CollisionEngine::FindCollisionLine(DetectedSpell spell) {
    CollisionInfo result;

    if (spell.spellInfo == nullptr) {
        return result;
    }

    if (spell.spellInfo->width < 1.f || spell.spellInfo->speed < 1.f)
        return result;

    auto direction = spell.endPos.sub(spell.currentPos).normalize();

    float UnitDelta = 1.f + spell.spellInfo->width / 3.f;

    Vector2 spellStart = Vector2(spell.currentPos.x, spell.currentPos.z);
    Vector2 spellEnd = Vector2(spell.endPos.x, spell.endPos.z);

    float distanceLeft = spellStart.distance(spellEnd);
    int iterations = (int) (max(0, distanceLeft - UnitDelta) / UnitDelta);
    float timePerIter = UnitDelta / spell.spellInfo->speed;

    float deltaXSpell = direction.x * timePerIter * spell.spellInfo->speed;
    float deltaYSpell = direction.z * timePerIter * spell.spellInfo->speed;
    for (auto &target: locator->GetObjectManager()->GetHeroList()) {
        if (target->GetUnitInfo() == nullptr) {
            continue;
        }
        if ((DWORD) target == (DWORD) spell.caster) {
            continue;
        }

        Vector2 spellPos = spellStart;
        for (int i = 0; i < iterations; ++i) {

            Vector3 targetPos3D = target->position;
            Vector2 targetPos2D = Vector2(targetPos3D.x, targetPos3D.z);;

            if (targetPos2D.distance(spellPos) < target->GetUnitInfo()->gameplayRadius + spell.spellInfo->width) {
                result.hitList.push_back(reinterpret_cast<ObjectBase *>((DWORD) target));
                if (target->IsLocalPlayer())
                    result.CollideWithPlayer = true;
                break;
            }
            spellPos.x += deltaXSpell;
            spellPos.y += deltaYSpell;
        }
    }

    /*
     * SORTING VECTOR
     */

    if (result.hitList.size() > 1) {
        auto startPos = spell.startPos;
        std::sort(result.hitList.begin(), result.hitList.end(), [&startPos](ObjectBase *a, ObjectBase *b) {
            return a->position.distance(startPos) < b->position.distance(startPos);
        });
    }

    return result;
}
