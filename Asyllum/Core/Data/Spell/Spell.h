//
// Created by XaDanX on 1/24/2023.
//

#ifndef ASYLLUM_SPELL_H
#define ASYLLUM_SPELL_H

#include "../../Objects/Hero/Hero.h"
#include "../../../Math/Geometry.h"

#define INVALID_FLOAT 999999.f

class Spell {
public:
    std::string name;
    Hero *caster;
    BYTE destIndex; // maybe auto resolve? idk
    int spellSlot;
    float castTime;
    Vector3 startPos;
    Vector3 endPos;
    Vector3 currentPos;
    Vector3 direction;
    float startTime;
    float endTime;
    SpellInfo *spellInfo;

public:
    float RemainingCastTime();

    float TimeToCollision(Vector3 pos);

    bool IsValid();

    bool IsPointInRange(Vector3 point);

    bool IsCasted();

    void CalculateCurrentPos();

    void RecalculateLength();
};


#endif //ASYLLUM_SPELL_H
