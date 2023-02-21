//
// Created by XaDanX on 1/30/2023.
//

#ifndef ASYLLUM_EVADABLESPELL_H
#define ASYLLUM_EVADABLESPELL_H
#include <string>
#include <iostream>
#include <list>
#include <map>

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
    SpellType spellType;
    Slot spellSlot;
    DangerLevel dangerLevel;

    bool affectMinion = true;
    bool affectHero  = true;
};

struct Champion {
    std::string name;
    int hash;
    std::map<Slot, EvadeSpell> spells;
};

#endif //ASYLLUM_EVADABLESPELL_H
