//
// Created by XaDanX on 2/28/2023.
//

#ifndef ASYLLUM_SPELLLIBRARY_H
#define ASYLLUM_SPELLLIBRARY_H
#include <iostream>
#include <map>
#include "../../Asyllum/Core/Objects/ObjectBase.h"
enum DangerLevel {
    NoDanger = 0,
    Low = 1,
    Medium,
    High,
    VeryHigh
};

enum Slot {
    _Q = 0,
    _W,
    _E,
    _R
};

enum SpellType {
    Circular,
    Linear,
    Interruptable
};


struct EvadeSpell {
    std::string name;
    std::string displayName;
    std::vector<std::string> missileNames;
    SpellType spellType;
    Slot spellSlot;
    DangerLevel dangerLevel;


    float extraWidth;

    bool affectMinion = true;
    bool affectHero = true;
};

struct Champion {
    std::string name;
    int hash;
    std::map<Slot, EvadeSpell> spells;
};

class SpellLibrary {
public:
    static std::map<HashName, Champion> championList;

    static EvadeSpell* FindSpell(HashName hashName, Slot spellSlotId) {
        auto championIt = championList.find(hashName);
        if (championIt == championList.end()) {
            return nullptr;
        }

        Champion& champion = championIt->second;
        auto spellIt = champion.spells.find(spellSlotId);
        if (spellIt == champion.spells.end()) {
            return nullptr;
        }

        return &spellIt->second;
    }


    static void Initialize() {
        { // ezreal
            Champion ezreal;
            ezreal.name = XorStr("ezreal");
            ezreal.hash = HashName::Ezreal;

            EvadeSpell ezrealQ;
            ezrealQ.name = XorStr("ezrealq");
            ezrealQ.displayName = XorStr("Ezreal Q");
            ezrealQ.missileNames = {"ezrealq"};
            ezrealQ.spellType = SpellType::Linear;
            ezrealQ.spellSlot = Slot::_Q;
            ezrealQ.dangerLevel = DangerLevel::Low;

            ezreal.spells[Slot::_Q] = ezrealQ;

            EvadeSpell ezrealW;
            ezrealW.name = XorStr("ezrealw");
            ezrealW.displayName = XorStr("Ezreal W");
            ezrealW.missileNames = {"ezrealw"};
            ezrealW.spellType = SpellType::Linear;
            ezrealW.spellSlot = Slot::_W;
            ezrealW.dangerLevel = DangerLevel::Low;
            ezrealW.extraWidth = 15;

            ezreal.spells[Slot::_W] = ezrealW;

            EvadeSpell ezrealR;
            ezrealR.name = XorStr("ezrealr");
            ezrealR.displayName = XorStr("Ezreal R");
            ezrealR.missileNames = {"ezrealr"};
            ezrealR.spellType = SpellType::Linear;
            ezrealR.spellSlot = Slot::_R;
            ezrealR.dangerLevel = DangerLevel::VeryHigh;

            ezreal.spells[Slot::_R] = ezrealR;

            championList[HashName::Ezreal] = ezreal;
        }

    }
};


#endif //ASYLLUM_SPELLLIBRARY_H
