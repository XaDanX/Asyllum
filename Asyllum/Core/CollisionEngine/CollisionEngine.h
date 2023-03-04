//
// Created by XaDanX on 1/22/2023.
//

#ifndef ASYLLUM_COLLISIONENGINE_H
#define ASYLLUM_COLLISIONENGINE_H

#include <iostream>
#include <map>
#include <string>
#include "../Objects/Hero/SpellCast/SpellCast.h"
#include "../Data/Spell/Spell.h"
#include "../../../Modules/Evade/SpellDetector.h"

struct CollisionInfo {
    bool CollideWithPlayer = false;
    std::vector<ObjectBase *> hitList;
};

class CollisionEngine {
public:
    static CollisionInfo FindCollisionLine(DetectedSpell spell);

};


#endif //ASYLLUM_COLLISIONENGINE_H
