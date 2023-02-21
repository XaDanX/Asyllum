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
        time += RemainingCastTime();
    }

    return time;
}

float Spell::RemainingCastTimeMath() {
    float remaining = castTime - (locator->GetEngine()->GameTime() - startTime);
    return (remaining < 0.f ? 0.f : remaining);
}
