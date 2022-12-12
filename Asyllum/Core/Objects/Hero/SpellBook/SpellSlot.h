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
#include "../../../Helpers/StringUtils.h"
#include "../../../Data/SpellInfo.h"


class SpellData {
public:
    union {
        DEFINE_MEMBER_N(LolString, name, Offsets::SpellBook::SpellName);
    };
};

class SpellSlotSpellInfo {
public:
    union {
        DEFINE_MEMBER_N(SpellData*, data, Offsets::SpellBook::SpellData);
    };

};

class SpellSlot {
public:
    union {
        DEFINE_MEMBER_N(int, level, Offsets::SpellBook::Level);
        DEFINE_MEMBER_N(float, readyTime, Offsets::SpellBook::ReadyTime);
        DEFINE_MEMBER_N(SpellSlotSpellInfo*, info, Offsets::SpellBook::SpellInfo);
    };


private:
    SpellInfo* spellInfo;
public:
    std::string GetName() {
        int addr = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(this) + Offsets::SpellBook::SpellInfo) + 0x18;
        return StringUtils::GetString(addr);

    }
    bool IsReady();
    int GetCooldown();
    SpellInfo* GetSpellInfo();
};


#endif //ASYLLUM_SPELLSLOT_H
