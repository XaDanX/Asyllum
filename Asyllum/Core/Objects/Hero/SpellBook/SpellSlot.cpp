//
// Created by XaDanX on 12/5/2022.
//

#include "SpellSlot.h"
#include "../../../Locator/Locator.h"

SpellInfo *SpellSlot::GetSpellInfo() {
    auto fixedName = StringUtils::ToLower(info->data->name.str());
    spellInfo = locator->GetGameData()->GetSpellInfoByName(fixedName);
    return spellInfo;
}

bool SpellSlot::IsReady() {
    return readyTime < locator->GetEngine()->GameTime();
}

int SpellSlot::GetCooldown() {
    auto time = readyTime - locator->GetEngine()->GameTime();
    if (time > 0)
        return (int)time;
    else
        return 0;
}
