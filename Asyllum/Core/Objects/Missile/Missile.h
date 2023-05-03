//
// Created by XaDanX on 2/25/2023.
//

#ifndef ASYLLUM_MISSILE_H
#define ASYLLUM_MISSILE_H
#include "../../../Globals/Offsets.h"
#include "../../../Globals/Globals.h"
#include "../../Types/Definitions.h"
#include "../../../Math/Vector.h"
#include "../../../Math/Geometry.h"
#include "../../Data/SpellInfo.h"
#include "../../Data/Spell/Spell.h"

class MissileData {
public:
    union {
        DEFINE_MEMBER_N(LolString, name, 0x8);
    };
};

class MissileInfo {
public:
    union {
        DEFINE_MEMBER_N(int, slot, Offsets::Missile::Slot);
        DEFINE_MEMBER_N(MissileData*, missileData, 0x18);
    };
};

class Missile {
public:
   union {
       DEFINE_MEMBER_N(Vector3, startPos, Offsets::Missile::StartPos);
       DEFINE_MEMBER_N(Vector3, endPos, Offsets::Missile::EndPos);
       DEFINE_MEMBER_N(Vector3, currentPos, Offsets::Missile::CurrentPos);
       DEFINE_MEMBER_N(MissileInfo*, missileInfo, Offsets::Missile::MissileInfo);
       DEFINE_MEMBER_N(int, slot, Offsets::Missile::Slot);
       DEFINE_MEMBER_N(BYTE, srcIndex, Offsets::Missile::SrcIndex);

   };
public:

    bool IsValid();

    SpellInfo* GetSpellInfo();

    Spell GetSpellObject();


};

/*class Missile{
public:
    union {
        DEFINE_MEMBER_N(MissileW*, missile, 0x14);

    };
};*/


#endif //ASYLLUM_MISSILE_H
