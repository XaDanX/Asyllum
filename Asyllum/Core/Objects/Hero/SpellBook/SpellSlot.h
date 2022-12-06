//
// Created by XaDanX on 12/5/2022.
//

#ifndef ASYLLUM_SPELLSLOT_H
#define ASYLLUM_SPELLSLOT_H
#include <vector>
#include "../../../../Globals/Globals.h"
#include "../../../../Globals/Offsets.h"
#include "../../../../Math/Vector.h"
#include "Windows.h"
#include "../../../Types/Definitions.h"

class SpellSlotSpellInfo {
public:
    union {
        DEFINE_MEMBER_N(LolString, name, 0x18);
    };
};


class SpellSlot {
public:
    union {
        DEFINE_MEMBER_N(int, level, Offsets::SpellBook::Level);
        DEFINE_MEMBER_N(float, readyTime, Offsets::SpellBook::ReadyTime);
        DEFINE_MEMBER_N(SpellSlotSpellInfo*, spellInfo, Offsets::SpellBook::SpellInfo);
    };

    LolString GetName() {
        auto nameAddress = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(this) + Offsets::SpellBook::SpellInfo);
        auto name = *reinterpret_cast<LolString*>(nameAddress + 0x18);
        return name;
    }
};


#endif //ASYLLUM_SPELLSLOT_H
