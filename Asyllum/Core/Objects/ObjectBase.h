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
#include "../../Protection/XorStr.h"

enum class ObjectTypeFlags {
    GameObject = (1 << 0),  //0x1
    NeutralCamp = (1 << 1),  //0x2
    DeadObject = (1 << 4),  //0x10
    InvalidObject = (1 << 5),  //0x20
    AIBaseCommon = (1 << 7),  //0x80
    AttackableUnit = (1 << 9),  //0x200
    AI = (1 << 10), //0x400
    Minion = (1 << 11), //0x800
    Hero = (1 << 12), //0x1000
    Turret = (1 << 13), //0x2000
    Unknown0 = (1 << 14), //0x4000
    Missile = (1 << 15), //0x8000
    Unknown1 = (1 << 16), //0x10000
    Building = (1 << 17), //0x20000
    Unknown2 = (1 << 18), //0x40000
};

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
        DEFINE_MEMBER_N(float, scale, (unsigned int)0x1838);
        DEFINE_MEMBER_N(bool, targetable, (unsigned int)Offsets::GameObject::Targetable);
    };

private:
    bool __thiscall CompareObjectFlags(int a2);

public:

    bool IsMinion() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Minion)) && maxHealth > 20;
    }

    bool IsHero() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Hero));
    }

    bool IsTurret() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Turret));
    }

    bool IsBuilding() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Building));
    }

    bool IsDummy() {
        return name.str().contains(XorStr("PracticeTool").c_str());
    }

    bool IsAlive() {
        return (*(unsigned __int8 (__thiscall **)(DWORD *))(*reinterpret_cast<DWORD*>(this) + 140))(reinterpret_cast<DWORD*>(this))
               && !(*(unsigned __int8 (__thiscall **)(DWORD *))(reinterpret_cast<DWORD*>(this)[148] + 8))(reinterpret_cast<DWORD*>(this) + 148);
    }

    bool IsLocalPlayer() {
        return reinterpret_cast<int>(this) == *reinterpret_cast<int*>(Globals::baseAddress + Offsets::Game::LocalPlayer);
    }

    template <class T>
    bool IsAllyTo(T obj) {
        return this->team == obj->team;
    }

    template <class T>
    bool IsEnemyTo(T obj) {
        return this->team != obj->team;
    }

    bool IsOnScreen(float offsetX=0, float offsetY=0);





};


#endif //ASYLLUM_OBJECTBASE_H
