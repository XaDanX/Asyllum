//
// Created by XaDanX on 1/24/2023.
//

#ifndef ASYLLUM_SPELL_H
#define ASYLLUM_SPELL_H

#include "../../Objects/Hero/Hero.h"


class Spell {
public:
    std::string name;
    Hero* caster;
    BYTE destIndex; // maybe auto resolve? idk
    int spellSlot;
    float castTime;
    Vector3 startPos;
    Vector3 endPos;
    float startTime;
    float endTime;
    SpellInfo* spellInfo;
};


#endif //ASYLLUM_SPELL_H
