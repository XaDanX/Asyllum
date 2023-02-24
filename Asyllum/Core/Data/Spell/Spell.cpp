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
    if (!Utils::IsValid((void*)spellInfo))
        return false;
    auto time = locator->GetEngine()->GameTime();

    if (endTime < time)
        return false;

    if (spellInfo->projectDestination) { // projectedDestination tells us its MOST LIKELY linear spell.
        direction = endPos.sub(startPos).normalize();

        if (spellInfo->projectDestination) {
            endPos = Vector3(endPos.x - startPos.x, 0, endPos.z - startPos.z);
            endPos = endPos.normalize();

            endPos.x = endPos.x * spellInfo->castRange + startPos.x;
            endPos.y = startPos.y;
            endPos.z = endPos.z * spellInfo->castRange + startPos.z;
        }

        float deltaTime = time - castTime;

        auto current = startPos;

        if (startTime < time) {
            current = startPos.add(
                    direction.mult(spellInfo->speed * (deltaTime - spellInfo->castTime)));
        }

        currentPos = current;
        if (startPos.distance(current) > spellInfo->castRange) {
            currentPos = endPos;
        }

        path = Geometry::Rectangle(currentPos, endPos, spellInfo->width).ToPolygon();
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
    return RemainingCastTime() <= 0;
}


