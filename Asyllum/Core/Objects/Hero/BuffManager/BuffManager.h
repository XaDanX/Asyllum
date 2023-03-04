//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_BUFFMANAGER_H
#define ASYLLUM_BUFFMANAGER_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include "../../../../Globals/Offsets.h"
#include "../../../../Globals/Globals.h"
#include "../../../Types/Definitions.h"

enum class BuffType : int {
    Internal = 0,
    Aura = 1,
    CombatEnhancer = 2,
    CombatDehancer = 3,
    SpellShield = 4,
    Stun = 5,
    Invisibility = 6,
    Silence = 7,
    Taunt = 8,
    Berserk = 9,
    Polymorph = 10,
    Slow = 11,
    Snare = 12,
    Damage = 13,
    Heal = 14,
    Haste = 15,
    SpellImmunity = 16,
    PhysicalImmunity = 17,
    Invulnerability = 18,
    AttackSpeedSlow = 19,
    NearSight = 20,
    Fear = 22,
    Charm = 23,
    Poison = 24,
    Suppression = 25,
    Blind = 26,
    Counter = 27,
    Currency = 21,
    Shred = 28,
    Flee = 29,
    Knockup = 30,
    Knockback = 31,
    Disarm = 32,
    Grounded = 33,
    Drowsy = 34,
    Asleep = 35,
    Obscured = 36,
    ClickproofToEnemies = 37,
    UnKillable = 38
};

class ScriptBaseBuff {
public:
    union {
        DEFINE_MEMBER_N(char, name[32], Offsets::BuffManager::Name);
    };
};

class BuffInstance {
public:
    union {
        DEFINE_MEMBER_N(BuffType, type, Offsets::BuffManager::BuffType);
        DEFINE_MEMBER_N(ScriptBaseBuff*, scriptBaseBuff, Offsets::BuffManager::BaseBuffEntry);
        DEFINE_MEMBER_N(float, startTime, Offsets::BuffManager::StartTime);
        DEFINE_MEMBER_N(float, endTime, Offsets::BuffManager::EndTime);
        DEFINE_MEMBER_N(int, stacks, Offsets::BuffManager::Stacks);
    };

};

class BuffManager {
public:
    std::vector<BuffInstance *> GetBuffList() {
        std::vector<BuffInstance *> buffs;
        const DWORD buffBegin = *reinterpret_cast<DWORD *>((DWORD) this + Offsets::BuffManager::BuffStart);
        const DWORD buffEnd = *reinterpret_cast<DWORD *>((DWORD) this + Offsets::BuffManager::BuffEnd);

        if (buffBegin != 0 && buffEnd != 0) {
            for (DWORD i = 0; i < (buffEnd - buffBegin); i += 0x08) {
                BuffInstance *buff = *reinterpret_cast<BuffInstance **>(buffBegin + i);

                if ((DWORD) buff < 0x1000)
                    continue;

                if ((DWORD) buff->scriptBaseBuff < 0x1000)
                    continue;

                // if (buff->stacks <= 0)
                //continue;

                if (*reinterpret_cast<float *>(RVA(Offsets::Game::GameTime)) > buff->endTime)
                    continue;

                if (*reinterpret_cast<float *>(RVA(Offsets::Game::GameTime)) < buff->startTime)
                    continue;

                buffs.emplace_back(buff);
            }
        }

        return buffs;
    }

    bool HasBuff(const std::string &name) {
        for (auto &buff: GetBuffList()) {
            if (strcmp(buff->scriptBaseBuff->name, name.c_str()) == 0)
                return true;
        }
        return false;
    }
};


#endif //ASYLLUM_BUFFMANAGER_H
