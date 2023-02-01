//
// Created by XaDanX on 1/22/2023.
//

#include "CollisionEngine.h"
#include "../Locator/Locator.h"
#include "../../Utils/Utils.h"

void CollisionEngine::Update() noexcept {

    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        auto spellCast = hero->GetSpellCast();
        if (!Utils::IsValid((void*)spellCast))
            continue;

        if (spellCast->spellSlot > 3 || spellCast->spellSlot < 0)
            continue;

        if (spells.contains(spellCast->GetName()))
            continue;

        if (spellCast->endTime < locator->GetEngine()->GameTime())
            continue;

        CollidableSpell spell = CollidableSpell();
        spell.endTime = spellCast->endTime;
        spell.startTime = spellCast->startTime;
        spell.name = spellCast->GetName();
        spell.startPos = spellCast->startPos;
        spell.endPos = spellCast->endPos;
        spells.insert({spell.name, spell});
    }

    for (auto it = spells.cbegin(), next_it = it; it != spells.cend(); it = next_it) {
        ++next_it;

        if (it->second.endTime < locator->GetEngine()->GameTime()) {
            spells.erase(it);
        }
    }

}
