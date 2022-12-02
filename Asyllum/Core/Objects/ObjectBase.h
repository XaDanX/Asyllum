//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_OBJECTBASE_H
#define ASYLLUM_OBJECTBASE_H
#include "../../Globals/Globals.h"
#include "../../Globals/Offsets.h"
#include "../../Math/Vector.h"
#include "../Types/Definitions.h"
#include "../Data/UnitInfo.h"

class ObjectBase {
public:
    union {
        DEFINE_MEMBER_N(short, index, (unsigned int)Offsets::GameObject::Index);
        DEFINE_MEMBER_N(short, team, (unsigned int)Offsets::GameObject::Team);
        DEFINE_MEMBER_N(int, networkId, (unsigned int)Offsets::GameObject::NetworkId);
        DEFINE_MEMBER_N(Vector3, position, (unsigned int)Offsets::GameObject::Position);
        DEFINE_MEMBER_N(bool, visibility, (unsigned int)Offsets::GameObject::Visibility);
        DEFINE_MEMBER_N(int, spawnCount, (unsigned int)Offsets::GameObject::SpawnCount);
        DEFINE_MEMBER_N(float, mana, (unsigned int)Offsets::GameObject::Mana);
        DEFINE_MEMBER_N(float, maxMana, (unsigned int)Offsets::GameObject::MaxMana);
        DEFINE_MEMBER_N(bool, dead, (unsigned int)Offsets::GameObject::Dead);
        DEFINE_MEMBER_N(float, health, (unsigned int)Offsets::GameObject::Health);
        DEFINE_MEMBER_N(float, maxHealth, (unsigned int)Offsets::GameObject::MaxHealth);
        DEFINE_MEMBER_N(LolString, name, (unsigned int)Offsets::GameObject::Name);
        DEFINE_MEMBER_N(float, attackRange, (unsigned int)Offsets::GameObject::AttackRange);
        DEFINE_MEMBER_N(bool, targetable, (unsigned int)Offsets::GameObject::Targetable);

    };
    UnitInfo* GetUnitInfo();


};


#endif //ASYLLUM_OBJECTBASE_H
