//
// Created by XaDanX on 1/22/2023.
//

#ifndef ASYLLUM_SPELLCAST_H
#define ASYLLUM_SPELLCAST_H
#include "../../../../Globals/Offsets.h"
#include "../../../../Globals/Globals.h"
#include "../../../Types/Definitions.h"
#include "../../../../Math/Vector.h"
#include "../../../Helpers/StringUtils.h"
#include <string>
#include <iostream>

class SpellCastData {
public:
    union {
        DEFINE_MEMBER_N(LolString, name, Offsets::SpellCast::SpellName);
    };
};

class SpellCast {
public:
    union {
        DEFINE_MEMBER_N(SpellCastData*, spellData, Offsets::SpellCast::SpellData);
        DEFINE_MEMBER_N(int, spellSlot, Offsets::SpellCast::SpellSlot);
        DEFINE_MEMBER_N(float, castTime, Offsets::SpellCast::CastTime);
        DEFINE_MEMBER_N(Vector3, startPos, Offsets::SpellCast::StartPos);
        DEFINE_MEMBER_N(Vector3, endPos, Offsets::SpellCast::EndPos);
        DEFINE_MEMBER_N(Vector3, endPosAlt, Offsets::SpellCast::EndPosAlt);
        DEFINE_MEMBER_N(float, startTime, Offsets::SpellCast::StartTime);
        DEFINE_MEMBER_N(float, endTime, Offsets::SpellCast::EndTime);
    };

    std::string GetName() {
        int addr = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(this) + Offsets::SpellCast::SpellData) + Offsets::SpellCast::SpellName;
        std::string name = StringUtils::ToLower(StringUtils::GetString(addr));
        return name;

    }
};


#endif //ASYLLUM_SPELLCAST_H
