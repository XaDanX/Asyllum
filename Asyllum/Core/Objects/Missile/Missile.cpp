//
// Created by XaDanX on 2/25/2023.
//

#include "Missile.h"
#include "../../../Utils/Utils.h"
#include "../../Locator/Locator.h"

bool Missile::IsValid() {
    auto spellInfo = GetSpellInfo();
    if (!Utils::IsValid((void*)spellInfo))
        return false;

    return true;
}

SpellInfo* Missile::GetSpellInfo() {
    auto name = StringUtils::ToLower(missileInfo->missileData->name.c_str());
    auto spellInfo = locator->GetGameData()->GetSpellInfoByName(name);
    if (Utils::IsValid((void*)spellInfo))
        return spellInfo;
    return nullptr;
}


Spell Missile::GetSpellObject() {
    auto spellInfo = GetSpellInfo();

    Spell result;
    result.spellInfo = spellInfo;
    result.currentPos = currentPos;
    result.startPos = startPos;
    result.endPos = endPos;
    result.name = StringUtils::ToLower(missileInfo->missileData->name.str());
    result.destIndex = 0;
    result.caster = locator->GetObjectManager()->GetHeroByIndex(srcIndex);
    result.spellSlot = slot;

    return result;
}