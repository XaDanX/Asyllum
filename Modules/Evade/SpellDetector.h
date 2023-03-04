//
// Created by XaDanX on 2/28/2023.
//

#ifndef ASYLLUM_SPELLDETECTOR_H
#define ASYLLUM_SPELLDETECTOR_H

#include "../../Asyllum/Math/Geometry.h"
#include "../../Asyllum/Core/Data/Spell/Spell.h"
#include "SpellLibrary.h"
#include "../../Asyllum/Utils/Utils.h"

class DetectedSpell {
public:
    Geometry::Polygon path;
    EvadeSpell* evadeSpellInfo;
    SpellInfo* spellInfo;
    Vector3 startPos;
    Vector3 endPos;
    Vector3 currentPos;
    float remainingCastTime;
    Hero* caster;

public:
    float TimeToCollision(Vector3 pos) {
        float time = 0.0;
        if (Utils::IsValid((void*)spellInfo)) {
            time = currentPos.distance(pos) / spellInfo->speed;//startPos.distance(pos) / spellInfo->speed;
        }
        time += remainingCastTime;
        return time;
    }
};


class SpellDetector {
public:
    std::vector<DetectedSpell> detectedSpells;
    static std::map<int, Spell> activeSpells;
public:
    void Initialize();
    void Update();
    void ProcessActiveSpells();
    void ProcessMissileList();

};


#endif //ASYLLUM_SPELLDETECTOR_H
