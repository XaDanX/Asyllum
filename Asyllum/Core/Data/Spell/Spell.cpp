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
        time = currentPos.distance(pos) / spellInfo->speed;
    }
    time += RemainingCastTime();
    return time;
}

bool Spell::IsValid() {
    if (!Utils::IsValid((void *)spellInfo))
        return false;
    auto time = locator->GetEngine()->GameTime();

    if (endTime < time && endTime > 0)
        return false;
    return true;
}

bool Spell::IsPointInRange(Vector3 point) {
    if (!Utils::IsValid((void *)spellInfo))
        return true;

    float distance = endPos.distance(point);
    distance += distance * 0.1f;
    if (spellInfo->castRange > distance) {
        return true;
    }
    return false;
}

bool Spell::IsCasted() {
    return RemainingCastTime() <= 0;
}

void Spell::CalculateCurrentPos() {
    direction = endPos.sub(startPos).normalize();
    auto time = locator->GetEngine()->GameTime();

    float deltaTime = time - castTime;

    if (endTime > 0) {
        auto current = startPos;

        if (startTime < time) {
            current = startPos.add(
                    direction.mult(spellInfo->speed * (deltaTime - spellInfo->castTime)));
        }

        currentPos = current;
    }

    if (startPos.distance(currentPos) > spellInfo->castRange - 10) {
        currentPos = endPos;
    }

    currentPos.y = startPos.y;
}

void Spell::RecalculateLength() {
    endPos = Vector3(endPos.x - startPos.x, 0, endPos.z - startPos.z);
    endPos = endPos.normalize();

    endPos.x = endPos.x * spellInfo->castRange + startPos.x;
    endPos.y = startPos.y;
    endPos.z = endPos.z * spellInfo->castRange + startPos.z;
}


