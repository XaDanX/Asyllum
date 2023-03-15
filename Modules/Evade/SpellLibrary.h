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


    float extraWidth = 0;
    bool recalculateLength = false;

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
            ezrealQ.recalculateLength = true;

            ezreal.spells[Slot::_Q] = ezrealQ;

            EvadeSpell ezrealW;
            ezrealW.name = XorStr("ezrealw");
            ezrealW.displayName = XorStr("Ezreal W");
            ezrealW.missileNames = {"ezrealw"};
            ezrealW.spellType = SpellType::Linear;
            ezrealW.spellSlot = Slot::_W;
            ezrealW.dangerLevel = DangerLevel::Low;
            ezrealW.recalculateLength = true;
            ezrealW.extraWidth = 15;

            ezreal.spells[Slot::_W] = ezrealW;

            EvadeSpell ezrealR;
            ezrealR.name = XorStr("ezrealr");
            ezrealR.displayName = XorStr("Ezreal R");
            ezrealR.missileNames = {"ezrealr"};
            ezrealR.spellType = SpellType::Linear;
            ezrealR.spellSlot = Slot::_R;
            ezrealR.dangerLevel = DangerLevel::VeryHigh;
            ezrealR.recalculateLength = true;

            ezreal.spells[Slot::_R] = ezrealR;

            championList[HashName::Ezreal] = ezreal;
        }


        { //amumu
            Champion amumu;
            amumu.name = XorStr("amumu");
            amumu.hash = HashName::Amumu;

            EvadeSpell amumuQ;
            //amumuQ.name = XorStr("bandagetoss"); // its fucking broken idk
            amumuQ.displayName = XorStr("Amumu Q");
            amumuQ.missileNames = {XorStr("sadmummybandagetoss")};
            amumuQ.spellType = SpellType::Linear;
            amumuQ.spellSlot = Slot::_Q;
            amumuQ.dangerLevel = DangerLevel::Low;

            //amumuQ.recalculateLength = true;

            amumu.spells[Slot::_Q] = amumuQ;

            championList[HashName::Amumu] = amumu;
        }

        {
            Champion blitzcrank;
            blitzcrank.name = XorStr("amumu");
            blitzcrank.hash = HashName::Amumu;

            EvadeSpell blitzcrankQ;
            blitzcrankQ.name = XorStr("rocketgrab");
            blitzcrankQ.displayName = XorStr("Blitzcrank Q");
            blitzcrankQ.missileNames = {XorStr("rocketgrabmissile")};
            blitzcrankQ.spellType = SpellType::Linear;
            blitzcrankQ.spellSlot = Slot::_Q;
            blitzcrankQ.dangerLevel = DangerLevel::High;

            blitzcrankQ.recalculateLength = true;

            blitzcrank.spells[Slot::_Q] = blitzcrankQ;

            championList[HashName::Blitzcrank] = blitzcrank;
        }

        {
            Champion lux;
            lux.name = XorStr("lux");
            lux.hash = HashName::Lux;

            EvadeSpell luxQ;
            luxQ.name = XorStr("luxlightbinding");
            luxQ.displayName = XorStr("Lux Q");
            luxQ.missileNames = {XorStr("luxlightbindingmis")};
            luxQ.spellType = SpellType::Linear;
            luxQ.spellSlot = Slot::_Q;
            luxQ.dangerLevel = DangerLevel::High;

            luxQ.recalculateLength = true;

            lux.spells[Slot::_Q] = luxQ;

            championList[HashName::Lux] = lux;

        }

        {
            Champion zed;
            zed.name = XorStr("zed");
            zed.hash = HashName::Zed;

            EvadeSpell zedQ;
            zedQ.name = XorStr("zedq");
            zedQ.displayName = XorStr("Zed Q");
            zedQ.missileNames = {XorStr("zedqmissile")};
            zedQ.spellType = SpellType::Linear;
            zedQ.spellSlot = Slot::_Q;
            zedQ.dangerLevel = DangerLevel::High;

            zedQ.recalculateLength = true;

            zed.spells[Slot::_Q] = zedQ;

            championList[HashName::Zed] = zed;

        }
    }
};


#endif //ASYLLUM_SPELLLIBRARY_H
