//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_SPELLINFO_H
#define ASYLLUM_SPELLINFO_H

#include <map>
#include <string>
#include <bitset>
#include <array>
#include "../../Math/Vector.h"

enum SpellFlags {

    // Flags from the game data files
    AffectAllyChampion = 1,
    AffectEnemyChampion = 1 << 1,
    AffectAllyLaneMinion = 1 << 2,
    AffectEnemyLaneMinion = 1 << 3,
    AffectAllyWard = 1 << 4,
    AffectEnemyWard = 1 << 5,
    AffectAllyTurret = 1 << 6,
    AffectEnemyTurret = 1 << 7,
    AffectAllyInhibs = 1 << 8,
    AffectEnemyInhibs = 1 << 9,
    AffectAllyNonLaneMinion = 1 << 10,
    AffectJungleMonster = 1 << 11,
    AffectEnemyNonLaneMinion = 1 << 12,
    AffectAlwaysSelf = 1 << 13,
    AffectNeverSelf = 1 << 14,
    ProjectedDestination = 1 << 22,
    AffectAllyMob = AffectAllyLaneMinion | AffectAllyNonLaneMinion,
    AffectEnemyMob = AffectEnemyLaneMinion | AffectEnemyNonLaneMinion | AffectJungleMonster,
    AffectAllyGeneric = AffectAllyMob | AffectAllyChampion,
    AffectEnemyGeneric = AffectEnemyMob | AffectEnemyChampion,
};

class SpellInfo {
public:
    std::string name = "";
    std::string parent = "";
    std::string icon = "";
    float castTime = 0;
    float castRange = 0;
    float castRadius = 0;
    float castConeAngle = 0;
    float castConeDistance = 0;
    float width = 0;
    float height = 0;
    float speed = 0;
    float travelTime = 0;
    float delay = 0;
    bool projectDestination = false;
    SpellFlags flags;

public:
    bool CheckFlag(SpellFlags flag) {
        return flags & flag;
    }


};

#endif //ASYLLUM_SPELLINFO_H
