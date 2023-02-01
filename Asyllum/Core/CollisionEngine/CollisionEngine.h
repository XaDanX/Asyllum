//
// Created by XaDanX on 1/22/2023.
//

#ifndef ASYLLUM_COLLISIONENGINE_H
#define ASYLLUM_COLLISIONENGINE_H
#include <iostream>
#include <map>
#include <string>
#include "../Objects/Hero/SpellCast/SpellCast.h"

class CollidableSpell {
public:
    std::string name;
    float startTime;
    float endTime;
    Vector3 startPos;
    Vector3 endPos;
};

class CollisionEngine {
public:
    std::map<std::string, CollidableSpell> spells; // <name, SpellCast>
    void Update() noexcept;

};


#endif //ASYLLUM_COLLISIONENGINE_H
