//
// Created by XaDanX on 1/24/2023.
//

#include "Spell.h"
#include "../../Locator/Locator.h"
#include "../../../Utils/Utils.h"

float Spell::RemainingCastTime() {
    float remaining = startTime - locator->GetEngine()->GameTime();
    return (remaining < 0.f ? 0.f : remaining);
}

float Spell::TimeToCollision(Vector3 pos) {
    float time = 0.0;
    if (Utils::IsValid((void*)spellInfo)) {
        time = startPos.distance(pos) / spellInfo->speed;
    }
    time += RemainingCastTime();
    return time;
}

bool Spell::IsValid() {
    if (Utils::IsValid((void*)spellInfo))
        return false;
    auto time = locator->GetEngine()->GameTime();
    if ((startTime + spellInfo->castRange / spellInfo->speed + spellInfo->delay) > time) {
        if (spellInfo->speed != INVALID_FLOAT && startTime + spellInfo->delay < time) {
            if (spellInfo->projectDestination) { // projectedDestination tells us its MOST LIKELY linear spell.
                float a = spellInfo->speed * (time - startTime - spellInfo->delay);
                currentPos = startPos.extend(endPos, a);

                endPos = Vector3(endPos.x - startPos.x, 0, endPos.z - startPos.z);
                endPos = endPos.normalize();

                endPos.x = endPos.x * spellInfo->castRange + startPos.x;
                endPos.y = startPos.y;
            }
        }
    } else {
        return false;
    }
    return true;
}

bool Spell::IsPointInRange(Vector3 point) {
    if (!Utils::IsValid((void*)spellInfo))
        return true;

    float distance = endPos.distance(point);
    distance += distance * 0.1f; // "predicted range"
    if (spellInfo->castRange > distance) {
        return true;
    }
    return false;
}

bool Spell::IsCasted() {
    return RemainingCastTime() < 0;
}


