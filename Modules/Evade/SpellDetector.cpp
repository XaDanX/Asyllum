//
// Created by XaDanX on 2/28/2023.
//

#include "SpellDetector.h"
#include "../../Asyllum/Core/Managers/EventManager/Event.h"
#include "../../Asyllum/Utils/Utils.h"
#include "SpellLibrary.h"
#include "../../Asyllum/Core/Locator/Locator.h"

std::map<int, Spell> SpellDetector::activeSpells;
std::map<HashName, Champion> SpellLibrary::championList;

void OnSpellCasted(Event::OnSpellCast args) {

    EvadeSpell* evadeSpell = SpellLibrary::FindSpell(args.caster->characterData->hash, (Slot)args.spell.spellSlot);
    if (Utils::IsValid((void*)evadeSpell)) {

        int uuid = 1000 * ((int) args.spell.endTime + (int) args.spell.castTime + (int) args.spell.startPos.x +
                           (int) args.spell.endPos.z + (int) args.spell.spellSlot);
        if (SpellDetector::activeSpells.contains(uuid))
            return;
        SpellDetector::activeSpells[uuid] = args.spell;


    }


}

void SpellDetector::Initialize() {
    SpellLibrary::Initialize();
    locator->GetEventManager()->Subscribe<Event::OnSpellCast>(&OnSpellCasted);
}

void SpellDetector::Update() {
    detectedSpells.clear();
    ProcessMissileList();
    ProcessActiveSpells();





}

void SpellDetector::ProcessActiveSpells() {
    for (auto it = SpellDetector::activeSpells.cbegin(), next_it = it; it != SpellDetector::activeSpells.cend(); it = next_it) {
        ++next_it;

        if (it->second.endTime < locator->GetEngine()->GameTime()) {
            SpellDetector::activeSpells.erase(it);
            continue;
        }

        auto spell = it->second;

        EvadeSpell *evadeSpell = SpellLibrary::FindSpell(spell.caster->characterData->hash, (Slot) spell.spellSlot);
        if (!Utils::IsValid((void *) evadeSpell))
            continue;

        if (!spell.IsValid())
            continue;

        DetectedSpell detectedSpell;


        if (spell.name == evadeSpell->name) {


            if (evadeSpell->recalculateLength) {
                spell.RecalculateLength();
            }
            spell.CalculateCurrentPos();

            if (evadeSpell->spellType == SpellType::Linear) {
                if (spell.spellInfo->width > 5) {
                    detectedSpell.path = Geometry::Rectangle(spell.currentPos, spell.endPos,
                                                             spell.spellInfo->width).ToPolygon();
                } else {
                    detectedSpell.path = Geometry::Rectangle(spell.currentPos, spell.endPos,
                                                             spell.spellInfo->height * 2).ToPolygon();
                }
            }

            detectedSpell.spellInfo = spell.spellInfo;
            detectedSpell.evadeSpellInfo = evadeSpell;
            detectedSpell.startPos = spell.startPos;
            detectedSpell.endPos = spell.endPos;
            detectedSpell.currentPos = spell.currentPos;
            detectedSpell.remainingCastTime = spell.RemainingCastTime();
            detectedSpell.caster = spell.caster;

            detectedSpells.push_back(detectedSpell);


        }
    }
}

void SpellDetector::ProcessMissileList() {

    for (auto missile : locator->GetObjectManager()->GetMissileList()) {
        if (!missile->IsValid())
            continue;

        auto spell = missile->GetSpellObject();

        if (!spell.caster->IsHero())
            continue;

        EvadeSpell* evadeSpell = SpellLibrary::FindSpell(spell.caster->characterData->hash, (Slot)spell.spellSlot);
        if (!Utils::IsValid((void*)evadeSpell))
            continue;

        if (!spell.IsValid())
            continue;

        if (!Utils::IsValid((void*)spell.spellInfo))
            continue;




        if(std::count(evadeSpell->missileNames.begin(), evadeSpell->missileNames.end(), spell.name)) {
            DetectedSpell detectedSpell;

            if (evadeSpell->recalculateLength) {
                spell.RecalculateLength();
            }
            spell.CalculateCurrentPos();

            if (evadeSpell->spellType == SpellType::Linear) {
                if (spell.spellInfo->width > 5) {
                    detectedSpell.path = Geometry::Rectangle(spell.currentPos, spell.endPos,
                                                             spell.spellInfo->width).ToPolygon();
                } else {
                    detectedSpell.path = Geometry::Rectangle(spell.currentPos, spell.endPos,
                                                             spell.spellInfo->height * 2).ToPolygon();
                }
            }

            detectedSpell.spellInfo = spell.spellInfo;
            detectedSpell.evadeSpellInfo = evadeSpell;
            detectedSpell.startPos = spell.startPos;
            detectedSpell.endPos = spell.endPos;
            detectedSpell.currentPos = spell.currentPos;
            detectedSpell.remainingCastTime = spell.RemainingCastTime();
            detectedSpell.caster = spell.caster;


            detectedSpells.push_back(detectedSpell);
        }

    }

}
