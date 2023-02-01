//
// Created by XaDanX on 1/24/2023.
//

#ifndef ASYLLUM_EVENT_H
#define ASYLLUM_EVENT_H

#include "../../Data/Spell/Spell.h"

namespace Event {
    struct OnTick {

    };

    struct OnSpellCast {
        Spell spell;
        Hero* caster;
    };

    struct OnAutoAttack {
        Hero* caster;
        BYTE destIndex;
    };

    struct OnRecall {
        Hero* caster;
        float startTime;
    };
}

#endif //ASYLLUM_EVENT_H
