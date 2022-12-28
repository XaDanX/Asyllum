//
// Created by XaDanX on 12/10/2022.
//

#include "Awareness.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "SpellTracker/SpellTracker.h"

void Awareness::OnTick() {

    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        SpellTracker::DrawSpells(hero);
    }


}

void Awareness::OnLoad() {

}

void Awareness::OnGui() {

}
